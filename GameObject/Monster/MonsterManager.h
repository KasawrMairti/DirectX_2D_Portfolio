#pragma once

class MonsterManager
{
public:
	enum MonsterType
	{
		LV1, LV2, LV3
	};

public:
	MonsterManager();
	~MonsterManager();

	void Update();
	void Render();

	void Add(MonsterType type, Vector2 Pos);

	vector<Monster*> Monsters() { return monsters; }

private:
	vector<Monster*> monsters;

	MonsterType type;
};