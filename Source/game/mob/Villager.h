#pragma once
#include "../base/Character.h"
#include"../SceneController.h"
#include<memory>
class AnimationController;
class Villager : public Character
{
public:
	Villager(int modelHandle,const Vector3& pos,scene name);
	~Villager();

	void Init()override;
	void End()override;
	void Update()override;
	void Draw()override;

	void Rotate(const Vector3 vec);
private:
	int m_modelHandle;
	std::shared_ptr<AnimationController>m_animationController;
};

