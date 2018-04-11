#include "TileMap.h"
#include <fstream>
#include <stdexcept>
#include <string>

using std::ifstream;
using std::string;

TileMap::TileMap (GameObject& associated, string file, TileSet* tileSet) :
		Component(associated), tileSet(tileSet) {
	Load(file);
}

void TileMap::Load (string file) {
	ifstream tileFile(file.c_str());
	if (tileFile.is_open()) {
		string aux;
		std::getline(tileFile, aux, ',');
		mapWidth = std::stoi(aux);

		std::getline(tileFile, aux, ',');
		mapHeight = std::stoi(aux);

		std::getline(tileFile, aux, ',');
		mapDepth = std::stoi(aux);

		string tile;
		while (std::getline(tileFile, tile, ',')) {
			// Subtracts one for convenience
			tileMatrix.push_back(std::stoi(tile) - 1);
		}
	}
	else {
		throw std::runtime_error("Couldn't open TileMap file");
	}
}

void TileMap::SetTileSet (TileSet *tileSet) {
	this->tileSet = tileSet;
}

int& TileMap::At (int x, int y, int z) {
	int zOffset = z * mapWidth * mapHeight;
	int yOffset = y * mapWidth;
	return tileMatrix[zOffset + yOffset + x];
}

void TileMap::RenderLayer (int layer, int cameraX, int cameraY) {
	for (int y = 0; y < mapHeight; ++y) {
		for (int x = 0; x < mapWidth; ++x) {
			tileSet->RenderTile(At(x, y, layer), tileSet->GetTileWidth() * x,
					tileSet->GetTileHeight() * y);
		}
	}
}

void TileMap::Render () {
	for (int z = 0; z < mapDepth; ++z) {
		RenderLayer(z);
	}
}

int TileMap::GetWidth () const {
	return mapWidth;
}
int TileMap::GetHeight () const {
	return mapHeight;
}
int TileMap::GetDepth () const {
	return mapDepth;
}

void TileMap::Update (float dt) {

}

bool TileMap::Is (string type) const {
	return (type == "TileMap");
}
