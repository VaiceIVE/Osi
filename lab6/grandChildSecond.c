#include <stdio.h>
#include <windows.h>

int main(int argc, char *argv[]) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN);

	printf("\nMy name is = %s %s\n", argv[1], argv[2]);
	fflush(stdout);

	Sleep(300);

	for (int i = 1; i < 100; ++i) {
		SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN);
		printf("I'm a second grand children. I'm %s %s, id = %d\n", argv[1], argv[2], i);
		fflush(stdout);
		Sleep(1000);
	}

	return 0;
}