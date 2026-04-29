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
	

	for (int e = 0;e < enemyNum ; e++)
	{
		m_alive[e] = true;

		

		enemySize[e] = ENEMY_LARGE;

		enemyPos[e].x = 640 + rand() % 500;
		enemyPos[e].y = rand() % (690 + 1 - 64) - (360 - 32);
	}
	//追加処理
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
			if (enemyPos[e].x < E_SCREEN_LEFT - 32)
			{
				enemyPos[e].x = E_SCREEN_RIGHT + 32;
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

		Math::Matrix transMat, scaleMat;
		if (enemySize[e] == ENEMY_LARGE)
		{
			scaleMat = Math::Matrix::CreateScale(1.2f,1.2f, 0);
		}
		if(enemySize[e] == ENEMY_SMALL)
		{
			scaleMat = Math::Matrix::CreateScale(1.0f, 1.0f, 0);
		}
		transMat = Math::Matrix::CreateTranslation(enemyPos[e].x, enemyPos[e].y, 0);

		//合成 ・・・　かく　かい　い
		// 拡大　回転　移動
		enemyMat[e] = scaleMat * transMat;
	}
}

void Enemy::Draw()
{

	//敵
	for (int e = 0;e < enemyNum;e++)
	{
		if (!m_alive[e])continue;

		//float scale = 1.0f;

		//if (enemySize[e] == ENEMY_LARGE) scale = 1.0f;
		//else scale = 1.0f;

		SHADER.m_spriteShader.SetMatrix(enemyMat[e]);

		
		//SHADER.m_spriteShader.DrawTex(&enemyTex,
		//	Math::Rectangle{ 0,0,64,64 },
		//	scale);

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

void Enemy::Split(int index)
{
	if (enemySize[index] == ENEMY_SMALL)
	{
		m_alive[index] = false;
		return;
	}

	// 親を消す
	m_alive[index] = false;

	// 子2体生成（空いてる枠に入れる）
	int count = 0;

	for (int i = 0; i < enemyNum; i++)
	{
		if (m_alive[i]) continue;


		m_alive[i] = true;
		enemySize[i] = ENEMY_SMALL;

		enemyPos[i] = enemyPos[index];

		enemyVel[i].x = -(rand() % 100) / 50.0f;
		enemyVel[i].y = (rand() % 200 - 100) / 50.0f;

		// ばらける方向
		enemyPos[i].x += (count == 0 ? -20 : 20);
		enemyPos[i].y += (count == 0 ? -20 : 20);

		if (enemyPos[i].x < E_SCREEN_LEFT - 32)
		{
			enemyPos[i].x = E_SCREEN_RIGHT + 32;
			enemyPos[i].y = rand() % (720 + 1 - 64) - (360 - 32);
		}
		if(enemyPos[i].y < E_SCREEN_BOTTOM - 32)
		{
			enemyPos[i].y = E_SCREEN_TOP + 32;
		}
		if(enemyPos[i].y > E_SCREEN_TOP + 32)
		{
			enemyPos[i].y = E_SCREEN_BOTTOM - 32;
		}


		count++;

		//ここで数を数えている
		if (count >= 2) break;
	}
}
