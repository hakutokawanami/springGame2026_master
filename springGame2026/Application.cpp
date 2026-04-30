#include "Application.h"
#include"system/Game.h"
#include<DxLib.h>
#include"manager/InputManager.h"
#include"SceneController.h"
#include"scene/GameScene.h"
#include"scene/TitleScene.h"
#include<memory>
#include"manager/ResourceManager.h"
#include"manager/FontManager.h"
#include"manager/SoundManager.h"
Application::Application():
	m_windowSize(Game::kScreenWidth,Game::kScreenHeight)
{

}

Application::~Application()
{

}

Application& Application::GetInstance()
{
	static Application instance;
	return instance;
}

bool Application::Init()
{
	//ウィンドウサイズ設定
	SetGraphMode(m_windowSize.w, m_windowSize.h, Game::kColorBitNum);
#ifdef _DEBUG
	//ウィンドウ
	ChangeWindowMode(true);
#else
	//フルスクリーン
	ChangeWindowMode(false);
#endif // _DEBUG

	//ウィンドウのタイトル設定
	SetMainWindowText( L"斬るゲーム");
	//文字コードの設定
	SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);

	if (DxLib_Init() == -1)
	{
		return false;
	}

	FontManager::Init();

	// 描画対象をバックバッファに変更
	SetDrawScreen(DX_SCREEN_BACK);
	// カリングの設定
	SetUseBackCulling(true);
	//ライティングの計算を行うかどうかの設定
	SetUseLighting(true);
	//初期化成功
	return true;
}

void Application::Run()
{
	//入力マネージャーの作成
	InputManager inputManager;

	//リソースのロード
	ResourceManager::GetInstance().LoadResources();

	//サウンドマネージャー初期化
	SoundManager::Init();

	//シーンコントローラーの作成&最初のシーンの設定
	SceneController controller;
	controller.ChangeScene(std::make_shared<TitleScene>(controller));

	// Zバッファの設定
	SetUseZBuffer3D(true);	// Zバッファを使います
	SetWriteZBuffer3D(true);	// 描画する物体はZバッファにも距離を書き込む

	while (ProcessMessage() != -1)
	{
		// このフレームの開始時間を取得
		LONGLONG start = GetNowHiPerformanceCount();

		// 前のフレームに描画した内容をクリアする
		ClearDrawScreen();

		//ここにゲームの処理を書く
		
		//入力の更新
		inputManager.Update();
		SoundManager::Update();
		//シーンコントローラーの更新と描画
		controller.Update(inputManager);
		controller.Draw();

		//------------------------
		ScreenFlip();
		
#ifdef _DEBUG
		
#endif // DEBUG
		//escキーを押したらゲームを強制終了	
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		//フレームレート固定
		while (GetNowHiPerformanceCount() - start < 16667)
		{

		}
	}
}

void Application::Terminate()
{
	//リソースの解放
	ResourceManager::GetInstance().ReleaseResources();
	DxLib_End();
}

const Size& Application::GetWindowSize() const
{
	return m_windowSize;
}


