/*------------------------------------------------------------------------------
KEY_GAPS.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_tariffs.h"
#include "../../console.h"
#include "../../time/timedate.h"
#include "../../tariffs/gaps.h"
#include "../../nvram/cache.h"



//                                         0123456789ABCDEF
static char const       szGaps[]        = "Периоды         ",
                        szMaskGap[]     = "__ __           ",
                        szNoGaps[]      = "  нет периодов  ",
                        szError[]       = " ошибка !";


static time             tiT;



void    ShowGapName(uchar  i)
{
  if (i < 12)
    sprintf(szLo+7, "период %u" , i+1);
  else
    strcpy(szLo+7, szError);
}


void    ShowGap(uchar  ibGap)
{
  if (GetGapSize() > 0)
  {
    GetGapDate(ibGap);

    sprintf(szLo,"%2u.%02u", tiGap.bDay, tiGap.bMonth);
    ShowGapName(tiGap.bSecond);
    sprintf(szHi+11,"%2u/%-2u", ibGap+1, GetGapSize());
  }
  else ShowLo(szNoGaps);
}



// добавление нового излома в список и сортировка
bool    AddGap(void)
{
uchar   i,j;
uint    k;

  // проверяем на наличие этого излома в списке
  for (i=0; i<GetGapSize(); i++)
  {
    GetGapDate(i);
    if ((tiGap.bMonth == tiT.bMonth) && (tiGap.bDay == tiT.bDay))
    {
      // заменяем тип излома, не добавляя его в список
      SetGapDate(i);

      SaveCache(&chGaps);
      return(0);
    }
  }


  // записываем излом в конец списка
  tiGap = tiT; SetGapDate(ibX);

  // сортировка
  for(i=0; i<=GetGapSize(); i++)
  {
    for(j=0; j<=GetGapSize(); j++)
    {
      GetGapDate(i);
      k = GetDayIndexMD(tiGap.bMonth, tiGap.bDay);

      GetGapDate(j); 
      if (k < GetDayIndexMD(tiGap.bMonth, tiGap.bDay))
      {
        GetGapDate(i);
        time ti = tiGap;

        GetGapDate(j);
        SetGapDate(i);

        tiGap = ti;
        SetGapDate(j);
      }
    }
  }

  // увеличиваем размер списка
  SetGapSize(GetGapSize() + 1);

  SaveCache(&chGaps);
  return(1);
}



// удаление излома из списка
void    DelGap(void)
{
uchar  i;

  // если удаляем не последний излом
  if (ibX < GetGapSize() - 1)
  {
    // сдвигаем последующие изломи вверх
    for (i=ibX; i<GetGapSize() - 1; i++)
    {
      GetGapDate(i + 1);
      SetGapDate(i);
    }
  }
  // иначе уменьшаем индекс текущего излома
  else if (ibX != 0) 
    ibX--;        

  // уменьшаем количество изломов
  if (GetGapSize() != 0)
    SetGapSize(GetGapSize() - 1);

  SaveCache(&chGaps);
}



// задание списка изломов
void    key_SetGaps(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {                                  
      if (boGapsFlag == false)
      { BlockProgram2(wSET_GAPS_FLAG, 1); return; }
      else
      {
        enKeyboard = KBD_POSTINPUT1;    // начинаем просмотр списка изломов
        ShowHi(szGaps);       
      }
    }     
    else if (enKeyboard == KBD_POSTINPUT2)              
    {                                   
      tiT.bDay = GetCharLo(0,1);
      if ((tiT.bDay > 0) && (tiT.bDay <= 31))
      {
        enKeyboard = KBD_INPUT3;
        szLo[2] = '.';
      }
      else Beep();
    }      
    else if (enKeyboard == KBD_POSTINPUT3)              
    {                                  
      tiT.bMonth = GetCharLo(3,4);
      tiT.bYear  = 0;

      if ((tiT.bMonth == 0) || (tiT.bMonth > 12))
        Beep();
      else if (tiT.bDay > GetDaysInMonthM(tiT.bMonth))
      {
        enKeyboard = KBD_INPUT2; 
        LongBeep();

        ShowLo(szMaskGap); 
      }     
      else
      {
        enKeyboard = KBD_INPUT4;
        tiT.bSecond = 0;              // тип излома (режим работы)

        ShowGapName(tiT.bSecond);
        szLo[6] = '.';
      }
    }
    else if (enKeyboard == KBD_INPUT4)              
    {
      enKeyboard = KBD_POSTENTER;       // переходим в режим ввода

      if (AddGap() == 1)                // добавляем новый излома в список
      {                               
        if (++ibX == bGAPS)             // если список заполнен
        {
          ibX = 0;                      // переходим на начало
          enKeyboard = KBD_SHOW;        // переходим в режим просмотра
        }
      }
      else Beep();                      // такой излом есть в списке
    }                                                            
    else if (enKeyboard == KBD_SHOW)    // режим проcмотра
    {                                   
      ibX++;                            // переходим на следующий излом
      if (ibX == GetGapSize())          // дошли до конца списка
      {                                 
        if (GetGapSize() == bGAPS) 
          ibX = 0;                      // если список заполнен - продолжаем просмотр с начала
        else 
          enKeyboard = KBD_POSTENTER;   // если в списке есть свободное место - переходим в режим ввода
      }
    }


    if ((enKeyboard == KBD_POSTINPUT1) || (enKeyboard == KBD_INPUT2))
    {                                   // начинаем или продолжаем просмотр списка изломов
      ibX = 0;                          // переходим на начало
      if (GetGapSize() == 0) 
        enKeyboard = KBD_POSTENTER;     // если список пустой - переходим в режим ввода
      else                  
        enKeyboard = KBD_SHOW;          // если список не пустой - переходим в режим просмотра
    }


    if (enKeyboard == KBD_POSTENTER)    // режим ввода
    {
      enKeyboard = KBD_INPUT2;          // подготовка к вводу излома
      ShowLo(szMaskGap);
    }
    else if (enKeyboard == KBD_SHOW)    // режим просмотра
      ShowGap(ibX);                     // просмотр текущего излома
  }


  else if (bKey < 10)
  {
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(0,1);
    }
    else 
    if ((enKeyboard == KBD_INPUT3) || (enKeyboard == KBD_POSTINPUT3))
    {
      enKeyboard = KBD_POSTINPUT3;
      ShiftLo(3,4);
    }
  }


  else if (bKey == bKEY_MINUS)
  {    
    if (enKeyboard == KBD_SHOW)         // в режиме просмотра
    {
      DelGap();                         // удаляем излом из списка
      LongBeep();

      if (GetGapSize() == 0)
      {
        enKeyboard = KBD_INPUT2; 

        ShowHi(szGaps); 
        ShowLo(szMaskGap);
      }
      else ShowGap(ibX);
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {    
    if (enKeyboard == KBD_POSTINPUT2)              
    {                                   
      tiT.bDay = GetCharLo(0,1);
      if ((tiT.bDay > 0) && (tiT.bDay <= 31))
      {
        enKeyboard = KBD_INPUT3;
        szLo[2] = '.';
      }       
      else Beep();
    }      
    else if (enKeyboard == KBD_INPUT4)   
    {
      if (++tiT.bSecond >= 12) tiT.bSecond = 0;

      ShowGapName(tiT.bSecond);
      szLo[6] = '.';
    }
    else Beep();
  }
  else Beep();
}



// просмотр списка изломов
void    key_GetGaps(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (boGapsFlag == false)
      { BlockProgram2(wSET_GAPS_FLAG, 1); return; }
      else
      {
        enKeyboard = KBD_POSTENTER;   
        ShowHi(szGaps); 
        
        ibX = 0;                
        ShowGap(ibX);
      }
    }
    else if (enKeyboard == KBD_POSTENTER)
    {  
      if (++ibX >= GetGapSize()) ibX = 0;
      ShowGap(ibX);
    }
  }
}
