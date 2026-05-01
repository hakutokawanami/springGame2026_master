#pragma once
#include "GameObject.h"
/// <summary>
/// キャラクター基底クラス
/// </summary>
class Character :public GameObject
{
protected:
	Vector3 m_velocity = {0.0f,0.0f,0.0f};
};

