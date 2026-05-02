#pragma once
#include "SceneBase.h"
#include<memory>
#include<vector>
class InputManager;
class ResultPlayer;
class SkyBox;
class Ground;
class Sword;
class Camera;
class Villager;
class ResultScene :public SceneBase
{
public:
	ResultScene(SceneController& controller);
	~ResultScene();
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
	using UpdateFunc_t = void (ResultScene::*)(InputManager&);
	UpdateFunc_t m_update;

	//通常Draw
	void NormalDraw();
	//フェードDraw
	void FadeDraw();
	//Drawメンバ関数を代入できるメンバ関数ポインタ
	using DrawFunc_t = void(ResultScene::*)();
	DrawFunc_t m_draw;

	//フェード用のフレームカウンター
	int m_frame;

	//プレイヤー
	std::shared_ptr<ResultPlayer>m_player;
	//スカイボックス
	std::shared_ptr<SkyBox>m_skyBox;
	//地面
	std::shared_ptr<Ground>m_ground;
	//カメラ
	std::shared_ptr<Camera>m_camera;
	//村人
	std::shared_ptr<Villager>m_villager;

	int m_playerModelHandle;
	int m_swordModelHandle;
	int m_enemyModelHandle;
	int m_groundModelHandle;
	int m_villagerModelHandle;
};

