#pragma once

const int E_SCREEN_LEFT = -640;
const int E_SCREEN_TOP = 360;
const int E_SCREEN_RIGHT = 640;
const int E_SCREEN_BOTTOM = -360;

class Bullet;

//敵のサイズ管理
enum EnemySize
{
	ENEMY_SMALL,
	ENEMY_LARGE
};

class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init();
	void Update();
	void Draw();

	void AvoidanceEnemy();

	void Split(int index);

	static const int enemyNum = 10;	//敵の数（書き換え不可能）
	Math::Vector2 enemyPos[enemyNum];
	bool m_alive[enemyNum]; //敵の生存状態を管理

	Math::Vector2 enemyVel[enemyNum];

private:
	EnemySize enemySize[enemyNum];


	KdTexture enemyTex;
	Math::Matrix enemyMat[enemyNum];
	int retry;

};