#include "Quaternion.h"
#include<cmath>
#include"DxLib.h"
Quaternion::Quaternion() :
	i(0.0f),
	j(0.0f),
	k(0.0f),
	w(0.0f)
{
}

Quaternion::Quaternion(float qi, float qj, float qk, float qw) :
	i(qi),
	j(qj),
	k(qk),
	w(qw)
{
}

Quaternion::Quaternion(VECTOR vec, float theta)
{
	i = vec.x * sinf(theta / 2);
	j = vec.y * sinf(theta / 2);
	k = vec.z * sinf(theta / 2);
	w = cosf(theta / 2);
}

Quaternion Quaternion::CreateQuaternion(VECTOR vec, float theta)
{
	float len = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

	if (len == 0.0f)
	{
		return Quaternion{ 0, 0, 0, 1 };
	}

	float inv = 1.0f / len;

	float x = vec.x * inv;
	float y = vec.y * inv;
	float z = vec.z * inv;

	float angle = theta * (DX_PI_F / 180.0f);

	return Quaternion{
		x * sinf(angle / 2) ,
		y * sinf(angle / 2) ,
		z * sinf(angle / 2),
		cosf(angle / 2) };
}

Quaternion Quaternion::operator*(const Quaternion& q)
{
	return Quaternion{
		   i * q.w + j * q.k - k * q.j + w * q.i
		, -i * q.k + j * q.w + k * q.i + w * q.j
		,  i * q.j - j * q.i + k * q.w + w * q.k
		, -i * q.i - j * q.j - k * q.k + w * q.w
	};
}

VECTOR Quaternion::operator*(const VECTOR vec)
{
	Quaternion qvec = { vec.x,vec.y,vec.z,0.0f };
	Quaternion q = this->Normalized();

	Quaternion inv{ -q.i,-q.j,-q.k,q.w };

	Quaternion result = q * qvec * inv;

	VECTOR ret = { result.i,result.j,result.k };

	return ret;
}

Quaternion Quaternion::Normalized()
{
	float len = sqrtf(i * i + j * j + k * k + w * w);

	if (len == 0.0f)
	{
		return Quaternion{ 0,0,0,1 };
	}

	float inv = 1.0f / len;

	return Quaternion{
		i * inv,
		j * inv,
		k * inv,
		w * inv };
}

void Quaternion::Normalize()
{
	float len = sqrtf(i * i + j * j + k * k + w * w);

	if (len == 0.0f)
	{
		*this = Quaternion{ 0.0f,0.0f,0.0f,1.0f };
		return;
	}

	float inv = 1.0f / len;

	i *= inv;
	j *= inv;
	k *= inv;
	w *= inv;
}


