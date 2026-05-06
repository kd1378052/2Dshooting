#pragma once

const int B_SCREEN_LEFT = -640;
const int B_SCREEN_TOP = 360;
const int B_SCREEN_RIGHT = 640;
const int B_SCREEN_BOTTOM = -360;

class Boss
{
public:
	Boss();
	~Boss();

	void Init();
	void Update();
	void Draw();


	Math::Vector2 bossPos;
	bool bossFlg; //生存フラグ
	int bossHP;

private:
	KdTexture bossTex;
	Math::Matrix bossMat;

};
