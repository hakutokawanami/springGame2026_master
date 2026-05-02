#pragma once
#include"PlayerStateBase.h"
class PlayerMoveState : public PlayerStateBase
{
	void Enter(GamePlayer& player)override;
	void Enter(TitlePlayer& player)override;
	void Enter(ResultPlayer& player)override;
	void Update(GamePlayer& player, InputManager& input,Camera& camera)override;
	void Update(TitlePlayer& player, InputManager& input,Camera& camera)override;
	void Update(ResultPlayer& player, InputManager& input,Camera& camera)override;
	void Exit(GamePlayer& player)override;
	void Exit(TitlePlayer& player)override;
	void Exit(ResultPlayer& player)override;
	PlayerStateType GetStateType()const override { return PlayerStateType::Move; }
};

