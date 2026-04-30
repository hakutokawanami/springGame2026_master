#pragma once
#include"base/GameObject.h"
class Sword : public GameObject
{
public:
	Sword(int modelHandle , int playerModelHandle);
	~Sword();

	void Init()override;
	void End()override;
	void Update()override;
	void Draw()override;

	void SetSword();

private:
	int m_modelHandle;

	int m_playerModelHandle;

	int m_handIndex;
};

