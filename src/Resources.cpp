#include "Resources.h"
#include "Game.h"

std::unordered_map <std::string, std::shared_ptr <SDL_Texture> > Resources::imageTable;
std::unordered_map <std::string, std::shared_ptr <Mix_Music> > Resources::musicTable;
std::unordered_map <std::string, std::shared_ptr <Mix_Chunk> > Resources::soundTable;

std::shared_ptr <SDL_Texture> Resources::GetImage(std::string file){
	if(imageTable.find(file) == imageTable.end()){
		SDL_Texture *texture = IMG_LoadTexture(Game::GetInstance()->GetRenderer(), file.c_str());

		if(not texture){
			printf("Erro ao carregar imagem: %s\n", SDL_GetError());
			exit(1);
		}

		std::shared_ptr <SDL_Texture> ptr(texture, [](SDL_Texture *t){ SDL_DestroyTexture(t); });

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

std::shared_ptr <Mix_Music> Resources::GetMusic(std::string file){
	if(musicTable.find(file) == musicTable.end()){
		Mix_Music *music = Mix_LoadMUS(file.c_str());

		if(not music){
			printf("Erro ao carregar muśica: %s\n", SDL_GetError());
			exit(1);
		}

		std::shared_ptr <Mix_Music> ptr(music, [](Mix_Music *m){ Mix_FreeMusic(m); });

		musicTable.emplace(file, ptr);
	}
	
	return musicTable[file];
}

void Resources::ClearMusic(){
	for(auto it = musicTable.begin(); it != musicTable.end(); it++){
		if(it->second.unique())
			musicTable.erase(it);
	}
}

std::shared_ptr <Mix_Chunk> Resources::GetSound(std::string file){
	if(soundTable.find(file) == soundTable.end()){
		Mix_Chunk *sound = Mix_LoadWAV(file.c_str());

		if(not sound){
			printf("Erro ao carregar som: %s\n", SDL_GetError());
			exit(1);
		}

		std::shared_ptr <Mix_Chunk> ptr(sound, [](Mix_Chunk *s){ Mix_FreeChunk(s); });

		soundTable.emplace(file, ptr);
	}
	
	return soundTable[file];
}

void Resources::ClearSound(){
	for(auto it = soundTable.begin(); it != soundTable.end(); it++){
		if(it->second.unique())
			soundTable.erase(it);
	}
}
