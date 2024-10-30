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
	phase_ = Phase::Approach;
}

void Enemy::Update() {
	// 速度分だけ位置を更新
	worldTranform_.translation_.x += velocity_.x;
	worldTranform_.translation_.y += velocity_.y;
	worldTranform_.translation_.z += velocity_.z;

	// 移動タイマーと回転の計算
	walkTimer += 1.0f / 60.0f;
	float parm = std::sin(std::numbers::pi_v<float> * 2.0f * walkTimer / kWalkMotionTime);
	float radian = kWalkMotionAngleStart + kWalkMontionAngleEnd * (parm + 1.0f) / 2.0f;
	worldTranform_.rotation_.z = radian;

	// フェーズごとの動作
	switch (phase_) {
	case Phase::Approach:
		worldTranform_.translation_.z -= 0.02f;
		if (worldTranform_.translation_.z <= -2.0f) {
			phase_ = Phase::Leave;
		}
		break;

	case Phase::Leave:
		worldTranform_.translation_.x += 0.03f;
		if (worldTranform_.translation_.z >= 5.0f) {
			phase_ = Phase::Approach;
		}
		break;

	default:
		break;
	}

	// 弾発射のタイミングを管理
	if (--attackTimer_ <= 0) {
		Attack();
		attackTimer_ = kAttackInterval; // カウンタをリセット
	}

	// 弾の更新と削除
	for (auto it = enemyBullets_.begin(); it != enemyBullets_.end();) {
		(*it)->Update();
		if ((*it)->isDead()) {
			delete *it;
			it = enemyBullets_.erase(it);
		} else {
			++it;
		}
	}

	// ワールド変換の行列を更新
	worldTranform_.UpdateMatrix();
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
