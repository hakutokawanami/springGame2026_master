#include "Villager.h"
#include<DxLib.h>
#include"../AnimationController.h"
Villager::Villager(int modelHandle,const Vector3& pos,scene name)
{
	m_modelHandle = MV1DuplicateModel(modelHandle);
	m_position = pos;

	m_animationController = std::make_shared<AnimationController>(m_modelHandle);

	//アニメーション登録
	m_animationController->AddAnimation("Idle", MV1GetAnimIndex(m_modelHandle, L"RigPawn|cheer_idle_b"));
	m_animationController->AddAnimation("sit", MV1GetAnimIndex(m_modelHandle, L"RigPawn|sit_floor_idle_a"));
	if (name == scene::title)
	{
		m_animationController->Play("sit", true);
	}
	else if (name == scene::result)
	{
		m_animationController->Play("Idle", true);
	}
}

Villager::~Villager()
{
	MV1DeleteModel(m_modelHandle);
}

void Villager::Init()
{
	MV1SetPosition(m_modelHandle, { m_position.x,m_position.y,m_position.z });
}

void Villager::End()
{
}

void Villager::Update()
{
	m_animationController->Update();
	MV1SetPosition(m_modelHandle, { m_position.x,m_position.y,m_position.z });
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_yaw, 0.0f));
}

void Villager::Draw()
{
	MV1DrawModel(m_modelHandle);
}

void Villager::Rotate(const Vector3 vec)
{
	//進行方向に回転
	if (vec.Length() > 0.0f)
	{
		m_yaw = atan2f(-vec.x, -vec.z);
	}
	//Y軸回転設定
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_yaw, 0.0f));
}
