#include "Matrix4x4.h"
#include<cmath>
Matrix4x4::Matrix4x4() :
	m00(0.0f), m01(0.0f), m02(0.0f), m03(0.0f),
	m10(0.0f), m11(0.0f), m12(0.0f), m13(0.0f),
	m20(0.0f), m21(0.0f), m22(0.0f), m23(0.0f),
	m30(0.0f), m31(0.0f), m32(0.0f), m33(0.0f)
{
}

Matrix4x4::Matrix4x4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33) :
	m00(m00), m01(m01), m02(m02), m03(m03),
	m10(m10), m11(m11), m12(m12), m13(m13),
	m20(m20), m21(m21), m22(m22), m23(m23),
	m30(m30), m31(m31), m32(m32), m33(m33)
{
}

Matrix4x4 Matrix4x4::Identity()
{
	return Matrix4x4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}

Matrix4x4 Matrix4x4::Translate(float x, float y, float z)
{
	return Matrix4x4(
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1);
}

Matrix4x4 Matrix4x4::Scale(float x, float y, float z)
{
	return Matrix4x4(
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1);
}

void Matrix4x4::Roll(float angle)
{
	m00 = 1; m01 = 0;            m02 = 0;            m03 = 0;
	m10 = 0; m11 = cosf(angle); m12 = -sinf(angle); m13 = 0;
	m20 = 0; m21 = sinf(angle); m22 = cosf(angle); m23 = 0;
	m30 = 0; m31 = 0;           m32 = 0;            m33 = 1;
}

void Matrix4x4::Pitch(float angle)
{
	m00 = cosf(angle); m01 = 0; m02 = sinf(angle); m03 = 0;
	m10 = 0;           m11 = 1; m12 = 0;           m13 = 0;
	m20 = -sinf(angle); m21 = 0; m22 = cosf(angle); m23 = 0;
	m30 = 0;           m31 = 0; m32 = 0;           m33 = 1;
}

void Matrix4x4::Yaw(float angle)
{
	m00 = cosf(angle); m01 = -sinf(angle); m02 = 0; m03 = 0;
	m10 = sinf(angle); m11 = cosf(angle); m12 = 0; m13 = 0;
	m20 = 0;           m21 = 0;            m22 = 1; m23 = 0;
	m30 = 0;           m31 = 0;            m32 = 0; m33 = 1;
}

MATRIX Matrix4x4::ChangeDxMat()
{
	MATRIX dxMat;

	dxMat.m[0][0] = m00; dxMat.m[0][1] = m01; dxMat.m[0][2] = m02; dxMat.m[0][3] = m03;
	dxMat.m[1][0] = m10; dxMat.m[1][1] = m11; dxMat.m[1][2] = m12; dxMat.m[1][3] = m13;
	dxMat.m[2][0] = m20; dxMat.m[2][1] = m21; dxMat.m[2][2] = m22; dxMat.m[2][3] = m23;
	dxMat.m[3][0] = m30; dxMat.m[3][1] = m31; dxMat.m[3][2] = m32; dxMat.m[3][3] = m33;

	return dxMat;
}

Matrix4x4 Matrix4x4::QuaternionMatrix(const Quaternion& q)
{
	float xx = q.i * q.i;
	float yy = q.j * q.j;
	float zz = q.k * q.k;
	float xy = q.i * q.j;
	float xz = q.i * q.k;
	float yz = q.j * q.k;
	float wx = q.w * q.i;
	float wy = q.w * q.j;
	float wz = q.w * q.k;

	return Matrix4x4(
		1 - 2 * (yy + zz), 2 * (xy - wz), 2 * (xz + wy), 0,
		2 * (xy + wz), 1 - 2 * (xx + zz), 2 * (yz - wx), 0,
		2 * (xz - wy), 2 * (yz + wx), 1 - 2 * (xx + yy), 0,
		0, 0, 0, 1
	);
}

Matrix4x4 Matrix4x4::operator+(Matrix4x4 right)
{
	return Matrix4x4(
		m00 + right.m00, m01 + right.m01, m02 + right.m02, m03 + right.m03,
		m10 + right.m10, m11 + right.m11, m12 + right.m12, m13 + right.m13,
		m20 + right.m20, m21 + right.m21, m22 + right.m22, m23 + right.m23,
		m30 + right.m30, m31 + right.m31, m32 + right.m32, m33 + right.m33
	);
}

Matrix4x4 Matrix4x4::operator-(Matrix4x4 right)
{
	return Matrix4x4(
		m00 - right.m00, m01 - right.m01, m02 - right.m02, m03 - right.m03,
		m10 - right.m10, m11 - right.m11, m12 - right.m12, m13 - right.m13,
		m20 - right.m20, m21 - right.m21, m22 - right.m22, m23 - right.m23,
		m30 - right.m30, m31 - right.m31, m32 - right.m32, m33 - right.m33
	);
}

Matrix4x4 Matrix4x4::operator*(Matrix4x4 right)
{
	return Matrix4x4(
		m00 * right.m00 + m01 * right.m10 + m02 * right.m20 + m03 * right.m30,
		m00 * right.m01 + m01 * right.m11 + m02 * right.m21 + m03 * right.m31,
		m00 * right.m02 + m01 * right.m12 + m02 * right.m22 + m03 * right.m32,
		m00 * right.m03 + m01 * right.m13 + m02 * right.m23 + m03 * right.m33,
		m10 * right.m00 + m11 * right.m10 + m12 * right.m20 + m13 * right.m30,
		m10 * right.m01 + m11 * right.m11 + m12 * right.m21 + m13 * right.m31,
		m10 * right.m02 + m11 * right.m12 + m12 * right.m22 + m13 * right.m32,
		m10 * right.m03 + m11 * right.m13 + m12 * right.m23 + m13 * right.m33,
		m20 * right.m00 + m21 * right.m10 + m22 * right.m20 + m23 * right.m30,
		m20 * right.m01 + m21 * right.m11 + m22 * right.m21 + m23 * right.m31,
		m20 * right.m02 + m21 * right.m12 + m22 * right.m22 + m23 * right.m32,
		m20 * right.m03 + m21 * right.m13 + m22 * right.m23 + m23 * right.m33,
		m30 * right.m00 + m31 * right.m10 + m32 * right.m20 + m33 * right.m30,
		m30 * right.m01 + m31 * right.m11 + m32 * right.m21 + m33 * right.m31,
		m30 * right.m02 + m31 * right.m12 + m32 * right.m22 + m33 * right.m32,
		m30 * right.m03 + m31 * right.m13 + m32 * right.m23 + m33 * right.m33
	);
}

VECTOR Matrix4x4::operator*(VECTOR right)
{
	Matrix4x4 rightMatrix = Matrix4x4(
		right.x, 0, 0, 0,
		right.y, 0, 0, 0,
		right.z, 0, 0, 0,
		1, 0, 0, 0
	);

	return VECTOR{
		m00 * right.x + m01 * right.y + m02 * right.z + m03 * 1,
		m10 * right.x + m11 * right.y + m12 * right.z + m13 * 1,
		m20 * right.x + m21 * right.y + m22 * right.z + m23 * 1,
	};
}


