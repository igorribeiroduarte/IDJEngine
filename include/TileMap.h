#ifndef TILEMAP_H
#define TILEMAP_H

#include "TileSet.h"
#include "Vec2.h"

#include <vector>

class TileMap{
	public:
		TileMap(string file, TileSet *tSet);
		~TileMap();

		void Load(string file);
		void SetTileSet(TileSet *tileSet);
		void Render(Vec2 *camera);
		void RenderLayer(int layer, Vec2 *camera);

		int &At(int x, int y, int z = 0);
		int GetWidth();
		int GetHeight();
		int GetDepth();

	private:
		std::vector <int> tileMatrix;

		TileSet *tileSet; 

		int mapWidth, mapHeight, mapDepth;
};

#endif
