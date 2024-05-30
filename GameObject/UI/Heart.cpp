#include "Framework.h"
#include "Heart.h"


Heart::Heart()
{
	line = new Character(L"UI/heart1.png");
	shape = new Character(L"UI/heart2.png");

	hearts = true;
}

Heart::~Heart()
{
	delete line;
	delete shape;
}

void Heart::Update()
{
	shape->Update();
	shape->Translation() = this->Translation();

	line->Update();
	line->Translation() = this->Translation();
}

void Heart::Render()
{
	if (hearts) shape->Render();
	line->Render();
}

void Heart::SetParents(Transform* transform)
{
	shape->SetParent(transform);
	line->SetParent(transform);
}

void Heart::Damaged()
{
	hearts = false;
}

void Heart::Healed()
{
	hearts = true;
}
