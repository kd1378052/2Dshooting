#include "ResultScreen.h"
#include"../Game/Score.h"
#include "../SceneManager.h"


ResultScreen::ResultScreen()
{
	ResultbackTex.Load("Texture/Result/resultback.png");


	m_score = new Score();

}

ResultScreen::~ResultScreen()
{
	delete m_score;

	ResultbackTex.Release();
}

void ResultScreen::Init()
{
}

void ResultScreen::Update()
{
	m_score->Load();

	ResultbackMat = Math::Matrix::CreateTranslation(0, 0, 0);

}

void ResultScreen::Draw()
{
	m_score->Draw();

	SHADER.m_spriteShader.SetMatrix(ResultbackMat);
	SHADER.m_spriteShader.DrawTex(&ResultbackTex, Math::Rectangle{ 0,0,1280,720 }, 1.0f);

	char text[1000];
	sprintf_s(text, sizeof(text), "1ˆÊ %d", m_score->saveScore[0]);
	SHADER.m_spriteShader.DrawString(-41, 13, text, Math::Vector4(1.00f, 1.00f, 1.00f, 1));
	SHADER.m_spriteShader.DrawString(-39, 10, text, Math::Vector4(1.00f, 1.00f, 1.00f, 1));
	SHADER.m_spriteShader.DrawString(-40, 12, text, Math::Vector4(0.00f, 0.00f, 0.00f, 1));
	sprintf_s(text, sizeof(text), "2ˆÊ %d", m_score->saveScore[1]);
	SHADER.m_spriteShader.DrawString(-151, -58, text, Math::Vector4(1.00f, 1.00f, 1.00f, 1));
	SHADER.m_spriteShader.DrawString(-148, -56, text, Math::Vector4(1.00f, 1.00f, 1.00f, 1));
	SHADER.m_spriteShader.DrawString(-150, -57, text, Math::Vector4(0.00f, 0.00f, 0.00f, 1));
	sprintf_s(text, sizeof(text), "3ˆÊ %d", m_score->saveScore[2]);
	SHADER.m_spriteShader.DrawString(69, -69, text, Math::Vector4(1.00f, 1.00f, 1.00f, 1));
	SHADER.m_spriteShader.DrawString(67, -66, text, Math::Vector4(1.00f, 1.00f, 1.00f, 1));
	SHADER.m_spriteShader.DrawString(68, -67, text, Math::Vector4(0.00f, 0.00f, 0.00f, 1));
	
}
