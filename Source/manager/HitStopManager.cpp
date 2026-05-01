#include "HitStopManager.h"

void HitStopManager::Update()
{
	m_delayFrame--;
	if (m_delayFrame < 0)
	{
		if (m_hitStopFrame > 0)
		{
			m_hitStopFrame--;
		}
	}
}

void HitStopManager::Start(int frame, int delay)
{
	m_delayFrame = delay;

	if (frame > m_hitStopFrame)
	{
		m_hitStopFrame = frame;
	}
}

bool HitStopManager::IsHitStop() const
{
	if (m_delayFrame > 0)
	{
		return false;
	}
	return m_hitStopFrame > 0;
}
