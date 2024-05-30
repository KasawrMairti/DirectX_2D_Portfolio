#include "Framework.h"
#include "TileManager.h"


TileManager::TileManager()
{
}

TileManager::~TileManager()
{
	for (auto tile : tiles)
		delete tile;
}

void TileManager::Update()
{
	for (auto tile : tiles)
		tile->Update();
}

void TileManager::Render()
{
	for (auto tile : tiles)
		tile->Render();
}

void TileManager::AddTile(wstring file, Vector2 pos)
{
	Tile* tile = new Tile(file, pos);
	tile->Scale() *= 2;
	tiles.push_back(tile);
}

void TileManager::AddTile(wstring file, Vector2 pos, Vector2 tileSize, Vector2 tileTranslation)
{
	Tile* tile = new Tile(file, pos, tileSize, tileTranslation);
	tile->Scale() *= 2;
	tiles.push_back(tile);
}
