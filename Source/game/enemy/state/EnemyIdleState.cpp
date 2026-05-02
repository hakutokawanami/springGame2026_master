#include "EnemyIdleState.h"
#include"graphics/AnimationController.h"
#include"EnemyDeadState.h"
#include"EnemyChaseState.h"
void EnemyIdleState::Enter(Enemy& enemy)
{
	enemy.GetAnimController()->Play("Idle");
	enemy.VelocityZero();
}

void EnemyIdleState::Update(Enemy& enemy)
{
	if (enemy.IsChase())
	{
		enemy.ChangeState(std::make_unique<EnemyChaseState>());
	}
	if (enemy.IsDead())
	{
		enemy.ChangeState(std::make_unique<EnemyDeadState>());
	}
}

void EnemyIdleState::Exit(Enemy& enemy)
{
}
