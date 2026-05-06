#include "Enemy.h"

Enemy::Enemy()
{
	srand(time(0));
	enemyTex.Load("Texture/Game/enemy.png");
}

Enemy::~Enemy()
{
	enemyTex.Release();
}

void Enemy::Init()
{
	for (int e = 0;e < enemyNum ; ++e)
	{
		alive[e] = true;

		enemyPos[e].x = 640 + rand() % 500;
		enemyPos[e].y = 323 - (e * (720 / enemyNum));

	}
}

void Enemy::Update()
{
	for (int e = 0;e < enemyNum;++e)
	{
		if (alive[e])
		{
			enemyPos[e].x -= 3;

			//敵がした端まで到達したら再出現
			if (enemyPos[e].x < -640 - 32)
			{
				enemyPos[e].x = 640 + 32;
				enemyPos[e].y = 323 - (e * (720 / enemyNum));
			}
			if (enemyPos[e].y < E_SCREEN_BOTTOM - 25)
			{
				enemyPos[e].y = E_SCREEN_TOP + 25;
			}
			if (enemyPos[e].y > E_SCREEN_TOP + 25)
			{
				enemyPos[e].y = E_SCREEN_BOTTOM - 25;
			}
		}
	}
	//%の確率で敵を1体復活させる
	if (rand() % 100 < 2) {
		for (int e = 0;e < enemyNum;++e) {

			if (!alive[e]) {
				alive[e] = true;
				enemyPos[e].x = 640 + rand() % 250;
				enemyPos[e].y = 323 - (e * (720 / enemyNum));

				break;//1体だけ復活させる
			}
		}
	}

	for (int e = 0;e < enemyNum;++e)
	{
		enemyMat[e] = Math::Matrix::CreateTranslation(enemyPos[e].x, enemyPos[e].y, 0);

	}
}

void Enemy::Draw()
{
	//敵
	for (int e = 0;e < enemyNum;++e)
	{
		if (!alive[e])continue;

		SHADER.m_spriteShader.SetMatrix(enemyMat[e]);
		SHADER.m_spriteShader.DrawTex(&enemyTex, Math::Rectangle{ 0,0,64,64 }, 1.0f);
	}
}
