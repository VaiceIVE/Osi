#include <windows.h>
#include <stdio.h>
#include <wincon.h>

void main() {
	int i, x, y;
	HANDLE fhandle, handlein, handleout, hW, hR;
	DWORD cbw = 0, length, rc, cbr;
	INPUT_RECORD infoCursor;
	COORD posOfSymbR, posOfSymbW, CoordPos;//там где пользователь тыкнул,позиция гдебудем писать, где будут отображаться коорд символа 
	char fname[30], buffer[4], symb[1];
	char ch, newChar;
	
	short color = BACKGROUND_RED | BACKGROUND_INTENSITY;
	
	handleout = GetStdHandle( STD_OUTPUT_HANDLE );//для написания хендл
	handlein  = GetStdHandle( STD_INPUT_HANDLE );//для чтения хендл
   	if(handlein == INVALID_HANDLE_VALUE || handleout==INVALID_HANDLE_VALUE) {
        return;
    }
    
	fhandle = CreateFile( "text.txt", GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );
  	if(fhandle==INVALID_HANDLE_VALUE) {
		printf("File not found\n");
		Sleep(5000);
		return;
    }

	do {
		rc = ReadFile(fhandle, buffer, 1, &cbr, NULL);	//считали из файлика
		WriteFile(handleout, buffer, cbr, &cbr, NULL);    //записали в консоль
	} while (cbr != 0);
	
	printf("\n");
	
	SetConsoleMode(handlein, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);//обработка нажатий мышки
	infoCursor.EventType = MOUSE_EVENT;
	while(1) {      
  		if(ReadConsoleInput(handlein, &infoCursor, 1, &cbw)) {
			if(infoCursor.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) return;//проверка на наэжатие правой мыши
			CoordPos.Y = 28;
			CoordPos.X = 57;
     		posOfSymbW.Y = 28;
			posOfSymbW.X = 10;
			
			if(infoCursor.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) { //обработка нажатия левой кнопки
       				posOfSymbR.X = infoCursor.Event.MouseEvent.dwMousePosition.X;
       				posOfSymbR.Y = infoCursor.Event.MouseEvent.dwMousePosition.Y;//получаем координаты символа на который тыкнули
       				ReadConsoleOutputCharacter(handleout, &ch, 1, posOfSymbR, &cbw);//считали сам символ
					
				if(ch!=' ' & (posOfSymbR.Y!=posOfSymbW.Y)) {// проверяем что это не пробел и не информационная строка
					SetConsoleCursorPosition(handleout, CoordPos);
					printf("      ");//ощищаем старые координаты на экране 
					SetConsoleCursorPosition(handleout, CoordPos);
       				printf("%d,%d",posOfSymbR.X,posOfSymbR.Y);//пишем координаты символа 
					newChar=ch;
					// в зависимости от регистра, изменяем его регистр уменьшая на 32 или прибавляя 32(тб аскии)
					if(newChar <= 'Z' && newChar >= 'A')
					{ 	
						newChar += 32;//получаем новый символ
						SetConsoleCursorPosition(handleout, posOfSymbR);//устанавливает позицию вывода
							printf("%c", newChar);
					}
					else if(newChar <= 'z' && newChar >= 'a')
					{	
						newChar -= 32;// получаем новый символ
						SetConsoleCursorPosition(handleout, posOfSymbR);// устанавливаем позицию вывода
							printf("%c", newChar);
					}
					symb[0]=newChar;//массив сохраняем ма
					cbw=1;	  //кол-во считыв символов
                    WriteConsoleOutputCharacter(handleout, symb, 1, posOfSymbW, &cbw);//пишем символ в информационной строке
       				FillConsoleOutputAttribute(handleout, color, 1, posOfSymbR, &cbw);//красим цветом
       			}
    		}
  		}
	}
}        
