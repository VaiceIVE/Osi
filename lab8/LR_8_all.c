#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <process.h>

HANDLE handleMutexWhite, handleMutexRead, hout;

CRITICAL_SECTION csec;

int N = 0;

char memoryBuffer[14];

char *allCity[] = { "Novosibirsk", "Semipalatink", "Ekaterinburg" };

void writeThread(void *arg) { //записывает в буфер
    int *arr = (int *)arg;
    while (TRUE) {
        WaitForSingleObject(handleMutexWhite, INFINITE); // пока буфер не станет свободный
        for (int i = 0; i < 12; ++i) {
            memoryBuffer[i] = allCity[arr[1]][i];  //записываем буквы города
        }
        ReleaseSemaphore(handleMutexWhite, 1, NULL); // записали в буфер и освобождаем его
        Sleep(100 * (int)(uintptr_t)arr[0]); // передаем массив. у каждого потока своя задержка,
    }
}

void readThread(void *arg) {
    int *arr = (int *)arg;
    COORD pos;
    for (int i = 0; i < 23; ++i) { // чтобы вывести к-н текст на консоль
        WaitForSingleObject(handleMutexRead, INFINITE);// ждем пока освободится консоль чтобы ввести в нее тест
        ++N;
        if (N == 1) {
            WaitForSingleObject(handleMutexWhite, INFINITE); // ждем пока в буфер запишется текст
        }

        ReleaseMutex(handleMutexRead); // чтобы он мог заполнять неск столбцов
        pos.X = arr[1];
        pos.Y = i;

        EnterCriticalSection(&csec); //критическая область в консоле
        SetConsoleCursorPosition(hout, pos); //хендл для вывода текста в консоль
        printf(memoryBuffer, "\n");
        LeaveCriticalSection(&csec);
        WaitForSingleObject(handleMutexRead, INFINITE);

        --N; // кол-во потоков которые занимают ресурс
        if (N == 0) {
            ReleaseSemaphore(handleMutexWhite, 1, 0); //может занять след потом
        }

        ReleaseMutex(handleMutexRead); // для освобождения объекта handleMutexRead, что ресурсы свободны для вывода в консоль
        Sleep(arr[2] * arr[0]);
    }
}

void main() {
    system("cls");
    HANDLE hWriteThread1, hWriteThread2, hWriteThread3;
    HANDLE hReadThread1, hReadThread2, hReadThread3;

    unsigned long writeThreadId1, writeThreadId2, writeThreadId3; // адрес потока
    unsigned long readThreadId1, readThreadId2, readThreadId3;

    hout = GetStdHandle(STD_OUTPUT_HANDLE);

    int sleepTime1 = 60; // для писателей
    int sleepTime2 = 3; // для читателей

    int firstArgsWrite[] = { sleepTime1, 0 };// создаем массив где будут лежать аргументы
    int secondArgsWrite[] = { sleepTime1, 1 };
    int thirdArgsWrite[] = { sleepTime1, 2 };
    
    int firstArgsRead[] = { sleepTime2, 20, 300 };
    int secondArgsRead[] = { sleepTime2, 40, 400 };
    int thirdArgsRead[] = { sleepTime2, 60, 350 }; // позиция, время в мс

    InitializeCriticalSection(&csec); // создаем крит обл

    handleMutexWhite = CreateSemaphore(NULL, 1, 1, "writing"); // создаем MutexW, свободные ресурсы или нет. только 1 поток может восполь
    handleMutexRead = CreateMutex(NULL, FALSE, "reading"); // никто не владеет резурсом
	
    // если не получилось создать 
    if (handleMutexWhite == NULL) {
        printf("Mutex=%d\n", handleMutexWhite);
        getchar();
        return;
    }

    if (handleMutexRead == NULL) {
        printf("Mutex=%d\n", handleMutexRead);
        getchar();
        return;
    }

    //1 поток на запись в буфер. 4,096КБ,передаем ф-цию которая будет выполняться в этом потоке, аргументы которые нужны для функции,0, передаем переменную,чтобы записать адрес созданного потока
    //1 поток вывод текста в консоль
    hWriteThread1 = (HANDLE) _beginthreadex(NULL, 4096, (void *)writeThread, (void *)firstArgsWrite, 0, (void *)&writeThreadId1);
    hReadThread1 = (HANDLE) _beginthreadex(NULL, 4096, (void *)readThread, (void *)firstArgsRead, 0, (void *)&readThreadId1);

    hWriteThread2 = (HANDLE) _beginthreadex(NULL, 4096, (void *)writeThread, (void *)secondArgsWrite, 0, (void *)&writeThreadId2);
    hReadThread2 = (HANDLE) _beginthreadex(NULL, 4096, (void *)readThread, (void *)secondArgsRead, 0, (void *)&readThreadId2);

    hWriteThread3 = (HANDLE) _beginthreadex(NULL, 4096, (void *)writeThread, (void *)thirdArgsWrite, 0, (void *)&writeThreadId3);
    hReadThread3 = (HANDLE) _beginthreadex(NULL, 4096, (void *)readThread, (void *)thirdArgsRead, 0, (void *)&readThreadId3);

    getchar();

    DeleteCriticalSection(&csec);

    CloseHandle(hWriteThread1);
    CloseHandle(hWriteThread2);
    CloseHandle(hWriteThread3);

    CloseHandle(hReadThread1);
    CloseHandle(hReadThread2);
    CloseHandle(hReadThread3);

    CloseHandle(handleMutexWhite);
    CloseHandle(handleMutexRead);
    CloseHandle(hout);
}