//Контроль исходных текстовых файлов
#include "CheckInpFile.h"

//-------------------------------------CheckFiles()
//Контроль текстовых файлов - вызывается из меню модуля kurs
void CheckFiles()
{							
	ProductArPtr   Products,	//динамические массивы для архива
							AddProducts;	//и добавляемых данных в архив
	if((FileError=fopen(FileErrorName,"wb+"))==NULL)
		{	//не удалось открыть файл ошибок
		 printf("\nФайл %s не найден\n",FileErrorName);
		 wait_press_key("\nДля завершения нажмите любую клавишу\n");
		 exit(0);
		}
	//запись заголовка в файл ошибок
	sprintf(Sr,"\n         ПРОТОКОЛ КОНТРОЛЯ ТЕКСТОВЫХ ФАЙЛОВ\n");
	fwrite(Sr,sizeof(string80),1,FileError);
  FatalError=0;	//флаг фатальных ошибок - ошибок нет
	//выделение памяти для массива строк архива
	Sf=(FileStringAr *)malloc(sizeof(FileStringAr));  
	//выделение памяти для массива структур архива
  Products=(ProductAr *)malloc(sizeof(ProductAr));  
	//выделение памяти для массива структур добавления в архив
	AddProducts=(ProductAr *)malloc(sizeof(ProductAr));  
	//проверка формата файла архива
	FormatFileProduct(fArTxt,fArTxtName,&np,NfMax,
                    Products);
	//проверка формата файла добавления данных в архив
  FormatFileProduct(fAddTxt,fAddTxtName,&nd,NfMax,
                    AddProducts);
	//проверка формата файла кодификатора

  if (FatalError==0)
	{	//фатальных ошибок не было
		//проверка диапазонов данных в исходных файлах
		//CheckProdDiapason(fArTxtName,np,Products);
    //CheckProdDiapason(fAddTxtName,nd,AddProducts);
    //CheckKodifDiapason();
	}

  if (! FatalError)
	{	//фатальных ошибок не было
		//Проверка дублирования параметра Kod в "Kodif.txt"
		//KodifParameters();
		//сортировка массива кодификатора
		//SortKodif(nk);
		//Проверка параметров записей в "input.txt"
    ProdParameters(Products,np,fArTxtName);
		//Проверка параметров записей в "add.txt"
    ProdParameters(AddProducts,nd,fAddTxtName);
    
	}
	if (FatalError) //фатальные ошибки были
    sprintf(Sr,"\nСкорректируйте исходные файлы\n");
  else						//фатальных ошибок не было
    sprintf(Sr,"\nВ исходных файлах ошибок не обнаружено\n");
	fwrite(Sr,sizeof(string80),1,FileError);
	//печать файла результатов проверки
	ReadFileError();
	//Освобождение памяти
	free(Sf); Sf=NULL;
  free(Products);    Products=NULL;
  free(AddProducts); AddProducts=NULL;
  fclose(FileError); //закрывается файл ошибок
} //------CheckFiles()
//-------------------------------------FormatFileProduct()
//Проверка форматов файлов "input.txt" и "add.txt"
void FormatFileProduct(FILE *F, char *FileName, int *nf,
                           int Nmax, ProductAr *Prod)
{       
	ProductType Product;
	char  k;
	int  i,Code;
	char *token;
	char Seps[]=" \t\n";
	string80 Sa;
	//проверка структуры файла *F - входной параметр
	//("input.txt" или "add.txt"), удаление пустых строк
	//и формирование массива строк *Sf из файла
	ReadAndCheckSpaces(F,FileName,nf,Nmax);
  if (FatalError) return;
  for (i=0; i<(*nf); i++)//просмотр массива строк
	{
    strcpy(Sa,(*Sf)[i]);	//копирование i-й строки в рабочую Sa 
		k=0;
		token=strtok(Sa,Seps);	//Выделение первого слова
		while(token!=NULL)			//цикл выделения слов из строки Sa
		{
      	k++;
      	if (k>8)		//слов больше 8 - ошибка
			{
        		FatalError=1;
        		sprintf(Sr,"Файл %s : в строке %d свыше 8 элементов\n",
								FileName,i+1);
				//запись сообщения в файл ошибок
        		fwrite(Sr,sizeof(string80),1,FileError);
			}
    	switch (k) 
			{	//заполнение полей структуры
				case 1:
              	if (strlen(token)>15)//Ед.изм. больше 14 символов
							{ 	FatalError=1;
								sprintf(Sr,
								"Файл %s : в строке %d  длина элемента 1 свыше 15 символов\n",
								FileName,i+1);
								//запись сообщения в файл ошибок
				        		fwrite(Sr,sizeof(string80),1,FileError);
							}
				strcpy(Product.Names,token);
				FillString(Product.Names,20,1); break;
				case 2:
              	if (strlen(token)!=10)//Ед.изм. больше 4 символов
							{ 	FatalError=1;
								sprintf(Sr,
								"Файл %s : в строке %d  длина элемента 2 не равна 10 символам\n",
								FileName,i+1);
								//запись сообщения в файл ошибок
				        		fwrite(Sr,sizeof(string80),1,FileError);
							}
				strcpy(Product.Date,token);
				FillString(Product.Date,13,1); break;
				case 3:
              	if (strlen(token)!=5)//Ед.изм. больше 4 символов
							{ 	FatalError=1;
								sprintf(Sr,
								"Файл %s : в строке %d  длина элемента 3 не равна 5 символам\n",
								FileName,i+1);
								//запись сообщения в файл ошибок
				        		fwrite(Sr,sizeof(string80),1,FileError);
							}
				strcpy(Product.Num,token);
				FillString(Product.Num,5,1); break;
				case 4:
              	if (strlen(token)>21)//Ед.изм. больше 4 символов
							{ 	FatalError=1;
								sprintf(Sr,
								"Файл %s : в строке %d  длина элемента 4 свыше 21 символов\n",
								FileName,i+1);
								//запись сообщения в файл ошибок
				        		fwrite(Sr,sizeof(string80),1,FileError);
							}
				strcpy(Product.Date,token);
				FillString(Product.Date,25,1); break;
				case 5:
              	if (strlen(token)>3)//Ед.изм. больше 3 символов
							{ 	FatalError=1;
								sprintf(Sr,
								"Файл %s : в строке %d  длина элемента 5 свыше 3 символов\n",
								FileName,i+1);
								//запись сообщения в файл ошибок
				        		fwrite(Sr,sizeof(string80),1,FileError);
							}
				strcpy(Product.IsApproved,token);
				FillString(Product.IsApproved,5,1); break;
			}
    //   if ((k!=3) && (Code<1))
	// 		{	//ошибка преобразования слова к числовому параметру
    //     FatalError=1;
    //     sprintf(Sr,
	// "Файл %s : в строке %d неправильный формат элемента %d (%s)\n",
	// 					FileName,i+1,k,token);
	// 				//запись сообщения в файл ошибок
	// 				fwrite(Sr,sizeof(string80),1,FileError);
	// 		}
			token=strtok(NULL,Seps);	//Выделение следующего слова
		}
    if (k<5)
		{	//количество параметров в строке меньше 5
			FatalError=1;
			sprintf(Sr,
				"Файл %s : в строке %d меньше 5 элементов\n",FileName,i+1);
				//запись сообщения в файл ошибок
			fwrite(Sr,sizeof(string80),1,FileError);
		}
    (*Prod)[i]=Product;//добавление структуры в массив
	}
}   //-----FormatFileProduct()
//-------------------------------------ReadAndCheckSpaces()
//Проверка наличия и ввод текстового файла, контроль количества
//строк, и удаление в нем пустых строк 
void ReadAndCheckSpaces(FILE *F, char *FileName, int *nf,
                            int Nmax)
{
	char  i,j;
	char  SignSpace;   // флаг пустых строк в файле нет
	string80 sw;
	char *token;
	char Seps[]=" \t\n";
	char ST[80];
// Проверка наличия файла F с именем FileName 
	if((F=fopen(FileName,"rt"))==NULL)
		{
		 sprintf(Sr,"Отсутствует исходный файл %s\n",FileName);
		 FatalError=1;
		 fwrite(Sr,sizeof(string80),1,FileError);
		 return;
		}

// Чтение текстового файла и запись строк в массив
  *nf=0;
  while (fgets(sw,80,F)!=NULL) 
	{
		if ((*nf)<PMax)
			strcpy((*Sf)[*nf],sw);
		(*nf)++;
	}
  fclose(F);


// Проверка: является ли файл F пустым
  if (*nf==0) 
	{
     FatalError=1;
     sprintf(Sr,"Исходный файл  %s   пустой\n",FileName);
		 fwrite(Sr,sizeof(string80),1,FileError);
     return;
	}

// Проверка: превышает ли кол-во строк максимальное значение 
  if (*nf>NfMax)
	{
    FatalError=1;
		sprintf(Sr,
			"В исходном файле  %s  свыше  %d  строк (%d)\n",
			FileName,NfMax,*nf);
		fwrite(Sr,sizeof(string80),1,FileError);
    return;
	}

// Удаление пустых строк из состава файла F 
  SignSpace=0;
  i=0;
  while (i<(*nf))
	{
		strcpy(ST,(*Sf)[i]);
		token=strtok(ST,Seps);	//Выделение первого слова
    if (token==NULL)
		{	//в строке только пробелы, табуляции и перевод строки
      for (j=i; j<(*nf)-1; j++)//сдвиг массива
        strcpy((*Sf)[j],(*Sf)[j+1]);
      (*nf)--;
      SignSpace=1;//флаг - пустые строки были
		}
    else
      i++;
	}
  if (SignSpace)//были пустые строки
	{	//массив без пустых строк переписывается в файл
		if((F=fopen(FileName,"wt"))==NULL)
		{
		 sprintf(Sr,
			 "Не удалось создать файл %s для удаления пустых строк\n",
			 FileName);
		 FatalError=1;
		 fwrite(Sr,sizeof(string80),1,FileError);
		 return;
		}
    for (i=0; i<(*nf);i++)
		 fputs((*Sf)[i],F);
    fclose(F);
	}

} //-----ReadAndCheckSpaces()
//-------------------------------------ProdParameters()
//Проверка параметров записей в файлах "input.txt" и "add.txt"
void ProdParameters(ProductAr *Prod, int n, char *FileName)
{     
	const char Measurs[2][5] = {{"шт. "},{"кг  "}};
	int  i,j,k,Cond;
	char Kod[5];
	char Meas[5];
	//{ Проверка дублирования параметра KodProduct }
	for (i=0; i<n-1; i++)
		{
		strcpy(Kod,(*Prod)[i].Num);
		//Kod=(*Prod)[i].Num;
		for (j=i+1; j<n; j++)
		if (Kod==(*Prod)[j].Num)
				{ //код дублируется
			FatalError=1;
					sprintf(Sr,
		"Файл %s : равные значения NumProduct в строках %d и %d (%d)\n",
						FileName,i+1,j+1,Kod);
					fwrite(Sr,sizeof(string80),1,FileError);
				}
		}

} //-----ProdParameters()
//-------------------------------------ReportError1()
//Формирование и запись в файл сообщения об ошибке диапазонов int
void ReportError1(char *FileName, int i, int k, int d1,int d2)
{
  FatalError=1;
	sprintf(Sr,
		"Файл %s : в строке %d элемент %d  вне пределов %d .. %d\n",
		FileName,i+1,k,d1,d2);
  fwrite(Sr,sizeof(string80),1,FileError);

} //-----ReportError1()
//-------------------------------------ReportError2()
//Формирование и запись в файл сообщения об ошибке 
//диапазонов double
void ReportError2(char *FileName, int i, int k, 
									double d1, double d2)
{
  FatalError=1;
	sprintf(Sr,
	"Файл %s : в строке %d элемент %d  вне пределов %4.2f .. %6.2f\n",
		FileName,i+1,k,d1,d2);
  fwrite(Sr,sizeof(string80),1,FileError);

}	//-----ReportError2()
//-------------------------------------ReadFileError()
//Чтение и вывод на экран протокола контроля текстовых файлов 
void ReadFileError()
{             
	char i=1;
  rewind(FileError);
	while (i!=EOF)	
	{
		i=fread(Sr,sizeof(string80),1,FileError);
			if (i<1) i = EOF;
			else printf("%s",Sr);
	}
	wait_press_key("\nДля продолжения нажмите любую клавишу\n");
}	//-----ReadFileError() 
