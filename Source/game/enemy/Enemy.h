#pragma once
#include "base/Character.h"
#include"physics/SphereCollider.h"
#include"game/enemy/state/EnemyStateBase.h"
#include<memory>
class EnemyStateBase;
class AnimationController;
class Enemy :public Character
{
public:
	//コンストラクタでモデルを受け取る
	Enemy(int modelHandle,Vector3& pos);
	~Enemy();

	void Init()override;
	void End()override;
	void Update()override;
	void Draw()override;

	/// <summary>
	/// ステートを切り替える関数
	/// </summary>
	/// <param name="newState">切り替えるステート</param>
	void ChangeState(std::unique_ptr<EnemyStateBase>newState);

	bool IsDead() { return m_isDead; }

	bool IsDelete() { return m_isDelete; }

	bool IsChase() { return m_isChase; }

	SphereCollider& GetCol() { return m_sphereCol; }

	SphereCollider& GetDistanceCol() { return m_distanceCol; }

	Vector3& GetPos() { return m_position; }

	void Hit();

	void DistanceHit(Vector3& vec);

	void SetLastDistanceHit(bool isHit) { m_isLastDistanceHit = isHit; }	

	void Delete();

	void VelocityZero() { m_velocity = { 0.0f, 0.0f, 0.0f }; }

	void SetVelocity(Vector3& vec) { m_velocity = vec; }

	//アニメーションコントローラー
	std::shared_ptr<AnimationController> GetAnimController() { return m_animationController; }

private:
	std::unique_ptr<EnemyStateBase>m_state;

	//モデルハンドル
	int m_modelHandle;

	//アニメーションコントローラー
	std::shared_ptr<AnimationController>m_animationController;

	//球の当たり判定
	SphereCollider m_sphereCol;
	//プレイヤーを視認する当たり判定
	SphereCollider m_distanceCol;

	bool m_isDead;

	bool m_isDelete;

	bool m_isChase;

	bool m_isLastDistanceHit;

	Vector3 m_velocity;

	int m_count;

	int m_deleteDelayCount;
};

