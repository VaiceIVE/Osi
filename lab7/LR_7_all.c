#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <unistd.h>

char alphabet[] = "abcdefghijklmnopqrst";

void thread(void *arg) {
	int intValue = (int)(uintptr_t)arg;

	if (intValue == 1 || intValue == 3) {
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	}

	for (int k = 0; k < 21; ++k) {
		printf("\033[%d;%d0H\033[1;3%dm", k + 1, 2 * intValue, 5 - intValue);
		
		for (int j = 0; j < intValue * 2; ++j) {
			printf("%c", alphabet[k]);
		}

		printf("\n");

		if (k == 12 && intValue == 3) {
			pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
			pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
		}

		if (k == 15 && intValue == 3) {
			usleep(1000000 + 750000 * intValue);
			pthread_testcancel();
		}

		else {
			usleep(1000000 + 500000 * (3 - intValue));
		}
	}
}

void main() {
	pthread_t tid1, tid2, tid3;

	printf("\033[2J\n");
	if (pthread_create(&tid1, NULL, (void *)thread, (void *)1) != 0) {
		printf("Error: start first thread failed");
		return;
	}

	if (pthread_create(&tid2, NULL, (void *)thread, (void *)2) != 0) {
		printf("Error: start second thread failed");
		return;
	}

	if (pthread_create(&tid3, NULL, (void *)thread, (void *)3) != 0) {
		printf("Error: start third thread failed");
		return;
	}

	for (int k = 0; k < 21; ++k) {
		printf("\033[%d;1H\033[1;37m", k + 1);
		printf("%c\n", alphabet[k]);
		if (k == 5) {
            if (pthread_cancel(tid1) == 0) {
                printf("\033[25;1H\033[1;34mFirst thread canceled");
            } else {
                printf("\033[25;1H\033[1;34mError: thread not canceled");
            }
        }

        if (k == 10) {
            if (pthread_cancel(tid3) == 0) {
                printf("\033[25;1H\033[0J\033[1;32mThird thread canceled");
            } else {
                printf("\033[25;1H\033[1;32mError: failed to cancel third thread");
            }
        }
		usleep(1500000);
	}
	getchar();
}
