#pragma once

class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init();
	void Update();
	void Draw();
private:
	//敵
	static const int enemyNum = 8;	//敵の数（書き換え不可能）
	
	KdTexture enemyTex;
	Math::Matrix enemyMat[enemyNum];
	float enemyX[enemyNum];
	float enemyY[enemyNum];
	int enemyFlg[enemyNum]; //敵の生存状態を管理(0 死亡,１ 生存)

};