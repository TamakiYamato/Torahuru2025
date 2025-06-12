#include "stdafx.h"
#include "GameCamera.h"
#include"Game.h"
#include"Player.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{
	
}

bool GameCamera::Start()
{
	//playerを見つける
	m_player = FindGO<Player>("player");
	//カメラの座標設定
	m_toCameraPos.Set(0.0f, 150.0f, -300.0f);;
	// カメラの初期化
	m_springCamera.Init(
		*g_camera3D,   // 3Dカメラ
		1000.0f,       // カメラの最大速度
		true,          // コリジョンの有効化
		5.0f           // コリジョンの大きさ
	);
	
	// 指定した軸とカメラでクォータニオンを初期化。
	Quaternion yRot180;
	yRot180.SetRotationDeg(Vector3::AxisY, 180.0f);
	// 回転をカメラに適用
	yRot180.Apply(m_toCameraPos);

	//カメラの近平面・遠平面の設定
	/*g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(1000000.0f);*/

	return true;
}

void GameCamera::Update()
{

	//カメラを更新。
	//注視点を計算する。
	Vector3 target = m_player->m_position;
	//プレイヤの足元からちょっと上を注視点とする。
	target.y += 100.0f;

	Vector3 toCameraPosOld = m_toCameraPos;
	//パッドの入力を使ってカメラを回す。
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();
	//Y軸周りの回転
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 2.0f * x);
	qRot.Apply(m_toCameraPos);
	//X軸周りの回転。
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * y);
	qRot.Apply(m_toCameraPos);
	//カメラの回転の上限をチェックする。
	//注視点から視点までのベクトルを正規化する。
	//正規化すると、ベクトルの大きさが１になる。
	//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.2f) {
		//カメラが上向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.9f) {
		//カメラが下向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}

	//視点を計算する。
	Vector3 pos = target + m_toCameraPos;

	// 
	m_springCamera.SetPosition(pos);
	m_springCamera.SetTarget(target);

	// カメラの更新。
	m_springCamera.Update();


	//メインカメラに注視点と視点を設定する。
	/*g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);*/

	//カメラの更新。
	/*g_camera3D->Update();*/
}

void GameCamera::Refresh()
{
	m_springCamera.Refresh();

	m_springCamera.Update();
}