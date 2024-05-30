#pragma once

/*
Design Pattern : 프로그램 설계 방식

Singleton

static Time* instance = nullptr;

private:
Time();
~Time();

public:
static void Create()
{
	if (instance == nullptr)
		instance = new Time();
}





*/

class Time
{
private:
	Time();
	~Time();

public:
	static void Create();
	static void Delete();
	static Time* Get();

public:
	void Update();
	void Render();

	static float Delta() { return timeElapsed; }
	static bool& OneTimed() { return oneSecBool; }

private:
	static Time* instance;

private:
	static float timeElapsed;

	INT64  curTick = 0;
	INT64 lastTick = 0;
	INT64 ticksPerSecond = 0;

	UINT frameCount = 0;
	UINT frameRate  = 0;

	float  runningTime = 0.0f;
	float scanningRate = 0.0f;

	float oneSecCount = 0.0f;
	static bool oneSecBool;
};