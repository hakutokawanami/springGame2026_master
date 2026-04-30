#pragma once
#include "DxLib.h"
#include"Quaternion.h"
class Matrix4x4
{
	float m00, m01, m02, m03;
	float m10, m11, m12, m13;
	float m20, m21, m22, m23;
	float m30, m31, m32, m33;

public:
	Matrix4x4();
	Matrix4x4(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);
	
	//’PˆÊs—ñ‚ğì‚é
	Matrix4x4 Identity();

	//•½sˆÚ“®s—ñ‚ğì‚é
	static Matrix4x4 Translate(float x, float y, float z);

	//Šg‘åk¬s—ñ‚ğì‚é
 	static Matrix4x4 Scale(float x, float y, float z);

	/// <summary>
	/// x²‰ñ“]
	/// </summary>
	/// <param name="angle"></param>
	void Roll(float angle);
	/// <summary>
	/// y²‰ñ“]
	/// </summary>
	/// <param name="angle"></param>
	void Pitch(float angle);
	/// <summary>
	/// z²‰ñ“]
	/// </summary>
	/// <param name="angle"></param>
	void Yaw(float angle);

	MATRIX ChangeDxMat();

	static Matrix4x4 QuaternionMatrix(const Quaternion& q);
	
	Matrix4x4 operator+(Matrix4x4 right);

	Matrix4x4 operator-(Matrix4x4 right);

	Matrix4x4 operator*(Matrix4x4 right);

	VECTOR operator*(VECTOR right);
};

