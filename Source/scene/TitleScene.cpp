#include "TitleScene.h"
#include"core/Application.h"
#include"DxLib.h"
#include"GameScene.h"
#include"core/SceneController.h"
#include"game/manager/InputManager.h"
#include"game/manager/ResourceManager.h"
#include"game/player/TitlePlayer.h"
#include"game/weapon/Sword.h"
#include"game/stage/SkyBox.h"
#include"game/stage/Ground.h"
#include"game/camera/Camera.h"
#include"graphics/FontManager.h"
#include"game/enemy/TitleEnemy.h"
#include"game/mob/Villager.h"
#include"game/manager/SoundManager.h"
namespace
{
	constexpr int kFadeInterval = 60;
	constexpr float kCameraDistance = 350.0f;
	constexpr float kCameraTopLimit = -0.28f;
	constexpr float kCameraBottomLimit = -0.27f;
}

TitleScene::TitleScene(SceneController& controller):
	SceneBase(controller),
	m_playerModelHandle(-1),
	m_swordModelHandle(-1),
	m_enemyModelHandle(-1),
	m_groundModelHandle(-1)
{
	//最初はフェードインから
	m_update = &TitleScene::FadeInUpdate;
	//最初はフェード描画
	m_draw = &TitleScene::FadeDraw;
	//フェード用のフレームカウンター初期化
	m_frame = kFadeInterval;

	m_playerModelHandle = MV1DuplicateModel(ResourceManager::GetInstance().GetPlayerModelHandle());
	m_swordModelHandle = MV1DuplicateModel(ResourceManager::GetInstance().m_swordModelHandle);
	m_enemyModelHandle = MV1DuplicateModel(ResourceManager::GetInstance().m_enemyModelHandle);
	m_groundModelHandle = MV1DuplicateModel(ResourceManager::GetInstance().m_groundModelHandle);
	m_villagerModelHandle = MV1DuplicateModel(ResourceManager::GetInstance().m_villagerModelHandle);

	m_camera = std::make_shared<Camera>();
	m_camera->Init({ -65.0f,0.0f,0.0f },kCameraDistance,kCameraTopLimit,kCameraBottomLimit);
	m_camera->Apply();
	m_player = std::make_shared<TitlePlayer>(m_playerModelHandle);
	m_player->Init();
	m_player->Rotate(-m_camera->GetForward().Normalized());
	m_sword = std::make_shared<Sword>(m_swordModelHandle, m_player->GetModelHandle());
	m_sword->Init();
	m_villager = std::make_shared<Villager>(m_villagerModelHandle,Vector3{-130.0f,0.0f,0.0f},scene::title);
	m_villager->Init();
	m_villager->Rotate(m_camera->GetForward().Normalized());
	m_skyBox = std::make_shared<SkyBox>();
	m_skyBox->Init(ResourceManager::GetInstance().m_skyBoxHandles);
	m_skyBox->SetCameraPos(m_camera->GetPos());
	m_ground = std::make_shared<Ground>();
	m_ground->Init(m_groundModelHandle);

	SoundManager::PlayBGM("title");
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update(InputManager& input)
{
	(this->*m_update)(input);
}

void TitleScene::Draw()
{
	(this->*m_draw)();
}

void TitleScene::FadeInUpdate(InputManager&)
{
	m_player->Update();
	if (--m_frame <= 0)
	{
		m_update = &TitleScene::NormalUpdate;
		m_draw = &TitleScene::NormalDraw;
		return;
	}
}

void TitleScene::NormalUpdate(InputManager& input)
{
	//プレイヤー更新
	m_player->Update();
	//カメラ更新
	m_camera->Update({-65.0f,0.0f,0.0f}, input);
	m_camera->Apply();
	//剣の更新
	m_sword->Update();
	m_villager->Update();
	//スカイボックスの位置更新
	m_skyBox->SetCameraPos(m_camera->GetPos());
	
	if (input.AnyPressButtonInput())
	{
		m_update = &TitleScene::FadeOutUpdate;
		m_draw = &TitleScene::FadeDraw;
		m_frame = 0;
		SoundManager::PlaySE("start",false);
		SoundManager::FadeOutBGM(kFadeInterval);
	}
}

void TitleScene::FadeOutUpdate(InputManager&)
{
	if (++m_frame >= kFadeInterval)
	{
		//シーンの切り替え
		m_controller.ChangeScene(std::make_shared<GameScene>(m_controller));
		return;
	}
}

void TitleScene::NormalDraw()
{
	auto wsize = Application::GetInstance().GetWindowSize();

	VECTOR light = { m_camera->GetForward().x,m_camera->GetForward().y,m_camera->GetForward().z };
	SetLightDirection(light);
	//スカイボックス描画
	m_skyBox->Draw();
	//プレイヤー描画
	m_player->Draw();
	//剣描画
	m_sword->Draw();
	m_villager->Draw();
	//地面描画
	m_ground->Draw();

	FontManager::DrawCenterString(wsize.w / 2, wsize.h / 24, L"スケルトン", 0xff00ff, FontType::Title);
	FontManager::DrawCenterString(wsize.w / 2, wsize.h / 6 , L"ラッシュ", 0xff00ff, FontType::Title);
	FontManager::DrawCenterFadeString(wsize.w / 2, static_cast<int>(wsize.h / 1.2f),L"ボタンヲオシテスタート",0xffffff,FontType::UI);
#ifdef _DEBUG
	DrawLine(wsize.w / 2, 0, wsize.w / 2, wsize.h, 0xffff00);
#endif // _DEBUG
}

void TitleScene::FadeDraw()
{
	NormalDraw();

	const Size& wsize = Application::GetInstance().GetWindowSize();
	//フェード処理
	float rate = static_cast<float>(m_frame) / static_cast<float>(kFadeInterval);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast <int>( 255 * rate));
	DrawBox(0, 0, wsize.w, wsize.h, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, static_cast <int>(255 * rate));
}
