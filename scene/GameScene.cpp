#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "imgui.h"

GameScene::GameScene() 
{

}


GameScene::~GameScene() {

	delete sprite_;
	delete player_;
	delete model_;
	delete enemy_;
}


void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	model_ = Model::Create();

	textureHandle_ = TextureManager::Load("mario.jpg");
	textureHandle_Enemy_ = TextureManager::Load("uvChecker.png");

	sprite_ = Sprite::Create(textureHandle_, {100, 50});
	sprite_ = Sprite::Create(textureHandle_Enemy_, {100, 50});

	viewProjection_.Initialize();

	player_ = new Player();
	enemy_ = new Enemy();

	player_->Initialize(model_, textureHandle_, &viewProjection_);

	enemy_->Initialize(model_, textureHandle_Enemy_, &viewProjection_);
}

void GameScene::Update() {
	player_->Update();
	enemy_->Update();

	Vector3 enemyPosition = enemy_->GetPosition();
	Vector3 enemyVelocity = enemy_->GetVelocity();
	float enemyRotationX = enemy_->GetRotationX();

	ImGui::Begin("Enemy Controls");
	ImGui::SliderFloat3("Position", &enemyPosition.x, -10.0f, 10.0f);   // 位置を調整
	ImGui::SliderFloat("Velocity Z", &enemyVelocity.z, -1.0f, 1.0f);    // Z軸速度を調整
	ImGui::SliderAngle("Rotation X", &enemyRotationX, -180.0f, 180.0f); // 回転角を調整
	ImGui::End();

	// ImGuiの変更をEnemyに適用
	enemy_->SetPosition(enemyPosition);
	enemy_->SetVelocity(enemyVelocity);
	enemy_->SetRotationX(enemyRotationX);
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	player_->Draw();
	enemy_->Draw();

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
