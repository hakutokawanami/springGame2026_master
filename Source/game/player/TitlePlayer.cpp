#include "TitlePlayer.h"
#include<DxLib.h>
#include<cmath>
#include"state/PlayerStateBase.h"
#include"graphics/AnimationController.h"
TitlePlayer::TitlePlayer(int modelHandle)
{
	m_modelHandle = modelHandle;

	m_animationController = std::make_shared<AnimationController>(m_modelHandle);

	//アニメーション登録
	m_animationController->AddAnimation("Idle", MV1GetAnimIndex(m_modelHandle, L"RigPawn|sit_floor_idle_a"));
	m_animationController->Play("Idle", true);
}

TitlePlayer::~TitlePlayer()
{
	MV1DeleteModel(m_modelHandle);
}

void TitlePlayer::Init()
{
	m_position = { 0.0f, 0.0f, 0.0f };
}

void TitlePlayer::End()
{
}

void TitlePlayer::Update()
{
	m_animationController->Update();
	MV1SetPosition(m_modelHandle, VGet(m_position.x, m_position.y, m_position.z));
}

void TitlePlayer::Update(InputManager& input)
{
}

void TitlePlayer::Draw()
{
	MV1DrawModel(m_modelHandle);
}

void TitlePlayer::Rotate(const Vector3& move)
{
	//進行方向に回転
	if (move.Length() > 0.0f)
	{
		m_yaw = atan2f(-move.x, -move.z);
	}

	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_yaw, 0.0f));
}

void TitlePlayer::ChangeState(std::unique_ptr<PlayerStateBase> newState)
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
