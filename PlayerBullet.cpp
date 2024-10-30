#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity, const Vector3& targetPosition) {
	assert(model);
	model_ = model;
	textureHandle_ = TextureManager::Load("white1x1.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
	targetPosition_ = targetPosition; // 追尾先の位置を保存
}

void PlayerBullet::Update(const Vector3& targetPosition) {

	
	// 敵の位置に向かってベクトルを計算
	Vector3 direction = targetPosition - worldTransform_.translation_;
	
	float distance = direction.Length();
	
	if (distance > 0.0f) {
		direction.Normalize();                // 方向を正規化
		velocity_ = direction * kBulletSpeed; // 速度を設定
	}

	// 現在の位置に速度を加算
	worldTransform_.translation_ += velocity_;

	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}


	// ワールド変換の行列を更新
	worldTransform_.UpdateMatrix();
}


void PlayerBullet::Draw(const ViewProjection& viewProjection) 
{
	model_->Draw(worldTransform_,viewProjection,textureHandle_);
}
