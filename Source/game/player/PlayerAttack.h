#pragma once
#include"system/Vector3.h"
#include"collider/SphereCollider.h"
class PlayerAttack
{
public:
	PlayerAttack(const Vector3& pos,float radius,int life);

	void Update();
	void Draw();
	bool IsDead()const;
	bool IsActive()const;

	SphereCollider& GetCol() { return m_sphereCol; }

private:
	Vector3 m_position;
	float m_radius;
	int m_life;
	bool m_isDead;
	bool m_isActive;
	int m_timer;

	SphereCollider m_sphereCol;
};

