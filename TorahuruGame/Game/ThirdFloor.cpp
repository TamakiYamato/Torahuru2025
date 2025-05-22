#include "stdafx.h"
#include "ThirdFloor.h"
#include "BackGround.h"
#include "ReverseFloor.h"
#include "SlowFloor.h"
#include "BlindFloor.h"
#include "FloorManager.h"
#include "FireGimmic.h"
#include "Stairs.h"

bool ThirdFloor::Start()
{
    return true;
}

void ThirdFloor::Update()
{
}

void ThirdFloor::Render(RenderContext& rc)
{
    //レベルの描画
    m_levelRender.Draw(rc);
}
