#include "ResultScene.h"
#include"core/Application.h"
#include"DxLib.h"
#include"GameScene.h"
#include"core/SceneController.h"
#include"game/manager/InputManager.h"
#include"game/manager/ResourceManager.h"
#include"game/player/ResultPlayer.h"
#include"game/weapon/Sword.h"
#include"game/stage/SkyBox.h"
#include"game/stage/Ground.h"
#include"game/camera/Camera.h"
#include"graphics/FontManager.h"
#include"TitleScene.h"
#include"game/manager/GameManager.h"
#include"game/mob/Villager.h"
#include"game/manager/SoundManager.h"
namespace
{
	constexpr int kFadeInterval = 60;
	constexpr float kCameraDistance = 350.0f;
	constexpr float kCameraTopLimit = -0.28f;
	constexpr float kCameraBottomLimit = -0.27f;
}

ResultScene::ResultScene(SceneController& controller):
	SceneBase(controller),
	m_playerModelHandle(-1),
	m_swordModelHandle(-1),
	m_enemyModelHandle(-1),
	m_groundModelHandle(-1)
{
	m_update = &ResultScene::FadeInUpdate;
	m_draw = &ResultScene::FadeDraw;
	m_frame = kFadeInterval;

	m_playerModelHandle = MV1DuplicateModel(ResourceManager::GetInstance().GetPlayerModelHandle());
	m_swordModelHandle = MV1DuplicateModel(ResourceManager::GetInstance().m_swordModelHandle);
	m_enemyModelHandle = MV1DuplicateModel(ResourceManager::GetInstance().m_enemyModelHandle);
	m_groundModelHandle = MV1DuplicateModel(ResourceManager::GetInstance().m_groundModelHandle);
	m_villagerModelHandle = MV1DuplicateModel(ResourceManager::GetInstance().m_villagerModelHandle);

	m_camera = std::make_shared<Camera>();
	m_camera->Init({ 0.0f,0.0f,0.0f }, kCameraDistance, kCameraTopLimit, kCameraBottomLimit);
	m_camera->Apply();
	m_player = std::make_shared<ResultPlayer>(m_playerModelHandle);
	m_player->Init();
	Vector3 rot = -m_camera->GetForward().Normalized();
	m_player->Rotate(rot);
	m_skyBox = std::make_shared<SkyBox>();
	m_skyBox->Init(ResourceManager::GetInstance().m_skyBoxHandles);
	m_skyBox->SetCameraPos(m_camera->GetPos());
	m_ground = std::make_shared<Ground>();
	m_ground->Init(m_groundModelHandle);
	m_villager = std::make_shared<Villager>(m_villagerModelHandle, Vector3{0.0f,0.0f,100.0f},scene::result);
	m_villager->Init();
	m_villager->Rotate(rot);

	SoundManager::PlayBGM("result");
}

ResultScene::~ResultScene()
{
}

void ResultScene::Update(InputManager& input)
{
	(this->*m_update)(input);
}

void ResultScene::Draw()
{
	(this->*m_draw)();
}

void ResultScene::FadeInUpdate(InputManager&)
{
	if (--m_frame <= 0)
	{
		m_update = &ResultScene::NormalUpdate;
		m_draw = &ResultScene::NormalDraw;
		return;
	}
}

void ResultScene::NormalUpdate(InputManager& input)
{
	//プレイヤー更新
	m_player->Update();
	//カメラ更新
	m_camera->Update({ 0.0f,0.0f,0.0f }, input);
	m_camera->Apply();
	//スカイボックスの位置更新
	m_skyBox->SetCameraPos(m_camera->GetPos());

	m_villager->Update();

	if (input.AnyPressButtonInput())
	{
		m_update = &ResultScene::FadeOutUpdate;
		m_draw = &ResultScene::FadeDraw;
		m_frame = 0;
		SoundManager::PlaySE("return", false);
		SoundManager::FadeOutBGM(kFadeInterval);
	}
}

void ResultScene::FadeOutUpdate(InputManager&)
{
	if (++m_frame >= kFadeInterval)
	{
		//シーンの切り替え
		m_controller.ChangeScene(std::make_shared<TitleScene>(m_controller));
		return;
	}
}

void ResultScene::NormalDraw()
{
	auto wsize = Application::GetInstance().GetWindowSize();

	VECTOR light = { m_camera->GetForward().x,m_camera->GetForward().y,m_camera->GetForward().z };
	SetLightDirection(light);
	//スカイボックス描画
	m_skyBox->Draw();
	//プレイヤー描画
	m_player->Draw();

	m_villager->Draw();
	//地面描画
	m_ground->Draw();

	FontManager::DrawCenterFadeString(wsize.w / 2, static_cast<int>( wsize.h / 1.2f), L"タイトルニモドル", 0xffffff, FontType::UI);
#ifdef _DEBUG
	
#endif // _DEBUG
}

void ResultScene::FadeDraw()
{
	NormalDraw();

	const Size& wsize = Application::GetInstance().GetWindowSize();
	//フェード処理
	float rate = static_cast<float>(m_frame) / static_cast<float>(kFadeInterval);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,static_cast<int>(255 * rate));
	DrawBox(0, 0, wsize.w, wsize.h, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,static_cast<int>(255 * rate));
}
