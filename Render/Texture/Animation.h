#pragma once

class Animation
{
public:
	Animation(wstring file, UINT frameX, UINT frameY, UINT nFrames = 0, float updateTime = 0.1f);
	~Animation();

	void Update();
	void Render();

	void Play();
	void Stop();

	void SetAll(bool isLoop = true);
	void SetPart(int start, int end, bool isLoop = true);
	void SetVector(vector<UINT> indices, bool isLoop = true);

	Vector2 GetSize() { return actions[0]->GetSize(); }

	void SetEndEvent(function<void()> EndEvent) { this->EndEvent = EndEvent; }

private:
	vector<Frame*>  frames;
	vector<Frame*> actions;

	bool isLoop = true;

	float updateTime = 0.0f;
	float  frameTime = 0.0f;
	float   playTime = 0.0f;

	bool isPlay = true;

	UINT curPlayIndex = 0;

	function<void()> EndEvent = nullptr;
};
