#pragma once

class GameManager
{
public:
	static GameManager& GetInstance();

	int GetKillCount()const { return m_killCount; }

	int m_killCount;
private:
	GameManager() :m_killCount(0){};
};

