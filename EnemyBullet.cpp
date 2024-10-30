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
	// 位置を更新
	worldTransform_.translation_ += velocity_; // 弾が前に進むように修正

	// 寿命をカウント
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	// ワールド変換の行列を更新
	worldTransform_.UpdateMatrix();
}


void EnemyBullet::Draw(const ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection, textureHandle_); }

void EnemyBullet::Fire() {
	// 弾の初期位置や速度を設定する処理
	// 弾を特定の位置から指定の速度で発射
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity_); // 現在位置と速度を使って弾を生成

	// 弾をenemyBullets_に追加
	enemyBullets_.push_back(newBullet);
}
