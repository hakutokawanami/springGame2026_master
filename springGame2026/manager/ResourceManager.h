#pragma once
class ResourceManager
{
public:
	static ResourceManager& GetInstance();
	//リソースのロード
	void LoadResources();
	//リソースの解放
	void ReleaseResources();

	int GetPlayerModelHandle() const { return m_playerModelHandle; }

	//プレイヤーモデル
	int m_playerModelHandle = -1;
	//剣モデル
	int m_swordModelHandle = -1;
	//敵モデル
	int m_enemyModelHandle = -1;
	//地面モデル
	int m_groundModelHandle = -1;
	//スカイボックスのテクスチャ
	int m_skyBoxHandles[6] = {-1, -1, -1, -1, -1, -1};
	//村人のモデル
	int m_villagerModelHandle = -1;
};

