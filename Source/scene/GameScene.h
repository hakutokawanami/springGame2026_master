#pragma once
#include "scene/SceneBase.h"
#include"game/manager/EnemyManager.h"
#include"game/manager/HitStopManager.h"

class InputManager;
class GamePlayer;
class Sword;
class SkyBox;
class Ground;
class GameScene : public SceneBase
{
public:
	GameScene(SceneController& controller);
	~GameScene();
	void Update(InputManager& input)override;
	void Draw()override;

private:
	//フェードイン更新
	void FadeInUpdate(InputManager&);
	//通常更新
	void NormalUpdate(InputManager&);
	//フェードアウト更新
	void FadeOutUpdate(InputManager&);
	//Updateメンバ関数を代入できるメンバ関数ポインタ
	using UpdateFunc_t = void (GameScene::*)(InputManager&);
	UpdateFunc_t m_update;

	//通常Draw
	void NormalDraw();
	//フェードDraw
	void FadeDraw();
	//Drawメンバ関数を代入できるメンバ関数ポインタ
	using DrawFunc_t = void(GameScene::*)();
	DrawFunc_t m_draw;

	void DrawGrid();
	//当たり判定
	void CheckCollision();
	void CheckAttackCollision();
	void ChackEnemyDistanceCollision();

	//フェード用のフレームカウンター
	int m_frame;

	//プレイヤー
	std::shared_ptr<GamePlayer>m_player;
	//エネミーマネージャー
	EnemyManager m_enemyManager;
	//剣
	std::shared_ptr<Sword>m_sword;
	//ヒットストップマネージャー
	HitStopManager m_hitStopManager;
	//地面
	std::shared_ptr<Ground>m_ground;

	int m_frameCount;

	//プレイヤーのモデル
	int m_playerModelHandle;
	//剣のモデルハンドル
	int m_swordModelHandle;

	int m_skyFrontHandle;
	int m_skyLeftHandle;
	int m_skyRightHandle;
	int m_skyBackHandle;
	int m_skyUpHandle;
	int m_skyBottomHandle;

	int m_groundModelHandle;

	//スカイボックス
	std::shared_ptr<SkyBox>m_skyBox;

	int m_time;
};

