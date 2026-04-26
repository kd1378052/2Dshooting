#include "GameScreen.h"
#include "../Game/Player.h"
#include "../Game/Enemy.h"

GameScreen::GameScreen()
{
	backTex.Load("Texture/back.png");
	m_player = new Player();
	m_enemy = new Enemy();
	
	m_player->Init();
	m_enemy->Init();

}

GameScreen::~GameScreen()
{
	backTex.Release();
	backX = 0;
	delete m_player;
	delete m_enemy;
}

void GameScreen::Init()
{
	
	m_player->Init();
	m_enemy->Init();
}

void GameScreen::Update()
{
	//背景スクロール
	backX -= 5;

	if (backX < -1280)
	{
		backX = 0;
	}
	//プレイヤーと弾を消す実験
	if (GetAsyncKeyState('U') & 0x8000)
	{
		m_player->playerFlg = false;
	}
	if (GetAsyncKeyState('I') & 0x8000)
	{
		m_player->playerFlg = true;
	}

	m_player->Update();

	m_enemy->Update();

	for (int e = 0;e < m_enemy->enemyNum;e++)
	{
		if (m_player->playerFlg && m_enemy->m_alive[e])
		{
			//自機との当たり判定
			float a = m_enemy->enemyPos[e].x - m_player->playerPos.x;//底辺(X座標の差)
			float b = m_enemy->enemyPos[e].y - m_player->playerPos.y;//高さ(Y座標の差)
			float c = sqrt(a * a + b * b);//斜辺（距離）

			if (c < 32 + 32)	//突撃していたら　(時機　半径×敵　半径)
			{
				//敵を倒す
				m_enemy->m_alive[e] = false;

				//時機を倒す処理
				m_player->playerFlg = false;

				//爆発
				//Explosion(playerX, playerY);
			}
		}
	}

	for (int bu = 0;bu < m_player->bulletNum;bu++)
	{
		//発射後の処理
		if (m_player->bulletFlg[bu] == true)
		{
			m_player->bulletPos[bu].x += 15.0f;

			//弾が画面外に出たら未発射状態に戻す
			if (m_player->bulletPos[bu].x > 1280 + 8)
			{
				m_player->bulletFlg[bu] = false;
			}
			//弾と敵の当たり判定
			for (int e = 0;e < m_enemy->enemyNum;e++) {


				if (m_enemy->m_alive[e])//敵が生きているか
				{
					float a = m_enemy->enemyPos[e].x - m_player->bulletPos[bu].x;//底辺(X座標の差)
					float b = m_enemy->enemyPos[e].y - m_player->bulletPos[bu].y;//高さ(Y座標の差)
					float c = sqrt(a * a + b * b);//斜辺（距離）
					//float dist2 = a * a + b * b;

					//if (c < 32 + 8)
					if (c < 25 + 8)//衝突していたら
					{
						m_enemy->m_alive[e] = false;
						m_player->bulletFlg[bu] = false;//弾を未発射にする

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

	//背景
	backMat1 = Math::Matrix::CreateTranslation(backX, 0, 0);
	backMat2 = Math::Matrix::CreateTranslation(backX + 1280, 0, 0);

}

void GameScreen::Draw()
{
	//背景 (一枚目)
	SHADER.m_spriteShader.SetMatrix(backMat1);
	SHADER.m_spriteShader.DrawTex(&backTex, Math::Rectangle{ 0,0,1280,720 }, 1.0f);

	//背景（二枚目）
	SHADER.m_spriteShader.SetMatrix(backMat2);
	SHADER.m_spriteShader.DrawTex(&backTex, Math::Rectangle{ 0,0,1280,720 }, 1.0f);

	m_player->Draw();
	m_enemy->Draw();

	// 文字列表示
	SHADER.m_spriteShader.DrawString(0, 0, "ゲーム画面", Math::Vector4(1, 1, 1, 1));

}