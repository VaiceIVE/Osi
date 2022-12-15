#include <stdio.h>
#include <windows.h>

int main() {
	STARTUPINFO s_info_1, s_info_2;
	PROCESS_INFORMATION p_info_1, p_info_2;
	HANDLE handleProcess_1, handleProcess_2;

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	printf("Set window full size and press any key...");
	getchar();

	printf("I'm parent! My name is Vladilen!\n\n");
	fflush(stdout);

	Sleep(2000);

	memset(&s_info_1, 0, sizeof(STARTUPINFO));
	s_info_1.cb = sizeof(s_info_1);

	if (!CreateProcess(NULL, "childFirst.exe Ivan Vladilenov", NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &s_info_1, &p_info_1)) {
		printf("Error CreateProcess: ", GetLastError());
		fflush(stdout);
		getchar();
		return 0;
	}

	handleProcess_1 = CreateJobObject(NULL, NULL);
	AssignProcessToJobObject(handleProcess_1, p_info_1.hProcess);

	Sleep(930);

	memset(&s_info_2, 0, sizeof(STARTUPINFO));
	s_info_2.cb = sizeof(s_info_2);

	if (!CreateProcess(NULL, "childSecond.exe Vasya Vladilenov", NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &s_info_2, &p_info_2)) {
		printf("Error CreateProcess: ", GetLastError());
		fflush(stdout);
		getchar();
		return 0;
	}
	
	handleProcess_2 = CreateJobObject(NULL, NULL);
	AssignProcessToJobObject(handleProcess_2, p_info_2.hProcess);

	for (int i = 1; i < 13; ++i) {
		SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_BLUE);
		SetConsoleTextAttribute(console, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
		printf("Parent Iterator: %d\n", i);
		SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		SetConsoleTextAttribute(console, BACKGROUND_BLUE | BACKGROUND_RED);
		fflush(stdout);

		if (i == 7) {
			fflush(stdout);
			TerminateJobObject(handleProcess_1, 0);
			SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			printf("First children was killed\n");
		}

		if (i == 11) {
			fflush(stdout);
			TerminateJobObject(handleProcess_2, 0);
			SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			printf("Second children was killed\n");
		}

		Sleep(3000);
	}

	SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	CloseHandle(p_info_1.hProcess);
	CloseHandle(p_info_1.hThread);
	CloseHandle(p_info_2.hProcess);
	CloseHandle(p_info_2.hThread);
	printf("All done!");
	getchar();
	return 0;
}