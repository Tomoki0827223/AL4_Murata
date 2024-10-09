#pragma once

/// <summary>
/// 3次元ベクトル
/// </summary>
class Vector3 {
public:
	float x, y, z;

	// コンストラクタ
	Vector3() : x(0), y(0), z(0) {}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

	// 演算子オーバーロード (+)
	Vector3 operator+(const Vector3& other) const { return Vector3{x + other.x, y + other.y, z + other.z}; }

	// 演算子オーバーロード (-)
	Vector3 operator-(const Vector3& other) const { return Vector3{x - other.x, y - other.y, z - other.z}; }

	// 演算子オーバーロード (* スカラー乗算)
	Vector3 operator*(float scalar) const { return Vector3{x * scalar, y * scalar, z * scalar}; }

	// 演算子オーバーロード (/ スカラー除算)
	Vector3 operator/(float scalar) const { return Vector3{x / scalar, y / scalar, z / scalar}; }

	// += 演算子オーバーロード
	Vector3& operator+=(const Vector3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	// -= 演算子オーバーロード
	Vector3& operator-=(const Vector3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	// *= スカラー乗算オーバーロード
	Vector3& operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	// /= スカラー除算オーバーロード
	Vector3& operator/=(float scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}
};
