#include "TileMap.h"

#include <stdio.h>
#include <fstream>
#include <sstream>

TileMap::TileMap(string file, TileSet *tSet){
	Load(file);

	SetTileSet(tSet);
}

TileMap::~TileMap(){
	delete(tileSet);
}

void TileMap::Load(string file){
	std::fstream f(file, f.in);

	if(not f.is_open()){
		printf("Não foi possível abrir o arquivo %s\n", file.c_str());
		exit(1);
	}else{
		string s;
		getline(f, s);

		std::stringstream ss;
		ss << s;

		ss >> mapWidth;
		ss.ignore(2, ',');

		ss >> mapHeight;
		ss.ignore(2, ',');

		ss >> mapDepth;
		ss.ignore(2, ',');

		while(getline(f, s)){
			ss.clear();
			ss << s;

			int index;
			while(ss >> index){
				tileMatrix.emplace_back(--index);

				ss.ignore(2, ',');
			}
		}
	}
}

void TileMap::SetTileSet(TileSet *tSet){
	tileSet = tSet;
}

int &TileMap::At(int x, int y, int z){
	int index = (y * mapWidth + x) + (z * mapWidth * mapHeight);

	return tileMatrix[index];
}

void TileMap::RenderLayer(int layer, int, int){
	for(int y = 0; y < mapHeight; y++){
		for(int x = 0; x < mapWidth; x++){
			tileSet->Render(At(x, y, layer), x * mapWidth, y * mapHeight);
		}
	}
}

void TileMap::Render(int, int){
	for(int layer = 0; layer < mapDepth; layer++){
		RenderLayer(layer);
	}
}
