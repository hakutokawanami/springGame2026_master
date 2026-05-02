#pragma once
#include<memory>
#include<list>

enum scene
{
	title,
	game,
	result
};

class InputManager;
class SceneBase;
class SceneController
{
public:
	SceneController();

	void ChangeScene(std::shared_ptr<SceneBase> newScene);

	void PushScene(std::shared_ptr<SceneBase> newScene);

	void PopScene();

	void Update(InputManager& input);

	void Draw();

private:
	std::list<std::shared_ptr<SceneBase>> m_scenes;
};

