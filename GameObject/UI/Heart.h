#pragma once

class Heart : public Transform
{
public:
	Heart();
	~Heart();

	void Update();
	void Render();

	void SetParents(Transform* transform);

	void Damaged();
	void Healed();

	bool Hearts() { return hearts; }

private:
	bool hearts = false;

	Character* line;
	Character* shape;
};