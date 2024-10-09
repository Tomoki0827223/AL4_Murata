#pragma once

#include <Model.h>
#include "WorldTransform.h"
#include "Input.h"
#include "affine.h"

class Player {

public:
	void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection);

	void Update();

	void Draw();

	Input* input_ = nullptr;

private:

	WorldTransform worldTransform_;

	ViewProjection* viewProjection_ = nullptr;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;
};
