#pragma once

class SelectImage : public Transform
{
public:
	SelectImage();
	~SelectImage();

	void Update();
	void Render();

private:
	Character* line;
	Character* circle;
};