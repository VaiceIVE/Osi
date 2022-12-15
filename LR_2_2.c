#include <stdio.h>
#include <windows.h>

void main() {
	char buf[100] = ""; // буфер, который будет хранить счиатываемый текст из файла 
	char fileName[]="Out_from_2_2.txt";
    const int len = 7; // 7 байт 

	DWORD actlen; 
	HANDLE hstdin, hstdout;
    HANDLE fileHandleFirst, fileHandleSecond, fileHandleThird;//три ссылки на 1 файл 
    
	hstdin = GetStdHandle(STD_INPUT_HANDLE);//открываем хендл на чтение
	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);// на запись 
	fileHandleFirst = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ || FILE_SHARE_WRITE, //открываем файл на чтение
                                 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	
	DuplicateHandle (GetCurrentProcess(), fileHandleFirst, // копируем ссылку на 1 хендл 
                     GetCurrentProcess(), &fileHandleSecond,// вставляем ссылку на 2 хендл
                     0, FALSE, DUPLICATE_SAME_ACCESS);// с теми же правами
	
	fileHandleThird = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ || FILE_SHARE_WRITE, //второй открывается ффайл
                                 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (fileHandleThird == INVALID_HANDLE_VALUE) return;

	printf("%d\n%d\n%d\n", fileHandleFirst, fileHandleSecond, fileHandleThird);	//выводим значения хендлов
    fflush(stdout);

	SetFilePointer(fileHandleFirst, 10, 0, FILE_BEGIN);//хендл будет считывать на 10 символов вперед относительно начала файла (считываем сначала файла ) 

	if (!ReadFile(fileHandleFirst, buf, 90, &actlen, NULL)) return;//счиытвает данные и выводит строчки в консооль
	WriteFile(hstdout, buf, len, &actlen, NULL);
	printf("\n");
    fflush(stdout);

	if (!ReadFile(fileHandleSecond, buf, 90, &actlen, NULL)) return;
	WriteFile(hstdout, buf, len, &actlen, NULL);
	printf("\n");
    fflush(stdout);

	if (!ReadFile(fileHandleThird, buf, 90, &actlen, NULL)) return;
	WriteFile(hstdout, buf, len, &actlen, NULL);
    printf("\n");
    fflush(stdout);

	CloseHandle(fileHandleFirst);
	CloseHandle(fileHandleSecond);
	CloseHandle(fileHandleThird);
	
	getchar();
}