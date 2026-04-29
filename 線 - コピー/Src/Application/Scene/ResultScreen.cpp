#include "ResultScreen.h"
#include "../SceneManager.h"


ResultScreen::ResultScreen()
{
}

ResultScreen::~ResultScreen()
{
}

void ResultScreen::Init()
{
}

void ResultScreen::Update()
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		SCENEMANAGER.ChangState(new SelectionScreen());

	}
}

void ResultScreen::Draw()
{
	// •¶Žš—ñ•\Ž¦
	SHADER.m_spriteShader.DrawString(0, 0, "ƒŠ‚´‚é‰æ–Ê", Math::Vector4(1, 1, 1, 1));

}
