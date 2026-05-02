#include "PlayerMoveState.h"
#include"game/manager/InputManager.h"
#include"game/player/GamePlayer.h"
#include"game/camera/Camera.h"
#include"graphics/AnimationController.h"
#include"PlayerIdleState.h"
#include"PlayerAttackState.h"
#include"game/manager/SoundManager.h"
void PlayerMoveState::Enter(GamePlayer& player)
{
	player.GetAnimController()->Play("Run");
}

void PlayerMoveState::Enter(TitlePlayer& player)
{
}

void PlayerMoveState::Enter(ResultPlayer& player)
{
}

void PlayerMoveState::Update(GamePlayer& player, InputManager& input,Camera& camera)
{
	Vector3 move = { 0.0f,0.0f,0.0f };

	//パッドが接続されているかどうか
	if (GetJoypadNum() > 0)
	{
		Vector2 vec2;
		//左スティックの入力値を取得
		vec2 = input.GetLeftStick();
		move -= camera.GetRight() * vec2.x;
		move += camera.GetForward() * vec2.y;
		move.y = 0.0f;
	}
	else
	{
		if (!CheckHitKey(KEY_INPUT_LSHIFT))
		{
			if (input.IsPressed("up"))
			{
				move += camera.GetForward();
			}
			if (input.IsPressed("down"))
			{
				move -= camera.GetForward();
			}
			if (input.IsPressed("left"))
			{
				move += camera.GetRight();
			}
			if (input.IsPressed("right"))
			{
				move -= camera.GetRight();
			}
		}
	}

	//正規化
	if (move.Length() > 0.0f)
	{
		move.Normalize();
	}
	else
	{
		//Idle
		player.ChangeState(std::make_unique<PlayerIdleState>());
		player.SetIsPlayRunSe(false);
		player.ResetRunSeDelay();
		SoundManager::StopSE("playerRun");
	}
	//攻撃の入力があったらattack
	if (input.IsTriggered("attack"))
	{
		player.ChangeState(std::make_unique<PlayerAttackState>());
		player.SetIsPlayRunSe(false);
		player.ResetRunSeDelay();
		SoundManager::StopSE("playerRun");
	}
	player.RunSeDelay();
	if (player.GetRunSeDelay() >= 15)
	{
		if (!player.IsPlayRunSe())
		{
			SoundManager::PlaySE("playerRun", true);
			player.SetIsPlayRunSe(true);
		}
	}
	
	//aプレイヤーに渡す
	player.Move(move);
	player.Rotate(move);

#ifdef _DEBUG
	DrawFormatString(16, 32, 0xffffff, L"move");
	DrawFormatString(16, 128, 0xffffff, L"move : %f,%f,%f",move.x,move.y,move.z);
#endif // _DEBUG
}

void PlayerMoveState::Update(TitlePlayer& player, InputManager& input, Camera& camera)
{
}

void PlayerMoveState::Update(ResultPlayer& player, InputManager& input, Camera& camera)
{
}

void PlayerMoveState::Exit(GamePlayer& player)
{
}

void PlayerMoveState::Exit(TitlePlayer& player)
{
}

void PlayerMoveState::Exit(ResultPlayer& player)
{
}
