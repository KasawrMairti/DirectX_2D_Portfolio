#pragma once

class TitleScene : public Scene
{
public:
	TitleScene();
	~TitleScene();

	virtual void Update() override;
	virtual void Render() override;

	virtual void Initialize() override;
	virtual void Release() override;

	void InitialImage();

private:
	IdleImage* background;
	Object* titleName;
	IdleImage* titleImage;

	SelectImage* selectImage;

	bool fadeEvent = false;
	UINT fadeEventTime = 0;

	Vector2 point[2];
	UINT selectPoint = 0;
};