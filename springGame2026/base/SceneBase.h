#pragma once
class SceneController;
class InputManager;
class SceneBase
{
public:
	SceneBase(SceneController& controller);

	virtual void Update(InputManager& input)abstract;

	virtual void Draw()abstract;

protected:
	SceneController& m_controller;
};

