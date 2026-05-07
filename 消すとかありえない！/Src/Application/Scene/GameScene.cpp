#include "GameScene.h"
#include "../Game/Player.h"
#include "../Game/Enemy.h"
#include "../Game/Particle.h"
#include "../Game/Score.h"
#include"../Game/Boss.h"
#include"../Game/DivisionEnemy.h"
#include "../SceneManager.h"



GameScene::GameScene()
{
	backTex.Load("Texture/Game/back.png");
	numbersTex.Load("Texture/Game/numbers.png");

	m_player = new Player();
	m_player->Init();
	m_enemy = new Enemy();
	m_enemy->Init();
	m_Denemy = new DivisionEnemy();
	m_Denemy->Init();
	m_boss = new Boss();
	m_boss->Init();
	

	m_score = new Score();
	m_score->Reset();

	for (int i = 0; i < explosionNum; i++)
	{
		m_explosion[i] = new Particle();
		m_explosion[i]->Init();
	}

	hitscore = 0.0f;
	bossscore = 0.0f;
}

GameScene::~GameScene()
{
	numbersTex.Release();
	backTex.Release();

	backX = 0;
	for (int i = 0; i < explosionNum; i++)
	{
		delete m_explosion[i];
	}
	
	delete m_player;
	delete m_enemy;
	delete m_boss;
	delete m_Denemy;


}

void GameScene::Init()
{
	hitscore = 0.0f;
	bossscore = 0.0f;

	m_player->Init();
	m_enemy->Init();
	m_boss->Init();
	m_Denemy->Init();

	m_score->Reset();

	for (int i = 0; i < explosionNum; i++)
	{
		m_explosion[i]->Init();
	}

}

void GameScene::Update()
{
	//実験
	if ( GetAsyncKeyState('T') & 0x8000) m_boss->bossHP -= 10;
	//背景スクロール
	backX -= 5;

	if (backX < -1280)
	{
		backX = 0;
	}
	m_player->Update();
	m_enemy->Update();
	m_Denemy->Update();

	if (bossscore >=1000)
	{
		for (int e = 0;e < m_enemy->enemyNum; ++e)
		{
			m_enemy->alive[e] = false;
			m_Denemy->m_alive[e] = false;
		}
		
		m_boss->effectFlg = true;
		m_boss->Update();
		
	}

	
	//弾当たり判定
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
			//弾と敵の当たり判定 ノーマル敵
			for (int e = 0;e < m_enemy->enemyNum;e++)
			{
				if (m_enemy->alive[e])//敵が生きているか
				{
					float a = m_enemy->enemyPos[e].x - m_player->bulletPos[bu].x;//底辺(X座標の差)
					float b = m_enemy->enemyPos[e].y - m_player->bulletPos[bu].y;//高さ(Y座標の差)
					float c = sqrt(a * a + b * b);//斜辺（距離）

					//(c < 32 + 10)
					if (c < 25 + 8)//衝突していたら
					{
						m_enemy->alive[e] = false;
						m_player->bulletFlg[bu] = false;//弾を未発射にする

						//スコア加算
						hitscore += 50;
						bossscore += 50;

						//爆発発生
						for (int i = 0; i < explosionNum; i++)
						{
							m_explosion[i]->Emit(
								{ m_enemy->enemyPos[e].x,m_enemy->enemyPos[e].y },//座標
								{ Rnd() * 6 - 3,Rnd() * 6 - 3 },//移動量
								Rnd() * 5 - 1,//サイズ 3 +2→2~5
								{ 1,1,1.1 },//色
								1000,//有効期限
								false);//繰り返しフラグ
						}

						break;//弾が未発射になったので敵の繰り返しを抜ける
						//ループを抜ける　そのあとの処理は続く
					}
				}
			}

			//弾と敵の当たり判定 分裂敵
			for (int e = 0;e < m_Denemy->enemyNum;e++) {

				if (m_Denemy->m_alive[e])//敵が生きているか
				{
					float a = m_Denemy->enemyPos[e].x - m_player->bulletPos[bu].x;//底辺(X座標の差)
					float b = m_Denemy->enemyPos[e].y - m_player->bulletPos[bu].y;//高さ(Y座標の差)
					float c = sqrt(a * a + b * b);//斜辺（距離）

					if (m_Denemy->enemySize[e] == ENEMY_LARGE)
					{
						if (c < 32 + 8)//衝突していたら 敵と弾の半径
						{
							//m_enemy->m_alive[e] = false;
							m_Denemy->Split(e);

							m_player->bulletFlg[bu] = false;//弾を未発射にする
							//スコア加算
							hitscore += 40;

							//爆発発生
							for (int i = 0; i < explosionNum; i++)
							{
								m_explosion[i]->Emit(
									{ m_Denemy->enemyPos[e].x,m_Denemy->enemyPos[e].y },//座標
									{ Rnd() * 6 - 3,Rnd() * 6 - 3 },//移動量
									Rnd() * 5 - 1,//サイズ 3 +2→2~5
									{ 1,1,1.1 },//色
									1000,//有効期限
									false);//繰り返しフラグ
							}
							break;//弾が未発射になったので敵の繰り返しを抜ける
						}
					}
					if (m_Denemy->enemySize[e] == ENEMY_SMALL)
					{
						if (c < 14 + 8)//衝突していたら
						{
							m_Denemy->m_alive[e] = false;

							m_player->bulletFlg[bu] = false;//弾を未発射にする


							//スコア加算
							hitscore += 60;

							//爆発発生
							for (int i = 0; i < explosionNum; i++)
							{
								m_explosion[i]->Emit(
									{ m_Denemy->enemyPos[e].x,m_Denemy->enemyPos[e].y },//座標
									{ Rnd() * 6 - 3,Rnd() * 6 - 3 },//移動量
									Rnd() * 5 - 1,//サイズ 3 +2→2~5
									{ 1,1,1.1 },//色
									1000,//有効期限
									false);//繰り返しフラグ
							}
							break;//弾が未発射になったので敵の繰り返しを抜ける
							//ループを抜ける　そのあとの処理は続く
						}
					}
				}
			}

			//弾当たり判定　ボス
			if (m_boss->bossFlg == true) {
				//距離判定
				float a = m_boss->bossPos.x - m_player->bulletPos[bu].x;
				float b = m_boss->bossPos.y - m_player->bulletPos[bu].y;
				float c = sqrt(a * a + b * b);

				if (c < 8 + 50) {

					m_boss->bossHP -= 5;
					//弾の座標に爆発
					//爆発発生
					for (int i = 0; i < explosionNum; i++)
					{
						m_explosion[i]->Emit(
							{ m_boss->bossPos.x,m_boss->bossPos.y },//座標
							{ Rnd() * 6 - 3,Rnd() * 6 - 3 },//移動量
							Rnd() * 5 - 1,//サイズ 3 +2→2~5
							{ 1,1,1.1 },//色
							1000,//有効期限
							false);//繰り返しフラグ
					}
					//弾を未発射
					m_player->bulletFlg[bu] = false;
				}

				if (m_boss->bossHP <= 0) {
					//ボスを倒す
					m_boss->bossFlg = false;
					//ボスの座標に爆発
					
					//追加処理
					for (int i = 0; i < explosionNum; i++)
					{
						m_explosion[i]->Emit(
							{ m_boss->bossPos.x,m_boss->bossPos.y },//座標
							{ Rnd() * 6 - 3,Rnd() * 6 - 3 },//移動量
							Rnd() * 5 - 1,//サイズ 3 +2→2~5
							{ 1,1,1.1 },//色
							1000,//有効期限
							false);//繰り返しフラグ
					}
					//スコア加算
					hitscore += 1000;
					bossscore = 0.0f;

					break;
				}
			}

		}
	}
	if (bossscore == 0.0f)
	{
		m_boss->Init();
	}

	
	//自機とノーマル敵の当たり判定
	for (int e = 0;e < m_enemy->enemyNum;e++)
	{
		if (m_player->playerFlg && m_enemy->alive[e])
		{
			//自機との当たり判定
			float a = m_enemy->enemyPos[e].x - m_player->playerPos.x;//底辺(X座標の差)
			float b = m_enemy->enemyPos[e].y - m_player->playerPos.y;//高さ(Y座標の差)
			float c = sqrt(a * a + b * b);//斜辺（距離）

			if (c < 32 + 32)	//突撃していたら　(自機　半径 35 ×敵　半径)
			{
				//敵を倒す
				m_enemy->alive[e] = false;

				//自機を倒す処理
				m_player->playerFlg = false;
				for (int be = 0;be < m_player->bulletNum;be++) {
					
					m_player->bulletFlg[be] = false;
				}

				m_score->SetScore(hitscore);
				m_score->Save();
				m_score->NowSave();
				//リザルト移動
				SCENEMANAGER.ChangState(new ResultScreen());
				
				return;
				//関数を抜ける　（これ以降の処理は行わない）
			}
		}
	}
	//自機と分裂敵の当たり判定
	for (int e = 0;e < m_Denemy->enemyNum;e++)
	{
		if (m_player->playerFlg && m_Denemy->m_alive[e])
		{
			//自機との当たり判定
			float a = m_Denemy->enemyPos[e].x - m_player->playerPos.x;//底辺(X座標の差)
			float b = m_Denemy->enemyPos[e].y - m_player->playerPos.y;//高さ(Y座標の差)
			float c = sqrt(a * a + b * b);//斜辺（距離）

			if (c < 32 + 32)	//突撃していたら　(時機　半径×敵　半径)
			{
				//敵を倒す
				m_Denemy->m_alive[e] = false;


				//時機を倒す処理
				m_player->playerFlg = false;

				//リザルト移動
				SCENEMANAGER.ChangState(new ResultScreen());
				return;

			}
		}
	}

	//ボスと時機の当たり判定
	if (m_player->playerFlg && m_boss->bossFlg)
	{
		//自機との当たり判定
		float a = m_boss->bossPos.x - m_player->playerPos.x;//底辺(X座標の差)
		float b = m_boss->bossPos.y - m_player->playerPos.y;//高さ(Y座標の差)
		float c = sqrt(a * a + b * b);//斜辺（距離）

		if (c < 32 + 52)	//突撃していたら　(自機　半径 35 ×敵　半径)
		{
			//敵を倒す
			m_boss->bossFlg = false;

			//自機を倒す処理
			m_player->playerFlg = false;
			for (int be = 0;be < m_player->bulletNum;be++) {

				m_player->bulletFlg[be] = false;
			}

			m_score->SetScore(hitscore);
			m_score->Save();
			//リザルト移動
			SCENEMANAGER.ChangState(new ResultScreen());

			return;
			//関数を抜ける　（これ以降の処理は行わない）
		}
	}
	
	//追加処理
	if (GetAsyncKeyState(VK_TAB) & 0x8000)
	{

	}

	unsigned long tep = hitscore;

	for (int i = maxDigits - 1; i >= 0; --i)
	{
		//下位の桁から抽出し、配列に格納
		m_digits[i] = tep % 10;
		tep /= 10;
	}

	//背景
	backMat1 = Math::Matrix::CreateTranslation(backX, 0, 0);
	backMat2 = Math::Matrix::CreateTranslation(backX + 1280, 0, 0);

	
	for (int i = 0; i < explosionNum; i++)
	{
		m_explosion[i]->Update(Math::Vector2::Zero);
	}
}

void GameScene::Draw()
{
	//背景 (一枚目)
	SHADER.m_spriteShader.SetMatrix(backMat1);
	SHADER.m_spriteShader.DrawTex(&backTex, Math::Rectangle{ 0,0,1280,720 }, 1.0f);

	//背景（二枚目）
	SHADER.m_spriteShader.SetMatrix(backMat2);
	SHADER.m_spriteShader.DrawTex(&backTex, Math::Rectangle{ 0,0,1280,720 }, 1.0f);
	//スコア表示

	for (int i = 0; i < maxDigits; ++i)
	{
		Math::Rectangle rc = { 45 * m_digits[i],0,45,70 };

		float posX = -610;
		float posY = 310;

		SHADER.m_spriteShader.SetMatrix(numbersMat);
		SHADER.m_spriteShader.DrawTex(&numbersTex,
			posX + (i * 30)//ｘ
			, posY + 0,//ｙ
			30, //幅
			55,//高さ
			&rc);
	}
	

	m_player->Draw();
	m_enemy->Draw();
	m_Denemy->Draw();
	m_boss->Draw();
	//パーティクル
	for (int i = 0; i < explosionNum; i++)
	{
		m_explosion[i]->Draw();
	}

}

float GameScene::Rnd()
{
	return rand() / (float)RAND_MAX;
}

