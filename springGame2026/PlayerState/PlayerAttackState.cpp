#include "PlayerAttackState.h"
#include"../character/GamePlayer.h"
#include"../AnimationController.h"
#include"PlayerIdleState.h"
#include"../manager/InputManager.h"
#include<memory>
#include"../manager/EffectManager.h"
#include"../manager/SoundManager.h"
namespace
{
	constexpr int kEffectInterval = 10;
}

void PlayerAttackState::Enter(GamePlayer& player)
{
	player.GetAnimController()->Play("Attack",false);
	player.Attack();
	m_frame = 0;
}

void PlayerAttackState::Enter(TitlePlayer& player)
{
}

void PlayerAttackState::Enter(ResultPlayer& player)
{
}

void PlayerAttackState::Update(GamePlayer& player, InputManager& input, Camera& camera)
{
	if (m_frame++ == kEffectInterval)
	{
		EffectManager::Play("sword", player.GetPos(), player.GetYaw());
		SoundManager::PlaySE("attack", false);
	}

	//アタックアニメーションが終わったら
	if (player.GetAnimController()->IsEnd())
	{
		player.ChangeState(std::make_unique<PlayerIdleState>());
	}
}
void PlayerAttackState::Update(TitlePlayer& player, InputManager& input, Camera& camera)
{
}
void PlayerAttackState::Update(ResultPlayer& player, InputManager& input, Camera& camera)
{
}
void PlayerAttackState::Exit(GamePlayer& player)
{
	
}

void PlayerAttackState::Exit(TitlePlayer& player)
{
}

void PlayerAttackState::Exit(ResultPlayer& player)
{
}
