#include "stdafx.h"
#include "RotationFloor.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Title.h"
#include "ReverseFloor.h"
#include "SlowFloor.h"
#include "BlindFloor.h"
#include "FloorManager.h"
#include "Stairs.h"
#include "Stamina.h"
#include "GameClear.h"
#include "Gameover.h"
#include "Loading.h"
#include "FireGimmic.h"
#include "FirstFloor.h"
#include "TutorialUI.h"
#include"SecondFloor.h"

 namespace 
 {
	const Vector3 COLLISION_HEIGHT(0.0f, 0.0f, 0.0f);		//当たり判定の高さ
	const Vector3 COLLISION_SIZE_Z(100.0f, 100.0f, 100.0f);	//当たり判定の大きさ

	const float ROTATION_DEG_Y = 5.0f; //回転床がY軸に毎フレームごとに5進む
}

 bool RotationFloor::Start() 
 {
	 m_modelRender.Init("Assets/modelData/Stage2/RotationFloor/kaitenyukasecond.tkm");	
	 m_modelRender.SetPosition(m_position);	
	 m_modelRender.SetScale(m_scale);
	 m_modelRender.Update();

	 m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	 m_player = FindGO<Player>("player");
	 return true;
 }

 void RotationFloor::RotationFloorCalc()
 {
	 // 回転床の角速度
	 float angularVelocityPerSec = 10.0f;
	 float angularVelocityPerFrame = angularVelocityPerSec * g_gameTime->GetFrameDeltaTime();
	 m_rotation.AddRotationDegY(angularVelocityPerFrame);//回転軸はY軸

	 //床とプレイヤーの当たり判定を行う
	 Vector3 diff = m_player->GetPosition() - m_position;
	 // 回転床とプレイヤーのY座標の初期化
	 diff.y = 0.0f; 

	 float halfWidth = m_scale.x * 0.5f; //x座標の計算
	 float halfDepth = m_scale.z * 0.5f; //z座標の計算

	 //回転床の半径をもとに弧の長さを計算
	 if (diff.Length() < m_scale.x) 
	 {
		 //回転床の回転処理の結果を保存するための変数
		 auto posXZ = m_position; 
		 //回転床のｙ座標を0にする
		 posXZ.y = 0; 
		 //プレイヤーの現在地点の値を更新する為の変数
		 auto playerPosXZ = m_player->GetPosition(); 
		 //プレイヤーのｙ座標を0にする
		 playerPosXZ.y = 0; 
		 //回転床の回転に応じてプレイヤーのモデルが同じ方向に回転する処理
		 Vector3 toPlayer = playerPosXZ - posXZ; 
		 //過去の座標の値を消す
		 Vector3 offset = m_player->GetPosition() - m_position; 

		 //回転軸
		 Quaternion rot; 
		 
		 //Y軸ごとの回転するフレームの更新
		 rot.SetRotationDegY(angularVelocityPerFrame); 
		 rot.Apply(toPlayer); //プレイヤーの回転
		 rot.Apply(offset); //回転した座標のリセット

		 //新しい座標を生成する
		 Vector3 newPlayerPos = posXZ + toPlayer; 

		 //プレイヤーの座標の更新
		 m_player->SetPosition(newPlayerPos);

		 //回転床が動いた分の座標をプレイヤーにも適用する
		 Vector3 addForce = newPlayerPos - playerPosXZ; 


 void RotationFloor::Update()
 {
	 m_modelRender.SetRotation(m_rotation);
	 m_modelRender.SetPosition(m_position);

	 RotationFloorCalc(); //回転床の計算処理

	 m_modelRender.Update();

	 //コリジョンを毎フレーム再生成
	 m_physicsStaticObject.Release();
	 m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
 }

 void RotationFloor::Rotation()
 {
	 m_rotation.AddRotationDegY(ROTATION_DEG_Y); //毎フレームごとにY軸に5ずつ移動する処理

	 m_modelRender.SetRotation(m_rotation);
 }

 /// 回転床のモデルの描画
 void RotationFloor::Render(RenderContext& renderContext)
 {
	 m_modelRender.Draw(renderContext);
 }

 void RotationFloor::RotationFloorCalc()
 {
	 // 回転床の角速度
	 float angularVelocityPerSec = 10.0f;
	 float angularVelocityPerFrame = angularVelocityPerSec * g_gameTime->GetFrameDeltaTime();
	 m_rotation.AddRotationDegY(angularVelocityPerFrame); //回転軸はY軸

	 //床とプレイヤーの当たり判定を行う
	 Vector3 diff = m_player->GetPosition() - m_position;
	 // 回転床とプレイヤーのY座標の初期化
	 diff.y = 0.0f; 

	 float halfWidth = m_scale.x * 0.5f; //x座標の計算
	 float halfDepth = m_scale.z * 0.5f; //z座標の計算

	 //回転床の半径をもとに弧の長さを計算
	 if (diff.Length() < m_scale.x) 
	 {
		 //回転床の回転処理の結果を保存するための変数
		 auto posXZ = m_position; 
		 //回転床のｙ座標を0にする
		 posXZ.y = 0; 
		 //プレイヤーの現在地点の値を更新する為の変数
		 auto playerPosXZ = m_player->GetPosition(); 
		 //プレイヤーのｙ座標を0にする
		 playerPosXZ.y = 0; 
		 //回転床の回転に応じてプレイヤーのモデルが同じ方向に回転する処理
		 Vector3 toPlayer = playerPosXZ - posXZ; 
		 //過去の座標の値を消す
		 Vector3 offset = m_player->GetPosition() - m_position; 

		 //回転軸
		 Quaternion rot; 
		 
		 //Y軸ごとの回転するフレームの更新
		 rot.SetRotationDegY(angularVelocityPerFrame); 
		 rot.Apply(toPlayer); //プレイヤーの回転
		 rot.Apply(offset);  //回転した座標のリセット

		 //新しい座標を生成する
		 Vector3 newPlayerPos = posXZ + toPlayer; 

		 //プレイヤーの座標の更新
		 m_player->SetPosition(newPlayerPos);

		 //回転床が動いた分の座標をプレイヤーにも適用する
		 Vector3 addForce = newPlayerPos - playerPosXZ; 


		 //フレーム時間で割ってcm/frame->cm/秒に単位を変換していく
		 //ヒューマンエラー対策 : Max側とK2Engine側の値設定ミスを防ぐため
		 addForce /= g_gameTime->GetFrameDeltaTime();  

		 //動く床の移動速度をキャラクターの移動速度に加算
		 m_player->AddForce(addForce); 
	 }

 }

 void RotationFloor::Update() 
 {
	 m_modelRender.SetRotation(m_rotation);	
	 m_modelRender.SetPosition(m_position);

	 RotationFloorCalc(); //回転床の計算処理

	 m_modelRender.Update();

	 //コリジョンを毎フレーム再生成
	 m_physicsStaticObject.Release();  
	 m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix()); 
 }

 void RotationFloor::Rotation() 
 {
    m_rotation.AddRotationDegY(ROTATION_DEG_Y); //毎フレームごとにY軸に5ずつ移動する処理

    m_modelRender.SetRotation(m_rotation); 
 }

 /// 回転床のモデルの描画
 void RotationFloor::Render(RenderContext& renderContext)
 {
	m_modelRender.Draw(renderContext);

 }