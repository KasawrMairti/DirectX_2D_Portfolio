#pragma once

class FirstScene : public Scene
{
public:
	FirstScene();
	~FirstScene();

	virtual void Update() override;
	virtual void Render() override;

	virtual void Initialize() override;
	virtual void Release() override;

	void MakeBG();
	void MakeTile();
	void MakeWall();
	void MakeMonster();

	void ObjectPosition();

private:
	vector<Object*> backgrounds;

	Player* player;
	TileManager* tile;
	WallManager* wall;

	MonsterManager* monster;

	float timeAfter = 0.0f;
	bool loading = false;
};