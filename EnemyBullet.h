#pragma once

#include "Input.h"
#include "Model.h"
#include "TextureManager.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <cassert>

class EnemyBullet {
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);
	void Update();
	void Draw(const ViewProjection& viewProjection);
	bool isDead() const { return isDead_; }

	void Fire();

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Vector3 velocity_;

	std::vector<EnemyBullet*> enemyBullets_;

	// 弾の消える処理
	static const int32_t kLifeTime = 60 * 5;
	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;

	// 弾の発射間隔を設定
	static const int32_t kFireInterval = 15; // 60フレームごとに発射
	int32_t fireTimer_ = 0;                  // 発射のためのカウンタ
};
