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
		//enemyPos[e].x = rand() % (1280 + 1 - 64) - (640 - 32);
		enemyPos[e].x = 640 + rand() % 500;
		enemyPos[e].y = rand() % (720 + 1 - 64) - (360 - 32);
			//for (int j = e + 1; j < enemyNum; j++)
			//{
			//	if (!m_alive[e] || !m_alive[j]) continue;

			//	
			//	float dx = enemyPos[e].x - enemyPos[j].x;
			//	float dy = enemyPos[e].y - enemyPos[j].y;
			//	
			//	if (dx * dx + dy * dy < 64 * 64)
			//	{
			//		enemyPos[e].x += 64;
			//		enemyPos[e].y += 64;
			//		//enemyPos[e].x += rand() % 2 ? 64 : -64;
			//		//enemyPos[e].y += rand() % 2 ? 64 : -64;
			//	}
			//}
			
		m_alive[e] = true;
	}
}

void Enemy::Update()
{
	for (int e = 0;e < enemyNum;e++)
	{
		if (m_alive[e])
		{
			enemyPos[e].x -= 3;

			//敵がした端まで到達したら再出現
			if (enemyPos[e].x < -640 - 32)
			{
				enemyPos[e].x = 640 + 32;
				enemyPos[e].y = rand() % (720 + 1 - 64) - (360 - 32);
			}
		}
	}
	//%2の確率で敵を1体復活させる
	if ((rand() % 100 - 1) <= 2) {
		for (int e = 0;e < enemyNum;e++) {

			if (!m_alive[e]) {
				m_alive[e] = true;
				enemyPos[e].x = 640 + 32;
				enemyPos[e].y = rand() % (720 + 1 - 64) - (360 - 32);
				break;//1体だけ復活させる
			}
		}
	}
	
	//敵
	for (int e = 0;e < enemyNum;e++)
	{
		enemyMat[e] = Math::Matrix::CreateTranslation(enemyPos[e].x, enemyPos[e].y, 0);

	}
}

void Enemy::Draw()
{
	//敵
	for (int e = 0;e < enemyNum;e++)
	{
		if (!m_alive[e])continue;

		SHADER.m_spriteShader.SetMatrix(enemyMat[e]);
		SHADER.m_spriteShader.DrawTex(&enemyTex, Math::Rectangle{ 0,0,64,64 }, 1.0f);
	}
}
