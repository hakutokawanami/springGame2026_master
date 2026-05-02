#include "TitleEnemy.h"
#include<DxLib.h>
#include"graphics/AnimationController.h"
TitleEnemy::TitleEnemy(int modelHandle,const Vector3& pos)
{
	m_modelHandle = MV1DuplicateModel(modelHandle);
	m_position = pos;
}

TitleEnemy::~TitleEnemy()
{
	MV1DeleteModel(m_modelHandle);
}

void TitleEnemy::Init()
{
	MV1SetPosition(m_modelHandle, VGet(m_position.x, m_position.y, m_position.z));
	//アニメーションコントローラー
	m_animationController = std::make_shared<AnimationController>(m_modelHandle);
	//アニメーション登録
	m_animationController->AddAnimation("Idle", MV1GetAnimIndex(m_modelHandle, L"RigPawn|sit_floor_idle_a"));
	//最初のアニメーション
	m_animationController->Play("Idle", true, 0.2f);
}

void TitleEnemy::End()
{
}

void TitleEnemy::Update()
{
	m_animationController->Update();
	MV1SetPosition(m_modelHandle, VGet(m_position.x, m_position.y, m_position.z));
	//Y軸回転設定
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_yaw, 0.0f));
}

void TitleEnemy::Draw()
{
	MV1DrawModel(m_modelHandle);
}

void TitleEnemy::Rotate(const Vector3 vec)
{
	//進行方向に回転
	if (vec.Length() > 0.0f)
	{
		m_yaw = atan2f(-vec.x, -vec.z);
	}
	//Y軸回転設定
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_yaw, 0.0f));
}

