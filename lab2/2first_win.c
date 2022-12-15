#include <windows.h>
#include <stdio.h>

void main() {
    char buf[100];
	char fileName[]="FileOutput.txt";

	DWORD actlen;
	HANDLE hstdin, fileHandle;
	
	hstdin = GetStdHandle(STD_INPUT_HANDLE);// получаем хендл для ввода
	if (hstdin == INVALID_HANDLE_VALUE) return;

	fileHandle = CreateFile(fileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, // Открывает консоль для вывода данных. данные атрибуты позволяют открывать файл всем программам, когда наша программа использует данные файл
                            0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0); // Создает новый файл. Если файл существует, функция переписывает файл, У файла нет других установленных атрибутов. Этот атрибут допустим только в том случае, если он используется один.
	if (fileHandle == INVALID_HANDLE_VALUE) return;

    printf("Enter text:\n"); // Вывод строки (строка записывается в буфер)
    fflush(stdout);//Сброс буфера (строка отобразится в консоли)

	if (!ReadFile(hstdin, buf, 90, &actlen, NULL)) return;

	WriteFile(fileHandle, buf, actlen, &actlen, NULL);
    

	CloseHandle(fileHandle);
    
}