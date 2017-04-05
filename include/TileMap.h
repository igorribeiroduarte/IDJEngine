#ifndef TILEMAP_H
#define TILEMAP_H

#include "TileSet.h"

#include <vector>

class TileMap{
	public:
		TileMap(string file, TileSet *tSet);
		~TileMap();

		void Load(string file);
		void SetTileSet(TileSet *tileSet);
		void Render(int cameraX = 0, int cameraY = 0);
		void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);

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
