#include "DxLib.h"
#include"system/Game.h"
#include<memory>

#include"Application.h"
using namespace std;

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	auto& app = Application::GetInstance();

	//初期化処理
	if (!app.Init())
	{
		return -1;
	}
	//ゲームループ
	app.Run();
	//後処理
	app.Terminate();
	
	return 0;				// ソフトの終了 
}