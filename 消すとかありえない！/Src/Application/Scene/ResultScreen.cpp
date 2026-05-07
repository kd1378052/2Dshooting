#include "ResultScreen.h"
#include"../Game/Score.h"
#include "../SceneManager.h"


ResultScreen::ResultScreen()
{
	ResultscoreTex.Load("Texture/Result/Resultscore.png");
	ResultbackTex.Load("Texture/Result/resultback.png");
	scorenumbersTex.Load("Texture/Result/scorenumbers.png");


	m_score = new Score();

}

ResultScreen::~ResultScreen()
{
	delete m_score;

	scorenumbersTex.Release();
	ResultscoreTex.Release();
	ResultbackTex.Release();

}

void ResultScreen::Init()
{

}

void ResultScreen::Update()
{
	unsigned long tep = m_score->score;

	for (int i = maxDigits - 1; i >= 0; --i)
	{
		//下位の桁から抽出し、配列に格納
		m_scorenumbers[i] = tep % 10;
		tep /= 10;
	}

	ResultbackMat = Math::Matrix::CreateTranslation(0, 0, 0);
	ResultscoreMat = Math::Matrix::CreateTranslation(0,250, 0);

}

void ResultScreen::Draw()
{
	m_score->Draw();

	SHADER.m_spriteShader.SetMatrix(ResultbackMat);
	SHADER.m_spriteShader.DrawTex(&ResultbackTex, Math::Rectangle{ 0,0,1280,720 }, 1.0f);
	//スコア文字
	SHADER.m_spriteShader.SetMatrix(ResultscoreMat);
	SHADER.m_spriteShader.DrawTex(&ResultscoreTex, Math::Rectangle{ 0,0,500,180 }, 1.0f);

	for (int i = 0; i < maxDigits; ++i)
	{
		Math::Rectangle rc = { 45 * m_scorenumbers[i],0,45,70 };

		float posX = 0;
		float posY = 0;

		SHADER.m_spriteShader.SetMatrix(scorenumbersMat);
		SHADER.m_spriteShader.DrawTex(&scorenumbersTex,
			posX + (i * 30)//ｘ
			, posY + 0,//ｙ
			30, //幅
			55,//高さ
			&rc);
	}

	
	//sprintf_s(text, sizeof(text), "1位 %d", m_score->saveScore[0]);
	//SHADER.m_spriteShader.DrawString(-41, 13, text, Math::Vector4(1.00f, 1.00f, 1.00f, 1));
	//SHADER.m_spriteShader.DrawString(-39, 10, text, Math::Vector4(1.00f, 1.00f, 1.00f, 1));
	//SHADER.m_spriteShader.DrawString(-40, 12, text, Math::Vector4(0.00f, 0.00f, 0.00f, 1));
	//sprintf_s(text, sizeof(text), "2位 %d", m_score->saveScore[1]);
	//SHADER.m_spriteShader.DrawString(-151, -58, text, Math::Vector4(1.00f, 1.00f, 1.00f, 1));
	//SHADER.m_spriteShader.DrawString(-148, -56, text, Math::Vector4(1.00f, 1.00f, 1.00f, 1));
	//SHADER.m_spriteShader.DrawString(-150, -57, text, Math::Vector4(0.00f, 0.00f, 0.00f, 1));
	//sprintf_s(text, sizeof(text), "3位 %d", m_score->saveScore[2]);
	//SHADER.m_spriteShader.DrawString(69, -69, text, Math::Vector4(1.00f, 1.00f, 1.00f, 1));
	//SHADER.m_spriteShader.DrawString(67, -66, text, Math::Vector4(1.00f, 1.00f, 1.00f, 1));
	//SHADER.m_spriteShader.DrawString(68, -67, text, Math::Vector4(0.00f, 0.00f, 0.00f, 1));
	//
}
