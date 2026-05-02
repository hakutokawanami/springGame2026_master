#pragma once
#include"../base/GameObject.h"
#include"../system/Vector3.h"

namespace
{
	//上方向の制限
	constexpr float kTopLimit = 1.0f;
	//下方向の制限
	constexpr float kBottomLimit = -0.27f;
}

class InputManager;
class Camera : public GameObject
{
public: 
	Camera();

	void Init()override;
	void Init(const Vector3& target,float distance,float topLimit = kTopLimit,float bottomLimit = kBottomLimit);
	void End()override;
	void Update()override;
	void Update(const Vector3& target,InputManager& input);
	void Draw()override;
	//カメラ位置セット
	void Apply();
	//前方向ベクトルを取得
	Vector3 GetForward();

	Vector3 GetRight();
	//カメラシェイク開始
	void ShakeStart(float power,int time,int delay);
	//カメラシェイク更新
	void ShakeUpdate();

	Vector3 GetPos()const { return m_position; }
private:
	//注視点
	Vector3 m_target;
	//注視点からの距離
	float m_distance;
	//前方向ベクトル
	Vector3 m_forward;

	float m_shakePower;
	int m_shakeTime;
	int m_shakeDilayTime;

	Vector3 m_shakeOffset;

	float m_topLimit;
	float m_bottomLimit;
};

