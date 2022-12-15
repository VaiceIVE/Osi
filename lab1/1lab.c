#include <windows.h>
#include <stdio.h>

void main()
{
char buffer[85] = "Open sourse: ";
char buffer2[85] = "Enter text: ";
int len;
DWORD cb,cbw1;
HANDLE handin, handout;
BOOL rc;

len=strlen(buffer);//длинна текста внутри буфера


handout = GetStdHandle(STD_OUTPUT_HANDLE);// получение хендла вывода

if (handout == INVALID_HANDLE_VALUE) return;//ловим неверный хендл

printf("HandlesOfOut: %d \r\n", handout);//выводим число хендлов

fflush(stdout);//перенос текста на следующую строку

handin = GetStdHandle(STD_INPUT_HANDLE);//получение хендла ввода

if (handin == INVALID_HANDLE_VALUE) return;//ловим неверный хендл

printf("HandlesOfInput: %d \r\n", handin);//выводим число хендлов

fflush(stdout);

printf("Enter text: ");//приглашение на ввод текста

fflush(stdout);

rc = ReadFile(handin, buffer+len, 80, &cb, NULL);//чтение из файла

if(!rc) return;//если файл не читается 

cb += len;

WriteFile(handout, buffer, cb, &cbw1, NULL);//небуферизированный вывод текста с предуведомлением

fflush(stdout);

getchar();//чтение символов из стандартного потока ввода

return;
}