//Удаление компонента из архива изделий
#include "desunit.h"
////#include "baseunit.h"
#include <string.h>

//----------------------------------DeleteArchive()
//Удаление компонента из архива изделий. 
//Просмотр дека слева направо
int DeleteArchive()
{											
int Row, RowPr, counter;
unsigned char Cond;
DynProduct *Del;		// указатель на удаляемый элемент из дека
DynProduct *Beg;		// указатель на начало стека
DynProduct *Run;        // текущий указатель стека архива 
int np;
char Sr[80]="";
  if ( ! SignArchive ) //архив не создан
  {
		 printf("\nАрхив не создан. Режим отменяется.\n");
		 wait_press_key("\nДля продолжения нажмите любую клавишу\n");
		 return 1;
	}
	ReadFileOut(&np,&Beg);//создается архивный дек
	//ввод кода удаляемого изделия
	printf("\nУкажите код удаляемого компонента : ");
 	Row=(int)ceil(GetNumber(0,np,1,0,6,0));
	Cond=0;
	counter = 1;
	RowPr = Row;
	
	//поиск введенного кода в деке
	if (Row == 1)
	{//удаляется крайний левый компонент 
		Cond=1;
		Del=Beg; Beg=Beg->Next;
		free(Del);
	}
  	else
	{  	//поиск введенного кода в средине cтека
		//просмотр с левой стороны
		Run=Beg;
		while ( Run->Next != NULL ) 
		{	if ( Row == counter+1 )
				{	//в стеке найден компонент с заданным кодом
					Cond=1;
					Del=Run->Next;
					//удаляется компонент внутри дека
					Run->Next = Del->Next;
					free(Del); //освобождение памяти
					break;
				}
			Run=Run->Next;
			counter++;
		}
	}
  if( Cond == 1 ) //компонент найден и удален
  {  
    np--;
    WriteFileOut(Beg);	//запись стека в бинарный файл
		Beg=NULL;
    printf("\nУдаление компонента из архива закончено");
	}
  else						//компонент не найден
	{
		DisposeProduct(Beg);
		Beg=NULL;
		printf("\nВ архиве нет компонента с кодом %d",RowPr);
	}
	wait_press_key("\nДля продолжения нажмите любую клавишу\n");
	return 0;
}  //------DeleteArchive()
