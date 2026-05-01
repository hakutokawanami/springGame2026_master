#include "SphereCollider.h"
#include<DxLib.h>
SphereCollider::SphereCollider():
	m_center({0.0f,0.0f,0.0f}),
	m_radius(1.0f)
{
}
SphereCollider::SphereCollider(const Vector3& center, float radius):
	m_center(center),
	m_radius(radius)
{
}

bool SphereCollider::IsCollide(const SphereCollider& other) const
{ 
	//中心座標間の距離を出す
	Vector3 diff = m_center - other.m_center;
	float dist = diff.Length();

	//それぞれの半径の合計
	float radiusSum = m_radius + other.m_radius;
	//中心座標間の距離が半径の合計よりも短ければ当たっている
	return dist <= radiusSum;
}

Vector3 SphereCollider::ResolveCollision(SphereCollider& other)
{
	//中心座標間の距離を出す
	Vector3 diff = m_center - other.m_center;
	float dist = diff.Length();
	//それぞれの半径の合計
	float radiusSum = m_radius + other.m_radius;
	//当たっていなければ何もしない
	if (dist > radiusSum)
	{
		return{0.0f,0.0f,0.0f};
	}
	
	if (dist < 0.0001f)
	{
		diff = { 1.0f,0.0f,0.0f };
		dist = 0.00001f;
	}
	//正規化
	Vector3 normal = diff * (1.0f / dist);
	//押し戻す量
	float penetration = radiusSum - dist;
	//押し戻す
	m_center += (normal * penetration);
	//押し戻すベクトルを返す
	return normal * penetration;
}

void SphereCollider::Draw()
{
	DrawSphere3D(VGet(m_center.x, m_center.y, m_center.z),m_radius,4,0x00ff00,0x00ff00,false);
}
