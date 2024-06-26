#pragma once

class Scene
{
public:
	virtual ~Scene() = default;

	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual void Initialize() = 0;
	virtual void Release() = 0;
};