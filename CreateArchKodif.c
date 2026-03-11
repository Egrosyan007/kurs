//Модуль создания архивного файла изделий и массива кодификатора,
//печати архива из бинарного файла и кодификатора из массива
////#include "desunit.h"
////#include "baseunit.h"
//Чтение файла "Kodif.txt" и формирование массива Kodifs 
void MakeKodifs(int *nk);
//Считывается строка из указанного файла (input.txt или add.txt),
int ReadProduct(FILE *f,ProductType *Product);

//----------------------------------------CreateArchive()
//Считываются строки описания продукта из текстового файла
//Формируется бинарный файл архива. 
//Из текстового файла считывается кодификатор и записывается
//в массив. Массив сортируется и сохраняется в памяти
//до закрытия приложения. nk - количество элементов в массиве 
void CreateArchive()
{
	ProductType Product;
	//Открывается исходный текстовый файл
	if((fArTxt=fopen(fArTxtName,"rt"))==NULL)
		{
		 printf("\nФайл %s не найден\n",fArTxtName);
		 wait_press_key("\nДля завершения программы нажмите любую клавишу\n");
		 exit(0);
		}
	//Открывается бинарный файл архива
	if((fArBin=fopen(fArBinName,"wb"))==NULL)
		{
		 printf("\nФайл %s не создан\n",fArTxtName);
		 wait_press_key("\nДля завершения программы нажмите любую клавишу\n");
		 exit(0);
		}
	do
	{ //формирование структуры архива изделия 
		if (ReadProduct(fArTxt,&Product)==0)
			//запись структуры архива изделия в бинарный файл
			fwrite(&Product,sizeof(ProductType),1,fArBin);
	}
	while ( ! feof(fArTxt) );
	//файлы закрываются
	fclose(fArTxt); fArTxt=NULL;
	fclose(fArBin); fArBin=NULL;
	//формирование массива кодификатора
	MakeKodifs(&nk);
	//сортировка массива кодификатора
	SortKodif(nk);
	//Установка флага - архив создан
	SignArchive=1;
	printf("\n	Архив создан\n");
	wait_press_key("\nДля продолжения нажмите любую клавишу\n");

}	//-----CreateArchive()
//------------------------------------------ReadProduct()
//Считывается строка из указанного файла (input.txt или add.txt),
//производится ее разбор и формирование структуры Product. 
//Возвращает 0,если структура сформирована.
//Если найден конец файла - возвращает 1
int ReadProduct(FILE *f,ProductType *Product)
{
	char sIn[80];		//строка из файла
	int k;
	char *token;
	char Seps[]=" \t\n";
	if ( fgets(sIn, 100, f) != NULL )	//считывание строки
	{	
		k=0;
		token=strtok(sIn,Seps);	//Выделение первого слова
		while(token!=NULL)//цикл выделения слов из исходной строки
		{
			k++;                  //k-номер найденного слова
			switch ( k )
			{	//Заполнение полей структуры по номеру слова
				// case 1:sscanf_s(token,"%d",&Product->NumberShop);	break;
				// case 2:sscanf_s(token,"%d",&Product->Kod);			break;
				// case 3:strcpy(Product->Dimens,token);
				// 			FillString(Product->Dimens,5,1);		break;
				// case 4:sscanf_s(token,"%lf",&Product->Price);		break;
				// case 5:sscanf_s(token,"%lf",&Product->Plan[0]);		break;
				// case 6:sscanf_s(token,"%lf",&Product->Plan[1]);		break;
				// case 7:sscanf_s(token,"%lf",&Product->Fact[0]);		break;
				// case 8:sscanf_s(token,"%lf",&Product->Fact[1]);		break;
				case 1:strcpy(Product->Names,token); FillString(Product->Names,16,1);break;
				case 2:strcpy(Product->Date,token); FillString(Product->Date,16,1);break;
				case 3:strcpy(Product->Num,token); FillString(Product->Num,13,1);break;
				case 4:strcpy(Product->Street,token); FillString(Product->Street,24,1);break;
				case 5:strcpy(Product->IsApproved,token); FillString(Product->IsApproved,11,1);break;
			}
			token=strtok(NULL,Seps);	//Выделение очередного слова
		}
		return 0;		//Product сформирован
	}
	else return 1;//найден конец файла 
}	//-----ReadProduct()
//---------------------------------------------PrintArchive()
//Из бинарного файла считывается архив и печатается на экране, в файл 
int PrintArchive()
{
	ProductType Product;
	int i;
	char s[80];
	if (SignArchive==0)//проверка флага создания архива
	{
		 printf("\nАрхив не создан. Режим отменяется.\n");
		 wait_press_key("\nДля продолжения нажмите любую клавишу\n");
		 return 0;
	}
	//открывается бинарный архивный файл
	if((fArBin=fopen(fArBinName,"rb"))==NULL)
	{
		 printf("\nФайл %s не найден. Режим отменяется.\n",fArBinName);
		 wait_press_key("\nДля продолжения нажмите любую клавишу\n");
		 SignArchive=0;
		 return 0;
	}
	//печать заголовка отчета
	WritelnString(
"\n                     АРХИВ СВЕДЕНИЙ О ЮНОШАХ ПРИЗЫВНОГО ВОЗРАСТА");
  WritelnString(
" ____________________________________________________________________________________ ");
  WritelnString(
"|  N |      ФИО      | Дата рождения | Номер дела |         Адрес         | Годность |");
  WritelnString(
"|------------------------------------------------------------------------------------|");


	i=0;
  while (fread(&Product,sizeof(ProductType),1,fArBin)==1)	//цикл чтения структур архивного файла
  {	//формирование строки s для печати
    i++; s[0]='|';s[1]='\0';
		 sprintf(s,
		 	"|%3d. %s %s %s %s %s|",
		 	i,Product.Names,Product.Date,Product.Num,Product.Street,Product.IsApproved);
	  WritelnString(s);//печать строки
	}
	WritelnString(
"|____________________________________________________________________________________|\n");
 	fclose(fArBin);
	wait_press_key("\nДля продолжения нажмите любую клавишу\n");

	return 0;

}	//-----PrintArchive()
//-----------------------------------------------MakeKodifs()
//Чтение файла "Kodif.txt" и формирование массива Kodifs 
//Возвращает через параметр длину массива nk
void MakeKodifs(int *nk)
{ 
	char Sa[80];
	int k;
	char *token;
	char Seps[]=" \t\n";
	//открывается файл кодификатора "Kodif.txt"
	if((fKodif=fopen(fKodifName,"rt"))==NULL)
	{
		 printf("\nФайл %s не найден\n",fArTxtName);
		 wait_press_key("\nДля завершения программы нажмите любую клавишу\n");
		 exit(0);
	}
  
  *nk=0;	//длина массива
  while (fgets(Sa,80,fKodif)!=NULL) //чтение "Kodif.txt"
	{
		k=0;
		token=strtok(Sa,Seps);	//Выделение первого слова
		while(token!=NULL)//цикл выделения слов из исходной строки
		{
			k++;
			switch ( k)
			{	//заполнение полей структуры кодификатора
				case 1:sscanf_s(token,"%d",&Kodif.Kod);				break;
				case 2:strcpy(Kodif.Name,token);							break;
				case 3:strcat(strcat(Kodif.Name," "),token);	break;
			}
			token=strtok(NULL,Seps);	//Выделение очередного слова
		}
		FillString(Kodif.Name,35,1);//заполнение пробелами справа
		Kodifs[*nk]=Kodif;//запись структуры в массив
    (*nk)++;					//увеличение длины массива
	}
  fclose(fKodif);
}	//----- MakeKodifs() 
//-----------------------------------------------PrintKodif()
// Вывод кодификатора изделий на экран, в файл 
int PrintKodif(int nk)
{
	char s[80];
	unsigned char i,j=0;
  if (SignArchive==0)
	{
		 printf("\nАрхив не создан. Режим отменяется.\n");
		 wait_press_key("\nДля продолжения нажмите любую клавишу\n");
		 return 0;
	}
  WritelnString(
"\n                КОДИФИКАТОР ВЫПУСКАЕМОЙ ПРОДУКЦИИ");
  WritelnString(
" ---------------------------------------------------------------- ");
  WritelnString(
"| Nп/п |   Код изделия  |    Наименование  изделия               |");
  WritelnString(
" ---------------------------------------------------------------- ");
  j=0;
  for ( i=0; i<nk; i++ )
	{
		Kodif=Kodifs[i];
		j++; 
		sprintf(s,"|%4d.       %6d          %s  |",
															j,Kodif.Kod,Kodif.Name);
		WritelnString(s);
	}
  WritelnString(
" ---------------------------------------------------------------- ");
	wait_press_key("\nДля продолжения нажмите любую клавишу\n");
	return 0;
}	//-----PrintKodif() 
