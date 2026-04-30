#include "Enemy.h"
#include<DxLib.h>
#include"../EnemyState/EnemyIdleState.h"
#include"../AnimationController.h"
#include"../manager/EffectManager.h"
#include"../manager/GameManager.h"
#include"../manager/SoundManager.h"
namespace
{
	constexpr float kRadius = 120.0f;
	constexpr float kDistanceColRadius = 1200.0f;
	constexpr Vector3 kSphereColOffset = { 0.0f,100.0f ,0.0f };
	constexpr float kSpeed = 1.5f;

	constexpr float kXLimit = 2300.0f;
	constexpr float kZLimit = 2300.0f;

	constexpr int kDeleteDeray = 60;
}

Enemy::Enemy(int modelHandle, Vector3& pos) :
	m_modelHandle(-1),
	m_isDead(false),
	m_isDelete(false),
	m_velocity(0.0f, 0.0f, 0.0f),
	m_isChase(false),
	m_count(300),
	m_isLastDistanceHit(false),
	m_deleteDelayCount(0)
{
	//モデルのコピー
	m_modelHandle = MV1DuplicateModel(modelHandle);
	m_position = pos;
	m_state = std::make_unique<EnemyIdleState>();

	//アニメーションコントローラー
	m_animationController = std::make_shared<AnimationController>(m_modelHandle);

	//アニメーション登録
	m_animationController->AddAnimation("Idle", MV1GetAnimIndex(m_modelHandle, L"RigPawn|idle_a"));
	m_animationController->AddAnimation("Dead", MV1GetAnimIndex(m_modelHandle, L"RigPawn|collapse_b"));
	m_animationController->AddAnimation("Chase", MV1GetAnimIndex(m_modelHandle, L"RigPawn|run_a"));
	//最初のアニメーション
	m_animationController->Play("Idle", true, 0.2f);
}

Enemy::~Enemy()
{
	MV1DeleteModel(m_modelHandle);
}

void Enemy::Init()
{
	MV1SetPosition(m_modelHandle, VGet(m_position.x, m_position.y, m_position.z));
	m_sphereCol.m_center = m_position + kSphereColOffset;
	m_sphereCol.m_radius = kRadius;
	m_distanceCol.m_center = m_position;
	m_distanceCol.m_radius = kDistanceColRadius;
}

void Enemy::End()
{
}

void Enemy::Update()
{
	m_state->Update(*this);
	m_position += m_velocity * kSpeed;
	m_animationController->Update();

	//進行方向に回転
	if (m_velocity.Length() > 0.0f)
	{
		m_yaw = atan2f(-m_velocity.x, -m_velocity.z);
	}

	if (m_position.x >= kXLimit)
	{
		m_position.x = kXLimit;
		m_sphereCol.m_center.x = m_position.x + kSphereColOffset.x;
	}
	else if (m_position.x <= -kXLimit)
	{
		m_position.x = -kXLimit;
		m_sphereCol.m_center.x = m_position.x + kSphereColOffset.x;
	}

	if (m_position.z >= kZLimit)
	{
		m_position.z = kZLimit;
		m_sphereCol.m_center.z = m_position.z + kSphereColOffset.z;
	}
	else if (m_position.z <= -kZLimit)
	{
		m_position.z = -kZLimit;
		m_sphereCol.m_center.z = m_position.z + kSphereColOffset.z;
	}

	m_isChase = false;
	m_sphereCol.m_center = m_position + kSphereColOffset;
	m_sphereCol.m_radius = kRadius;
	m_distanceCol.m_center = m_position;
	m_distanceCol.m_radius = kDistanceColRadius;
	MV1SetPosition(m_modelHandle, VGet(m_position.x, m_position.y, m_position.z));
	//Y軸回転設定
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_yaw, 0.0f));
}

void Enemy::Draw()
{
	MV1DrawModel(m_modelHandle);
#ifdef _DEBUG
	m_sphereCol.Draw();
	m_distanceCol.Draw();
#endif // _DEBUG
}

void Enemy::ChangeState(std::unique_ptr<EnemyStateBase> newState)
{
	//今のステートと違うステートになるときしか通さない
	if (m_state != newState)
	{
		//現在のステートのExit関数を呼ぶ
		m_state->Exit(*this);
		//次のステートに切り替える
		m_state = std::move(newState);
		//切り替えた後のステートのEnter関数を呼ぶ
		m_state->Enter(*this);
	}
}

void Enemy::Hit()
{
	m_isDead = true;
}

void Enemy::DistanceHit(Vector3& vec)
{
	if (m_isLastDistanceHit)
	{
		if(m_count-- <=0)
		{
			m_velocity = vec;
			m_count = 300;
		}
		m_isChase = true;
		m_isLastDistanceHit = true;
	}
	else
	{
		m_count = 300;
		m_velocity = vec;
		m_isChase = true;
		m_isLastDistanceHit = true;
	}
}

void Enemy::Delete()
{
	m_isDelete = true;
	GameManager::GetInstance().m_killCount++;
}
