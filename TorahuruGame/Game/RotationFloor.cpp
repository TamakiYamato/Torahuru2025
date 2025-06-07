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
namespace {
	const Vector3 COLLISION_HEIGHT (0.0f, 0.0f, 0.0f);//当たり判定の高さ
	const Vector3 COLLISION_SIZE_Z (100.0f,100.0f, 100.0f);//当たり判定の大きさ
}

RotationFloor::RotationFloor() {
	
}

RotationFloor::~RotationFloor() {
}

bool RotationFloor::Start() {
	m_modelRender.Init("Assets/modelData/Stage2/RotationFloor/kaitenyuka.tkm");	//回転床の修正
	//当たり判定を可視化する。
   // PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	//コリジョンオブジェクトを。
		//動く床の上に設置する(キャラクターが上に乗ったら反応するようにしたいため)。

	m_modelRender.SetPosition(m_position);
	
	//playerの呼びこみやUpdateの初期化などを行う
	m_player = FindGO<Player>("player");
	
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	
	

	return true;
}

void RotationFloor::Update() {
	// 回転床の角速度
	float angularVelocityPerSec = 5.0f; // 度/秒
	// 1フレームあたりの角度変化量
	float angularVelocityPerFrame = angularVelocityPerSec * g_gameTime->GetFrameDeltaTime();
	m_rotation.AddRotationDegY(angularVelocityPerFrame);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetPosition(m_position);
	// 床とプレイヤーの当たり判定を行う
	Vector3 diff = m_player->GetPosition() - m_position;
	diff.y = 0.0f; // Y軸の差分は無視する
	if (diff.Length() < m_scale.x)
	{
	   // プレイヤーの位置を回転床で回転させた結果の座標を求める
		auto posXZ = m_position;
		posXZ.y = 0;
		auto playerPosXZ = m_player->GetPosition();
		playerPosXZ.y = 0;
	   Vector3 toPlayer = playerPosXZ - posXZ;

	   Quaternion rot;
	   rot.SetRotationDegY(angularVelocityPerFrame);
	   rot.Apply(toPlayer);
	   Vector3 newPlayerPos = posXZ + toPlayer;
	   Vector3 addForce = newPlayerPos - playerPosXZ;
	   addForce /= g_gameTime->GetFrameDeltaTime(); // フレーム時間で割ってcm/frame->cm/秒に単位を変換

	   //動く床の移動速度をキャラクターの移動速度に加算。
	   m_player->AddForce(addForce);
	}
	m_modelRender.Update();
}

void RotationFloor::Rotation() {
	m_rotation.AddRotationDegY(3.0f);

	m_modelRender.SetRotation(m_rotation);
}
void RotationFloor::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);
}