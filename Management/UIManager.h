#pragma once

class UIManager : public Singleton<UIManager>
{
public:
	UIManager();
	~UIManager();

	void Update();
	void Render();

	void hearts_add();
	void hearts_remove();

	UINT Hearts_HP() { return hearts_HP; }

private:
	Object* frontGround;
	Object* playerImage;

	Object* box;
	Skillbox* box_normal;
	Skillbox* box_fire;
	Skillbox* box_ice;
	Skillbox* box_thurnder;

	vector<Heart*> hearts;
	UINT hearts_HP = 3;
};