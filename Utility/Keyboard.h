#pragma once

#define MAX_KEY 256

enum KeyState
{
	NONE,
	DOWN,
	UP,
	PRESS
};

class Keyboard
{
private:
	Keyboard();
	~Keyboard();

public:
	static void Create()
	{
		if (instance == nullptr)
			instance = new Keyboard();
	}

	static void Delete()
	{
		if (instance != nullptr)
			delete instance;
	}

	static Keyboard* Get()
	{
		if (instance == nullptr)
			instance = new Keyboard;

		return instance;
	}

public:
	void Update();

	bool  Down(DWORD key) { return keyMap[key] ==  DOWN; }
	bool    Up(DWORD key) { return keyMap[key] ==    UP; }
	bool Press(DWORD key) { return keyMap[key] == PRESS; }

private:
	static Keyboard* instance;

	BYTE keyCurState[MAX_KEY];
	BYTE keyOldState[MAX_KEY];

	BYTE keyMap[MAX_KEY];
};
