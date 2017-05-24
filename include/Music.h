#ifndef MUSIC_H
#define MUSIC_H

#include "SDL2/SDL_mixer.h"

#include "Resources.h"

#include <string>
#include <memory>

class Music{
	public:
		Music();
		Music(std::string file);
		~Music();

		void Play(int times);
		void Stop(int ms = 0);
		void Open(std::string file);

		bool IsOpen();

	private:
		std::shared_ptr <Mix_Music> music;
		
};

#endif
