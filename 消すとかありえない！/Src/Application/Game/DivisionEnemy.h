#pragma once

const int E_SCREENLEFT = -640;
const int E_SCREENTOP = 360;
const int E_SCREENRIGHT = 640;
const int E_SCREENBOTTOM = -360;

//敵のサイズ管理
enum EnemySize
{
	ENEMY_SMALL,
	ENEMY_LARGE
};

class DivisionEnemy
{
public:
	DivisionEnemy();
	~DivisionEnemy();

	void Init();
	void Update();
	void Draw();

	void Split(int index);

	static const int enemyNum = 5;	//敵の数（書き換え不可能）
	Math::Vector2 enemyPos[enemyNum];
	bool m_alive[enemyNum]; //敵の生存状態を管理
	EnemySize enemySize[enemyNum];

	Math::Vector2 enemyVel[enemyNum];


private:

	KdTexture enemyTex;
	Math::Matrix enemyMat[enemyNum];
	int retry;

};
