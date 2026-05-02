#include "EnemyDeadState.h"
#include"graphics/AnimationController.h"
#include"graphics/EffectManager.h"
#include"game/manager/SoundManager.h"
void EnemyDeadState::Enter(Enemy& enemy)
{
	enemy.GetAnimController()->Play("Dead",false);
	enemy.VelocityZero();
	EffectManager::Play("hit",enemy.GetPos() + Vector3(0.0f, 100.0f, 0.0f),0.0f);
	SoundManager::PlaySE("hit", false);
}

void EnemyDeadState::Update(Enemy& enemy)
{
	if (enemy.GetAnimController()->IsEnd())
	{
		enemy.Delete();
	}
}

void EnemyDeadState::Exit(Enemy& enemy)
{
}
