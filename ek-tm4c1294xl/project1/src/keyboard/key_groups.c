/*------------------------------------------------------------------------------
KEY_GROUPS.C

 Группы
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../mem_groups.h"
#include        "../mem_program.h"
#include        "../display.h"
#include        "../beep.h"
#include        "../keyboard.h"
#include        "../groups.h"



//                                         0123456789ABCDEF
static char const       szMaskGroups[]  = "    + ___       ",
                        szGroups[]      = "Группы          ",
                        szNoNodes[]     = "  нет каналов   ";

static nodes            noT;



// добавление узла в группу
bool    AddNode(void)
{
uchar   i,j;

  // проверяем на вхождение этого узла в группу
  for (i=0; i<GetGroupsSize(ibX); i++)
  {
    if (GetGroupsNodeCanal(ibX,i) == (noT.ibCanal & 0x7F))
    {           
      // заменяем знак узла
      SetGroupsNode(ibX,i,noT);
      SaveGroups();

      return(0);
    }
  }

  // добавляем узел в конец группы
  SetGroupsNode(ibX,ibY, noT);

  // сортировка узлов     
  for(i=0; i<=GetGroupsSize(ibX); i++)
  {
    for(j=0; j<=GetGroupsSize(ibX); j++)
    {
      if (GetGroupsNodeCanal(ibX,i) < GetGroupsNodeCanal(ibX,j))
      {
        noT = GetGroupsNode(ibX,i);
        SetGroupsNode(ibX,i, GetGroupsNode(ibX,j));
        SetGroupsNode(ibX,j, noT);
      }
    }
  }

  // увеличиваем размер группы
  SetGroupsSize(ibX, GetGroupsSize(ibX)+1);
  SaveGroups();

  return(1);
}



// удаление узла из группы
void    DelNode(void)
{
uchar   i;

  // если это не последний узел в группе
  if (ibY+1 < GetGroupsSize(ibX))
  {
    // сдвигаем следующие узлы вверх
    for (i=ibY; i<GetGroupsSize(ibX)-1; i++)
    {
      noT = GetGroupsNode(ibX,i+1);
      SetGroupsNode(ibX,i, noT);
    }
  }
  // иначе уменьшаем индекс узла
  else if (ibY != 0) 
    ibY--;

  // уменьшаем количество узлов в группе
  if (GetGroupsSize(ibX) != 0)
    SetGroupsSize(ibX, GetGroupsSize(ibX)-1);
}



// показываем номер текущего узла и общее количество узлов в текущей группе
void    ShowNodes(void)
{
  sprintf(szLo+11,"%2u/%-2u",
          ibY+1,
          GetGroupsSize(ibX));
}



// показываем текущий узел
void    ShowGroup(void)
{ 
  if (GetGroupsSize(ibX) > 0)
  {
    sprintf(szLo,"      %-3u  ",
            GetGroupsNodeCanal(ibX,ibY)+1);

    if (GetGroupsNodeSign(ibX,ibY) == 0)
      szLo[4] = '+';
    else
      szLo[4] = '-';

    ShowNodes();
  }
  else ShowLo(szNoNodes);
}



// показываем номер группы
void    ShowGroupNumber(void)
{ 
  sprintf(szHi,"Группа: %u",ibX+1);
}



void    key_SetGroups(void)
{
  if (bKey == bKEY_ENTER)
  {    
    if (enKeyboard == KBD_ENTER)        
    {                                   // первое нажатие кнопки 'Ввод'
      enKeyboard = KBD_INPUT2;          // подготовка к вводу номера группы
      ShowHi(szGroups); 
      Group();

      boSetGroups = boTrue; 
    }
    else if (enKeyboard == KBD_INPUT2)  // номер группы не введён
    {                                   // начинаем с первой группы
      enKeyboard = KBD_POSTINPUT3;      
      ibX = 0;                          // индекс группы
      ShowGroupNumber();  
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {                                   
      if ((ibX = GetChar(10,11)-1) < bGROUPS)
      {                                 // получили индекс группы
        enKeyboard = KBD_POSTINPUT3;
        ShowGroupNumber();
      } 
      else Beep();
    }    
    else if (enKeyboard == KBD_POSTINPUT1)              
    {                                   // запись данных после ввода
      if ((noT.ibCanal = GetChar(6,8)-1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;     

        if (szLo[4] == '-')
          noT.ibCanal |= 0x80;

        if (AddNode() == 1)             // добавление узла в группу
        {                               // нет такого узла                                        
          if (++ibY == bCANALS)      // если группа заполнена полностью
          {
            enKeyboard = KBD_SHOW;      // переходим в режим просмотра
            ibY = 0;
          }
        }
        else Beep();                    // есть такой узел
      }
      else Beep();
    }                                                                
    else if (enKeyboard == KBD_SHOW)
    {                                   // продолжаем просмотр
      ibY++;                            // переходим на следующий узел
      if (ibY == GetGroupsSize(ibX))    // дошли до последнего узла     
      {                                 
        if (GetGroupsSize(ibX) == bCANALS) 
          ibY = 0;                      // если полный список - продолжаем просмотр с начала
        else 
          enKeyboard = KBD_POSTENTER;   // иначе ввод нового узла        
      }
    }


    if (enKeyboard == KBD_POSTINPUT3)
    {
      // при перепрограммировании разрешается редактировать незаданные группы
      if ((enGlobal == GLB_REPROGRAM) && (mpboUsedGroups[ibX] == boTrue))
      {
        Error();
        LongBeep();
        return;
      }
    }


    if ((enKeyboard == KBD_POSTINPUT3) || (enKeyboard == KBD_INPUT1))
    {                                   // начинаем просмотр группы с начала
      ibY = 0;                          // переход на первый узел
      if (GetGroupsSize(ibX) == 0) 
        enKeyboard = KBD_POSTENTER;     // если группа пустая - режим ввода
      else                  
        enKeyboard = KBD_SHOW;          // есть группа не пустая - режим просмотра
    }


    if (enKeyboard == KBD_POSTENTER)    // неповредственно подготовка ввода  
    {
      enKeyboard = KBD_INPUT1; 
      ShowLo(szMaskGroups);
    }
    else if (enKeyboard == KBD_SHOW)    // непосредственно просмотр
      ShowGroup();     
  }


  else if (bKey < 10)
  {
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(10,11);
    }
    else 
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(6,8);
    }
  }


  else if (bKey == bKEY_MINUS)
  {    
    if (enKeyboard == KBD_SHOW)         
    {                                   // в режиме просмотра
      DelNode();                        // удалить узел из группы
      LongBeep();

      if (GetGroupsSize(ibX) == 0)
      {
        enKeyboard = KBD_INPUT1; 
        ShowLo(szMaskGroups);
      }
      else ShowGroup();
    }
 

    else if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1)) 
    {                                   // в режиме ввода
      if (szLo[4] == '-')               // изменить знак узла на противоположный 
        szLo[4] = '+';
      else
        szLo[4] = '-';
    } 
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if ((enKeyboard == KBD_POSTENTER) || 
        (enKeyboard == KBD_INPUT1)    || (enKeyboard == KBD_SHOW))
    {
      if (++ibX >= bGROUPS)
        ibX = 0;

      ShowGroupNumber();
      ibY = 0;                

      if (GetGroupsSize(ibX) == 0) 
      {
        enKeyboard = KBD_INPUT1;        // если группа пустая - режим ввода
        ShowLo(szMaskGroups);
      }
      else                  
      {
        enKeyboard = KBD_SHOW;          // есть группа не пустая - режим просмотра
        ShowGroup();
      }
    }
    else Beep();
  }
}



void    key_GetGroups(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT2;

      ShowHi(szGroups); 
      Group();
    }

    else if (enKeyboard == KBD_INPUT2)
    {
      enKeyboard = KBD_POSTENTER;   
        
      ibX = 0;
      ShowGroupNumber();

      ibY = 0;                
      ShowGroup();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      if ((ibX = GetChar(10,11)-1) < bGROUPS)
      {
        enKeyboard = KBD_POSTENTER;   
        ShowGroupNumber();

        ibY = 0;                
        ShowGroup();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {  
      if (++ibY >= GetGroupsSize(ibX))
        ibY = 0;
      ShowGroup();
    }
  }


  else if (bKey < 10)
  {
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(10,11);
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)  
    {
      if (++ibX >= bGROUPS)
        ibX = 0;

      ShowGroupNumber();

      ibY = 0;                
      ShowGroup();
    }
    else Beep();
  }
}

