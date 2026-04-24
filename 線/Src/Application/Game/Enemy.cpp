#include "Enemy.h"

Enemy::Enemy()
{
	srand(time(0));
	enemyTex.Load("Texture/enemy.png");
}

Enemy::~Enemy()
{
	enemyTex.Release();
}

void Enemy::Init()
{
	srand(time(0));

	//敵の初期化処理
	for (int e = 0;e < enemyNum;e++)
	{
		enemyX[e] = rand() % (1280 + 1 - 64) - (640 - 32);
		enemyY[e] = rand() % (720 + 1 - 64) - (360 - 32);
		enemyFlg[e] = 1;
	}
}

void Enemy::Update()
{
	for (int e = 0;e < enemyNum;e++)
	{
		if (enemyFlg[e] == 1)
		{
			enemyX[e] -= 3;

			//敵がした端まで到達したら再出現
			if (enemyX[e] < -640 - 32)
			{
				enemyX[e] = 640 + 32;
			}
		}
	}
	//敵
	for (int e = 0;e < enemyNum;e++)
	{
		enemyMat[e] = Math::Matrix::CreateTranslation(enemyX[e], enemyY[e], 0);

	}
}

void Enemy::Draw()
{
	//敵
	for (int e = 0;e < enemyNum;e++)
	{
		if (enemyFlg[e] == 1)
		{
			SHADER.m_spriteShader.SetMatrix(enemyMat[e]);
			SHADER.m_spriteShader.DrawTex(&enemyTex, Math::Rectangle{ 0,0,64,64 }, 1.0f);
		}
	}
}
