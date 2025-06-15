#include "stdafx.h"
#include "Offering.h"
#include "Player.h"
#include "Game.h"

namespace
{
	const Vector3 COLLISION_SIZE(10.0f, 10.0f, 10.0f);	//当たり判定の大きさ
}

Offering::Offering()
{
}

Offering::~Offering()
{
}

bool Offering::Start() 
{
	//モデルの読み込み
	m_modelRender->Init("Assets/modelData/item/dedicationItem.tkm");		//モデルを実装
	
	m_modelRender->Update();
	m_physicsStaticObject->CreateFromModel(m_modelRender->GetModel(), m_modelRender->GetModel().GetWorldMatrix());

	m_collisionObject = NewGO<CollisionObject>(0, "collisionObject");
	m_collisionObject->CreateBox(
		m_position,	//座標
		Quaternion::Identity, //回転
		COLLISION_SIZE //大きさ
	);
	m_collisionObject->SetIsEnableAutoDelete(false);	//自動で削除されないようにする
	return true;
}

void Offering::Update() 
{
	if (m_player == nullptr) {
		m_player = FindGO<Player>("Player");
	}
	if(m_game== nullptr) {
		m_game = FindGO<Game>("Game");
	}

	Rotation();	//回転処理。

	//コリジョンとplayerが当たった場合
	//floorManagerで効果を与える
	//if (m_collisionObject->IsHit(m_player->GetCharacterController()) == true)
	//{
	//	m_game->m_dedicationItemCount++;
	//	DeleteGO(this);	//自分自身を削除
	//}
	//絵描きさんの更新処理。
	m_modelRender->Update();
}

void Offering::Rotation()
{
	//回転を加算
	m_rotation.AddRotationDegY(2.0f);

	//絵描きに回転を教える
	m_modelRender->SetRotation(m_rotation);
}
void Offering::Render(RenderContext&rc) 
{
	m_modelRender->Draw(rc);
}