#include "State.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Face.h"
#include "Vec2.h"

#include <cstdlib>
#include <cmath>

State::State(){
	quitRequested = false;

	bg = new Sprite();

	tileSet = new TileSet(64, 64, "img/tileset.png");
	tileMap = new TileMap("map/tileMap.txt", tileSet);
}

State::~State(){
	delete(bg);
	objectArray.clear();
}

void State::LoadAssets(){
	bg->Open("img/ocean.jpg");
}
/*
void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while(SDL_PollEvent(&event)){

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}

		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {
			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; i--){
				// Obtem o ponteiro e casta pra Face.
				Face *face = (Face*) objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if(face->box->IsInside((double)mouseX, (double)mouseY)){
					// Aplica dano
					face->Damage(rand() % 10 + 10);
					// Sai do loop (só queremos acertar um)
					break;
				}
			}
		}

		if(event.type == SDL_KEYDOWN){
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ){
				quitRequested = true;
			}
			// Se não, crie um objeto
			else{
				AddObject((double)mouseX, (double)mouseY);
			}
		}
	}
}
*/

void State::Update(){
	static InputManager inputManager = InputManager::GetInstance();
	
	if(inputManager.KeyPress(SDLK_ESCAPE)){
		quitRequested = true;
	}

	if(inputManager.KeyPress(SDLK_SPACE)){
		AddObject((double)inputManager.GetMouseX(), (double)inputManager.GetMouseY());
	}

	for(int i = 0; i < (int) objectArray.size(); i++){
		if(objectArray[i]->IsDead())
			objectArray.erase(objectArray.begin() + i);
	}

	for(auto it = objectArray.begin(); it < objectArray.end(); it++){
		if((*it)->IsDead())
			objectArray.erase(it);
	}
}

void State::Render(){
	bg->Render(0, 0);
	tileMap->Render(0, 0);

	for(auto &it : objectArray){
		it->Render();
	}
}

void State::AddObject(double mouseX, double mouseY){
	double angle = ((rand() % 360) * acos(-1))/180.0;

	Vec2 *vec = new Vec2(mouseX, mouseY);

	vec = vec->translate(200, 0);
	vec = vec->rotate(angle, mouseX, mouseY);

	Face *face = new Face(vec->x, vec->y);

	delete(vec);

	objectArray.emplace_back(face);
}

bool State::QuitRequested(){
	return quitRequested;
}
