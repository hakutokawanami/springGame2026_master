#include "PlayerIdleState.h"
#include"../manager/InputManager.h"
#include"../character/GamePlayer.h"
#include"PlayerMoveState.h"
#include"PlayerAttackState.h"
#include"../AnimationController.h"
void PlayerIdleState::Enter(GamePlayer& player)
{
	player.GetAnimController()->Play("Idle");
}

void PlayerIdleState::Enter(TitlePlayer& player)
{
}

void PlayerIdleState::Enter(ResultPlayer& player)
{
}

void PlayerIdleState::Update(GamePlayer& player, InputManager& input,Camera& camera)
{
	//左スティックの入力が入ったらMove
	if (input.GetLeftStick().x > 0.0f || input.GetLeftStick().y > 0.0f)
	{
		player.ChangeState(std::make_unique<PlayerMoveState>());
	}

	//方向の入力が入ったらMove
	if (!CheckHitKey(KEY_INPUT_LSHIFT))
	{
		if (input.IsPressed("up") || input.IsPressed("down") || input.IsPressed("left") || input.IsPressed("right"))
		{
			player.ChangeState(std::make_unique<PlayerMoveState>());
		}
	}
	//攻撃のボタン入力があったらattack
	if (input.IsTriggered("attack"))
	{
		player.ChangeState(std::make_unique<PlayerAttackState>());
	}
	
#ifdef _DEBUG
	DrawFormatString(16, 32, 0xffffff, L"idle");
	DrawFormatString(16, 48, 0xffffff, L"LeftStick : %f,%f", input.GetLeftStick().x, input.GetLeftStick().y);
#endif // _DEBUG
}

void PlayerIdleState::Update(TitlePlayer& player, InputManager& input, Camera& camera)
{
}

void PlayerIdleState::Update(ResultPlayer& player, InputManager& input, Camera& camera)
{
}

void PlayerIdleState::Exit(GamePlayer& player)
{

}

void PlayerIdleState::Exit(TitlePlayer& player)
{
}

void PlayerIdleState::Exit(ResultPlayer& player)
{
}
