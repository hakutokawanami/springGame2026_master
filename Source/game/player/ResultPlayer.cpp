#include "ResultPlayer.h"
#include<DxLib.h>
#include"../AnimationController.h"
#include"../base/PlayerStateBase.h"
ResultPlayer::ResultPlayer(int modelHandle)
{
	m_modelHandle = modelHandle;

	m_animationController = std::make_shared<AnimationController>(m_modelHandle);

	//アニメーション登録
	m_animationController->AddAnimation("Idle", MV1GetAnimIndex(m_modelHandle, L"RigPawn|cheer_idle_a"));
	m_animationController->Play("Idle", true);
}

ResultPlayer::~ResultPlayer()
{
	MV1DeleteModel(m_modelHandle);
}

void ResultPlayer::Init()
{
	m_position = { 0.0f,0.0f,-100.0f };
	MV1SetPosition(m_modelHandle, VGet(m_position.x, m_position.y, m_position.z));
}

void ResultPlayer::End()
{
}

void ResultPlayer::Update()
{
	m_animationController->Update();
	MV1SetPosition(m_modelHandle, VGet(m_position.x, m_position.y, m_position.z));
}

void ResultPlayer::Update(InputManager& input)
{
}

void ResultPlayer::Draw()
{
	MV1DrawModel(m_modelHandle);
}

void ResultPlayer::Rotate(const Vector3& move)
{
	//進行方向に回転
	if (move.Length() > 0.0f)
	{
		m_yaw = atan2f(-move.x, -move.z);
	}

	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_yaw, 0.0f));
}

void ResultPlayer::ChangeState(std::unique_ptr<PlayerStateBase> newState)
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
