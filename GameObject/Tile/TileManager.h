#pragma once

class TileManager
{
public:
	TileManager();
	~TileManager();

	void Update();
	void Render();

	void AddTile(wstring file, Vector2 pos);
	void AddTile(wstring file, Vector2 pos, Vector2 tileSize, Vector2 tileTranslation);

	vector<Tile*> GetTile() { return tiles; }

private:
	vector<Tile*> tiles;
};