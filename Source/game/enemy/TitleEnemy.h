#pragma once
#include "base/Character.h"
#include<memory>
class AnimationController;
class TitleEnemy : public Character
{
public:
	//コンストラクタでモデルを受け取る
	TitleEnemy(int modelHandle, const Vector3& pos);
	~TitleEnemy();

	void Init()override;
	void End()override;
	void Update()override;
	void Draw()override;

	void Rotate(const Vector3 vec);
private:
	//モデルハンドル
	int m_modelHandle;
	//アニメーションコントローラー
	std::shared_ptr<AnimationController>m_animationController;
};

