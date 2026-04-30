#include "GameScene.h"
#include"../SceneController.h"
#include"DxLib.h"
#include"../Application.h"
#include"../character/GamePlayer.h"
#include"../Sword.h"
#include"../manager/EffectManager.h"
#include"../SkyBox.h"
#include"../Ground.h"
#include"../camera/Camera.h"
#include"../PlayerAttack.h"
#include"ResultScene.h"
#include"../manager/InputManager.h"
#include"../manager/GameManager.h"
#include"../manager/ResourceManager.h"
#include"../manager/FontManager.h"
#include"../manager/SoundManager.h"
namespace
{ 
	//フェード時間
	constexpr int kFadeInterval = 60;
	//制限時間
	constexpr int kTimeLimit = 60;
	//敵を倒す目標
	constexpr int kRequiredEnemyKills = 20;
}

GameScene::GameScene(SceneController& controller):
	SceneBase(controller),
	m_frameCount(0),
	m_playerModelHandle(-1),
	m_swordModelHandle(-1),
	m_skyFrontHandle(-1),
	m_skyLeftHandle(-1),
	m_skyRightHandle(-1),
	m_skyBackHandle(-1),
	m_skyUpHandle(-1),
	m_skyBottomHandle(-1),
	m_hitStopManager(),
	m_groundModelHandle(-1),
	m_time(kTimeLimit)
{
	//最初はフェードインから
	m_update = &GameScene::FadeInUpdate;
	//最初はフェード描画
	m_draw = &GameScene::FadeDraw;
	//フェード用のフレームカウンター初期化
	m_frame = kFadeInterval;
	//プレイヤーのモデルロード
	m_playerModelHandle = MV1LoadModel(L"data/player.mv1");
	//プレイヤー作成
	m_player = std::make_shared<GamePlayer>(m_playerModelHandle);
	//プレイヤー初期化
	m_player->Init();
	//剣のモデルロード
	m_swordModelHandle = MV1LoadModel(L"data/sword.mv1");
	//剣作成
	m_sword = std::make_shared<Sword>(m_swordModelHandle, m_player->GetModelHandle());
	//剣初期化
	m_sword->Init();
	//エネミーマネージャー初期化
	m_enemyManager.Init(MV1LoadModel(L"data/enemy.mv1"));
	//エフェクトマネージャー初期化
	EffectManager::Init();
	//エフェクトのロード
	EffectManager::Load("hit", "data/ToonHit.efk");
	EffectManager::Load("sword", "data/sword.efk");
	EffectManager::Load("spawn", "data/spawn.efk");
	//スカイボックスのロード
	m_skyFrontHandle = LoadGraph(L"data/sky_front.png");
	m_skyLeftHandle = LoadGraph(L"data/sky_left.png");
	m_skyRightHandle = LoadGraph(L"data/sky_right.png");
	m_skyBackHandle = LoadGraph(L"data/sky_back.png");
	m_skyUpHandle = LoadGraph(L"data/sky_up.png");
	m_skyBottomHandle = LoadGraph(L"data/sky_bottom.png");
	//スカイボックス作成&初期化
	m_skyBox = std::make_shared<SkyBox>();
	m_skyBox->Init(ResourceManager::GetInstance().m_skyBoxHandles);
	m_skyBox->SetCameraPos(m_player->GetCamera()->GetPos());
	//地面のモデルロード
	m_groundModelHandle = MV1LoadModel(L"data/ground.mv1");
	//地面作成&初期化
	m_ground = std::make_shared<Ground>();
	m_ground->Init(m_groundModelHandle);

	GameManager::GetInstance().m_killCount = 0;

	SoundManager::PlayBGM("game");
}

GameScene::~GameScene()
{
	MV1DeleteModel(m_playerModelHandle);
	MV1DeleteModel(m_swordModelHandle);
	EffectManager::End();
	DeleteGraph(m_skyFrontHandle);
	DeleteGraph(m_skyLeftHandle);
	DeleteGraph(m_skyRightHandle);
	DeleteGraph(m_skyBackHandle);
	DeleteGraph(m_skyUpHandle);
	DeleteGraph(m_skyBottomHandle);
}

void GameScene::Update(InputManager& input)
{
	(this->*m_update)(input);
}

void GameScene::Draw()
{
	(this->*m_draw)();
}

void GameScene::FadeInUpdate(InputManager&)
{
	if (--m_frame <= 0)
	{
		m_update = &GameScene::NormalUpdate;
		m_draw = &GameScene::NormalDraw;
		return;
	}
}

void GameScene::NormalUpdate(InputManager& input)
{
	//ヒットストップの更新
	m_hitStopManager.Update();
	//フレームカウント
	m_frameCount++;
	//プレイヤー更新
	m_player->Update(input);
	//ヒットストップ中は敵の更新や当たり判定を行わない
	if (m_hitStopManager.IsHitStop())
	{
		return;
	}
	//敵マネージャー更新
	m_enemyManager.Update();
	//敵とプレイヤーの当たり判定
	CheckCollision();
	//攻撃と敵の当たり判定
	CheckAttackCollision();
	//敵との距離の当たり判定
	ChackEnemyDistanceCollision();
	//プレイヤーの位置更新
	m_player->UpdatePos();
	//剣の更新
	m_sword->Update();
	//エフェクトの更新
	EffectManager::Update();
	//スカイボックスの位置更新
	m_skyBox->SetCameraPos(m_player->GetCamera()->GetPos());
	//敵を目標数倒したら
	if (GameManager::GetInstance().GetKillCount() >= kRequiredEnemyKills)
	{
		m_update = &GameScene::FadeOutUpdate;
		m_draw = &GameScene::FadeDraw;
		SoundManager::FadeOutBGM(kFadeInterval);
	}

#ifdef _DEBUG
	if (input.IsTriggered("SELECT"))
	{
		GameManager::GetInstance().m_killCount = 19;
	}
#endif // _DEBUG
}

void GameScene::FadeOutUpdate(InputManager&)
{
	if (m_frame++ >= kFadeInterval)
	{
		//シーンの切り替え
		m_controller.ChangeScene(std::make_shared<ResultScene>(m_controller));
		return;
	}
}

void GameScene::NormalDraw()
{
	auto wsize = Application::GetInstance().GetWindowSize();
	VECTOR light = {m_player->GetCamera()->GetForward().x,m_player->GetCamera()->GetForward().y,m_player->GetCamera()->GetForward().z};
	SetLightDirection(light);
	//スカイボックス描画
	m_skyBox->Draw();
	//プレイヤー描画
	m_player->Draw();
	//敵描画
	m_enemyManager.Draw();
	//剣描画
	m_sword->Draw();
	//地面描画
	m_ground->Draw();
	//エフェクト描画
	EffectManager::Draw();

	wchar_t killCountText[64];
	swprintf_s(killCountText, L"%d / %d", GameManager::GetInstance().GetKillCount(), kRequiredEnemyKills);
	FontManager::DrawCenterString(wsize.w / 2, wsize.h / 7, killCountText, 0xff00ff, FontType::UI);
#ifdef _DEBUG
	DrawGrid();
	DrawString(0, 0, L"SceneMain", GetColor(255, 255, 255));
	DrawFormatString(0, 16, GetColor(255, 255, 255), L"FRAME:%d", m_frameCount);
	DrawFormatString(96, 16, GetColor(255, 255, 255), L"KILL COUNT:%d", GameManager::GetInstance().m_killCount);
	DrawFormatString(236, 16, GetColor(255, 255, 255), L"TIME:%d", m_time);
#endif // DEBUG
}

void GameScene::FadeDraw()
{
	NormalDraw();

	const Size& wsize = Application::GetInstance().GetWindowSize();
	//フェード処理
	float rate = static_cast<float>(m_frame) / static_cast<float>(kFadeInterval);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,static_cast<int>( 255 * rate));
	DrawBox(0, 0, wsize.w, wsize.h, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, static_cast<int>( 255 * rate));
}

void GameScene::CheckCollision()
{
	//敵の配列取得
	auto& enemies = m_enemyManager.GetEnemies();
	for (auto& enemy : enemies)
	{
		//敵が死んでいたら当たり判定を行わない
		if (enemy->IsDead())continue;
		//押し戻し量の取得
		Vector3 push = m_player->GetCol().ResolveCollision(enemy->GetCol());
		//押し戻し量が0より大きいとき
		if (push.Length() > 0.0f)
		{
			//押し戻し量の法線をとる
			Vector3 normal = push.Normalized();
			//プレイヤーの速度を取得
			Vector3& velocity = m_player->GetVelocity();
			//速度と法線の内積をとる
			float dot = velocity.Dot(normal);
			//内積が0より小さいとき
			if (dot < 0.0f)
			{
				//速度から法線方向の成分を引く
				velocity -= normal * dot;
			}
			//y方向の速度は0にする
			velocity.y = 0.0f;
			//プレイヤーを移動させる
			m_player->Move(velocity);
		}
	}
}

void GameScene::CheckAttackCollision()
{
	//敵の配列と攻撃の配列を取得
	auto& enemies = m_enemyManager.GetEnemies();
	auto& attacks = m_player->GetAttacks();

	for (auto& atk : attacks)
	{
		for (auto& enemy : enemies)
		{
			//敵が死んでいたら当たり判定を行わない
			if (enemy->IsDead())continue;
			//攻撃が有効なとき
			if (atk->IsActive())
			{
				//攻撃と敵が当たっているとき
				if (atk->GetCol().IsCollide(enemy->GetCol()))
				{
					//最後の一体を倒す時
					if (GameManager::GetInstance().GetKillCount() >= kRequiredEnemyKills - 1)
					{
						SoundManager::PlaySE("ko", false);
					}

					//敵に当たったことを伝える
					enemy->Hit();
					//ヒットストップ
					m_hitStopManager.Start(7, 0);
					//カメラシェイク開始
					m_player->GetCamera()->ShakeStart(20.0f, 7, 0);
					break;
				}
			}
		}
	}
}

void GameScene::ChackEnemyDistanceCollision()
{
	//敵の配列を取得
	auto& enemies = m_enemyManager.GetEnemies();

	for (auto& enemy : enemies)
	{
		//敵が死んでいたら当たり判定を行わない
		if (enemy->IsDead())continue;
		//敵とプレイヤーの距離が一定以下になったら
		if (enemy->GetDistanceCol().IsCollide(m_player->GetCol()))
		{
			//敵が逃げる方向をプレイヤーの位置から計算する
			Vector3 vec = enemy->GetPos() - m_player->GetPos();
			//正規化する
			vec.Normalize();
			//敵に当たったことを伝える
			enemy->DistanceHit(vec);
		}
		else
		{
			//敵が逃げる方向をリセットす
			enemy->SetLastDistanceHit(false);
		}
	}
}

void GameScene::DrawGrid()
{
	// 直線の始点と終点
	VECTOR startPos;
	VECTOR endPos;

	for (int z = -300; z <= 300; z += 100)
	{
		startPos = VGet(-300.0f, 0.0f, static_cast<float>(z));
		endPos = VGet(300.0f, 0.0f, static_cast<float>(z));
		DrawLine3D(startPos, endPos, 0xff0000);
	}
	for (int x = -300; x <= 300; x += 100)
	{
		startPos = VGet(static_cast<float>(x), 0.0f, -300.0f);
		endPos = VGet(static_cast<float>(x), 0.0f, 300.0f);
		DrawLine3D(startPos, endPos, 0x0000ff);
	}
}
