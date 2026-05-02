#include "EnemyManager.h"
#include"game/enemy/Enemy.h"
#include<DxLib.h>
#include"graphics/EffectManager.h"
#include"GameManager.h"
#include"SoundManager.h"
namespace
{
	constexpr int kSpawnIntervalFrame = 60;
}

EnemyManager::EnemyManager() :
	m_modelHandle(-1),
	m_frame(0),
	m_waveNum(0)
{
	m_spawnPos[0] = { 0.0f,0.0f,0.0f };
	m_spawnPos[1] = { 0.0f,0.0f,0.0f };
	m_spawnPos[2] = { 0.0f,0.0f,0.0f };
}
void EnemyManager::Init(int modelHandle)
{
	m_modelHandle = modelHandle;
}
void EnemyManager::Update()
{
	// 更新
	for (auto& enemy : m_enemies)
	{
		enemy->Update();
	}

	// 死亡した敵を削除
	m_enemies.erase(
		std::remove_if(m_enemies.begin(), m_enemies.end(),
			[](const std::unique_ptr<Enemy>& enemy)
			{
				return enemy->IsDelete();
			}),
		m_enemies.end()
	);

	// 全滅したら生成
	if (m_enemies.empty())
	{
		if (m_frame == 0)
		{
			if (m_waveNum == 0)
			{
				for (int i = 0; i < 4; i++)
				{
					m_spawnPos[i].x = 1000.0f - GetRand(2000);
					m_spawnPos[i].y = 0.0f;
					m_spawnPos[i].z = 1000.0f - GetRand(2000);
					EffectManager::Play("spawn", m_spawnPos[i], 0.0f);
					SoundManager::PlaySE("spawn", false);
				}
			}
			else if (m_waveNum == 1)
			{
				for (int i = 0; i < 6; i++)
				{
					m_spawnPos[i].x = 1000.0f - GetRand(2000);
					m_spawnPos[i].y = 0.0f;
					m_spawnPos[i].z = 1000.0f - GetRand(2000);
					EffectManager::Play("spawn", m_spawnPos[i], 0.0f);
					SoundManager::PlaySE("spawn", false);
				}
			}
			else if (m_waveNum == 2)
			{
				for (int i = 0; i < 10; i++)
				{
					m_spawnPos[i].x = 1000.0f - GetRand(2000);
					m_spawnPos[i].y = 0.0f;
					m_spawnPos[i].z = 1000.0f - GetRand(2000);
					EffectManager::Play("spawn", m_spawnPos[i], 0.0f);
					SoundManager::PlaySE("spawn", false);
				}
			}
		}

		if (m_frame++ > kSpawnIntervalFrame)
		{
			Spawn(m_spawnPos);
			m_frame = 0;
		}
	}
}

void EnemyManager::Draw()
{
	for (auto& enemy : m_enemies)
	{
		enemy->Draw();
	}
}

void EnemyManager::Spawn(Vector3 pos[])
{	
	if (m_waveNum == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			m_enemies.push_back(std::make_unique<Enemy>(m_modelHandle, pos[i]));
			m_enemies.back()->Init();
		}
	}
	else if (m_waveNum == 1)
	{
		for (int i = 0; i < 6; i++)
		{
			m_enemies.push_back(std::make_unique<Enemy>(m_modelHandle, pos[i]));
			m_enemies.back()->Init();
		}
	}
	else if (m_waveNum == 2)
	{
		for (int i = 0; i < 10; i++)
		{
			m_enemies.push_back(std::make_unique<Enemy>(m_modelHandle, pos[i]));
			m_enemies.back()->Init();
		}
	}
	m_waveNum++;
}
