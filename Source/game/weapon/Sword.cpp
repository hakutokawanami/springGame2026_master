#include "Sword.h"
#include<DxLib.h>

namespace
{
	const VECTOR kSwordPosOffset = VGet(100.0f,100.0f,100.0f);
}

Sword::Sword(int modelHandle,int playerModelHandle)
{
	m_modelHandle = modelHandle;
	m_playerModelHandle = playerModelHandle;

	m_handIndex = MV1SearchFrame(m_playerModelHandle, L"DEF_hand_R");
}

Sword::~Sword()
{
	MV1DeleteModel(m_modelHandle);
}

void Sword::Init()
{
    SetSword();
}

void Sword::End()
{
}

void Sword::Update()
{
    SetSword();
}

void Sword::Draw()
{
    SetUseLighting(false);
	MV1DrawModel(m_modelHandle);
    SetUseLighting(true);
}

void Sword::SetSword()
{
    //ボーンの位置、回転、スケールを取得する
    MATRIX boneMat = MV1GetFrameLocalWorldMatrix(m_playerModelHandle, m_handIndex);

    //回転だけを残す
    VECTOR x = VNorm(VGet(boneMat.m[0][0], boneMat.m[0][1], boneMat.m[0][2]));
    VECTOR y = VNorm(VGet(boneMat.m[1][0], boneMat.m[1][1], boneMat.m[1][2]));
    VECTOR z = VNorm(VGet(boneMat.m[2][0], boneMat.m[2][1], boneMat.m[2][2]));

    //回転だけを残した後の行列を作る
    MATRIX rot;
    rot.m[0][0] = x.x; rot.m[0][1] = x.y; rot.m[0][2] = x.z; rot.m[0][3] = 0;
    rot.m[1][0] = y.x; rot.m[1][1] = y.y; rot.m[1][2] = y.z; rot.m[1][3] = 0;
    rot.m[2][0] = z.x; rot.m[2][1] = z.y; rot.m[2][2] = z.z; rot.m[2][3] = 0;

    // 位置を追加する
    rot.m[3][0] = boneMat.m[3][0];
    rot.m[3][1] = boneMat.m[3][1];
    rot.m[3][2] = boneMat.m[3][2];
    rot.m[3][3] = 1;

    //位置の修正をする
    //X軸
    VECTOR right = x;
    //Y軸
    VECTOR up = y;
    //Z軸
    VECTOR forward = z;
    //前後
    float offsetForward = 0.0f;
    //上下
    float offsetUp = 20.0f;
    //左右
    float offsetRight = -10.0f;

    rot.m[3][0] += forward.x * offsetForward + up.x * offsetUp + right.x * offsetRight;
    rot.m[3][1] += forward.y * offsetForward + up.y * offsetUp + right.y * offsetRight;
    rot.m[3][2] += forward.z * offsetForward + up.z * offsetUp + right.z * offsetRight;

    //剣のモデルの向きを修正する
    MATRIX rotOffset = MGetRotZ(DX_PI_F / 2);

    //最終的な行列
    MATRIX finalMat = MMult(rotOffset, rot);

    //モデルに反映
    MV1SetMatrix(m_modelHandle, finalMat);
}
