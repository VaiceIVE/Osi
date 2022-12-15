#include <stdio.h>
#include <fcntl.h>

void main(){
	int fhandle1, // хэндлы
    fhandle2,     
    fhandle3,    
    kolch;       // количество прочитанных байтов
	char handle_handler[50]; // массив символов для хранения текста
	
	fhandle1 = open("datafile", O_RDONLY); // открытие файла для чтения и передача хэндла переменной fhandle1
	fhandle2 = dup(fhandle1);	 // предоставляем доступ к блоку где обрабатывается файл, fhandle1
	fhandle3 = open("datafile", O_RDONLY); // открытие файла для чтения и передача хэндла переменной fhandle3
    // запись в массив хэндлов и вывод их поочередно
    kolch = sprintf(handle_handler, "%d handle1\n", fhandle1);
    write(1, handle_handler, kolch);
    kolch = sprintf(handle_handler,"%d handle2\n", fhandle2);
    write(1, handle_handler,kolch);
    kolch = sprintf(handle_handler,"%d handle3\n", fhandle3);
    write(1, handle_handler, kolch);    
    /*
    lseek. Функция имеет три аргумента, в первом указывается файловый дескриптор (хэндл),
    второй задает величину используемого в ней смещения, последний обозначает точку отсчета
    для этого смещения – от начала файла, от предыдущего позиции или от конца
    файла.
    Образуется два управляющих блока. В первом 1 и 2 хэндл, во втором 3. Что объясняется результат.
    SEEK_SET - Смещение отсчитывается от начала файла
    */
	lseek(fhandle2, 10, SEEK_SET);  
    // чтение с файла 7 символов  - хэндл 1
    kolch=read(fhandle1, handle_handler, 7);	
    // вывод на экран консоли прочитанное
	write(1, handle_handler, kolch);    
    
    // чтение с файла 7 символов - хэндл 2
	kolch=read(fhandle2, handle_handler, 7);
    // вывод на экран консоли прочитанное
	write(1, handle_handler, kolch);

    // чтение с файла 7 символов - хэндл 3
	kolch=read(fhandle3, handle_handler, 7);	
     // вывод на экран консоли прочитанное
	write(1, handle_handler, kolch);
 
}
