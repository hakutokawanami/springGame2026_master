#pragma once
#include"../system/Vector3.h"
class SphereCollider
{
public:
	SphereCollider();
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="center">中心座標</param>
	/// <param name="radius">半径</param>
	SphereCollider(const Vector3& center, float radius);
	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="other">判定をする相手</param>
	/// <returns>当たっているかどうか</returns>
	bool IsCollide(const SphereCollider& other)const;
	
	/// <summary>
	/// 押し戻し
	/// </summary>
	/// <param name="other">判定をする相手</param>
	/// <returns>押し戻し量</returns>
	Vector3 ResolveCollision(SphereCollider& other);
	//デバッグ表示用
	void Draw();

public:
	//中心座標
	Vector3 m_center;
	//半径
	float m_radius;
};

