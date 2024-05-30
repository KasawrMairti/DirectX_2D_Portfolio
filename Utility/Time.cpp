#include "Framework.h"
#include "Time.h"

Time* Time::instance = nullptr;

float Time::timeElapsed = 0.0f;
bool Time::oneSecBool = false;

Time::Time()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&ticksPerSecond); //CPU의 초당 진동(Tick) 수

	QueryPerformanceCounter((LARGE_INTEGER*)&lastTick); //CPU의 진동(Tick) 누적 값
}

Time::~Time()
{
	
}

void Time::Create()
{
	if (instance == nullptr)
		instance = new Time;
}

void Time::Delete()
{
	if (instance != nullptr)
		delete instance;
}

Time* Time::Get()
{
	if (instance == nullptr)
		instance = new Time();

	return instance;
}

void Time::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&curTick);

	//1프레임 동안 흐른 시간
	timeElapsed = (curTick - lastTick) / (float)ticksPerSecond;

	lastTick = curTick;

	//프로그램 시작 후 경과 시간
	runningTime += timeElapsed;

	//1초를 체크하기 위한 변수
	oneSecCount += timeElapsed;

	if (oneSecCount >= 1.0f)
	{
		oneSecCount -= 1.0f;
		oneSecBool = true;

		frameRate  = frameCount;
		frameCount = 0;
	}

	frameCount++;
}

void Time::Render()
{
	wstring str;

	str = L"RunTime : " + to_wstring((int)runningTime);
	FONT->RenderText(str, "D2Coding", Vector2(0, 20));

	str = L"FPS     : " + to_wstring((int)frameRate  );
	FONT->RenderText(str, "D2Coding", Vector2(0, 40));

}