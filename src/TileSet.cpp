#include "TileSet.h"

TileSet::TileSet(int width, int height, string file){
	this->tileWidth = width;
	this->tileHeight = height;
	
	tileSet = new Sprite(file);

	rows = tileSet->GetHeight() / tileHeight;
	columns = tileSet->GetWidth() / tileWidth;
}

TileSet::~TileSet(){
	delete(tileSet);
}

void TileSet::Render(int index, double x, double y){
	if(index >= rows * columns){
		printf("Falha ao renderizar tile, índice inválido\n");
		exit(1);
	}

	int xx = (index % columns) * tileWidth;
	int yy = (index / columns) * tileHeight;

	tileSet->SetClip(xx, yy, tileWidth, tileHeight);
	tileSet->Render((int)x, (int)y);
}

int TileSet::GetTileWidth(){
	return tileWidth;
}

int TileSet::GetTileHeight(){
	return tileHeight;	
}
