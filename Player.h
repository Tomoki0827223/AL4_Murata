#pragma once

#include "Enemy.h"
#include "Input.h"
#include "PlayerBullet.h"
#include "WorldTransform.h"
#include "affine.h"
#include <Model.h>
#include <list>

class Player {
public:
	~Player();

	void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection);
	void Update();
	void Rotate();
	void Attack();
	void Draw();

	Input* input_ = nullptr;
	std::list<PlayerBullet*> bullets_;

	// プレイヤーの位置を取得するメソッド
	Vector3 GetPosition() const { return position_; }

	// プレイヤーの位置を設定するメソッド
	void SetPosition(const Vector3& position) { position_ = position; }

private:
	Vector3 position_ = {0, 0, 0}; // プレイヤーの位置を保持
	Vector3 move = {0, 0, 0};      // 初期化をゼロベクトルに変更

	WorldTransform worldTransform_;
	ViewProjection* viewProjection_ = nullptr;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;

	Vector3 velocity;
};
