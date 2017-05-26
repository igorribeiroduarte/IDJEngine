#include "Game.h"
#include "StageState.h"
#include "TitleState.h"

using namespace std;

int main(int, char **){
	Game game("Igor Duarte, 14/0098275", 1024, 600);	

	game.Push(new TitleState());

	game.Run();

	return 0;
}
