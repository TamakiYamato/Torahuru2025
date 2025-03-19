#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include"Player.h"
#include"BackGround.h"
#include"GameClear.h"
Title::Title() {

}
Title::~Title() {

}
bool Title::Start() {
    m_spriteRender.Init("Assets/modelData/title.DDS", 1920, 1080);

    return true;

}
void Title::Update() {

    if (g_pad[0]->IsTrigger(enButtonA)) {
        //se->Play(false);
        NewGO<Game>(0, "game");
        DeleteGO(this);
    }
    m_spriteRender.Update();
}
void Title::Render(RenderContext& rc) {
    m_spriteRender.Draw(rc);
}