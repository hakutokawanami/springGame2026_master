#pragma once
class HitStopManager
{
public:
	void Update();

	void Start(int frame,int delay);

	bool IsHitStop()const;

private:
	int m_hitStopFrame;
	int m_delayFrame;
};

