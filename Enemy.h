#pragma once

#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Enemy {

public:

	void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection);

	void Update();

	void Draw();

	// Getter/Setterの追加
	Vector3 GetPosition() const { return worldTranform_.translation_; }
	void SetPosition(const Vector3& position) { worldTranform_.translation_ = position; }

	Vector3 GetVelocity() const { return velocity_; }
	void SetVelocity(const Vector3& velocity) { velocity_ = velocity; }

	float GetRotationX() const { return worldTranform_.rotation_.x; }
	void SetRotationX(float rotationX) { worldTranform_.rotation_.x = rotationX; }


private:

	static inline const float kWalkSpeed = 0.03f;
	static inline const float kWalkMotionAngleStart = 0.0f;
	static inline const float kWalkMontionAngleEnd = 30.0f;
	static inline const float kWalkMotionTime = 1.0f;

	Model* model_ = nullptr;
	WorldTransform worldTranform_;
	ViewProjection* viewProjection_ = nullptr;
	Vector3 velocity_ = {};
	float walkTimer = 0.0f;
	uint32_t textureHandle_ = 0;





};
