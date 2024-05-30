#include "Framework.h"
#include "SceneManager.h"

SceneManager* SceneManager::instance = nullptr;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	curScene->Release();

	for (pair<string, Scene*> pair : scenes)
		delete pair.second;

	scenes.clear();
}

void SceneManager::Update()
{
	if (!curScene)
		return;

	curScene->Update();
}

void SceneManager::Render()
{
	if (!curScene)
		return;

	curScene->Render();
}

Scene* SceneManager::Add(string key, Scene* scene)
{
	if (scenes.count(key) > 0)
		return scenes[key];

	scenes.emplace(key, scene);

	return scene;
}

void SceneManager::ChangeScene(string key)
{
	if (scenes.count(key) == 0)
		return;

	if (scenes[key] == curScene)
		return;

	if (curScene != nullptr)
		curScene->Release();

	loadComplete = false;

	curScene = scenes[key];
	curScene->Initialize();
}
