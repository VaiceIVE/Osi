#include <stdio.h>
#include <windows.h>

int main() {
    char buffer[100];
    char fileName[] = "new_file.txt";

    DWORD actlen, errorMsg;
    HANDLE hstdout, fhandle;

    COORD coordinates;
    
    coordinates.X = 50;
    coordinates.Y = 13;

    hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(hstdout, coordinates);
    SetConsoleTextAttribute(hstdout, FOREGROUND_GREEN);

    fhandle = CreateFile(fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if(fhandle == INVALID_HANDLE_VALUE) { //смогла открыть файл
        errorMsg = GetLastError(); 
        if (errorMsg == 32) { // код ошибки - не смогла прочитать файл 
            printf("Can't read file!");
            fflush(stdout);

            while(fhandle == INVALID_HANDLE_VALUE) {
                Sleep(3000);// каждые 3с идет проверка
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