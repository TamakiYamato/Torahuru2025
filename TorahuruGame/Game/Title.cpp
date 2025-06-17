#include "stdafx.h"
#include "Loading.h"
#include "Title.h"
#include "Tips.h"
#include "Game.h"
#include"Player.h"
#include"BackGround.h"
#include"sound/SoundEngine.h"
#include"sound/SoundSource.h"

namespace {
    Vector3 BUTTON_POSITION = Vector3(0.0f, -200.0f, 0.0f);
}

Title::Title() {
}

Title::~Title() {

}

bool Title::Start() {
    m_spriteRender.Init("Assets/modelData/Title/title.DDS", 1920, 1080);
    m_Loading = NewGO<Loading>(1, "loading");

    m_startButtonRender.Init("Assets/modelData/Title/startButtonText.DDS",1920, 1080);
    m_startButtonRender.SetPosition(Vector3(BUTTON_POSITION));

    // 効果音を読み込む。
    g_soundEngine->ResistWaveFileBank(1,"Assets/sound/wadaiko.wav");
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
			// 効果音を再生。
            SoundSource* se = NewGO<SoundSource>(0);
            se->Init(1);
            // 効果音はループさせない。
            se->Play(false);
            // 音量。
            se->SetVolume(2.0f);
            // シーン切り替え開始。
            m_isWaitLoadOut = true;
            m_Loading->StartLoadOut();
            // BGMを停止。
            DeleteGO(m_bgm);
        }
    }

    //α値を変化させる。
    if (m_isWaitLoadOut)
    {
       
    }
    else
    {
        m_alpha += g_gameTime->GetFrameDeltaTime() * 1.2f;
        // TODO: ボタンテキストが点滅する仕組みを理解する。
        // fabsf→float型の絶対値（absolute value）を返す関数。
        // sinf→sin（サイン、正弦）関数のfloat版。
        m_startButtonRender.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, fabsf(sinf(m_alpha))));
    }

    m_startButtonRender.Update();
    m_spriteRender.Update();
}

void Title::Buttontext()
{
    
}

void Title::Render(RenderContext& rc) {
    m_spriteRender.Draw(rc);
    m_startButtonRender.Draw(rc);
}
