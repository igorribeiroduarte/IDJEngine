#ifndef TILESET_H
#define TILESET_H

#include "Sprite.h"

class TileSet{
	public:
		TileSet(int tileWidth, int tileHeight, string file);
		~TileSet();

		void Render(int index, double x, double y);

		int GetTileWidth();
		int GetTileHeight();

	private:
		Sprite *tileSet;

		int rows, columns;
		int tileWidth, tileHeight;
};

#endif
