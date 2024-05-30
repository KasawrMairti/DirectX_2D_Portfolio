#include "Framework.h"
#include "Wall.h"


Wall::Wall(Vector2 size, Type type)
	:type(type)
{
	collider = new ColliderRect(size);
	collider->SetParent(this);
}

Wall::~Wall()
{
	delete collider;
}

void Wall::Update()
{
	collider->Update();
}

void Wall::Render()
{
	collider->Render();
}
