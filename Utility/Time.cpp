#include "Framework.h"
#include "Time.h"

Time* Time::instance = nullptr;

float Time::timeElapsed = 0.0f;
bool Time::oneSecBool = false;

Time::Time()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&ticksPerSecond); //CPU�� �ʴ� ����(Tick) ��

	QueryPerformanceCounter((LARGE_INTEGER*)&lastTick); //CPU�� ����(Tick) ���� ��
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

	//1������ ���� �帥 �ð�
	timeElapsed = (curTick - lastTick) / (float)ticksPerSecond;

	lastTick = curTick;

	//���α׷� ���� �� ��� �ð�
	runningTime += timeElapsed;

	//1�ʸ� üũ�ϱ� ���� ����
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