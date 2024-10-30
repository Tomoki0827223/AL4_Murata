#include "EnemyBullet.h"

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	model_ = model;

	textureHandle_ = TextureManager::Load("white1x1.png");

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;

	velocity_ = velocity;
}

void EnemyBullet::Update() {
	worldTransform_.UpdateMatrix();
	worldTransform_.translation_ -= velocity_;

	// 発射カウントが指定の間隔に達したら発射
	if (++fireTimer_ >= kFireInterval) {
		Fire();
		fireTimer_ = 0; // カウントをリセット
	}

	// 弾の寿命をカウント
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection, textureHandle_); }

void EnemyBullet::Fire() {
	// 弾の初期位置や速度を設定する処理
	// 必要に応じて弾を生成する
	// 例: 弾を特定の位置から指定の速度で発射
	worldTransform_.translation_ -= velocity_; // 現在位置に速度を加える
}
