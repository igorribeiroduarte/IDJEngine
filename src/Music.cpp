#include "Music.h"

Music::Music(){
	music = nullptr;
}

Music::Music(std::string file){
	Open(file);
}

Music::~Music(){

}

void Music::Play(int times){
	Mix_PlayMusic(music.get(), times);
}

void Music::Stop(int ms){
	Mix_FadeOutMusic(ms);
}

void Music::Open(std::string file){
	music = Resources::GetMusic(file);
}

bool Music::IsOpen(){
	return (music != nullptr);
}
