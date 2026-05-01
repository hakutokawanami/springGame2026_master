#pragma once
#include"../system/Matrix4x4.h"
#include<memory>
#include<map>
#include<string>
#include<vector>
//プレイヤーの状態の種類
enum class PlayerStateType
{
	//待機状態
	Idle,
	//移動状態
	Move,
	//攻撃状態
	Attack
};

class GamePlayer;
class TitlePlayer;
class ResultPlayer;
class InputManager;
class Camera;
class PlayerStateBase
{
public:
	virtual ~PlayerStateBase() = default;
	/// <summary>
	/// その状態になったとき、一回だけ呼ばれる関数
	/// </summary>
	/// <param name="player">プレイヤーの参照</param>
	virtual void Enter(GamePlayer& player) = 0;
	virtual void Enter(TitlePlayer& player) = 0;
	virtual void Enter(ResultPlayer& player) = 0;
	/// <summary>
	/// その状態のとき毎フレーム呼ばれる関数
	/// </summary>
	/// <param name="player">プレイヤーの参照</param>
	/// <param name="input">入力を受け取るためのInputの参照</param>
	virtual void Update(GamePlayer& player, InputManager& input, Camera& camera) = 0;
	virtual void Update(TitlePlayer& player, InputManager& input, Camera& camera) = 0;
	virtual void Update(ResultPlayer& player, InputManager& input, Camera& camera) = 0;
	/// <summary>
	/// その状態が終わるとき、一回だけ呼ばれる関数
	/// </summary>
	/// <param name="player"></param>
	virtual void Exit(GamePlayer& player) = 0;
	virtual void Exit(TitlePlayer& player) = 0;
	virtual void Exit(ResultPlayer& player) = 0;
	/// <summary>
	/// 現在のステートを取得する関数
	/// </summary>
	/// <returns>現在のステート</returns>
	virtual PlayerStateType GetStateType()const = 0;
protected:
};

