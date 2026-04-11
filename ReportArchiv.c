////#include "desunit.h"
////#include "baseunit.h"
#include <string.h>
// Обработка архива изделий и формирование отчетов
//-----------------------------------------WorkUpArchive()
void WorkUpArchive()
{           
char* endptr = 0;
char Yes[15] = "Да";
char Day[3], Month[3], Year[5];
FillString(Yes,11,1);
int k=-1,m,np;
int *plist;

char St[80];
DynProduct *Beg;				  // указатель на начало стека
DynProduct *Run;          // текущий указатель стека архива 
  if ( ! SignArchive )		// архив не создан
	{
      printf("Архивный файл не создан. Режим отменяется");
      return;
	}
  ReadFileOut(&np,&Beg);//формирование архивного дека
	//ПЕЧАТЬ СВЕДЕНИй О ЮНОШАХ ПРИЗЫВАЕМЫХ НА СЛУЖБУ
  m = 1;
  k=0; Run=Beg;
  plist = (int *)malloc(sizeof(int)*np);
  while (Run!=NULL) 
  {	//поиск сведений по заданному цеху
    if (strcmp(Yes,Run->Inf.IsApproved) == 0)
		{ strncpy(Day, Run->Inf.Date, 2);
      strncpy(Month, Run->Inf.Date+3, 2);
      strncpy(Year, Run->Inf.Date+6, 4);

      if (strtol(Year, &endptr, 10) < 2008)
        {plist[k] = m; k++;}
      else if (strtol(Year, &endptr, 10) == 2008)
        if (strtol(Month, &endptr, 10) < 8)
          {plist[k] = m; k++;}
        else if (strtol(Month, &endptr, 10) == 8)
          if (strtol(Day, &endptr, 10) < 2)
            {plist[k] = m; k++;}
		}
    m++;
    Run=Run->Next;
	}
  if (k==0)
    printf("В архиве нет юнош, подлежащих призыву на военную службу");

  else
	{
      //ПЕЧАТЬ СВЕДЕНИЙ ПО ВЫПОЛНЕНИЮ ПЛАНА ПО ИЗДЕЛИЯМ
      //печать заголовка таблицы
      WritelnString(
"\n            СПИСОК ЮНОШ ПОДЛЕЖАЩИХ ПРИЗЫВУ НА ВОЕННУЮ СЛУЖБУ");
    WritelnString(
" _________________________________________________________________________ ");
      WritelnString(
"|  N |      ФИО      | Дата рождения | Номер дела |         Адрес         |");
      WritelnString(
"|-------------------------------------------------------------------------|");
      m=1; k = 0;
      Run=Beg;
      while ( Run != NULL)	//цикл просмотра дека
      {	//расчет выполнения плана по изделию
        if (m == plist[k]) {
          sprintf(St,"| %2d  %15s %15s %s        %s|",
                  m, Run->Inf.Names, Run->Inf.Date, Run->Inf.Num, Run->Inf.Street);
          //печать сформированной строки
          WritelnString(St);
          k++;
        }
        Run=Run->Next;
        m++;
      }
      
	}
  WritelnString(
" ------------------------------------------------------------------------- ");
//" --------------------------------------------------------------- ");
  free(plist);
	DisposeProduct(Beg);//удаление дека
	printf("\nОбработка архива закончена");

	wait_press_key("\nДля продолжения нажмите любую клавишу\n");
} //-----------WorkUpArchive() 
