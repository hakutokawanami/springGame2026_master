#include "GamePlayer.h"
#include"../base/PlayerStateBase.h"
#include"../PlayerState/PlayerIdleState.h"
#include<DxLib.h>
#include"../camera/Camera.h"
#include"../AnimationController.h"
#include"../PlayerAttack.h"
#include"../manager/EffectManager.h"
#include"../system/Matrix4x4.h"
namespace
{
	//スピード
	constexpr float kSpeed = 10.0f;
	constexpr float kRadius = 120.0f;
	constexpr Vector3 kSphereColOffset = { 0.0f,100.0f ,0.0f };

	constexpr float kXLimit = 2300.0f;
	constexpr float kZLimit = 2300.0f;

	constexpr float kCameraDistance = 700.0f;
}

GamePlayer::GamePlayer(int modelHandle) :
	m_forward({ 0.0f,0.0f,0.0f }),
	m_runSeDeray(0),
	m_isPlayRunSe(false)
{
	//ステートの初期化
	m_state = std::make_unique<PlayerIdleState>();
	//モデルのコピー
	m_modelHandle = modelHandle;
	//カメラ
	m_camera = std::make_shared<Camera>();
	//アニメーションコントローラー
	m_animationController = std::make_shared<AnimationController>(m_modelHandle);

	//アニメーション登録
	m_animationController->AddAnimation("Idle", MV1GetAnimIndex(m_modelHandle, L"RigPawn|idle_a"));
	m_animationController->AddAnimation("Run", MV1GetAnimIndex(m_modelHandle, L"RigPawn|run_a"));
	//m_animationController->AddAnimation("Attack", MV1GetAnimIndex(m_modelHandle, L"RigPawn|melee_onehand_slice_b"));
	m_animationController->AddAnimation("Attack", MV1GetAnimIndex(m_modelHandle, L"RigPawn|melee_onehand_jump_chop_a"));
	//最初のアニメーション
	m_animationController->Play("Idle", true, 0.2f);
}

GamePlayer::~GamePlayer()
{
	//モデル削除
	MV1DeleteModel(m_modelHandle);
}

void GamePlayer::Init()
{
	//カメラの初期化
	m_camera->Init(m_position, kCameraDistance);
	m_camera->Apply();

	Rotate(m_camera->GetForward().Normalized());
	//当たり判定の初期化
	m_sphereCol.m_center = m_position + kSphereColOffset;
	m_sphereCol.m_radius = kRadius;

	//ポジション設定
	MV1SetPosition(m_modelHandle, VGet(m_position.x, m_position.y, m_position.z));
	//Y軸回転設定
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_yaw, 0.0f));
}

void GamePlayer::End()
{
}

void GamePlayer::Update()
{
}

void GamePlayer::Update(InputManager& input)
{
	m_velocity = { 0.0f,0.0f,0.0f };

	//カメラ更新
	m_camera->Update(m_position, input);
	m_camera->Apply();

	//現在のステートのUpdate
	m_state->Update(*this, input, *m_camera);

	m_velocity.y = 0.0f;
	m_position += m_velocity;

	//アニメーション更新
	m_animationController->Update();
	//当たり判定更新
	m_sphereCol.m_center = m_position + kSphereColOffset;

	//攻撃判定の更新
	for (const auto& attack : m_attacks)
	{

		if (attack->IsDead())
		{
			m_attacks.erase(
				std::remove_if(
					m_attacks.begin(),
					m_attacks.end(),
					[](const std::unique_ptr<PlayerAttack>& atk)
					{
						return atk->IsDead();
					}),
				m_attacks.end()
			);
		}

		attack->Update();
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

	//モデルの変換行列情報を生成
	MATRIX scaleMtx = MGetScale(VECTOR{1.0f,1.0f,1.0f});
	MATRIX rotMtx = MGetRotY(m_yaw);
	MATRIX transMtx = MGetTranslate(VECTOR{ m_position.x,m_position.y,m_position.z });

	MATRIX mtx = scaleMtx;
	mtx = MMult(mtx, rotMtx);
	mtx = MMult(mtx, transMtx);

	MV1SetMatrix(m_modelHandle, mtx);
}

void GamePlayer::Draw()
{
	//モデル描画
	MV1DrawModel(m_modelHandle);

#ifdef _DEBUG

	DrawFormatString(16,32,0xffffff,L"pos : %f,%f,%f",m_position.x,m_position.y,m_position.z);

	//プレイヤーの当たり判定の描画
	m_sphereCol.Draw();

	//攻撃判定の描画
	for (const auto& attack : m_attacks)
	{
		attack->Draw();
	}

#endif // _DEBUG
}

void GamePlayer::ChangeState(std::unique_ptr<PlayerStateBase> newState)
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

void GamePlayer::Move(const Vector3& move)
{
	m_velocity = move * kSpeed;
}

void GamePlayer::Rotate(const Vector3& move)
{
	//進行方向に回転
	if (move.Length() > 0.0f)
	{
		m_yaw = atan2f(-move.x, -move.z);
	}
}

void GamePlayer::Attack()
{
	m_forward.x = -sinf(m_yaw);
	m_forward.y = 0.0f;
	m_forward.z = -cosf(m_yaw);
	m_forward.Normalize();

	Vector3 pos = m_position + m_forward * 200.0f;
	pos += kSphereColOffset;
	m_attacks.push_back(std::make_unique<PlayerAttack>(pos, kRadius, 40));
}

void GamePlayer::UpdatePos()
{
	m_position = m_sphereCol.m_center - kSphereColOffset;
}
