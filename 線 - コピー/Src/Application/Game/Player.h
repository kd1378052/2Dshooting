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

	bool playerFlg;
	Math::Vector2 playerPos;

	Bullet* GetBullet() { return m_bullet; }
	Bullet* m_bullet;

private:

	const float m_moveSpeed = 5.0f;

	KdTexture playerTex;
	Math::Matrix playerMat;

	
};
