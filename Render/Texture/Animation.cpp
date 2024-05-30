#include "Framework.h"
#include "Animation.h"

Animation::Animation(wstring file, UINT frameX, UINT frameY, UINT nFrames, float updateTime)
	:updateTime(updateTime)
{
	if (nFrames == 0)
		nFrames = frameX * frameY;

	for (UINT i = 0; i < nFrames; i++)
	{
		UINT x = i % frameX;
		UINT y = i / frameX;

		Vector2 uvStart = {  x      / (float)frameX,  y      / (float)frameY };
		Vector2 uvEnd   = { (x + 1) / (float)frameX, (y + 1) / (float)frameY };

		Frame* frame = new Frame(file, uvStart, uvEnd);
		frames.push_back(frame);
	}

	SetAll();
}

Animation::~Animation()
{
	for (Frame* frame : frames)
		delete frame;

	frames.clear();
}

void Animation::Update()
{
	if (!isPlay)
		return;

	frameTime += Time::Delta();
	 playTime += Time::Delta();

	if (frameTime < updateTime)
		return;

	frameTime -= updateTime;

	if (isLoop)
	{
		++curPlayIndex %= actions.size();

		if (curPlayIndex == 0)
			playTime = 0.0f;
	}
	else
	{
		curPlayIndex++;

		if (curPlayIndex >= actions.size())
		{
			curPlayIndex--;
			Stop();
		}
	}
}

void Animation::Render()
{
	actions[curPlayIndex]->Render();
}

void Animation::Play()
{
	isPlay = true;

	frameTime = 0.0f;
	 playTime = 0.0f;

	curPlayIndex = 0;
}

void Animation::Stop()
{
	isPlay = false;

	frameTime = 0.0f;
	 playTime = 0.0f;

	if (EndEvent != nullptr)
		EndEvent();
}

void Animation::SetAll(bool isLoop)
{
	this->isLoop = isLoop;

	actions.clear();

	for (UINT i = 0; i < frames.size(); i++)
	{
		actions.push_back(frames[i]);
	}
}

void Animation::SetPart(int start, int end, bool isLoop)
{
	this->isLoop = isLoop;

	actions.clear();

	if (end > start)
	{
		for (int i = start; i <= end; i++)
		{
			actions.push_back(frames[i]);
		}
	}
	else
	{
		for (int i = start; i >= end; i--)
		{
			actions.push_back(frames[i]);
		}
	}
}

void Animation::SetVector(vector<UINT> indices, bool isLoop)
{
	this->isLoop = isLoop;

	actions.clear();

	for (UINT i = 0; i < indices.size(); i++)
	{
		actions.push_back(frames[indices[i]]);
	}
}

