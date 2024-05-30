#include "Framework.h"
#include "WallManager.h"


WallManager::WallManager()
{
	OBJECT->SetWall(this);
}

WallManager::~WallManager()
{
	for (Wall* wall : walls)
		delete wall;

	walls.clear();
}

void WallManager::Update()
{
	for (Wall* wall : walls)
		wall->Update();
}

void WallManager::Render()
{
	for (Wall* wall : walls)
		wall->Render();
}

void WallManager::AddWall(Vector2 size, Vector2 point, Wall::Type type)
{
	Wall* wall = new Wall(size, type);
	wall->GetCollider()->Translation() = point;
	walls.push_back(wall);
}
