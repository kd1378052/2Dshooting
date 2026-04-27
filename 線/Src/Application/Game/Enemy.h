#pragma once

class Bullet;

class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init();
	void Update();
	void Draw();

	void AvoidanceEnemy();

	static const int enemyNum = 10;	//敵の数（書き換え不可能）
	Math::Vector2 enemyPos[enemyNum];
	bool m_alive[enemyNum]; //敵の生存状態を管理

private:
	KdTexture enemyTex;
	Math::Matrix enemyMat[enemyNum];
	int retry;
};