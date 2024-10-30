#include "Enemy.h"
#include "MathUtilityForText.h"
#include <cassert>
#include <numbers>

void Enemy::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection) {
	assert(model);
	model_ = model;

	worldTranform_.Initialize();
	worldTranform_.rotation_.z = std::numbers::pi_v<float> * 3.0f / 2.0f;

	viewProjection_ = viewProjection;
	textureHandle_ = textureHandle;

	// 初期位置と速度
	worldTranform_.translation_ = {0, 0.0f, 5.0f}; // 初期Z位置を5に設定
	velocity_ = {0, 0, -kWalkSpeed};
	walkTimer = 0.0f;

	// 初期フェーズ設定
	phase_ = Phase::Leave;
}

void Enemy::Update(Vector3 playerPosition) {
	// 速度分だけ位置を更新
	worldTranform_.translation_.x += velocity_.x;
	worldTranform_.translation_.y += velocity_.y;
	worldTranform_.translation_.z += velocity_.z;

	// プレイヤーに向かって移動
	Vector3 direction = playerPosition - worldTranform_.translation_;
	if (direction.Length() > 0) {
		direction.Normalize();
		worldTranform_.translation_.x += direction.x * kApproachSpeed; // プレイヤーに向かって進む
		worldTranform_.translation_.y += direction.y * kApproachSpeed;
		worldTranform_.translation_.z += direction.z * kApproachSpeed;
	}


}


void Enemy::Draw() {
	model_->Draw(worldTranform_, *viewProjection_, textureHandle_);

	// 弾の描画
	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Draw(*viewProjection_);
	}
}

void Enemy::Attack() {
	const float kBulletSpeed = 1.0f;
	Vector3 velocity(0, 0, kBulletSpeed);

	velocity = TransformNormal(velocity, worldTranform_.matWorld_);

	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTranform_.translation_, velocity);

	enemyBullets_.push_back(newBullet);
}
