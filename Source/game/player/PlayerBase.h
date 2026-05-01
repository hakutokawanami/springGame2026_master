#pragma once
#include "Character.h"
#include"../system/Quaternion.h"
#include<memory>
class InputManager;
class PlayerBase : public Character
{
public:
	PlayerBase():m_modelHandle(-1) {};
	virtual ~PlayerBase() = default;
	virtual void Init()abstract;
	virtual void End()abstract;
	virtual void Update()abstract;
	virtual void Update(InputManager& input)abstract;
	virtual void Draw()abstract;
	int GetModelHandle() { return m_modelHandle; }
protected:
	int m_modelHandle;

	Quaternion m_rotation;
};

