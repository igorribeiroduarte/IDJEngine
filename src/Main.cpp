#include "Game.h"
#include "StageState.h"

using namespace std;

int main(int argc, char **argv){
	Game game("Igor Duarte, 14/0098275", 1024, 600);	

	game.Push(new StageState());

	game.Run();

	return 0;
}
