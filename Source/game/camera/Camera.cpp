#include "Camera.h"
#include"game/manager/InputManager.h"

namespace
{
	//カメラ感度
	constexpr float ksensitivity = 0.02f;
	//注視点との距離
	constexpr float kDistance = 700.0f;
}

Camera::Camera():
	m_target(0.0f,0.0f,0.0f),
	m_distance(kDistance),
	m_forward(0.0f,0.0f,0.0f),
	m_shakeOffset(0.0f, 0.0f, 0.0f),
	m_shakePower(0.0f),
	m_shakeTime(0),
	m_shakeDilayTime(0),
	m_topLimit(kTopLimit),
	m_bottomLimit(kBottomLimit)
{
}

void Camera::Init()
{
	// カメラの設定
	SetupCamera_Perspective(DX_PI_F / 2.4f);
	SetCameraNearFar(200.0f, 6000.0f);
	m_position = { 0.0f,300.0f,-700.0f };
}

void Camera::Init(const Vector3& target,float distance,float topLimit,float bottomLimit)
{
	// カメラの設定
	SetupCamera_Perspective(DX_PI_F / 2.4f);
	SetCameraNearFar(100.0f, 6000.0f);
	m_target = target;	
	m_distance = distance;
	m_topLimit = topLimit;
	m_bottomLimit = bottomLimit;

	//上下の制限
	if (m_pitch > m_topLimit)
	{
		m_pitch = m_topLimit;
	}
	if (m_pitch < m_bottomLimit)
	{
		m_pitch = m_bottomLimit;
	}

	// カメラ位置計算
	Vector3 vec = { 0.0f,0.0f,0.0f };		
	vec.x = cosf(m_pitch) * cosf(m_yaw) * m_distance;
	vec.y = sinf(m_pitch) * m_distance;
	vec.z = cosf(m_pitch) * sinf(m_yaw) * m_distance;

	//カメラ位置確定
	m_position = m_target + vec + m_shakeOffset;

	//前方向ベクトルの計算
	m_forward = m_target - m_position;
	SetLightDirection({m_forward.x,m_forward.y,m_forward.z});
	m_forward.y = 0.0f;
	m_forward.Normalize();
}

void Camera::End()
{
}

void Camera::Update()
{
}

void Camera::Update(const Vector3& target, InputManager& input)
{
	//注視点更新
	m_target = target;
	//右スティックの入力値を取得
	Vector2 stick = input.GetRightStick();
	
	m_yaw -= stick.x * ksensitivity;
	m_pitch -= stick.y * ksensitivity;

	if (CheckHitKey(KEY_INPUT_LSHIFT))
	{
		if (input.IsPressed("left"))
		{
			m_yaw += 1.0f * ksensitivity;
		}
		if (input.IsPressed("right"))
		{
			m_yaw -= 1.0f * ksensitivity;
		}
		if (input.IsPressed("up"))
		{
			m_pitch += 1.0f * ksensitivity;
		}
		if (input.IsPressed("down"))
		{
			m_pitch -= 1.0f * ksensitivity;
		}
	}

	//上下の制限
	if (m_pitch > m_topLimit)
	{
		m_pitch = m_topLimit;
	}
	if (m_pitch < m_bottomLimit)
	{
		m_pitch = m_bottomLimit;
	}

	// カメラ位置計算
	Vector3 vec = {0.0f,0.0f,0.0f};
	vec.x = cosf(m_pitch) * cosf(m_yaw) * m_distance;
	vec.y = sinf(m_pitch) * m_distance;
	vec.z = cosf(m_pitch) * sinf(m_yaw) * m_distance;

	ShakeUpdate();

	//カメラ位置確定
	m_position = m_target + vec + m_shakeOffset;

	//前方向ベクトルの計算
	m_forward = m_target - m_position;
	SetLightDirection({ m_forward.x,m_forward.y,m_forward.z });
	m_forward.y = 0.0f;
	m_forward.Normalize();

#ifdef _DEBUG
	DrawFormatString(16, 96, 0xffffff, L"cameraPos : %f,%f,%f", m_position.x, m_position.y, m_position.z);
	DrawFormatString(16, 144, 0xffffff, L"forward : %f,%f,%f", m_forward.x, m_forward.y, m_forward.z);
	DrawFormatString(16, 256, 0xffffff, L"cameraToTarget : %f,%f,%f", (m_target - m_position).Length());
#endif // _DEBUG

}

void Camera::Draw()
{
}

void Camera::Apply()
{
	SetCameraPositionAndTarget_UpVecY(VGet(m_position.x, m_position.y + 300.0f, m_position.z),VGet(m_target.x, m_target.y + 100.0f, m_target.z));
}

Vector3 Camera::GetForward()
{
	return m_forward;
}

Vector3 Camera::GetRight()
{
	Vector3 vec = { 0.0f,1.0f,0.0f };
	Vector3 right;
	right = m_forward.Cross(vec);
	right.Normalized();
	return right;
}

void Camera::ShakeStart(float power, int time,int delay)
{
	m_shakePower = power;
	m_shakeTime = time;
	m_shakeDilayTime = delay;
}

void Camera::ShakeUpdate()
{
	m_shakeOffset = { 0.0f,0.0f,0.0f };
	if(m_shakeDilayTime < 0)
	{
		if (m_shakeTime > 0)
		{
			m_shakeTime--;
			m_shakeOffset.x = (rand() / (float)RAND_MAX - 0.5f) * 2.0f * m_shakePower;
			m_shakeOffset.y = (rand() / (float)RAND_MAX - 0.5f) * 2.0f * m_shakePower;
			m_shakeOffset.z = (rand() / (float)RAND_MAX - 0.5f) * 2.0f * m_shakePower;
		}
	}
	m_shakeDilayTime--;
}