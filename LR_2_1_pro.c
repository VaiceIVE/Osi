#include <windows.h>
#include <stdio.h>

void main() {
    char buf[100]; //заводится буфер для сохранения текста 
	char fileName[]="Out_from_2_2.txt"; //имя файла

	DWORD actlen; //используется для хранения ссылок на хендлы
	HANDLE hstdin, fileHandle; //для хранения ссылок
	
	hstdin = GetStdHandle(STD_INPUT_HANDLE); //получить ссылку на хендел который будет считаывать вводимую инфу
	if (hstdin == INVALID_HANDLE_VALUE) return;// если ссылка битая, то завершаем работу 

	fileHandle = CreateFile(fileName, GENERIC_WRITE, FILE_SHARE_READ || FILE_SHARE_WRITE, //в файл хендл записываем ссылку
                            0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);// имя,параментры которые настраивает, можно открыть в др. программе
	if (fileHandle == INVALID_HANDLE_VALUE) return; // если не получилось создать файл то завершаем прогу 

    printf("Enter text:\n"); // выводим в консоль
    fflush(stdout); //очищает буфер

	if (!ReadFile(hstdin, buf, 90, &actlen, NULL)) return; //функция отвечает за сохранение текста (из консоли в буфер), &actlen - то число символов которое мы ввели 

	WriteFile(fileHandle, buf, actlen, &actlen, NULL);//записывает из буфера в файл.  беерт хендл, буфер, число символов, кол-во из буфера, обнуляем значения
    
	CloseHandle(fileHandle); //закрываем хендл, чтобы не было утечки памяти
    
}