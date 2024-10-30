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

	worldTranform_.translation_ = {0, 8.0f, 0}; 
	velocity_ = {0, 0, -kWalkSpeed};
	walkTimer = 0.0f;
}

void Enemy::Update() {
	// 速度分だけ位置を更新
	worldTranform_.translation_.x += velocity_.x;
	worldTranform_.translation_.y += velocity_.y;
	worldTranform_.translation_.z += velocity_.z;

	// 既存の移動タイマーや回転の計算
	walkTimer += 1.0f / 60.0f;
	float parm = std::sin(std::numbers::pi_v<float> * 2.0f * walkTimer / kWalkMotionTime);
	float radian = kWalkMotionAngleStart + kWalkMontionAngleEnd * (parm + 1.0f) / 2.0f;
	worldTranform_.rotation_.z = radian;

	// ワールド変換の行列を更新
	worldTranform_.UpdateMatrix();
}


void Enemy::Draw() 
{

	model_->Draw(worldTranform_, *viewProjection_);

}
