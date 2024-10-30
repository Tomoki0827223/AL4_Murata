#pragma once

#include <cassert>
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Input.h"
#include "TextureManager.h"

class PlayerBullet {
public:
	
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity, const Vector3& targetPosition);
	void Update(const Vector3& targetPosition);
	void Draw(const ViewProjection& viewProjection);
	bool isDead() const { return isDead_; }
	static constexpr float kBulletSpeed = 1.0f; // 定数を追加

private:
	
	Vector3 velocity_;
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Vector3 targetPosition_; // 追尾先の位置
	static const int32_t kLifeTime = 60 * 5;
	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;

};
