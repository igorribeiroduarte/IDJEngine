#include "State.h"

#include "Sprite.h"

State::State(){
	quitRequested = false;
	bg = new Sprite();
}

State::~State(){
	delete(bg);
	objectArray.clear();
}

void State::LoadAssets(){
	bg->Open("res/img/ocean.jpg");
}

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
				Face* face = (Face*) objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if(face->box.IsInside((float)mouseX, (float)mouseY)){
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
				AddObject((float)mouseX, (float)mouseY);
			}
		}
	}
}

void State::Update(){

}

void State::Render(){
	bg->Render(0, 0);
}

bool State::QuitRequested(){
	return quitRequested;
}
