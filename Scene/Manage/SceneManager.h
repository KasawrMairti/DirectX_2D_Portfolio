#pragma once

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

public:
	static SceneManager* Get()
	{
		if (instance == nullptr)
			instance = new SceneManager;

		return instance;
	}

	static void Delete()
	{
		delete instance;
	}

	void Update();
	void Render();

	Scene* Add(string key, Scene* scene);

	void ChangeScene(string key);
	bool& LoadComplete() { return loadComplete; }

private:
	static SceneManager* instance;
	bool loadComplete;

	map<string, Scene*> scenes;

	Scene* curScene = nullptr;
};