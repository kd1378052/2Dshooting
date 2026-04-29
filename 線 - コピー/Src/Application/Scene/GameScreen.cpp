#include "GameScreen.h"
#include "../Game/Player.h"
#include "../Game/Enemy.h"
#include "../Game/Particle.h"
#include "../SceneManager.h"



GameScreen::GameScreen()
{
	backTex.Load("Texture/back.png");
	m_player = new Player();
	m_enemy = new Enemy();
	for (int i = 0; i < explosionNum; i++)
	{
		m_explosion[i] = new Particle();
	}
	m_player->Init();
	m_enemy->Init();
	for (int i = 0; i < explosionNum; i++)
	{
		m_explosion[i]->Init();
	}

	hitscore = 0.0f;

}

GameScreen::~GameScreen()
{
	backTex.Release();
	backX = 0;
	for (int i = 0; i < explosionNum; i++)
	{
		delete m_explosion[i];
	}
	delete m_enemy;
	m_enemy = nullptr;
	delete m_player;
	m_player = nullptr;
}

void GameScreen::Init()
{
	hitscore = 0.0f;

	m_player->Init();
	m_enemy->Init();
	for (int i = 0; i < explosionNum; i++)
	{
		m_explosion[i]->Init();
	}

}

void GameScreen::Update()
{
	//背景スクロール
	backX -= 5;

	if (backX < -1280)
	{
		backX = 0;
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

				//リザルト移動
				//SCENEMANAGER.ChangState(new ResultScreen());


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
					if (c < 20 + 8)//衝突していたら
					{
						m_enemy->m_alive[e] = false;
						m_player->bulletFlg[bu] = false;//弾を未発射にする


						//スコア加算
						hitscore += 50;

						//爆発発生
						for (int i = 0; i < explosionNum; i++)
						{
							m_explosion[i]->Emit(
								{ m_enemy->enemyPos[e].x,m_enemy->enemyPos[e].y },//座標
								{ Rnd() * 6 - 3,Rnd() * 6 - 3 },//移動量
								//Rnd() * 10 - 5,//サイズ 3 +2→2~5
								Rnd() * 5 - 1,//サイズ 3 +2→2~5
								{ 1,1,1.1 },//色
								1000,//有効期限
								false);//繰り返しフラグ
						}

						break;//弾が未発射になったので敵の繰り返しを抜ける

					}
				}
			}
		}
	}

	

	
	//背景
	backMat1 = Math::Matrix::CreateTranslation(backX, 0, 0);
	backMat2 = Math::Matrix::CreateTranslation(backX + 1280, 0, 0);
	
	// パーティクル更新：元コードはプレイヤーの弾数 (bulletNum=100) を使って
	// m_enemy->enemyPos[bu] を参照していたため、敵配列の範囲 (0..9) を超えるアクセスが発生していました。
	// ここでは各パーティクルを一度だけ更新するように修正します。
	for (int i = 0; i < explosionNum; i++)
	{
		// Particle::Update は Math::Vector2 を受け取るため安全な値を渡します。
		// 必要に応じて適切な座標（例: プレイヤー座標や敵座標）に変更してください。
		m_explosion[i]->Update(Math::Vector2::Zero);
	}
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
	//パーティクル
	for (int i = 0; i < explosionNum; i++)
	{
		m_explosion[i]->Draw();
	}


char text[1000];//1文字列格納用sの配列作成
sprintf_s(text, sizeof(text), "すこあ：%d", hitscore);
SHADER.m_spriteShader.DrawString(-620, 350, text, Math::Vector4(0, 0, 0, 1));
	
}

float GameScreen::Rnd()
{
	return rand() / (float)RAND_MAX;
}
