#ifndef TEXT_H
#define TEXT_H

#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

#include "Rect.h"

#include <string>
#include <memory>

class Text{
	public:
		enum TextStyle { SOLID, SHADED, BLENDED };
	
		Text();
		Text(std::string fontFile, int pFontSize, TextStyle style, std::string pText, SDL_Color pColor, int x = 0, int y = 0);

		~Text();

		void Render(int cameraX = 0, int cameraY = 0);

		void SetPos(int x, int y, bool centerX = false, bool centerY = false);

		void SetText(std::string pText);
		void SetColor(SDL_Color pColor);
		void SetStyle(TextStyle pStyle);
		void SetFontSize(int pFontSize);
		void SetVisibility(bool visibility);

	private:
		void RemakeTexture();

		bool visibility;

		std::shared_ptr <TTF_Font> font;

		SDL_Texture *texture;

		std::string text;
		
		TextStyle style;

		int fontSize;

		SDL_Color color;

		Rect *box;
};

#endif
