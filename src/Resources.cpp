#include "Resources.h"
#include "Game.h"

std::unordered_map <std::string, std::shared_ptr <SDL_Texture> > Resources::imageTable;

std::shared_ptr <SDL_Texture> Resources::GetImage(std::string file){
	if(imageTable.find(file)==imageTable.end()){
		SDL_Texture *texture = IMG_LoadTexture(Game::GetInstance()->GetRenderer(), file.c_str());

		if(not texture){
			printf("Erro ao carregar imagem: %s\n", SDL_GetError());
			exit(1);
		}

		shared_ptr<SDL_Texture> ptr(texture, [](SDL_Texture *t){ SDL_DestroyTexture(t); });

		imageTable.emplace(file, ptr);
	}
		
	return imageTable[file];
}

void Resources::ClearImages(){
	for(auto it = imageTable.begin(); it != imageTable.end(); it++){
		if(it->second.unique())
			imageTable.erase(it);
	}
}
