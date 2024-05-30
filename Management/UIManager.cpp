#include "Framework.h"
#include "UIManager.h"


UIManager::UIManager()
{
	frontGround = new Object(L"UI/FrontGround.png");
	frontGround->Translation().x = WIN_WIDTH * 0.5f;
	frontGround->Translation().y = WIN_HEIGHT * 0.5f;
	frontGround->SetParent(CAMERA->GetTransform());

	playerImage = new Object(L"UI/DownPlayerImage.png");
	playerImage->Translation().x = 60.0f;
	playerImage->Translation().y = 60.0f;
	playerImage->SetParent(CAMERA->GetTransform());

	for (int i = 0; i < 3; i++)
	{
		Heart* heart = new Heart();
		heart->Translation().x = 110.0f + (30.0f * i);
		heart->Translation().y = 30.0f;
		heart->SetParents(CAMERA->GetTransform());
		hearts.push_back(heart);
	}

	box = new Object(L"UI/BigBox.png");
	box->Translation().x = 1000.0f;
	box->Translation().y = 58.0f;
	box->SetParent(CAMERA->GetTransform());

	box_normal = new Skillbox(Skillbox::NORMAL);
	box_normal->Translation().x = 815.0f;
	box_normal->Translation().y = 65.0f;
	box_normal->isSelect() = true;
	box_normal->SetParents(CAMERA->GetTransform());

	box_fire = new Skillbox(Skillbox::FIRE);
	box_fire->Translation().x = 930.0f;
	box_fire->Translation().y = 65.0f;
	box_fire->SetParents(CAMERA->GetTransform());

	box_ice = new Skillbox(Skillbox::ICE);
	box_ice->Translation().x = 1050.0f;
	box_ice->Translation().y = 65.0f;
	box_ice->SetParents(CAMERA->GetTransform());

	box_thurnder = new Skillbox(Skillbox::THURNDER);
	box_thurnder->Translation().x = 1175.0f;
	box_thurnder->Translation().y = 65.0f;
	box_thurnder->SetParents(CAMERA->GetTransform());
}

UIManager::~UIManager()
{
	delete frontGround;
	delete playerImage;
	delete box;

	delete box_normal;
	delete box_fire;
	delete box_ice;
	delete box_thurnder;

	for (Heart* heart : hearts)
		delete heart;
	hearts.clear();

}

void UIManager::Update()
{
	frontGround->Update();
	playerImage->Update();
	box->Update();

	box_normal->Update();
	box_fire->Update();
	box_ice->Update();
	box_thurnder->Update();

	for (Heart* heart : hearts)
		heart->Update();

	if (KEY_DOWN('1'))
	{
		box_normal->isSelect() = true;
		box_fire->isSelect() = false;
		box_ice->isSelect() = false;
		box_thurnder->isSelect() = false; 
		OBJECT->GetPlayer()->WeaponCount() = 1;
	}
	else if (KEY_DOWN('2'))
	{
		box_normal->isSelect() = false;
		box_fire->isSelect() = true;
		box_ice->isSelect() = false;
		box_thurnder->isSelect() = false;
		OBJECT->GetPlayer()->WeaponCount() = 2;
	}
	else if (KEY_DOWN('3'))
	{
		box_normal->isSelect() = false;
		box_fire->isSelect() = false;
		box_ice->isSelect() = true;
		box_thurnder->isSelect() = false;
		OBJECT->GetPlayer()->WeaponCount() = 3;
	}
	else if (KEY_DOWN('4'))
	{
		box_normal->isSelect() = false;
		box_fire->isSelect() = false;
		box_ice->isSelect() = false;
		box_thurnder->isSelect() = true;
		OBJECT->GetPlayer()->WeaponCount() = 4;
	}

	if (KEY_DOWN('T'))
	{
		Collider::HiddenInGame();
	}
}

void UIManager::Render()
{
	frontGround->Render();
	playerImage->Render();
	box->Render();

	box_normal->Render();
	box_fire->Render();
	box_ice->Render();
	box_thurnder->Render();

	for (Heart* heart : hearts)
		heart->Render();
}

void UIManager::hearts_add()
{
	if (hearts_HP < 3)
	{
		hearts_HP++;

		hearts[hearts_HP - 1]->Healed();
	}
}

void UIManager::hearts_remove()
{
	if (hearts_HP > 0)
	{
		hearts_HP--;

		hearts[hearts_HP]->Damaged();
	}
}
