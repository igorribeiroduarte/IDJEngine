#ifndef SPRITE_H
#define SPRITE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <string>

using std::string;

class Sprite{
	public:
		Sprite();	
		Sprite(string file);
		~Sprite();

		void Open(string file);
		void SetClip(int x, int y, int w, int h);
		void Render(int x, int y, double angle = 0);
		
		int GetWidth();
		int GetHeight();

		void SetScaleX(int scale);
		void SetScaleY(int scale);

		bool IsOpen();

	private:
		SDL_Texture *texture;

		SDL_Rect *clipRect;
		SDL_Rect *dstRect;

		int width, height;
		int scaleX, scaleY;
};

#endif
