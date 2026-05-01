#pragma once
#include"DxLib.h"
class Quaternion
{
public:
	Quaternion();
	Quaternion(float i,float j,float k,float w);

	Quaternion(VECTOR vec, float theta);

	//“x”–@
	static Quaternion CreateQuaternion(VECTOR vec, float theta);

	Quaternion operator*(const Quaternion& q);

	VECTOR operator*(const VECTOR vec);
	//’l‚ğ•Ô‚·
	Quaternion Normalized();
	//©•ª‚ğ‘‚«Š·‚¦‚é
	void Normalize();

	float i;
	float j;
	float k;
	float w;
};

