#pragma once

class PlayerBullet;

class Skillbox : public Transform
{
public:
	enum WeaponType
	{
		NORMAL,
		FIRE,
		ICE,
		THURNDER
	};

public:
	Skillbox(WeaponType type);
	~Skillbox();

	void Update();
	void Render();

	void SetParents(Transform* transform);
	bool& isSelect() { return bullet->IsSelect(); }

private:
	PlayerBullet* bullet;
	wstring weaponName = L"";

	WeaponType type;
};