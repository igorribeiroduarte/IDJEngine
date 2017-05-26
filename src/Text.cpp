#include "Text.h"
#include "Resources.h"
#include "Game.h"

Text::Text(){

}

Text::Text(std::string fontFile, int pFontSize, TextStyle pStyle, std::string pText, SDL_Color pColor, int x, int y){
	texture = nullptr;
	text = pText;
	style = pStyle;
	fontSize = pFontSize;
	font = Resources::GetFont(fontFile, fontSize);
	color = pColor;
	visibility = true;
	box = new Rect(x, y);

	if(font)
		RemakeTexture();
}

Text::~Text(){
	if(texture)
		SDL_DestroyTexture(texture);
}

void Text::SetVisibility(bool pVisibility){
	visibility = pVisibility;
}

void Text::Render(int cameraX, int cameraY){
	if(texture && visibility){
		SDL_Rect *srcRect = new SDL_Rect{ 0, 0, (int)box->width, (int)box->height };
		SDL_Rect *dstRect = new SDL_Rect{ (int)box->GetDrawX() + cameraX, (int)box->GetDrawY() + cameraY, (int)box->width, (int)box->height };
	
		SDL_RenderCopy(Game::GetInstance()->GetRenderer(), texture, srcRect, dstRect);
	}
}

void Text::SetPos(int x, int y, bool centerX, bool centerY){
	if(centerX) x -= box->width / 2;
	if(centerY) y -= box->height / 2;

	box->x = x;
	box->y = y;
}

void Text::SetText(std::string pText){
	text = pText;
	RemakeTexture();
}

void Text::SetColor(SDL_Color pColor){
	color = pColor;
	RemakeTexture();
}

void Text::SetStyle(Text::TextStyle pStyle){
	style = pStyle;
	RemakeTexture();
}

void Text::SetFontSize(int pFontSize){
	fontSize = pFontSize;
	RemakeTexture();
}

void Text::RemakeTexture(){
	if(texture)
		SDL_DestroyTexture(texture);

	SDL_Surface *surface = nullptr;

	if(style == Text::TextStyle::SOLID)
		surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
	else if(style == Text::TextStyle::SHADED){
		SDL_Color black = { 0, 0, 0, 0 };
		surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color, black);
	}
	else if(style == Text::TextStyle::BLENDED)
		surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);

	texture = SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(), surface);

	int width, height;

	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

	box->width = width;
	box->height = height;

	SDL_FreeSurface(surface);
}
