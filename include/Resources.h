#ifndef RESOURCES_H
#define RESOURCES_H

#include "SDL2/SDL.h"

#include <string>
#include <memory>
#include <unordered_map>

class Resources{
	public:
		static std::shared_ptr <SDL_Texture> GetImage(std::string file);
		static void ClearImages();

	private:
		static std::unordered_map <std::string, std::shared_ptr <SDL_Texture> > imageTable;
};

#endif
