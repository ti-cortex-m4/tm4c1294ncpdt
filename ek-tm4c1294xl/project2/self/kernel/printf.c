/*------------------------------------------------------------------------------
printf.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include <stdarg.h>
#include "utils/uartstdio.h"
#include "utils/ustdlib.h"
#include "settings.h"
#include "../udp/udp_log.h"
#include "clock.h"
#include "printf.h"



#define PRINTF_SIZE     0x400

static uchar            mbPrintf[PRINTF_SIZE];
static uint             iwPrintf;


uint                    cwErrPrintfOverflow = 0;



static const char * const pczHex = "0123456789abcdef";



static void CharPut(unsigned char ucData)
{
  if (iwPrintf < PRINTF_SIZE)
    mbPrintf[iwPrintf++] = ucData;
  else
    cwErrPrintfOverflow++;
}


static int LogWrite(const char *pcBuf, uint32_t ui32Len)
{
    unsigned int uIdx;

    // Check for valid arguments.
    ASSERT(pcBuf != 0);

    // Send the characters
    for(uIdx = 0; uIdx < ui32Len; uIdx++)
    {
        // If the character to the UART is \n, then add a \r before it so that
        // \n is translated to \n\r in the output.
        if(pcBuf[uIdx] == '\n')
        {
            CharPut('\r');
        }

        // Send the character to the UART output.
        CharPut(pcBuf[uIdx]);
    }

    // Return the number of characters written.
    return(uIdx);
}


static void LogPrintVarArg(const char *pcString, va_list vaArgP)
{
    uint32_t ui32Idx, ui32Value, ui32Pos, ui32Count, ui32Base, ui32Neg;
    char *pcStr, pcBuf[16], cFill;

    // Check the arguments.
    ASSERT(pcString != 0);

    // Loop while there are more characters in the string.
    while(*pcString)
    {
        // Find the first non-% character, or the end of the string.
        for(ui32Idx = 0;
            (pcString[ui32Idx] != '%') && (pcString[ui32Idx] != '\0');
            ui32Idx++)
        {
        }

        // Write this portion of the string.
        LogWrite(pcString, ui32Idx);

        // Skip the portion of the string that was written.
        pcString += ui32Idx;

        // See if the next character is a %.
        if(*pcString == '%')
        {
            // Skip the %.
            pcString++;

            // Set the digit count to zero, and the fill character to space
            // (in other words, to the defaults).
            ui32Count = 0;
            cFill = ' ';

            // It may be necessary to get back here to process more characters.
            // Goto's aren't pretty, but effective.  I feel extremely dirty for
            // using not one but two of the beasts.
again:

            // Determine how to handle the next character.
            switch(*pcString++)
            {
                // Handle the digit characters.
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                {
                    // If this is a zero, and it is the first digit, then the
                    // fill character is a zero instead of a space.
                    if((pcString[-1] == '0') && (ui32Count == 0))
                    {
                        cFill = '0';
                    }

                    // Update the digit count.
                    ui32Count *= 10;
                    ui32Count += pcString[-1] - '0';

                    // Get the next character.
                    goto again;
                }

                // Handle the %c command.
                case 'c':
                {
                    // Get the value from the varargs.
                    ui32Value = va_arg(vaArgP, uint32_t);

                    // Print out the character.
                    LogWrite((char *)&ui32Value, 1);

                    // This command has been handled.
                    break;
                }

                // Handle the %d and %i commands.
                case 'd':
                case 'i':
                {
                    // Get the value from the varargs.
                    ui32Value = va_arg(vaArgP, uint32_t);

                    // Reset the buffer position.
                    ui32Pos = 0;

                    // If the value is negative, make it positive and indicate
                    // that a minus sign is needed.
                    if((int32_t)ui32Value < 0)
                    {
                        // Make the value positive.
                        ui32Value = -(int32_t)ui32Value;

                        // Indicate that the value is negative.
                        ui32Neg = 1;
                    }
                    else
                    {
                        // Indicate that the value is positive so that a minus
                        // sign isn't inserted.
                        ui32Neg = 0;
                    }

                    // Set the base to 10.
                    ui32Base = 10;

                    // Convert the value to ASCII.
                    goto convert;
                }

                // Handle the %s command.
                case 's':
                {
                    // Get the string pointer from the varargs.
                    pcStr = va_arg(vaArgP, char *);

                    // Determine the length of the string.
                    for(ui32Idx = 0; pcStr[ui32Idx] != '\0'; ui32Idx++)
                    {
                    }

                    // Write the string.
                    LogWrite(pcStr, ui32Idx);

                    // Write any required padding spaces
                    if(ui32Count > ui32Idx)
                    {
                        ui32Count -= ui32Idx;
                        while(ui32Count--)
                        {
                            LogWrite(" ", 1);
                        }
                    }

                    // This command has been handled.
                    break;
                }

                // Handle the %u command.
                case 'u':
                {
                    // Get the value from the varargs.
                    ui32Value = va_arg(vaArgP, uint32_t);

                    // Reset the buffer position.
                    ui32Pos = 0;

                    // Set the base to 10.
                    ui32Base = 10;

                    // Indicate that the value is positive so that a minus sign
                    // isn't inserted.
                    ui32Neg = 0;

                    // Convert the value to ASCII.
                    goto convert;
                }

                // Handle the %x and %X commands.  Note that they are treated
                // identically; in other words, %X will use lower case letters
                // for a-f instead of the upper case letters it should use.  We
                // also alias %p to %x.
                case 'x':
                case 'X':
                case 'p':
                {
                    // Get the value from the varargs.
                    ui32Value = va_arg(vaArgP, uint32_t);

                    // Reset the buffer position.
                    ui32Pos = 0;

                    // Set the base to 16.
                    ui32Base = 16;

                    // Indicate that the value is positive so that a minus sign
                    // isn't inserted.
                    ui32Neg = 0;

                    // Determine the number of digits in the string version of
                    // the value.
convert:
                    for(ui32Idx = 1;
                        (((ui32Idx * ui32Base) <= ui32Value) &&
                         (((ui32Idx * ui32Base) / ui32Base) == ui32Idx));
                        ui32Idx *= ui32Base, ui32Count--)
                    {
                    }

                    // If the value is negative, reduce the count of padding
                    // characters needed.
                    if(ui32Neg)
                    {
                        ui32Count--;
                    }

                    // If the value is negative and the value is padded with
                    // zeros, then place the minus sign before the padding.
                    if(ui32Neg && (cFill == '0'))
                    {
                        // Place the minus sign in the output buffer.
                        pcBuf[ui32Pos++] = '-';

                        // The minus sign has been placed, so turn off the
                        // negative flag.
                        ui32Neg = 0;
                    }

                    // Provide additional padding at the beginning of the
                    // string conversion if needed.
                    if((ui32Count > 1) && (ui32Count < 16))
                    {
                        for(ui32Count--; ui32Count; ui32Count--)
                        {
                            pcBuf[ui32Pos++] = cFill;
                        }
                    }

                    // If the value is negative, then place the minus sign
                    // before the number.
                    if(ui32Neg)
                    {
                        // Place the minus sign in the output buffer.
                        pcBuf[ui32Pos++] = '-';
                    }

                    // Convert the value into a string.
                    for(; ui32Idx; ui32Idx /= ui32Base)
                    {
                        pcBuf[ui32Pos++] = pczHex[(ui32Value / ui32Idx) % ui32Base];
                    }

                    // Write the string.
                    LogWrite(pcBuf, ui32Pos);

                    // This command has been handled.
                    break;
                }

                // Handle the %% command.
                case '%':
                {
                    // Simply write a single %.
                    LogWrite(pcString - 1, 1);

                    // This command has been handled.
                    break;
                }

                // Handle all other commands.
                default:
                {
                    // Indicate an error.
                    LogWrite("ERROR", 5);

                    // This command has been handled.
                    break;
                }
            }
        }
    }
}



void UDPPrintF(const char *pcsz, ...)
{
  memset(&mbPrintf, 0, sizeof(mbPrintf));
  iwPrintf = 0;

  va_list va;
  va_start(va, pcsz);

  LogPrintVarArg(pcsz, va);

  va_end(va);

  UDPLog((uchar *)mbPrintf, iwPrintf);
}


void DebugPrintF(const char *pcsz, ...)
{
  if (ibDebugMode == DEBUG_MODE_UDP)
  {
    date_t date2 = SecondsToDate(GetClockSeconds());

    memset(&mbPrintf, 0, sizeof(mbPrintf));
    iwPrintf = 0;

    uint n = usprintf(mbPrintf,
                       "<%d>%d(v%d) %4d-%02d-%02d %02d:%02d:%02d [%02d][%03d] ",
                 5/*level*/, wSerialNumber, 2/*str_VersPrg*/,
                 0, 0, date2.wDays, date2.bHours, date2.bMinutes, date2.bSeconds,
                 3/*portId*/, 4/*devId*/
    );

    iwPrintf += n;

    va_list va;
    va_start(va, pcsz);

    LogPrintVarArg(pcsz, va);

    va_end(va);

    UDPLog((unsigned char *)mbPrintf, iwPrintf);
  }
  else if (ibDebugMode == DEBUG_MODE_UART)
  {
    va_list va;
    va_start(va, pcsz);

    UARTvprintf(pcsz, va);

    va_end(va);
  }
}


buff BuffPrintF(const char *pcsz, ...)
{
  memset(&mbPrintf, 0, sizeof(mbPrintf));
  iwPrintf = 0;

  va_list va;
  va_start(va, pcsz);

  LogPrintVarArg(pcsz, va);

  va_end(va);

  buff bf;
  bf.pbBuff = (uchar *)&mbPrintf;
  bf.wSize = iwPrintf;

  return bf;
}
