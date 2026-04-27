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

	bool playerFlg;

	//追加処理?
	//Math::Vector2 playerPos = Math::Vector2::Zero;
	Math::Vector2 playerPos;

	//弾
	static const int  bulletNum = 100;
	bool bulletFlg[bulletNum];
	Math::Vector2 bulletPos[bulletNum];

private:

	const float m_moveSpeed = 5.0f;

	KdTexture playerTex;
	Math::Matrix playerMat;

	//弾

	KdTexture bulletTex;
	Math::Matrix bulletMat[bulletNum];

	int  shotWait;//発射待期時間
};
