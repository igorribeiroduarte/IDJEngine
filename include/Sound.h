#ifndef SOUND_H
#define SOUND_H

#include "SDL2/SDL_mixer.h"

#include "Resources.h"

#include <string>
#include <memory>

class Sound{
	public:
		Sound();
		Sound(std::string file);
		~Sound();

		void Play(int times);
		void Stop();
		void Open(std::string file);

		bool IsOpen();

	private:
		std::shared_ptr <Mix_Chunk> chunk;

		int channel;
};

#endif
