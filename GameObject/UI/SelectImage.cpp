#include "Framework.h"
#include "SelectImage.h"


SelectImage::SelectImage()
{
	line = new Character(L"UI/SelectImage.png");
	line->Scale() /= 2;
	line->SetColor(0.3f, 1.0f, 0.3f, 0.6f);


	circle = new Character(L"UI/MainImage2.png");
	circle->Scale() /= 6;
	circle->SetColor(0.3f, 1.0f, 0.3f, 0.6f);
}

SelectImage::~SelectImage()
{
	delete line;
	delete circle;
}

void SelectImage::Update()
{
	line->Update();
	circle->Update();

	line->Translation() = this->Translation();
	circle->Translation() = this->Translation();
}

void SelectImage::Render()
{
	line->Render();
	circle->Render();
}
