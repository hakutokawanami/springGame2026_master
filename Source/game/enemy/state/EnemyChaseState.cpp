#include "EnemyChaseState.h"
#include"../AnimationController.h"
#include"EnemyIdleState.h"
#include"EnemyDeadState.h"
void EnemyChaseState::Enter(Enemy& enemy)
{
	enemy.GetAnimController()->Play("Chase");
}

void EnemyChaseState::Update(Enemy& enemy)
{
	if (!enemy.IsChase())
	{
		enemy.ChangeState(std::make_unique<EnemyIdleState>());
	}
	if (enemy.IsDead())
	{
		enemy.ChangeState(std::make_unique<EnemyDeadState>());
	}
}

void EnemyChaseState::Exit(Enemy& enemy)
{
}
