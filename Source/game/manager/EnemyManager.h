#pragma once
#include<vector>
#include<memory>
#include"../character/Enemy.h"
class Enemy;
/// <summary>
/// 敵を管理するクラス
/// </summary>
class EnemyManager
{
public:
	EnemyManager();
	/// <summary>
	/// モデルを受け取る
	/// </summary>
	void Init(int modelHandle);
	/// <summary>
	/// 敵全体の更新をする
	/// </summary>
	void Update();
	/// <summary>
	/// 敵全体の描画をする
	/// </summary>
	void Draw();
	/// <summary>
	/// 敵を生成する
	/// </summary>
	void Spawn(Vector3 pos[]);

	std::vector<std::unique_ptr<Enemy>>& GetEnemies() { return m_enemies; }

private:
	//敵を管理
	std::vector<std::unique_ptr<Enemy>>m_enemies;
	int m_modelHandle;

	int m_frame;

	Vector3 m_spawnPos[20];

	int m_waveNum;
};

