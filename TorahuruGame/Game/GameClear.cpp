#include "stdafx.h"
#include "GameClear.h"
#include"Stairs.h"
#include"Player.h"
#include"Title.h"

GameClear::GameClear()
{

}

GameClear::~GameClear() {

}

bool GameClear:: Start() {
	
	m_spriteRender.Init("Assets/modelData/GameClear.DDS", 1920, 1080);//ゲームクリア
	//プレイヤー側のオブジェクトを持ってくる
	m_player = FindGO<Player>("player");
	m_stairs = FindGO<Stairs>("stairs");//ここでインスタンスを呼び込む!!
	return true;
}
void GameClear::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		DeleteGO(m_player);
		DeleteGO(m_stairs);

		NewGO<Title>(0, "title");
		DeleteGO(this);
		//自身を削除する
	}

	//画像の更新。
	m_spriteRender.Update();
}


void GameClear::Render(RenderContext& rc)
{
	//画像の描画。
	m_spriteRender.Draw(rc);
}