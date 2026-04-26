#pragma once
#include "../State.h"

class Player;
class Enemy;
class Bullet;

class GameScreen : public State
{
public:
	GameScreen();
	~GameScreen();


	void Init()override;
	void Update()override;
	void Draw()override;

private:

	Player *m_player;
	Enemy* m_enemy;
	Bullet* m_bullet;

	//背景
	Math::Matrix backMat1;
	Math::Matrix backMat2;
	KdTexture backTex;
	float backX;
};
