#include <stdio.h>
#include <fcntl.h>

int main(){
	char char_massive[50]; // массив для хранения текста
	int kolch; // целое число являющеся количеством прочитанных байтов
	int fhandle; // хэндл файла
	/*    
    Открытие файла
    O_WRONLY - Открываем для записи
    O_CREAT - Создаем файл если он не существует
    O_TRUNC - Если файл есть, то обнуляем данные в нем
    0777 - Каждый может читать, писать и выполнять файл
    */
    fhandle=open("datafile", O_WRONLY | O_CREAT | O_TRUNC, 0777); 
    /*
    записываем в массив строку и выводим с помощью функции write
    */
    kolch = sprintf(char_massive,"Enter text:\n");
    write(1, char_massive, kolch);
    /*
    Читаем с пользовательского ввода
    Возвращает реальное количество прочитаных байт
    */
	kolch=read(0, char_massive, 50);
    /*
    запись в файлы
    */
	write(fhandle, char_massive, kolch);
	close(fhandle);   // закрытие файла
    return 0;
}
