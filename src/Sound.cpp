#include "Sound.h"

Sound::Sound(){
	chunk = nullptr;
}

Sound::Sound(std::string file){
	Open(file);
}

Sound::~Sound(){

}

void Sound::Play(int times){
	channel = Mix_PlayChannel(-1, chunk.get(), times);
}

void Sound::Stop(){
	Mix_HaltChannel(channel);
}

void Sound::Open(std::string file){
	chunk = Resources::GetSound(file);
}
