#include "Boss.h"

Boss::Boss()
{
	bossTex.Load("Texture/Game/boss.png");
}

Boss::~Boss()
{
	bossTex.Release();
}

void Boss::Init()
{
	bossFlg = true;

	bossPos.x = 0;
	bossPos.y = 0;

}

void Boss::Update()
{
	if (bossFlg)
	{
		bossPos.x -= 3;

		//端まで到達したら再出現
		if (bossPos.x < B_SCREEN_LEFT)
		{
			bossPos.x = B_SCREEN_RIGHT;
		}
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

}

void Boss::Draw()
{
	if (bossFlg)
	{
		SHADER.m_spriteShader.SetMatrix(bossMat);
		SHADER.m_spriteShader.DrawTex(&bossTex, Math::Rectangle(0, 0, 200, 200), 1.0f);
	}
}
