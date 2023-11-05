#include "menu.h"

static struct termios orig_termios;

void disableRaw(){
	curson();
	tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

int setRaw() {
	struct termios raw;
	int c;
	cursoff();
	atexit(disableRaw);
 	tcgetattr(STDIN_FILENO, &orig_termios);
	raw = orig_termios;
	cfmakeraw(&raw);
	c = tcsetattr(STDIN_FILENO, TCSANOW, &raw);
	return c;
}

int main(){
	int retour;
	const char *const path = "../menu_csv/";
	DIR *dir;
	dir = opendir(path);
	if (dir == NULL){
		printf("'%s' n'est pas le dossier de version valide\n\r", path);
		return 0;
	}
	setRaw();
	retour = BrowseMenu("main.csv","main");
	if(loadedSave!=NULL)
		free(loadedSave);
	printf("\n\rRetour : %d\n\r",retour);
	return retour;
}