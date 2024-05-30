#include "Framework.h"
#include "Skillbox.h"

Skillbox::Skillbox(WeaponType type)
	:type(type)
{
	switch (type)
	{
	case Skillbox::NORMAL:
	{
		bullet = new PlayerBullet(PlayerBullet::NORMAL, false);

		weaponName = L"Normal";
	}
		break;
	case Skillbox::FIRE:
	{
		bullet = new PlayerBullet(PlayerBullet::FIRE, false);

		weaponName = L"Fire";
	}
		break;
	case Skillbox::ICE:
	{
		bullet = new PlayerBullet(PlayerBullet::ICE, false);

		weaponName = L"Ice";
	}
		break;
	case Skillbox::THURNDER:
	{
		bullet = new PlayerBullet(PlayerBullet::THURNDER, false);

		weaponName = L"Thurnder";
	}
		break;
	default:
		break;
	}
}

Skillbox::~Skillbox()
{
	delete bullet;
}

void Skillbox::Update()
{
	bullet->Update();

	if (bullet->Type() == PlayerBullet::FIRE)
	{
		bullet->Translation().x = this->Translation().x - 25.0f;
		bullet->Translation().y = this->Translation().y;
	}
	else if (bullet->Type() == PlayerBullet::THURNDER)
	{
		bullet->Translation().x = this->Translation().x;
		bullet->Translation().y = this->Translation().y + 8.0f;
	}
	else
		bullet->Translation() = this->Translation();
	bullet->Scale() = this->Scale();
}

void Skillbox::Render()
{
	bullet->Render();

	FONT->RenderText(weaponName, "WeaponName", Vector2(this->Translation().x, WIN_HEIGHT - this->Translation().y + 35.0f));
}

void Skillbox::SetParents(Transform* transform)
{
	bullet->SetParent(transform);
}
