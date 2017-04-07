#include "Resources.h"
#include "Game.h"

std::unordered_map <std::string, SDL_Texture *> Resources::imageTable;

SDL_Texture *Resources::GetImage(std::string file){
	if(imageTable.find(file)==imageTable.end())
		imageTable.emplace(file, IMG_LoadTexture(Game::GetInstance()->GetRenderer(), file.c_str()));
		
	return imageTable[file];
}

void Resources::ClearImages(){
	for(auto &image : imageTable){
		SDL_DestroyTexture(image.second);
	}

	imageTable.clear();
}
