#include "Ground.h"
#include<DxLib.h>
Ground::Ground():
	m_modelHandle(-1)
{
}

Ground::~Ground()
{
	MV1DeleteModel(m_modelHandle);
}

void Ground::Init(int modelHandle)
{
	m_modelHandle = MV1DuplicateModel(modelHandle);
}

void Ground::Draw()
{
	SetLightDirection({0.0f,-1.0f,0.5f});
	MV1SetPosition(m_modelHandle, VGet(0.0f, -60.0f, 0.0f));
	MV1DrawModel(m_modelHandle);
}
