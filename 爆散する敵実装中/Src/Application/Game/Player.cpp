#include "Player.h"

Player::Player()
{
	playerTex.Load("Texture/player.png");
	bulletTex.Load("Texture/bullet.png");

}

Player::~Player()
{
	playerTex.Release();
	bulletTex.Release();
		
}

void Player::Init()
{
	playerPos.x = -500;
	playerPos.y = 0;
	playerFlg = true;

	shotWait = 0.0f;
	//球の初期化
	for (int be = 0;be < bulletNum;be++) {
		bulletPos[be].x = 0.0f;
		bulletPos[be].y = 0.0f;
		bulletFlg[be] = false;
	}
}

void Player::Update()
{
	if (playerFlg)
	{
		Math::Vector2 dir = Math::Vector2::Zero;

		// 入力
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState('D') & 0x8000) dir.x += 1;
		if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState('A') & 0x8000) dir.x -= 1;
		if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState('W') & 0x8000) dir.y += 1;
		if (GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState('S') & 0x8000) dir.y -= 1;

		// 斜め速度調整
		if (dir.Length() != 0)
		{
			dir.Normalize();
			playerPos += dir * m_moveSpeed;
		}
		

		//画面外に出ないようにする処理
		if (playerPos.x > SCREEN_RIGHT - 35)
		{
			playerPos.x = SCREEN_RIGHT - 35;
		}     //後で変える    ↑飛行機の半径
		if (playerPos.x < SCREEN_LEFT + 35)
		{
			playerPos.x = SCREEN_LEFT + 35;
		}
		if (playerPos.y < SCREEN_BOTTOM + 35)
		{
			playerPos.y = SCREEN_BOTTOM + 35;
		}
		if (playerPos.y > SCREEN_TOP - 35)
		{
			playerPos.y = SCREEN_TOP - 35;
		}

		if (shotWait == 0.0f)
		{
			for (int bu = 0;bu < bulletNum;bu++)
			{
				if (!bulletFlg[bu]) {//未発射状態
					bulletFlg[bu] = true;//発射状態にする
					bulletPos[bu].y = playerPos.y;
					bulletPos[bu].x = playerPos.x;

					//待機時間7フレーム
					shotWait = 7;
					break;//1発「発射状態」にしたので弾の繰り返しを抜ける
				}
			}
		}
	}
	shotWait--;
	if (shotWait < 0.0f)
	{
		shotWait = 0.0f;
	}
	for (int bu = 0;bu < bulletNum;bu++) {
		bulletMat[bu] = Math::Matrix::CreateTranslation(bulletPos[bu].x, bulletPos[bu].y, 0);
	}

	playerMat = Math::Matrix::CreateTranslation(playerPos.x, playerPos.y, 0);
	
	
}

void Player::Draw()
{
	if(playerFlg)
	{
		SHADER.m_spriteShader.SetMatrix(playerMat);
		SHADER.m_spriteShader.DrawTex(&playerTex, Math::Rectangle(64, 0, 64, 64), 1.0f);
	}
	for (int bu = 0.0f;bu < bulletNum;bu++) {
		if (bulletFlg[bu] == 1)
		{
			SHADER.m_spriteShader.SetMatrix(bulletMat[bu]);
			SHADER.m_spriteShader.DrawTex(&bulletTex, Math::Rectangle{ 0,0,16,16 }, 1.0f);
		}
	}
	
}
