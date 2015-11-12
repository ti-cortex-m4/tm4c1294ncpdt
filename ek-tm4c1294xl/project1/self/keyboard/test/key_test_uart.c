/*------------------------------------------------------------------------------

 KEY_TEST_UART.C

------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../hardware/watchdog.h"
#include "../../isr/serial2.h"
#include "../../isr/serial3.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "key_test_uart.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "Тест UART       ",
                        szMessage2[]    = "    тест ?__    ";


#define TEST_CHAR       0x4B


static uchar            bOut0, bIn0,
                        bOut1, bIn1,
                        bOut2, bIn2,
                        bOut3, bIn3;



static void Disable(void)
{
  IntDisable(INT_UART0);
  IntDisable(INT_UART2);
  IntDisable(INT_UART3);
  IntDisable(INT_UART4);

  bOut0 = 0; bIn0 = 0;
  bOut1 = 0; bIn1 = 0;
  bOut2 = 0; bIn2 = 0;
  bOut3 = 0; bIn3 = 0;
}


static void Enable(void)
{
  IntEnable(INT_UART0);
  IntEnable(INT_UART2);
  IntEnable(INT_UART3);
  IntEnable(INT_UART4);
}



static void OutIn(ulong  dwBaseOut, uchar  *pbOut, ulong  dwBaseIn, uchar  *pbIn)
{
  if (UARTCharPutNonBlocking(dwBaseOut, TEST_CHAR))
    (*pbOut)++;

  if (UARTCharGetNonBlocking(dwBaseIn) == TEST_CHAR)
    (*pbIn)++;
}



static void GetTest0(void)
{
  Disable();

  while (1)
  {
    OutIn(UART0_BASE, &bOut0, UART0_BASE, &bIn0);
    OutIn(UART2_BASE, &bOut1, UART2_BASE, &bIn1);
    OutIn(UART3_BASE, &bOut2, UART3_BASE, &bIn2);
    OutIn(UART4_BASE, &bOut3, UART4_BASE, &bIn3);

    Lo( 0, bOut0); Lo( 2, bIn0);
    Lo( 5, bOut1); Lo( 7, bIn1);
    Lo(10, bOut2); Lo(12, bIn2);
    Hi(10, bOut3); Hi(12, bIn3);

    if (fKey == true) {fKey = false; break; }

    Delay(50);
    ResetWatchdog();
  }

  Enable();
}


static void GetTest1(void)
{
  Disable();
  sprintf(szLo,"3:     > 4:");

  OutputMode2();
  InputMode3();

  while (1)
  {
    OutIn(UART3_BASE, &bOut2, UART4_BASE, &bIn3);

    Lo( 2, bOut2); Lo( 4, bIn2);
    Lo(11, bOut3); Lo(13, bIn3);

    if (fKey == true) {fKey = false; break; }

    Delay(50);
    ResetWatchdog();
  }

  Enable();
}


static void GetTest2(void)
{
  Disable();
  sprintf(szLo,"3:     < 4:");

  InputMode2();
  OutputMode3();

  while (1)
  {
    OutIn(UART4_BASE, &bOut3, UART3_BASE, &bIn2);

    Lo( 2, bOut2); Lo( 4, bIn2);
    Lo(11, bOut3); Lo(13, bIn3);

    if (fKey == true) {fKey = false; break; }

    Delay(50);
    ResetWatchdog();
  }

  Enable();
}



static void GetTest(uchar  i)
{
  sprintf(szHi+15,"%u",i+1);
  Clear();

  switch (i)
  {
    case 0:  GetTest0();  break;
    case 1:  GetTest1();  break;
    case 2:  GetTest2();  break;
    default: ASSERT(false);
  }
}


void    key_TestUART(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      ShowHi(szMessage1);
      ShowLo(szMessage2);
    }
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      GetTest(0);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      uchar i;
      if ((i = GetCharLo(10,11) - 1) < 3)
      {
        enKeyboard = KBD_POSTENTER;
        GetTest(i);
      }
      else Beep();
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(10,11);
    }
    else Beep();
  }
  else Beep();
}
