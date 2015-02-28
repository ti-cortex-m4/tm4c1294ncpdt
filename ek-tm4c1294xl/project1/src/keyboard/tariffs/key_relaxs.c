/*------------------------------------------------------------------------------
KEY_RELAXS.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_tariffs.h"
#include        "../../memory/mem_settings.h"
#include        "../../memory/mem_realtime.h"
#include        "../keyboard.h"
#include        "../../display/display.h"
#include        "../../timedate.h"
#include        "../../hardware/rtc.h"
#include        "../../tariffs/relaxs.h"
#include        "../../flash/files.h"



//                                         0123456789ABCDEF
static char const       szRelaxs[]      = "Праздники       ",
                        szMaskRelax[]   = " __ __          ",
                        szNoRelaxs[]    = " нет праздников ",
                        szHoliday[]     = " выходной",
                        szWeekday[]     = " рабочий ",
                        szError[]       = " ошибка !";



void    ShowRelaxName(uchar  i)
{
  switch (i)
  {
    case 1:  strcpy(szLo+7, szHoliday);  break;
    case 2:  strcpy(szLo+7, szWeekday);  break;
    default: strcpy(szLo+7, szError);    break;
  }
}


void    ShowRelax(uchar  ibRelax)
{
  if (GetRelaxSize() > 0)
  {
    GetRelaxDate(ibRelax);

    sprintf(szLo," %2u.%02u", tiRelax.bDay, tiRelax.bMonth);
    ShowRelaxName(tiRelax.bSecond);
    sprintf(szHi+11,"%2u/%-2u", ibRelax+1, GetRelaxSize());
  }
  else ShowLo(szNoRelaxs);
}



// добавление нового праздника в список и сортировка
bool    AddRelax(void)
{
uchar   i,j;
uint    k;

  // проверяем на наличие этого праздника в списке
  for (i=0; i<GetRelaxSize(); i++)
  {
    GetRelaxDate(i);
    if ((tiRelax.bMonth == tiKey.bMonth) && (tiRelax.bDay == tiKey.bDay))
    {
      // заменяем тип праздника, не добавляя его в список
      SetRelaxDate(i);

    	SaveFile(&flRelaxs);
      return(0);
    }
  }


  // записываем праздник в конец списка
  tiRelax = tiKey; SetRelaxDate(ibX);

  // сортировка      
  for(i=0; i<=GetRelaxSize(); i++)
  {
    for(j=0; j<=GetRelaxSize(); j++)
    {
      GetRelaxDate(i);
      k = GetDayIndexMD(tiRelax.bMonth, tiRelax.bDay);

      GetRelaxDate(j);
      if (k < GetDayIndexMD(tiRelax.bMonth, tiRelax.bDay))
      {
        GetRelaxDate(i); tiAlt = tiRelax;

        GetRelaxDate(j);
        SetRelaxDate(i);

        tiRelax = tiAlt; SetRelaxDate(j);
      }
    }
  }

  // увеличиваем размер списка
  SetRelaxSize(GetRelaxSize() + 1);

	SaveFile(&flRelaxs);
  return(1);
}



// удаление праздника из списка
void    DelRelax(void)
{
uchar  i;

  // если удаляем не последний праздник
  if (ibX < GetRelaxSize() - 1)
  {
    // сдвигаем последующие праздники вверх
    for (i=ibX; i<GetRelaxSize() - 1; i++)
    {
      GetRelaxDate(i + 1);
      SetRelaxDate(i);
    }
  }
  // иначе уменьшаем индекс текущего праздника
  else if (ibX != 0) 
    ibX--;        

  // уменьшаем количество праздников
  if (GetRelaxSize() != 0)
    SetRelaxSize(GetRelaxSize() - 1);

	SaveFile(&flRelaxs);
}



void    key_SetRelaxs(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {                                  
      if (boRelaxsFlag == false)
      { BlockProgram(bSET_RELAXS_FLAG); return; }
      else
      {
        enKeyboard = KBD_POSTINPUT1;    // начинаем просмотр списка праздников
        ShowHi(szRelaxs);       
      }
    }     
    else if (enKeyboard == KBD_POSTINPUT2)              
    {                                   
      tiKey.bDay = GetCharLo(1,2);
      if ((tiKey.bDay > 0) && (tiKey.bDay <= 31))
      {
        enKeyboard = KBD_INPUT3;
        szLo[3] = '.';
      }
      else Beep();
    }      
    else if (enKeyboard == KBD_POSTINPUT3)              
    {                                  
      tiKey.bMonth = GetCharLo(4,5);
      tiKey.bYear  = GetCurrTimeDate()->bYear;

      if ((tiKey.bMonth == 0) || (tiKey.bMonth > 12))
        Beep();
      else if (tiKey.bDay > GetDaysInMonthYM(tiKey.bYear, tiKey.bMonth))
      {
        enKeyboard = KBD_INPUT2; 
        LongBeep();

        ShowLo(szMaskRelax); 
      }     
      else
      {
        enKeyboard = KBD_INPUT4;
        tiKey.bSecond = 1;              // тип праздника (режим работы)              

        ShowRelaxName(tiKey.bSecond);
        szLo[7] = '.';
      }
    }
    else if (enKeyboard == KBD_INPUT4)              
    {
      enKeyboard = KBD_POSTENTER;       // переходим в режим ввода 

      if (AddRelax() == 1)              // добавляем новый праздника в список
      {
        if (++ibX == bRELAXS)           // если список заполнен
        {
          ibX = 0;                      // переходим на начало
          enKeyboard = KBD_SHOW;        // переходим в режим просмотра
        }
      }
      else Beep();                      // такой праздник есть в списке
    }                                                            
    else if (enKeyboard == KBD_SHOW)    // режим проcмотра
    {                                   
      ibX++;                            // переходим на следующий праздник
      if (ibX == GetRelaxSize())        // дошли до конца списка      
      {                                 
        if (GetRelaxSize() == bRELAXS) 
          ibX = 0;                      // если список заполнен - продолжаем просмотр с начала
        else 
          enKeyboard = KBD_POSTENTER;   // если в списке есть свободное место - переходим в режим ввода        
      }
    }


    if ((enKeyboard == KBD_POSTINPUT1) || (enKeyboard == KBD_INPUT2))
    {                                   // начинаем или продолжаем просмотр списка праздников
      ibX = 0;                          // переходим на начало
      if (GetRelaxSize() == 0) 
        enKeyboard = KBD_POSTENTER;     // если список пустой - переходим в режим ввода 
      else                  
        enKeyboard = KBD_SHOW;          // если список не пустой - переходим в режим просмотра
    }


    if (enKeyboard == KBD_POSTENTER)    // режим ввода  
    {
      enKeyboard = KBD_INPUT2;          // подготовка к вводу праздника
      ShowLo(szMaskRelax);
    }
    else if (enKeyboard == KBD_SHOW)    // режим просмотра
      ShowRelax(ibX);                   // просмотр текущего праздника
  }


  else if (bKey < 10)
  {
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(1,2);
    }
    else 
    if ((enKeyboard == KBD_INPUT3) || (enKeyboard == KBD_POSTINPUT3))
    {
      enKeyboard = KBD_POSTINPUT3;
      ShiftLo(4,5);
    }
  }


  else if (bKey == bKEY_MINUS)
  {    
    if (enKeyboard == KBD_SHOW)         // в режиме просмотра         
    {
      DelRelax();                       // удаляем праздник из списка
      LongBeep();

      if (GetRelaxSize() == 0)
      {
        enKeyboard = KBD_INPUT2; 

        ShowHi(szRelaxs); 
        ShowLo(szMaskRelax);
      }
      else ShowRelax(ibX);
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {    
    if (enKeyboard == KBD_POSTINPUT2)              
    {                                   
      tiKey.bDay = GetCharLo(1,2);
      if ((tiKey.bDay > 0) && (tiKey.bDay <= 31))
      {
        enKeyboard = KBD_INPUT3;
        szLo[3] = '.';
      }
      else Beep();
    }      
    else if (enKeyboard == KBD_INPUT4)   
    {
      if (++tiKey.bSecond > 2) tiKey.bSecond = 1;

      ShowRelaxName(tiKey.bSecond);
      szLo[7] = '.';
    }
    else Beep();
  }
  else Beep();
}



void    key_GetRelaxs(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (boRelaxsFlag == false)
      { BlockProgram(bSET_RELAXS_FLAG); return; }
      else
      {
        enKeyboard = KBD_POSTENTER;   
        ShowHi(szRelaxs); 
        
        ibX = 0;                
        ShowRelax(ibX);
      }
    }
    else if (enKeyboard == KBD_POSTENTER)
    {  
      if (++ibX >= GetRelaxSize()) ibX = 0;
      ShowRelax(ibX);
    }
  }
}
