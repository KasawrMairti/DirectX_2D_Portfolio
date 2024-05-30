#include "Framework.h"
#include "Keyboard.h"

Keyboard* Keyboard::instance = nullptr;

Keyboard::Keyboard()
{
	/*
	배열, 구조체 초기화 하는 방법

	1. 변수 선언 시 = {};

	2. memset
		
	3. ZeroMemory
	*/

	memset(keyCurState, 0, sizeof(keyCurState));
	memset(keyOldState, 0, sizeof(keyOldState));
	memset(keyMap     , 0, sizeof(keyMap     ));

	//ZeroMemory(keyCurState, sizeof(keyCurState));
}

Keyboard::~Keyboard()
{
}

void Keyboard::Update()
{
	memcpy(keyOldState, keyCurState, sizeof(keyCurState));

	ZeroMemory(keyCurState, sizeof(keyCurState));
	ZeroMemory(keyMap     , sizeof(keyMap     ));
	
	/*
	BYTE

	  0,   1: 키보드를 누르지 않은 상태

	128, 129: 키보드를 누른 상태
	
	*/
	if (!GetKeyboardState(keyCurState))
		return;

	for (UINT i = 0; i < MAX_KEY; i++)
	{
		BYTE key = keyCurState[i] & 0x80; //눌리면 128, 안눌리면 0

		keyCurState[i] = key ? 1 : 0;     //눌리면   1, 안눌리면 0

		/*
		삼항 연산자:

		bool ? True일 때 결과값 : False일 때 결과값
		
		bool isMale = false;

		cout << isMale << endl;

		cout << isMale ? "남자" : "여자" << endl;
		*/

		BYTE old = keyOldState[i];
		BYTE cur = keyCurState[i];

		if (old == 0 && cur == 1)      //이전에는 False, 현재는 True  : DOWN
			keyMap[i] = DOWN;
		else if (old == 1 && cur == 0) //이전에는 True , 현재는 False : UP
			keyMap[i] = UP;
		else if (old == 1 && cur == 1) //이전에는 True , 현재는 True  : PRESS 
			keyMap[i] = PRESS;
		else
			keyMap[i] = NONE;
	}
}
