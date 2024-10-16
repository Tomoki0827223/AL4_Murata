#pragma once

#include "Input.h"
#include "PlayerBullet.h"
#include "WorldTransform.h"
#include "affine.h"
#include <Model.h>

class Player {

public:
	void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection);

	void Update();

	void Rotate();

	void Attack();

	void Draw();

	Input* input_ = nullptr;

	PlayerBullet* bullet_ = nullptr;

private:
	Vector3 move = {0, 0, 0}; // 初期化をゼロベクトルに変更

	WorldTransform worldTransform_;

	ViewProjection* viewProjection_ = nullptr;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;
};
