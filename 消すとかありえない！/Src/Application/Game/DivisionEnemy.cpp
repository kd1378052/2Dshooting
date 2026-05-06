#include "DivisionEnemy.h"

DivisionEnemy::DivisionEnemy()
{
	srand(time(0));
	enemyTex.Load("Texture/Game/enemy1.png");
}

DivisionEnemy::~DivisionEnemy()
{
	enemyTex.Release();
}

void DivisionEnemy::Init()
{
	for (int e = 0;e < enemyNum; e++)
	{
		m_alive[e] = true;

		enemySize[e] = ENEMY_LARGE;

		enemyPos[e].x = 640 + rand() % 500;
		enemyPos[e].y = rand() % (690 + 1 - 64) - (360 - 32);
		enemyVel[e].x = -(rand() % 100) / 50.0f;
		enemyVel[e].y = (rand() % 200 - 100) / 50.0f;
	}


}

void DivisionEnemy::Update()
{
	for (int e = 0;e < enemyNum;e++)
	{
		if (m_alive[e])
		{
			enemyPos[e].x -= 3;

			enemyPos[e].x += enemyVel[e].x;
			enemyPos[e].y += enemyVel[e].y;

			//敵がした端まで到達したら再出現
			if (enemyPos[e].x < E_SCREENLEFT - 32)
			{
				enemyPos[e].x = E_SCREENRIGHT + 32;
				enemyPos[e].y = E_SCREENTOP + 32;
			}
			if (enemyPos[e].y < E_SCREENBOTTOM - 32)
			{
				enemyPos[e].y = E_SCREENTOP + 32;
			}
			if (enemyPos[e].y > E_SCREENTOP + 32)
			{
				enemyPos[e].y = E_SCREENBOTTOM - 32;
			}

		}
	}
	//%2の確率で敵を1体復活させる
	if ((rand() % 100 - 1) <= 2) {
		for (int e = 0;e < enemyNum;e++) {

			if (!m_alive[e]) {
				m_alive[e] = true;
				enemySize[e] = ENEMY_LARGE;
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
			scaleMat = Math::Matrix::CreateScale(1.2f, 1.2f, 1.0f);
		}
		if (enemySize[e] == ENEMY_SMALL)
		{
			scaleMat = Math::Matrix::CreateScale(0.9f, 0.9f, 1.0f);
		}
		transMat = Math::Matrix::CreateTranslation(enemyPos[e].x, enemyPos[e].y, 0);
		//合成 ・・・　かく　かい　い
		// 拡大　回転　移動
		enemyMat[e] = scaleMat * transMat;
	}
}

void DivisionEnemy::Draw()
{
	//敵
	for (int e = 0;e < enemyNum;e++)
	{
		if (!m_alive[e])continue;

		SHADER.m_spriteShader.SetMatrix(enemyMat[e]);
		SHADER.m_spriteShader.DrawTex(&enemyTex, Math::Rectangle{ 0,0,64,64 }, 1.0f);

	}
}

void DivisionEnemy::Split(int index)
{
	//小さい処理は爆散しない
	if (enemySize[index] == ENEMY_SMALL)
	{
		m_alive[index] = false;//小さいと消す
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

		enemyVel[i].x = -(rand() % 100) / 50.0f;
		enemyVel[i].y = (rand() % 200 - 100) / 50.0f;

		// ばらける方向　左右上下にずらす
		enemyPos[i].x += (count == 0 ? -20 : 20);
		enemyPos[i].y += (count == 0 ? -20 : 20);

		count++;

		//ここで数を数えている
		if (count >= 2) break;
	}
}
