#include "Bullet.h"
#include "Enemy.h"

Bullet::Bullet()
{
	bulletTex.Load("Texture/bullet.png");
}

Bullet::~Bullet()
{
	bulletTex.Release();
	delete m_enemy;
}

void Bullet::Init()
{
	m_enemy = new Enemy();
	m_enemy->Init();
	shotWait = 0.0f;

	//球の初期化
	for (int be = 0;be < bulletNum;be++) {
		bulletPos[be].x = 0.0f;
		bulletPos[be].y = 0.0f;
		bulletFlg[be] = false;
	}
}

void Bullet::Update()
{
	m_enemy->Update();


	for (int bu = 0;bu < bulletNum;bu++)
	{
		//発射後の処理
		if (bulletFlg[bu] == true)
		{
			bulletPos[bu].x += 15.0f;

			//弾が画面外に出たら未発射状態に戻す
			if (bulletPos[bu].x > 1280 + 8)
			{
				bulletFlg[bu] = false;
			}
			//弾と敵の当たり判定
			for (int e = 0;e < m_enemy->enemyNum;e++) {


				if (m_enemy->m_alive[e])//敵が生きているか
				{
					float a = m_enemy->enemyPos[e].x - bulletPos[bu].x;//底辺(X座標の差)
					float b = m_enemy->enemyPos[e].y - bulletPos[bu].y;//高さ(Y座標の差)
					float c = sqrt(a * a + b * b);//斜辺（距離）
					//float dist2 = a * a + b * b;

					//if (dist2 < (32 + 8) * (32 + 8))
					if (c < 32 + 8)//衝突していたら
					{
						m_enemy->m_alive[e] = false;
						bulletFlg[bu] = false;//弾を未発射にする

						//スコア加算
						//score += 100;

						//爆発発生！ 追加処理
						//Explosion(enemyX[e], enemyY[e]);

						break;//弾が未発射になったので敵の繰り返しを抜ける

					}
				}
			}
		}
	}
	shotWait--;
	if (shotWait < 0.0f)
	{
		shotWait = 0.0f;
	}
	//球
	for (int bu = 0;bu < bulletNum;bu++) {
		bulletMat[bu] = Math::Matrix::CreateTranslation(bulletPos[bu].x, bulletPos[bu].y, 0);
	}
}

void Bullet::Draw()
{
	m_enemy->Draw();

	for (int bu = 0.0f;bu < bulletNum;bu++) {
		if (bulletFlg[bu] == 1)
		{
			SHADER.m_spriteShader.SetMatrix(bulletMat[bu]);
			SHADER.m_spriteShader.DrawTex(&bulletTex, Math::Rectangle{ 0,0,16,16 }, 1.0f);
		}
	}

}

void Bullet::Flring()
{
	if (shotWait == 0.0f)
	{
		for (int bu = 0.0f;bu < bulletNum;bu++)
		{
			if (bulletFlg[bu] == false) {//未発射状態
				bulletFlg[bu] = true;//発射状態にする
				bulletPos[bu].y = m_Pos.y;
				bulletPos[bu].x = m_Pos.x;

				//待機時間10フレーム
				shotWait = 10;
				break;//1発「発射状態」にしたので弾の繰り返しを抜ける
			}
		}
	}
}

void Bullet::SetPlayerPos(Math::Vector2 pos)
{
	m_Pos = pos;
}
