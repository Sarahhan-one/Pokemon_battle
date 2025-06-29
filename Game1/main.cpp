#include "Tools.h"
#include "GameManager.h"
#include "conio.h"

int main() {
	GameManager gameManager;


	cout << "계속하려면 아무 키나 누르세요...";
	(void)_getch();
	
	while (true) {
		gameManager.update();
	}

	return 0;
}