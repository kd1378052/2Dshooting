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
	for (int e = 0;e < enemyNum ; e++)
	{
		m_alive[e] = true;

		enemyPos[e].x = 640 + rand() % 500;
		enemyPos[e].y = rand() % (690 + 1 - 64) - (360 - 32);
	}
	//for (int i = 0; i < enemyNum; i++)
	//{
	//	AvoidanceEnemy();
	//}

}

void Enemy::Update()
{
	for (int e = 0;e < enemyNum;e++)
	{
		if (m_alive[e])
		{
			enemyPos[e].x -= 3;

			enemyPos[e].x += enemyVel[e].x;
			enemyPos[e].y += enemyVel[e].y;

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

//追加処理?
void Enemy::AvoidanceEnemy()
{
	for (int a = 0;a < enemyNum;a++)
	{
		for (int b = a + 1; b < enemyNum; b++)
		{
			if (!m_alive[a] || !m_alive[b]) continue;


			float dx = enemyPos[a].x - enemyPos[b].x;
			float dy = enemyPos[a].y - enemyPos[b].y;

			if (dx * dx + dy * dy < 64 * 64)
			{
				enemyPos[a].x += rand() % 2 ? 64 : -64;
				enemyPos[a].y += rand() % 2 ? 64 : -64;
			}
		}
	}
}

void Enemy::EnemyChange()
{

	for (int e = 0;e < enemyNum;e++) {

		if (!m_alive[e]) {
			m_alive[e] = true;
			enemyPos[e].x = 640 + 32;
			enemyPos[e].y = rand() % (720 + 1 - 64) - (360 - 32);
			
			enemyVel[e].x = -(rand() % 100) / 50.0f;
			enemyVel[e].y = (rand() % 200 - 100) / 50.0f;

			break;//1体だけ復活させる
		}
		if (enemyPos[e].x < -640 - 32)
		{
			enemyPos[e].x = 640 + 32;
			enemyPos[e].y = rand() % (720 + 1 - 64) - (360 - 32);
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
