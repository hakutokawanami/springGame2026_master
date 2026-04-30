#include "SoundManager.h"
#include<DxLib.h>
#include<cassert>

std::unordered_map<std::string, int>SoundManager::m_bgmHandles;
std::unordered_map<std::string, int>SoundManager::m_seHandles;
int SoundManager::m_currentBGM = -1;
int SoundManager::m_fadeFrame = 0;
int SoundManager::m_fadeTimer = 0;

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
	for (auto se : m_seHandles)
	{
		DeleteSoundMem(se.second);
	}

	for (auto bgm : m_bgmHandles)
	{
		DeleteSoundMem(bgm.second);
	}
}

void SoundManager::Init()
{
	m_seHandles["attack"] = LoadSoundMem(L"data/se/Attack.mp3");
	assert(m_seHandles["attack"] > -1);
	m_seHandles["hit"] = LoadSoundMem(L"data/se/Hit.mp3");
	assert(m_seHandles["hit"] > -1);
	m_seHandles["start"] = LoadSoundMem(L"data/se/Start.mp3");
	assert(m_seHandles["start"] > -1);
	m_seHandles["return"] = LoadSoundMem(L"data/se/Return.mp3");
	assert(m_seHandles["return"] > -1);
	m_seHandles["ko"] = LoadSoundMem(L"data/se/KO.mp3");
	assert(m_seHandles["ko"] > -1);
	m_seHandles["playerRun"] = LoadSoundMem(L"data/se/PlayerRun.mp3");
	assert(m_seHandles["playerRun"] > -1);
	m_seHandles["spawn"] = LoadSoundMem(L"data/se/Spawn.mp3");
	assert(m_seHandles["spawn"] > -1);

	m_bgmHandles["title"] = LoadSoundMem(L"data/bgm/Title.mp3");
	assert(m_bgmHandles["title"] > -1);
	m_bgmHandles["game"] = LoadSoundMem(L"data/bgm/Game.mp3");
	assert(m_bgmHandles["game"] > -1);
	m_bgmHandles["result"] = LoadSoundMem(L"data/bgm/Result.mp3");
	assert(m_bgmHandles["result"] > -1);
}

void SoundManager::Update()
{
	if (m_fadeTimer > 0 && m_currentBGM != -1)
	{
		float rate = static_cast<float>(m_fadeTimer) / m_fadeFrame;
		int volume = static_cast<int>(160 * rate);

		ChangeVolumeSoundMem(volume, m_currentBGM);

		m_fadeTimer--;
		if (m_fadeTimer == 0)
		{
			StopSoundMem(m_currentBGM);
			m_currentBGM = -1;
		}
	}
}

void SoundManager::PlayBGM(const std::string& name, bool loop)
{
	auto it = m_bgmHandles.find(name);
	if (it == m_bgmHandles.end())
	{
		return;
	}

	m_fadeTimer = 0;
	m_fadeFrame = 0;

	if (m_currentBGM != -1)
	{
		StopSoundMem(m_currentBGM);
	}

	m_currentBGM = it->second;
	ChangeVolumeSoundMem(160, m_currentBGM);
	PlaySoundMem(m_currentBGM, loop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK);
}

void SoundManager::StopBGM()
{
	if (m_currentBGM != -1)
	{
		StopSoundMem(m_currentBGM);
		m_currentBGM = -1;
	}
}

void SoundManager::FadeOutBGM(int frame)
{
	m_fadeFrame = frame;
	m_fadeTimer = frame;
	if (m_currentBGM != -1)
	{
		SetVolumeSoundMem(160, m_currentBGM);
	}
}

void SoundManager::PlaySE(const std::string& name, bool loop)
{
	auto it = m_seHandles.find(name);
	if (it == m_seHandles.end())
	{
		return;
	}
	if (loop)
	{
		PlaySoundMem(it->second, DX_PLAYTYPE_LOOP);
	}
	else
	{
		PlaySoundMem(it->second, DX_PLAYTYPE_BACK);
	}
}

void SoundManager::StopSE(const std::string& name)
{
	auto it = m_seHandles.find(name);
	if (it == m_seHandles.end())
	{
		return;
	}
	StopSoundMem(it->second);
}
