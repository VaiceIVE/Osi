#include <stdio.h>
#include <windows.h>

int main() {
    char buffer[100];// заводим буфер
    char fileName[] = "new_file.txt";

    DWORD actlen, errorMsg;
    HANDLE hstdout, fhandle;

    COORD coordinates;
    
    coordinates.X = 50;
    coordinates.Y = 13;

    //Дескриптор устройства стандартного вывода. Вначале, это - дескриптор активного экранного буфера консоли

    hstdout = GetStdHandle(STD_OUTPUT_HANDLE); 

    SetConsoleCursorPosition(hstdout, coordinates); // дескриптор экранного буфера / координаты нового курсора
    SetConsoleTextAttribute(hstdout, FOREGROUND_GREEN); // дескриптор экранного буфера / цвет текста и фона

    fhandle = CreateFile(fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if(fhandle == INVALID_HANDLE_VALUE) {
        errorMsg = GetLastError(); //извлекает значение кода последней ошибки вызывающего потока
        if (errorMsg == 32) {
            printf("Can't read file!");
            fflush(stdout);

            while(fhandle == INVALID_HANDLE_VALUE) {
                Sleep(3000);
                printf(".");
                fhandle = CreateFile(fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
            }
        }
    }

    if (!ReadFile(fhandle, buffer, 100, &actlen, NULL)) {
        return -1;
    }
    WriteFile(hstdout, buffer, actlen, &actlen, NULL);
    getch();
    CloseHandle(fhandle);
}