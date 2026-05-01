#pragma once
#include "../base/PlayerBase.h"
#include<memory>
class InputManager;
class PlayerStateBase;
class AnimationController;
class TitlePlayer : public PlayerBase
{
public:
	TitlePlayer(int modelHandle);
	~TitlePlayer();
	void Init()override;
	void End()override;
	void Update()override;
	void Update(InputManager& input)override;
	void Draw()override;

	void Rotate(const Vector3& move);

	void ChangeState(std::unique_ptr<PlayerStateBase> newState);
private:

	std::shared_ptr<AnimationController> m_animationController;

	std::unique_ptr<PlayerStateBase> m_state;
};

