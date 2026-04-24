#pragma once

const int SCREEN_LEFT = -640;
const int SCREEN_TOP = 360;
const int SCREEN_RIGHT = 640;
const int SCREEN_BOTTOM = -360;

class Bullet;

class Player
{
public:
	Player();
	~Player();

	void Init();
	void Update();
	void Draw();

private:

	float playerX;
	float playerY;
	const float m_moveSpeedY = 5.0f;
	const float m_moveSpeedX = 5.0f;

	KdTexture playerTex;
	Math::Matrix playerMat;

	Bullet *m_bullet;
	
};
