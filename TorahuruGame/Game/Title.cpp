#include "stdafx.h"
#include "Loading.h"
#include "Title.h"
#include "Tips.h"
#include "Game.h"
#include"Player.h"
#include"BackGround.h"
#include"sound/SoundEngine.h"
#include"sound/SoundSource.h"
//#include"GameManager.h"
Title::Title() {
   // NewGO<GameManager>(0, "gamemanager");
}
Title::~Title() {

}
bool Title::Start() {
    m_spriteRender.Init("Assets/modelData/Title/title.DDS", 1920, 1080);

    m_Loading = FindGO<Loading>("loading");
    m_tips = FindGO<Tips>("tips");
    return true;
}
void Title::Update() {
    // シーンを切り替える時。
    if (m_isWaitLoadOut) {
        if (!m_Loading->IsLoading()) {
            NewGO<Game>(0, "game");
            // タイトルを削除。
            DeleteGO(this);
        }

    }
    else {
        // Aボタンを押したら。
        if (g_pad[0]->IsTrigger(enButtonA)) {
            //se->Play(false);
            // シーン切り替え開始。
            m_isWaitLoadOut = true;
            NewGO<Tips>(0, "tips");
            m_Loading->StartLoadOut();
        }
    }

    //α値を変化させる。
    if (m_isWaitLoadOut)
    {
        //m_Loading->
    }
    else
    {
        m_alpha += g_gameTime->GetFrameDeltaTime() * 1.2f;
    }

    m_spriteRender.Update();
    m_pressButton.Update();
}
void Title::Render(RenderContext& rc) {
    m_spriteRender.Draw(rc);
}