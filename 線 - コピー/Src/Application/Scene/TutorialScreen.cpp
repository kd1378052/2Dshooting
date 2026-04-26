#include "TutorialScreen.h"

TutorialScreen::TutorialScreen()
{
}

TutorialScreen::~TutorialScreen()
{
}

void TutorialScreen::Init()
{
}

void TutorialScreen::Update()
{
}

void TutorialScreen::Draw()
{
	// 文字列表示
	SHADER.m_spriteShader.DrawString(0, 0, "チュートリアル", Math::Vector4(1, 1, 1, 1));

}