#ifndef RESOURCES_H
#define RESOURCES_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

#include <string>
#include <memory>
#include <unordered_map>

class Resources{
	public:
		static std::shared_ptr <SDL_Texture> GetImage(std::string file);
		static void ClearImages();

		static std::shared_ptr <Mix_Music> GetMusic(std::string file);
		static void ClearMusic();

		static std::shared_ptr <Mix_Chunk> GetSound(std::string file);
		static void ClearSound();

	private:
		static std::unordered_map <std::string, std::shared_ptr <SDL_Texture> > imageTable;
		static std::unordered_map <std::string, std::shared_ptr <Mix_Music> > musicTable;
		static std::unordered_map <std::string, std::shared_ptr <Mix_Chunk> > soundTable;

};

#endif
