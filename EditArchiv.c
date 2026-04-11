// Изменение компонента в архиве изделий
////#include "desunit.h"
////#include "baseunit.h"
// Формирование изменяемого компонента. 
void MakeComponent(ProductType *Product);

//-------------------------------------------ChangeArchive()
// Изменение компонента в архиве изделий 
// Просмотр дека слева направо
// Возвращает 1, если архив не создан, 0 - создан
int ChangeArchive()
{           
int Row, RowPr, counter; 
int np;
unsigned char Cond=0;
ProductType Product;
DynProduct *Beg;		// указатель на начало стека
DynProduct *Run;        // текущий указатель стека архива 
  if ( ! SignArchive )	// архив не создан
  {
		 printf("\nАрхив не создан. Режим отменяется.\n");
		 wait_press_key("\nДля продолжения нажмите любую клавишу\n");
		 return 1;
	}
	//формирование архивного дека
	ReadFileOut(&np,&Beg);
	//ввод кода изменяемого компонента
  printf("\nУкажите код изделия изменяемого компонента :");
	Row=(int)ceil(GetNumber(1,np,1,0,6,0));
  RowPr=Row; printf("Строка = %2d",RowPr);
	Run=Beg; Cond=0; counter = 1;
  while (Run!=NULL) //цикл поиска введенного кода в деке
  {
		if (Row==counter)
		{	//компонент найден
			Cond=1;
			//считывание текущих значений 
			Product=Run->Inf;
			printf("\n     Укажите следующие реквизиты :\n");
			printf("         Номер дела   Годность к службе\n");
			MakeComponent(&Product);	//ввод изменений в полях
			Run->Inf=Product;			//запись измененной структуры в стек
			WriteFileOut(Beg);			//запись стека в архивный файл
			Beg=NULL;
			printf("\nИзменение компонента в архиве закончено\n");
			break;
		}
		counter++;
		Run=Run->Next;
	}
	if (! Cond )	//компонент не найден
    printf("\nВ архиве нет компонента с кодом %d\n",RowPr);
	wait_press_key("\nДля продолжения нажмите любую клавишу\n");
	return 0;
}	//-----СhangeArchive() 
//--------------------------------------------MakeComponent()
// Формирование изменяемого компонента. Перед вводом новых
//значений на экране печатаются текущие значения полей.
//Изменять можно все значения, или любое их количество.
//Если нужно изменить значение в k-ом поле, необходимо ввести
//старые значения всех предшествующих полей. Если значения
//за k-ым полем не редактируются, их старые значения вводить
//не надо. Если с клавиатуры введено меньше шести значений,
//последние поля изменяться не будут.
void MakeComponent(ProductType *Product)
{                    
	int k=0;
	char Sa[80];
	char *token;
	char Seps[]=" \t\n";

	//печать на экран текущих значений
	printf("Тек. зн. %s        %s\nНов. зн. ",
		 	Product->Num, Product->IsApproved);
	rewind(stdin);	//очистка буфера клавиатуры
	/*
		//очистка буфера клавиатуры(если fflush(stdin) не работает)
		rewind(stdin);
	*/	
	fgets(Sa,80,stdin);				//считывание строки с клавиатуры
	token=strtok(Sa,Seps);	//Выделение первого слова
	while(token!=NULL)//цикл выделения слов из исходной строки
	{									// и запись значений в поля структуры
		k++;
		switch ( k )
		{
				case 1:strcpy(Product->Num,token); //FillString(Product->Num,13,1);
				break;
				case 2:strcpy(Product->IsApproved,token); FillString(Product->IsApproved,11,1);break;
		}
		token=strtok(NULL,Seps);	//Выделение очередного слова
	}
} //-----MakeComponent()
