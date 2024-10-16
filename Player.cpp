#include "Player.h"
#include "cassert"

Player::~Player() {


	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}

	bullets_.clear();
}

void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection) {
	
	input_ = Input::GetInstance();
	assert(model);

	worldTransform_.Initialize();

	model_ = model;
	textureHandle_ = textureHandle;
	viewProjection_ = viewProjection;
}

void Player::Update() {
	const float kCharacterSpeed = 1.0f;

	// 移動量を毎フレームリセット
	move = {0, 0, 0};

	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->isDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

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

	Rotate(); // 回転処理
	Attack(); // 攻撃処理

	for (PlayerBullet* bullet : bullets_) {

		bullet->Update();
	}

	// アフィン変換行列を更新
	worldTransform_.UpdateMatrix();
}



void Player::Rotate() {
	// 回転速さ [ラジアン/frame]
	const float kRotSpeed = 0.02f;

	// キー入力に応じてY軸周りの回転を変更
	if (input_->PushKey(DIK_A)) {
		// Y軸周り角度を回転速さ分減算
		worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
		// Y軸周り角度を回転速さ分加算
		worldTransform_.rotation_.y += kRotSpeed;
	}
}

void Player::Attack() 
{
	if (input_->PushKey(DIK_SPACE)) {

		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		velocity = TransformNormal(velocity, worldTransform_.matWorld_);

		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_, velocity);

		bullets_.push_back(newBullet);
	}
}

void Player::Draw() 
{ 
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_); 

	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(*viewProjection_);
	}
}
