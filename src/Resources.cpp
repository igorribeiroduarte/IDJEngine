#include "Resources.h"
#include "Game.h"

std::unordered_map <std::string, std::shared_ptr <SDL_Texture> > Resources::imageTable;
std::unordered_map <std::string, std::shared_ptr <Mix_Music> > Resources::musicTable;
std::unordered_map <std::string, std::shared_ptr <Mix_Chunk> > Resources::soundTable;
std::unordered_map <std::string, std::shared_ptr <TTF_Font> > Resources::fontTable;

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
			printf("Erro ao carregar música: %s\n", SDL_GetError());
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

std::shared_ptr <TTF_Font> Resources::GetFont(std::string file, int fontSize){
	string fontKey = file + to_string(fontSize);

	if(fontTable.find(fontKey) == fontTable.end()){
		TTF_Font *font = TTF_OpenFont(file.c_str(), fontSize);

		if(not font){
			printf("Erro ao carregar fonte: %s\n", SDL_GetError());
			exit(1);
		}

		std::shared_ptr <TTF_Font> ptr(font, [](TTF_Font *f){ TTF_CloseFont(f); });

		fontTable.emplace(fontKey, ptr);
	}
	
	return fontTable[fontKey];
}

void Resources::ClearFonts(){
	for(auto it = fontTable.begin(); it != fontTable.end(); it++){
		if(it->second.unique())
			fontTable.erase(it);
	}
}
