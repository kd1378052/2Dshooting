#include "Player.h"
#include "Bullet.h"

Player::Player()
{
	playerTex.Load("Texture/player.png");
	m_bullet = new Bullet();
	m_bullet->Init();
}

Player::~Player()
{
	delete m_bullet;
	playerTex.Release();

}

void Player::Init()
{
	playerX = -500;
	playerY = 0;
	m_bullet = new Bullet();
	m_bullet->Init();
}

void Player::Update()
{
	m_bullet->SetPlayerPos(playerX, playerY);

	//プレイヤー動き
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)playerX += m_moveSpeedX;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)playerX -= m_moveSpeedX;
	if (GetAsyncKeyState(VK_UP) & 0x8000)playerY += m_moveSpeedY;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)playerY -= m_moveSpeedY;

	//画面外に出ないようにする処理
	if (playerX > SCREEN_RIGHT - 35)
	{
		playerX = SCREEN_RIGHT - 35;
	}     //後で変える    ↑飛行機の半径
	if (playerX < SCREEN_LEFT + 35)
	{
		playerX = SCREEN_LEFT + 35;
	}
	if (playerY < SCREEN_BOTTOM + 35)
	{
		playerY = SCREEN_BOTTOM + 35;
	}
	if (playerY > SCREEN_TOP - 35)
	{
		playerY = SCREEN_TOP - 35;
	}
	  
	m_bullet->Update();

	playerMat = Math::Matrix::CreateTranslation(playerX, playerY, 0);
	
	
}

void Player::Draw()
{
	SHADER.m_spriteShader.SetMatrix(playerMat);
	SHADER.m_spriteShader.DrawTex(&playerTex, Math::Rectangle(64, 0, 64, 64), 1.0f);
	
	m_bullet->Draw();
}
