#pragma once
#include "../base/Character.h"
#include<memory>
#include<vector>
#include"../collider/SphereCollider.h"
#include"../base/PlayerBase.h"
class PlayerStateBase;
class InputManager;
class Camera;
class AnimationController;
class SphereCollider;
class PlayerAttack;
class GamePlayer :public PlayerBase
{
public:
	//コンストラクタでモデルを受け取る
	GamePlayer(int modelHandle);
	~GamePlayer();

	void Init()override;
	void End()override;
	void Update()override;
	void Update(InputManager& input)override;
	void Draw()override;
	/// <summary>
	/// ステートを切り替える関数
	/// </summary>
	/// <param name="newState">切り替えるステート</param>
	void ChangeState(std::unique_ptr<PlayerStateBase>newState);
	/// <summary>
	/// プレイヤー移動関数
	/// </summary>
	/// <param name="move">方向</param>
	void Move(const Vector3& move);
	/// <summary>
	/// プレイヤー回転関数
	/// </summary>
	/// <param name="move">方向</param>
	void Rotate(const Vector3& move);
	/// <summary>
	///	攻撃する
	/// </summary>
	void Attack();

	void UpdatePos();

	Vector3& GetPos() { return m_position; }	

	SphereCollider& GetCol() { return m_sphereCol; }

	Vector3& GetVelocity() { return m_velocity; }

	float GetYaw() { return m_yaw; }

	std::vector<std::unique_ptr<PlayerAttack>>& GetAttacks() { return m_attacks; }

	//アニメーションコントローラー
	std::shared_ptr<AnimationController> GetAnimController() { return m_animationController; }

	std::shared_ptr<Camera>& GetCamera() { return m_camera; }

	int GetRunSeDelay() { return m_runSeDeray; }

	void RunSeDelay() { m_runSeDeray++; }

	void ResetRunSeDelay() { m_runSeDeray = 0; }

	bool IsPlayRunSe() { return m_isPlayRunSe; }

	void SetIsPlayRunSe(bool is) { m_isPlayRunSe = is; }

private:
	//現在のステート
	std::unique_ptr<PlayerStateBase>m_state;
	//カメラを持つ
	std::shared_ptr<Camera>m_camera;
	//アニメーションコントローラー
	std::shared_ptr<AnimationController>m_animationController;
	//球の当たり判定
	SphereCollider m_sphereCol;
	//攻撃判定
	std::vector<std::unique_ptr<PlayerAttack>>m_attacks;
	//向いている方向
	Vector3 m_forward;
	//runSeを再生するまでの時間
	int m_runSeDeray;
	bool m_isPlayRunSe;
};

