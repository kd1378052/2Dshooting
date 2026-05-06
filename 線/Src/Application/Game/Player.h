#pragma once

static const int SCREEN_LEFT = -640;
static const int SCREEN_TOP = 360;
static const int SCREEN_RIGHT = 640;
static const int SCREEN_BOTTOM = -360;

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


	//弾
	static const int  bulletNum = 100;
	bool bulletFlg[bulletNum];
	Math::Vector2 bulletPos[bulletNum];

private:

	const float m_moveSpeed = 5.0f;

	KdTexture playerTex;
	Math::Matrix playerMat;

	float animecount;

	//弾

	KdTexture bulletTex;
	Math::Matrix bulletMat[bulletNum];

	int  shotWait;//発射待期時間
};
