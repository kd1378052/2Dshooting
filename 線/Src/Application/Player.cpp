#include "Player.h"

Player::Player()
{
	playerTex.Load("Texture/player.png");
	//球
	bulletTex.Load("Texture/bullet.png");

}

Player::~Player()
{
	playerTex.Release();
	//球
	bulletTex.Release();

}

void Player::Init()
{
	playerX = 10;
	playerY = 10;
}

void Player::Update()
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)playerX += m_moveSpeed;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)playerX -= m_moveSpeed;
	if (GetAsyncKeyState(VK_UP) & 0x8000)playerY += m_moveSpeed;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)playerY -= m_moveSpeed;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		//待機時間が0の場合
		if (shotWait == 0)
		{
			for (int bu = 0;bu < bulletNum;bu++)
			{
				if (bulletFlg[bu] == 0) {//未発射状態
					bulletFlg[bu] = 1;//発射状態にする
					bulletX[bu] = playerX;
					bulletY[bu] = playerY;

					//待機時間10フレーム
					shotWait = 10;
					break;//1発「発射状態」にしたので弾の繰り返しを抜ける
				}
			}
		}
	}

	playerMat = Math::Matrix::CreateTranslation(playerX, playerY, 0);
	
	for (int bu = 0;bu < bulletNum;bu++) {
		bulletMat[bu] = Math::Matrix::CreateTranslation(bulletX[bu], bulletY[bu], 0);
	}
}

void Player::Draw()
{
	SHADER.m_spriteShader.SetMatrix(playerMat);
	SHADER.m_spriteShader.DrawTex(&playerTex, Math::Rectangle(64, 0, 64, 64), 1.0f);
	
	for (int bu = 0;bu < bulletNum;bu++) {
		if (bulletFlg[bu] == 1)
		{
			SHADER.m_spriteShader.SetMatrix(bulletMat[bu]);
			SHADER.m_spriteShader.DrawTex(&bulletTex, Math::Rectangle{ 0,0,16,16 }, 1.0f);
		}
	}
}
