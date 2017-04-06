#ifndef RESOURCES_H
#define RESOURCES_H

#include <SDL2/SDL.h>

#include <string>
#include <unordered_map>

class Resources{
	public:
		static SDL_Texture *GetImage(std::string file);
		static void ClearImages();

	private:
		static std::unordered_map <std::string, SDL_Texture *> imageTable;
};

#endif
