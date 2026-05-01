#include "PlayerAttack.h"
#include<DxLib.h>

namespace
{
	constexpr int kActivateDelay = 20;
}

PlayerAttack::PlayerAttack(const Vector3& pos, float radius, int life):
	m_position(pos),
	m_radius(radius),
	m_life(life),
	m_isDead(false),
	m_isActive(false),
	m_timer(0)
{

}

void PlayerAttack::Update()
{
	if (m_timer++ > kActivateDelay)
	{
		m_isActive = true;
	}

	if (m_life-- <= 0)
	{
		m_isDead = true;
	}

	m_sphereCol.m_center = m_position;
	m_sphereCol.m_radius = m_radius;
}

void PlayerAttack::Draw()
{
#ifdef _DEBUG
	if (m_isActive)
	{
		DrawSphere3D(VGet(m_position.x, m_position.y, m_position.z), m_radius, 8, 0x00ffff, 0x00ffff, false);
	}
	DrawFormatString(16, 16 * 20, 0xffffff, L"atkPos : %f,%f,%f", m_position.x, m_position.y, m_position.z);
#endif // _DEBUG
}

bool PlayerAttack::IsDead() const
{
	return m_isDead;
}

bool PlayerAttack::IsActive() const
{
	return m_isActive;
}
