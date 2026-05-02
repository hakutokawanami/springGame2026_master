#pragma once
#include"system/Vector3.h"
/// <summary>
/// ゲームオブジェクト基底クラス
/// </summary>
class GameObject
{
public:
	virtual ~GameObject()=default;
	/// <summary>
	/// 初期化関数
	/// </summary>
	virtual void Init()abstract;
	/// <summary>
	/// 終了時処理関数
	/// </summary>
	virtual void End()abstract;
	/// <summary>
	/// 更新関数
	/// </summary>
	virtual void Update()abstract;
	/// <summary>
	/// 描画関数
	/// </summary>
	virtual void Draw()abstract;

	Vector3 GetPos()const { return m_position; }
protected:
	//ポジション
	Vector3 m_position{};
	//生きているかどうか
	bool m_isActive = true;
	//左右回転
	float m_yaw = 0.0f;
	//上下回転
	float m_pitch = 0.0f;
};

