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
		m_alive[e] = true;

		enemyPos[e].x = 640 + rand() % 500;
		enemyPos[e].y = 328 - (e * (720 / enemyNum));

		//enemyPos[e].y = rand() % (720 + 1 - 64) - (360 - 32);

		//enemyDirection[e].x = -(rand() % 100) / 50.0f;
		//enemyDirection[e].y = (rand() % 200 - 100) / 50.0f;

	}
}

void Enemy::Update()
{
	for (int e = 0;e < enemyNum;++e)
	{
		if (m_alive[e])
		{
			enemyPos[e].x -= 3;

			//enemyPos[e].x += enemyDirection[e].x;
			//enemyPos[e].y += enemyDirection[e].y;

			//敵がした端まで到達したら再出現
			if (enemyPos[e].x < -640 - 32)
			{
				enemyPos[e].x = 640 + 32;
				enemyPos[e].y = 328 - (e * (720 / enemyNum));
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
	//%2の確率で敵を1体復活させる
	if (rand() % 100 < 2) {
		for (int e = 0;e < enemyNum;++e) {

			if (!m_alive[e]) {
				m_alive[e] = true;
				enemyPos[e].x = 640 + 32;
				enemyPos[e].y = 328 - (e * (720 / enemyNum));

				break;//1体だけ復活させる
			}
		}
	}

	//敵
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
		if (!m_alive[e])continue;

		SHADER.m_spriteShader.SetMatrix(enemyMat[e]);
		SHADER.m_spriteShader.DrawTex(&enemyTex, Math::Rectangle{ 0,0,64,64 }, 1.0f);
	}
}
