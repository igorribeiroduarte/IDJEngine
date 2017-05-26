#ifndef RESOURCES_H
#define RESOURCES_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

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

		static std::shared_ptr <TTF_Font> GetFont(std::string file, int fontSize);
		static void ClearFonts();

	private:
		static std::unordered_map <std::string, std::shared_ptr <SDL_Texture> > imageTable;
		static std::unordered_map <std::string, std::shared_ptr <Mix_Music> > musicTable;
		static std::unordered_map <std::string, std::shared_ptr <Mix_Chunk> > soundTable;
		static std::unordered_map <std::string, std::shared_ptr <TTF_Font> > fontTable;

};

#endif
