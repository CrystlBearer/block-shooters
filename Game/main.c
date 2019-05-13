#include "GameMain.h"


int main(int argc, char *argv[]) {
	puts("Would you like to play the game? Y/N");
	char response;
	scanf_s("%c",&response);
	if (response == 'Y') {
		start_menu();
	}
	return 0;
}
