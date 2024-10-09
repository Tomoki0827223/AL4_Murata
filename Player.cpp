#include "Player.h"
#include "cassert"

void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection) {
	
	input_ = Input::GetInstance();
	assert(model);

	worldTransform_.Initialize();

	model_ = model;
	textureHandle_ = textureHandle;
	viewProjection_ = viewProjection;
}

void Player::Update() {
	Vector3 move = {0, 0, 0}; // 初期化をゼロベクトルに変更

	const float kCharacterSpeed = 1.0f;

	// キー入力に応じて移動量を変更
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed; // 上に移動する際はY軸のプラス方向
	}
	if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed; // 下に移動する際はY軸のマイナス方向
	}

	// 移動ベクトルを現在の座標に加算
	worldTransform_.translation_ += move;

	// アフィン変換行列を更新
	worldTransform_.UpdateMatrix(); // TransferMatrix()を直接呼ばず、行列更新も含める
}



void Player::Draw() 
{ 
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_); 
}
