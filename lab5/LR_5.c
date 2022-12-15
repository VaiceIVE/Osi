#include <windows.h>
#include <stdio.h>
#include <wincon.h>

void main() {
	HANDLE fileHandle, handleIn, handleOut;
	DWORD cbw = 0, cbRead;
	INPUT_RECORD inputBuffer;
	COORD pos_1, pos_2, pos_3, outCoordPos, writePos;
    
    short winWeight = 100, winHeight = 30; 
	char fileName[50], buf[255], buffer[4];
	char ch, newChar;

	//Дескриптор устройства стандартного вывода. Вначале, это - дескриптор активного экранного буфера консоли
	//Дескриптор стандартного устройства ввода данных. Вначале, это - дескриптор консольного буфера ввода
	
	handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	handleIn  = GetStdHandle(STD_INPUT_HANDLE);

   	if (handleIn == INVALID_HANDLE_VALUE || handleOut == INVALID_HANDLE_VALUE) {
        return;
    }
    
    printf("Input file name: ");

    scanf("%s", &fileName);
    fflush(stdout);

	fileHandle = CreateFile( fileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

  	if(fileHandle==INVALID_HANDLE_VALUE) {
		printf("File not found!\n");
        Sleep(5000);
        return;
    }

	do {
		if(!ReadFile(fileHandle, buffer, 4, &cbRead, NULL)) {
            printf("Can't read file!\n");
            Sleep(5000);
            return;
        }	
		WriteFile(handleOut, buffer, cbRead, &cbRead, NULL);    
	} while (cbRead != 0);
	
	printf("\n");
	
	// дескриптор экранного буфера или буфера ввода консоли
    // режим ввода или вывода данных

	SetConsoleMode(handleIn, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);//обработка нажатий мышки

	inputBuffer.EventType = MOUSE_EVENT;
	
    while(TRUE) {      
  		if(ReadConsoleInput(handleIn, &inputBuffer, 1, &cbw)) {
			if (inputBuffer.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) { //правая нажата - выход
                return;
            }
            
			outCoordPos.Y = winHeight - 2;
			outCoordPos.X = 1;

     		pos_3.Y = winHeight - 1;
			pos_3.X = 1;
			
			if (inputBuffer.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {  //обработка нажатия левой кнопки
                pos_1.X = inputBuffer.Event.MouseEvent.dwMousePosition.X;
                pos_1.Y = inputBuffer.Event.MouseEvent.dwMousePosition.Y;

                writePos.X = inputBuffer.Event.MouseEvent.dwMousePosition.X;
                writePos.Y = inputBuffer.Event.MouseEvent.dwMousePosition.Y;

                ReadConsoleOutputCharacter(handleOut, &ch, 1, pos_1, &cbw);// читается символ 
                ReadConsoleOutputCharacter(handleOut, &newChar, 1, pos_1, &cbw);// читается символ 
					
				if (ch != ' ') { 
					FillConsoleOutputAttribute(handleOut, 0x00, winWeight, pos_3, &cbw);

       				for (int i = 0; i < cbw; ++i) {
						buf[i]=' ';//очищ буфер 
					}

					WriteConsoleOutputCharacter(handleOut, buf, strlen(buf), pos_3, &cbw);//записывается слово

					SetConsoleCursorPosition(handleOut, outCoordPos);

					SetConsoleCursorPosition(handleOut, outCoordPos);
       				printf("%d, %d", pos_1.X, pos_1.Y);
                    
					pos_2 = pos_1;

					if (newChar <= 'Z' && newChar >= 'A') { 
						newChar += 32;
						SetConsoleCursorPosition(handleOut, writePos);
						printf("%c", newChar);
					} else if (newChar <= 'z' && newChar >= 'a') {
						newChar -= 32;
						SetConsoleCursorPosition(handleOut, writePos);
						printf("%c", newChar);
					}
                    
                    FillConsoleOutputAttribute(handleOut, BACKGROUND_RED, 1, pos_1, &cbw);
       		
        			ReadConsoleOutputCharacter(handleOut, &ch, 1, pos_2, &cbw);
       			
       				ReadConsoleOutputCharacter(handleOut, buf, cbw, pos_1, &cbw);
                    WriteConsoleOutputCharacter(handleOut, buf, cbw, pos_3, &cbw);

       				FillConsoleOutputAttribute(handleOut, BACKGROUND_GREEN, cbw, pos_3, &cbw);
       			}
    		}
  		}
	}
}          