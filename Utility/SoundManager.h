#pragma once

#define MAX_CHANNEL 10 //�Ҹ��� 10�� �̻� �ʿ��ϸ� ���ڸ� �ø��� �ȴ�

struct SoundInfo
{
	~SoundInfo()
	{
		sound->release();
	}

	  Sound*   sound;
	Channel* channel;
};

class SoundManager
{
private:
	SoundManager();
	~SoundManager();

public:
	static void Create()
	{
		if (instance == nullptr)
			instance = new SoundManager;
	}

	static void Delete() 
	{
		if (instance != nullptr)
			delete instance;
	}

	static SoundManager* Get()
	{
		if (instance == nullptr)
			instance = new SoundManager;

		return instance;
	}

public:
	void Update();

	void AddSound(string key, string path, bool stream = false);

	void   Play(string key, float volume = 0.1f);
	void   Stop(string key);
	void  Pause(string key);
	void Resume(string key);

private:
	static SoundManager* instance;

	map<string, SoundInfo*> sounds;

	System* system;
};
