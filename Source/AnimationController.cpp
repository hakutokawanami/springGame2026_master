#include "AnimationController.h"
#include<DxLib.h>
AnimationController::AnimationController(int modelHandle):
	m_modelHandle(modelHandle),
	m_currentAnim(-1),
	m_currentAttachNo(-1),
	m_currentTime(0.0f),
	m_isLoop(true),
	m_isEnd(false),
	m_prevAnim(-1),
	m_prevAttachNo(-1),
	m_prevTime(0.0f),
	m_blendTime(0.0f),
	m_blendTimer(0.0f)
{
}

void AnimationController::Update()
{
	//アニメーションがなければ何もしない
	if (m_currentAnim < 0)
	{
		return;
	}
	//アニメーション時間の更新
	m_currentTime += 0.5f;

	float totalTime = MV1GetAnimTotalTime(m_modelHandle, m_currentAnim);

	if (m_isLoop)
	{
		// ループする場合
		while (m_currentTime > totalTime)
			m_currentTime -= totalTime;
		m_isEnd = false;
	}
	else
	{
		// ループしない場合
		if (m_currentTime > totalTime)
		{
			m_currentTime = totalTime;
			m_isEnd = true;
		}
		else
		{
			m_isEnd = false;
		}
	}

	// アニメーションをモデルに反映
	MV1SetAttachAnimTime(m_modelHandle, m_currentAttachNo, m_currentTime);

	//ブレンド処理
	if (m_prevAnim >= 0)
	{
		//前のアニメーションの時間更新
		m_prevTime += 0.5f;
		MV1SetAttachAnimTime(m_modelHandle, m_prevAttachNo, m_prevTime);
		//ブレンド時間の更新
		m_blendTimer += 1.0f;
		//ブレンドレート
		float rate = 1.0f;

		if (m_blendTime > 0.0f)
		{
			rate = m_blendTimer / m_blendTime;
		}

		if (rate > 1.0f)
		{
			rate = 1.0f;
		}
		//新しいアニメーション
		MV1SetAttachAnimBlendRate(m_modelHandle, m_currentAttachNo, rate);

		//前のアニメーション
		MV1SetAttachAnimBlendRate(m_modelHandle, m_prevAttachNo, 1.0f - rate);

		//ブレンドの終了
		if (rate >= 1.0f)
		{
			//前のアニメーションを削除
			MV1DetachAnim(m_modelHandle, m_prevAttachNo);
			m_prevAnim = -1;
		}
	}
	else
	{
		// ブレンドしてないときは100%
		MV1SetAttachAnimBlendRate(m_modelHandle, m_currentAttachNo, 1.0f);
	}
}

void AnimationController::Play(const std::string& name, bool loop, float blendTime)
{
	//アニメーション名で探す
	auto it = m_animTable.find(name);
	if (it == m_animTable.end())
	{
		return;
	}

	int newAnim = it->second;
	//同じアニメーションなら再生しない
	if (newAnim == m_currentAnim)
	{
		return;
	}

	//現在のアニメーションを前のアニメーションとして保存
	MV1DetachAnim(m_modelHandle, m_prevAttachNo);
	m_prevAnim = m_currentAnim;
	m_prevAttachNo = m_currentAttachNo;
	m_prevTime = m_currentTime;

	//新しいアニメーションを設定
	m_currentAnim = newAnim;
	m_currentTime = 0.0f;
	m_isLoop = loop;

	m_currentAttachNo = MV1AttachAnim(m_modelHandle, m_currentAnim);

	m_blendTime = blendTime;
	m_blendTimer = 0.0f;
}

void AnimationController::AddAnimation(const std::string& name, int animIndex)
{
	//アニメーション名とアニメーション番号を登録
	m_animTable[name] = animIndex;
}