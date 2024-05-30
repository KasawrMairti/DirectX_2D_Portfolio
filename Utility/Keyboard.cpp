#include "Framework.h"
#include "Keyboard.h"

Keyboard* Keyboard::instance = nullptr;

Keyboard::Keyboard()
{
	/*
	�迭, ����ü �ʱ�ȭ �ϴ� ���

	1. ���� ���� �� = {};

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

	  0,   1: Ű���带 ������ ���� ����

	128, 129: Ű���带 ���� ����
	
	*/
	if (!GetKeyboardState(keyCurState))
		return;

	for (UINT i = 0; i < MAX_KEY; i++)
	{
		BYTE key = keyCurState[i] & 0x80; //������ 128, �ȴ����� 0

		keyCurState[i] = key ? 1 : 0;     //������   1, �ȴ����� 0

		/*
		���� ������:

		bool ? True�� �� ����� : False�� �� �����
		
		bool isMale = false;

		cout << isMale << endl;

		cout << isMale ? "����" : "����" << endl;
		*/

		BYTE old = keyOldState[i];
		BYTE cur = keyCurState[i];

		if (old == 0 && cur == 1)      //�������� False, ����� True  : DOWN
			keyMap[i] = DOWN;
		else if (old == 1 && cur == 0) //�������� True , ����� False : UP
			keyMap[i] = UP;
		else if (old == 1 && cur == 1) //�������� True , ����� True  : PRESS 
			keyMap[i] = PRESS;
		else
			keyMap[i] = NONE;
	}
}
