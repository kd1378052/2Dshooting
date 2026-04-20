#pragma once

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
	const float m_moveSpeed = 5.0f;

	KdTexture playerTex;
	Math::Matrix playermat;
};
