#pragma once
#include "../State.h"

class Player;
class Enemy;
class Particle;

class GameScreen : public State
{
public:
	GameScreen();
	~GameScreen();


	void Init()override;
	void Update()override;
	void Draw()override;

	float Rnd();

private:
	int hitscore;

	Player *m_player;
	Enemy* m_enemy;

	//パーティクル
	static const int explosionNum = 50;
	Particle* m_explosion[explosionNum];

	//背景
	Math::Matrix backMat1;
	Math::Matrix backMat2;
	KdTexture backTex;
	float backX;
};
