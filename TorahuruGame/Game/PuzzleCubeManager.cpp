#include "stdafx.h"
#include "PuzzleCubeManager.h"
#include "PuzzleCube.h"

PuzzleCubeManager::PuzzleCubeManager()
{
}

PuzzleCubeManager::~PuzzleCubeManager()
{
}

bool PuzzleCubeManager::Start()
{
	return true;
}

void PuzzleCubeManager::Update()
{
}

void PuzzleCubeManager::Rotation()
{
	//if (g_pad[0]->IsTrigger(enButtonLeft))
	//{
	//	// 90度ずつ加算
	//	m_rotationY += 90.0f;
	//	if (m_rotationY > 360)
	//	{
	//		m_rotationY = 0;
	//	}

	//	SetRotation();

	//	modelRender.SetRotation(rotation);
	//}
	//else if (g_pad[0]->IsTrigger(enButtonUp))
	//{
	//	// 90度ずつ加算
	//	m_rotation2Y += 90.0f;
	//	if (m_rotation2Y > 360)
	//	{
	//		m_rotation2Y = 0;
	//	}

	//	SetRotation();

	//	modelRender2.SetRotation(rotation2);
	//}
	//else if (g_pad[0]->IsTrigger(enButtonRight))
	//{
	//	// 90度ずつ加算
	//	m_rotation3Y += 90.0f;
	//	if (m_rotation3Y > 360)
	//	{
	//		m_rotation3Y = 0;
	//	}

	//	SetRotation();

	//	modelRender3.SetRotation(rotation3);
	//}
}

void PuzzleCubeManager::Render(RenderContext& rc)
{
}