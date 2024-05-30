#pragma once

class IdleImage : public Character
{
public:
	IdleImage(wstring file, UINT frameX, UINT frameY);
	~IdleImage();

	void Update();
	void Render();

	bool& FadeInOut() { return fadeInOut; }

private:
	float alpha = 0.0f;

	bool fadeInOut = true;
};