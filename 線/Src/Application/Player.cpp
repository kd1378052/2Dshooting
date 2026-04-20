#include "Player.h"

Player::Player()
{
	playerTex.Load("Texture/player.png");
}

Player::~Player()
{
	playerTex.Release();
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

	}

	playerMat = Math::Matrix::CreateTranslation(playerX, playerY, 0);

}

void Player::Draw()
{
	SHADER.m_spriteShader.SetMatrix(playerMat);
	SHADER.m_spriteShader.DrawTex(&playerTex, Math::Rectangle(64, 0, 64, 64), 1.0f);
}
