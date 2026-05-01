#pragma once
/// <summary>
/// Vector3構造体
/// </summary>
struct Vector3
{
	//x,y,z,の3要素
	float x, y, z;
	//ベクトルの大きさをとる関数
	float Length()const;
	//ベクトルを正規化する関数
	void Normalize();
	//正規化したベクトルを返す関数
	Vector3 Normalized()const;
	//内積
	float Dot(const Vector3& other)const;
	//外積
	Vector3 Cross(const Vector3& other)const;
	//ベクトルの反転に使う
	Vector3 operator-()const;
	//加算
	void operator+=(const Vector3& val);
	//減算
	void operator-=(const Vector3& val);
	//ベクトルをn倍する
	void operator*=(const float scale);
	//加算
	Vector3 operator+(const Vector3& val);
	//減算
	Vector3 operator-(const Vector3& val)const;
	//ベクトルの累乗
	Vector3 operator*(float scale)const;
};

