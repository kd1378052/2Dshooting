#include "Boss.h"

Boss::Boss()
{
	bossTex.Load("Texture/Game/boss.png");
	effectTex.Load("Texture/Game/Effect/effect.png");
	m_alpha = 1.0f;
	m_alphaAdd = -0.01f;
}

Boss::~Boss()
{
	bossTex.Release();
	effectTex.Release();

}

void Boss::Init()
{
	bossFlg = false;
	effectFlg = false;

	bossPos.x = screenRight - 100.0f;
	bossPos.y = 0.0f;
	bossMove.x = -5.0f;
	bossMove.y = 5.0f;
	bossHP = 100.0f;
	bossAppearance = 0.0f;
	m_alphaAdd = -0.01f;
	m_alpha = 1.0f;

}

void Boss::Update()
{
	//出現カウント
	bossAppearance++;

	//エフェクト透明
	m_alpha += m_alphaAdd;

	if (m_alpha < 0.5f)
	{
		m_alpha = 0.5f;
		m_alphaAdd *= -1;

	}
	else if (m_alpha > 1.0f)
	{
		m_alpha = 1.0f;
		m_alphaAdd *= -1;
	}

	if (bossAppearance > 120)
	{
		bossFlg = true;
		if (bossFlg)
			{
			bossPos.x += bossMove.x;
			bossPos.y += bossMove.y;
			if (bossPos.x > screenRight - 100 || bossPos.x < screenLeft + 60)
			{
				bossMove.x *= -1;
			}
			if (bossPos.y > screenTop - 120 || bossPos.y < screenBottom + 90)
			{
				bossMove.y *= -1;
			}
		}
		if (bossAppearance > 130)
		{
			effectFlg = false;
		}
		
		////端まで到達したら再出現
		//if (bossPos.x < screenLeft -100)
		//{
		//	bossPos.x = screenRight +100;
		//}

		//if (bossPos[e].y < B_SCREEN_BOTTOM - 25)
		//{
		//	bossPos[e].y = B_SCREEN_TOP + 25;
		//}
		//if (bossPos[e].y > B_SCREEN_TOP + 25)
		//{
		//	bossPos[e].y = B_SCREEN_BOTTOM - 25;
		//}
	}

	bossMat = Math::Matrix::CreateTranslation(bossPos.x, bossPos.y, 0);
	effectMat = Math::Matrix::CreateTranslation(0, 0, 0);

}

void Boss::Draw()
{
	if (bossFlg)
	{
		if (bossAppearance > 120)
		{
			SHADER.m_spriteShader.SetMatrix(bossMat);
			SHADER.m_spriteShader.DrawTex(&bossTex, Math::Rectangle(0, 0, 200, 200), 1.0f);

			char Hp[100];//1文字列格納用の配列作成
			sprintf_s(Hp, sizeof(Hp), "HP : %d", bossHP);
			SHADER.m_spriteShader.DrawString(bossPos.x, bossPos.y + 64, Hp, Math::Vector4(1, 1, 0, 1));
		}
	}
	if (effectFlg == true)
	{
		//エフェクト
		SHADER.m_spriteShader.SetMatrix(effectMat);
		SHADER.m_spriteShader.DrawTex(&effectTex, Math::Rectangle{ 0,0,1280,720 }, m_alpha);
	}
}
