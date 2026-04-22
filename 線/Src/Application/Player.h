#pragma once

const int SCREEN_LEFT = -640;
const int SCREEN_TOP = 360;
const int SCREEN_RIGHT = 640;
const int SCREEN_BOTTOM = -360;

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
	Math::Matrix playerMat;

	//球
	static const int  bulletNum = 100;

	KdTexture bulletTex;
	Math::Matrix bulletMat[bulletNum];
	float bulletX[bulletNum];
	float bulletY[bulletNum];
	int bulletFlg[bulletNum];

	int  shotWait;//発射待期時間
};
