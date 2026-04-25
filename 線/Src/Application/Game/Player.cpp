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
	playerPos.x = -500;
	playerPos.y = 0;
	playerFlg = true;

	m_bullet = new Bullet();
	m_bullet->Init();
}

void Player::Update()
{
	m_bullet->SetPlayerPos(playerPos);
	if (playerFlg)
	{
		//プレイヤー動き
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)playerPos.x += m_moveSpeed;
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)playerPos.x -= m_moveSpeed;
		if (GetAsyncKeyState(VK_UP) & 0x8000)playerPos.y += m_moveSpeed;
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)playerPos.y -= m_moveSpeed;

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

		m_bullet->Flring();
	}
		m_bullet->Update();

	playerMat = Math::Matrix::CreateTranslation(playerPos.x, playerPos.y, 0);
	
	
}

void Player::Draw()
{
	if(playerFlg)
	{
		SHADER.m_spriteShader.SetMatrix(playerMat);
		SHADER.m_spriteShader.DrawTex(&playerTex, Math::Rectangle(64, 0, 64, 64), 1.0f);
	}
	
	m_bullet->Draw();

	
}
