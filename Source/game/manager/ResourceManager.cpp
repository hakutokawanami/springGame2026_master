#include "ResourceManager.h"
#include"DxLib.h"
ResourceManager& ResourceManager::GetInstance()
{
	static ResourceManager instance;
	return instance;
}

void ResourceManager::LoadResources()
{
	m_playerModelHandle = MV1LoadModel(L"data/player.mv1");
	m_enemyModelHandle = MV1LoadModel(L"data/enemy.mv1");
	m_swordModelHandle = MV1LoadModel(L"data/sword.mv1");
	m_groundModelHandle = MV1LoadModel(L"data/ground.mv1");
	m_skyBoxHandles[0] = LoadGraph(L"data/sky_front.png");
	m_skyBoxHandles[1] = LoadGraph(L"data/sky_left.png");
	m_skyBoxHandles[2] = LoadGraph(L"data/sky_right.png");
	m_skyBoxHandles[3] = LoadGraph(L"data/sky_back.png");
	m_skyBoxHandles[4] = LoadGraph(L"data/sky_up.png");
	m_skyBoxHandles[5] = LoadGraph(L"data/sky_bottom.png");
	m_villagerModelHandle = MV1LoadModel(L"data/villager_f.mv1");
}

void ResourceManager::ReleaseResources()
{
	MV1DeleteModel(m_playerModelHandle);
	MV1DeleteModel(m_enemyModelHandle);
	MV1DeleteModel(m_swordModelHandle);
	MV1DeleteModel(m_groundModelHandle);
	for (int i = 0; i < 6; i++)
	{
		DeleteGraph(m_skyBoxHandles[i]);
	}
	MV1DeleteModel(m_villagerModelHandle);
}
