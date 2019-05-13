#include "GameMain.h"
#define MAX_PATH_LENGTH 80


int bubblesort(int * scores, int *counter) {
	for (int c = 0; c < *counter - 1; c++) {
		for (int i = 0; i < *counter-1; i++) {
			//printf_s("scores[%d] = %d | scores[%d] = %d\n",i,scores[i],i+1,scores[i+1]);
				if (scores[i] < scores[i + 1]) {
					int temp = scores[i];
					scores[i] = scores[i + 1];
					scores[i + 1] = temp;
				}
		} 
	}
	return 0;
}


int main(int argc, char *argv[]) {
	puts("Would you like to play the game? Y/N");
	char response;
	scanf_s("%c",&response);
	int result = 0;
	int scores[50] = { 0 };
	int counter = 0;
	if (response == 'Y') {
		result = start_menu(scores,&counter);
		if (result == 0) {
			bubblesort(scores,&counter);
			FILE *cfPtr;
			errno_t err;
			if ((err = fopen_s(&cfPtr,"game_log.txt", "w+")) != 0) {
				puts("FILE could not be opened!");
			}
			else {
				for (int i = 0; i < counter; i++) {
					char buff[50];
					sprintf_s(buff, 50, "%d\n", scores[i]);
					fprintf(cfPtr, buff);

				}
				fclose(cfPtr);
			}
		}
	}
	
	return 0;

}
