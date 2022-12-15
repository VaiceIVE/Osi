#include <stdio.h>
#include <windows.h>

int main(int argc, char *argv[]) {
	STARTUPINFO s_info;
	PROCESS_INFORMATION p_info;

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(console, FOREGROUND_RED);

	printf("\nMy name is = %s %s\n", argv[1], argv[2]);
	fflush(stdout);

	memset(&s_info, 0, sizeof(STARTUPINFO));
	s_info.cb = sizeof(s_info);
	
	Sleep(270);

	if (!CreateProcess(NULL, "grandChildSecond.exe Petya Vasyliev", NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &s_info, &p_info)) {
		printf("Error CreateProcess: ", GetLastError());
		fflush(stdout);
		getchar();
		return 0;
	}
	
	printf("\n");
	fflush(stdout);
	
	for (int i = 1; i < 100; i++) {
		SetConsoleTextAttribute(console, FOREGROUND_RED);
		printf("I'm a second children. My name is %s %s, my id = %d\n", argv[1], argv[2], i);
		fflush(stdout);
		Sleep(1000);
	}

	CloseHandle(p_info.hProcess);
	CloseHandle(p_info.hThread);

	return 0;
}