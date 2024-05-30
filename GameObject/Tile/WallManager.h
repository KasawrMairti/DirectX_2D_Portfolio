#pragma once

class WallManager
{
public:
	WallManager();
	~WallManager();

	void Update();
	void Render();

	void AddWall(Vector2 size, Vector2 point, Wall::Type type);

	vector<Wall*> GetWalls() { return walls; }

private:
	vector<Wall*> walls;
};