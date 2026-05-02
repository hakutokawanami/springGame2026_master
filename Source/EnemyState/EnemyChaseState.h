#pragma once
#include "../base/EnemyStateBase.h"
class EnemyChaseState : public EnemyStateBase
{
	void Enter(Enemy& enemy)override;
	void Update(Enemy& enemy)override;
	void Exit(Enemy& enemy)override;

	EnemyStateType GetStateType()const override { return EnemyStateType::Chase; }
};

