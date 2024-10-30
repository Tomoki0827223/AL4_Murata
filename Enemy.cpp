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
	worldTranform_.translation_ = {0, 8.0f, 5.0f}; // 初期Z位置を5に設定
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
		// Z方向へ近づく
		worldTranform_.translation_.z -= 0.02f;

		// Z位置が閾値に達したらフェーズをLeaveに変更

		if (worldTranform_.translation_.z <= -2.0f) {
			phase_ = Phase::Leave;
		}
		break;

	case Phase::Leave:
		// 離れる動作（例えばZを増加させる）
		worldTranform_.translation_.x += 0.03f;

		// Z位置が一定以上になったらApproachに戻す
		if (worldTranform_.translation_.z >= 5.0f) {
			phase_ = Phase::Approach;
		}
		break;

	default:
		break;
	}

	// ワールド変換の行列を更新
	worldTranform_.UpdateMatrix();
}



void Enemy::Draw() 
{

	model_->Draw(worldTranform_, *viewProjection_, textureHandle_);

}
