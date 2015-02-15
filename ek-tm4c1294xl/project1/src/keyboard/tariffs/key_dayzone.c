/*------------------------------------------------------------------------------
KEY_DAYZONE.С

 Запись суточного тарифного графика
------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_tariffs.h"
#include        "../../display/display.h"
#include        "../../keyboard.h"
#include        "../../tariffs/tariffs.h"
#include        "../../tariffs/zones.h"
#include        "../../flash/files.h"



//                                         0123456789ABCDEF
static char const       szMaskBreak[]   = "  __ __   _     ";
                        


// добавление излома и сортировка суточного тарифного графика
bool    AddBreak(void)
{
uchar   i,j;

  // записываем излом в конец суточного тарифного графика
  SetZoneKeyBreak(ibX);

  // проверяем на наличие этого излома в суточном тарифном графике
  for(i=0; i<GetZoneKeySize(); i++)
  {
    // если такой излом уже есть
    if (GetBreakKeyIndex(i) == GetBreakKeyIndex(ibX))
    {
      // заменяем тариф
      GetZoneKeyBreak(ibX);
      SetZoneKeyBreak(i);

      SaveFile(&flZone);
      return(0);
    }
  }

  // сортировка      
  for(i=0; i<=GetZoneKeySize(); i++)
  {
    for(j=0; j<=GetZoneKeySize(); j++)
    {
      if (GetBreakKeyIndex(i) < GetBreakKeyIndex(j))
      {
        GetZoneKeyBreak(i);
        brAlt = brKey;

        GetZoneKeyBreak(j);
        SetZoneKeyBreak(i);

        brKey = brAlt;
        SetZoneKeyBreak(j);
      }
    }
  }

  // увеличиваем размер суточного тарифного графика
  SetZoneKeySize(GetZoneKeySize() + 1);

  SaveFile(&flZone);
  return(1);
}



// удаление излома из суточного тарифного графика
void    DelBreak(void)
{
uchar   i;

  // если это не последний излом
  if (ibX < GetZoneKeySize() - 1)      
  {                                 
    // сдвигаем последующие изломы вверх 
    for (i=ibX; i<GetZoneKeySize() - 1; i++)
    {
      GetZoneKeyBreak(i + 1);
      SetZoneKeyBreak(i);
    }
  }
  // иначе уменьшаем индекс излома
  else if (ibX != 0)
    ibX--;            

  // уменьшаем количество изломов 
  if (GetZoneKeySize() != 0)
    SetZoneKeySize(GetZoneKeySize() - 1);

  // обнуляем удалённые изломы
  if (GetZoneKeySize() < bBREAKS)
  {
    brKey = brZero;
    SetZoneKeyBreak(GetZoneKeySize());
  }

  SaveFile(&flZone);
}



// задание суточного тарифного графика
void    key_SetDayZone(void)
{
  if (bKey == bKEY_ENTER)
  {    
    if (enKeyboard == KBD_ENTER)
    {         
      enKeyboard = KBD_POSTINPUT4;      // начинаем просмотр суточного тарифного графика

      ShowHi(szTariffs);
      Clear();
    }    
    else if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      if (enKeyboard == KBD_INPUT2)
      {
        bKey = 0; ShiftLo(5,6);
        bKey = 0; ShiftLo(5,6);
      }

      brKey.bMinute = GetCharLo(5,6);

      if ((brKey.bMinute % 30) == 0)
      {
        enKeyboard = KBD_INPUT3;
        szLo[8] = '-';        
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      brKey.ibTariff = GetCharLo(10,10) - 1;

      if (brKey.ibTariff < bTARIFFS)
      {
        enKeyboard = KBD_POSTENTER;     // переходим в режим ввода
        
        if (AddBreak() == 1)            // добавляем новый излом в суточный график
        {                               
          if (++ibX == bBREAKS)         // если суточный график заполнен
          {                               
            ibX = 0;                    // переходим на начало
            enKeyboard = KBD_SHOW;      // переходим в режим просмотра
          }
        } 
        else Beep();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_SHOW)    // режим просмотра
    {
      ibX++;                            // переходим на следующий излом

      if (ibX == GetZoneKeySize())      // дошли до конца суточного графика 
      {                                 
        if (ibX == bBREAKS)
          ibX = 0;                      // если суточный график заполнен - продолжаем просмотр с начала
        else
          enKeyboard = KBD_POSTENTER;   // если в суточном графике есть свободное место - переходим в режим ввода
      }
    }


    if ((enKeyboard == KBD_POSTINPUT4) || (enKeyboard == KBD_INPUT1))
    {                                   // начинаем или продолжаем просмотр суточного тарифного графика
      ibX = 0;                          // переход на начало

      if (GetZoneKeySize() == 0)
        enKeyboard = KBD_POSTENTER;     // если суточный график пустой - переходим в режим ввода
      else
        enKeyboard = KBD_SHOW;          // если суточный график не пустой - переходим в режим просмотра
    }


    if (enKeyboard == KBD_POSTENTER)    // режим ввода            
    { 
      enKeyboard = KBD_INPUT1;          // подготовка к вводу излома
      ShowLo(szMaskBreak);               
    }
    else if (enKeyboard == KBD_SHOW)    // режим просмотра
      ShowZoneKeyBreak(ibX);            // просмотр текущего излома
  }



  else if (bKey == bKEY_MINUS)          // в режиме просмотра
  {
    if (enKeyboard == KBD_SHOW)
    {                                   
      DelBreak();                       // удаляем излом
      LongBeep();

      if (GetZoneKeySize() == 0)
      {                                 
        enKeyboard = KBD_INPUT1;         
        ShowLo(szMaskBreak);
      }
      else ShowZoneKeyBreak(ibX);
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTINPUT1)
    {
      brKey.bHour = GetCharLo(2,3);

      if (brKey.bHour <= 24)
      {
        enKeyboard = KBD_INPUT2;
        szLo[4] = '.';        
      } 
      else Beep();
    }
  }


  else if (bKey < 10)
  {
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(2,3);
    }
    else 
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(5,6);
    }
    else 
    if ((enKeyboard == KBD_INPUT3) || (enKeyboard == KBD_POSTINPUT3))
    {
      enKeyboard = KBD_POSTINPUT3;
      ShiftLo(10,10);
    }
    else Beep();
  }
  else Beep();
}
