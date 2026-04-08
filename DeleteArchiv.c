//Удаление компонента из архива изделий
#include "desunit.h"
////#include "baseunit.h"
#include <string.h>

//----------------------------------DeleteArchive()
//Удаление компонента из архива изделий. 
//Просмотр дека слева направо
int DeleteArchive()
{											
char Num[5], NumPr[5];
unsigned char Cond;
DynProduct  *Del;		// указатель на удаляемый элемент из дека
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
	scanf_s("%s", Num, 5);
 	//Num=(int)ceil(GetNumber(0,999999,1,0,6,0));
	Cond=0;
	strcpy(NumPr, Num);
	
	//поиск введенного кода в деке
	if ( Num == Beg->Inf.Num)
	{//удаляется крайний левый компонент 
		Cond=1;
		Del=Beg; Beg=Beg->Next;
		free(Del);
	}
  	else
	{  	//поиск введенного кода в средине cтека
		//просмотр с левой стороны
		Run=Beg->Next;
		while ( Run->Next != NULL ) 
		{	if ( Num == Run->Next->Inf.Num )
				{	//в стеке найден компонент с заданным кодом
					Cond=1;
					Del=Run->Next;
					//удаляется компонент внутри дека
					Run->Next = Del->Next;
					free(Del); //освобождение памяти
					break;
				}
				Run=Run->Next;
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
		printf("\nВ архиве нет компонента с кодом %6s",NumPr);
	}
	wait_press_key("\nДля продолжения нажмите любую клавишу\n");
	return 0;
}  //------DeleteArchive()
