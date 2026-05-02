#pragma once
#include"game/enemy/Enemy.h"

enum EnemyStateType
{
	Idle,
	Dead,
	Chase
};

class Enemy;
class EnemyStateBase
{
public:
	virtual ~EnemyStateBase() = default;
	/// <summary>
	/// その状態になったとき、一回だけ呼ばれる関数
	/// </summary>
	/// <param name="player">プレイヤーの参照</param>
	virtual void Enter(Enemy& enemy) = 0;
	/// <summary>
	/// その状態のとき毎フレーム呼ばれる関数
	/// </summary>
	/// <param name="player">プレイヤーの参照</param>
	/// <param name="input">入力を受け取るためのInputの参照</param>
	virtual void Update(Enemy& enemy) = 0;

	/// <summary>
	/// その状態が終わるとき、一回だけ呼ばれる関数
	/// </summary>
	/// <param name="player"></param>
	virtual void Exit(Enemy& enemy) = 0;
	/// <summary>
	/// 現在のステートを取得する関数
	/// </summary>
	/// <returns>現在のステート</returns>
	virtual EnemyStateType GetStateType()const = 0;

};

