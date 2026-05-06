#pragma once

const int E_SCREEN_LEFT = -640;
const int E_SCREEN_TOP = 360;
const int E_SCREEN_RIGHT = 640;
const int E_SCREEN_BOTTOM = -360;

class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init();
	void Update();
	void Draw();

	static const int enemyNum = 10;	//敵の数（書き換え不可能）
	Math::Vector2 enemyPos[enemyNum];
	bool alive[enemyNum]; //敵の生存状態を管理


private:
	KdTexture enemyTex;
	Math::Matrix enemyMat[enemyNum];

};