//Сортировка архива
#include "desunit.h"
////#include "baseunit.h"
//---------------------------------------------SortArchive()
//Сортировка архива по возрастанию кода изделия. Просмотр дека 
//с левой стороны и сортировка "школьным" методом по возрастанию
int SortArchive()
{							
int np;
ProductType Product;
DynProduct *Runi;
DynProduct *Runj;		// текущие указатели стека архива 
DynProduct *Beg;		// указатель на начало стека
  if ( ! SignArchive )	//архив не создан
  {
		 printf("\nАрхив не создан. Режим отменяется.\n");
		 wait_press_key("\nДля продолжения нажмите любую клавишу\n");
		 return 1;
	}
	ReadFileOut(&np,&Beg);	//Формирование архивного дека
	//Сортировка дека по алфавиту "Пузырьком"

	for ( Runi=Beg; Runi!=NULL; Runi=Runi->Next )
		for ( Runj=Runi->Next; Runj!=NULL; Runj=Runj->Next )
			if ( Runi->Inf.Num[0] > Runj->Inf.Num[0] )
			{	Product=Runi->Inf; 
				Runi->Inf=Runj->Inf;
       			Runj->Inf=Product;
			}

	WriteFileOut(Beg);	//запись дека в архивный файл
	Beg = NULL;
	printf("\nСортировка архива закончена.\n");
	wait_press_key("\nДля продолжения нажмите любую клавишу\n");
	return 0;
}	//------SortArchive()
