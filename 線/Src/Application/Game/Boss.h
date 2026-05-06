#pragma once

static const int screenLeft   =  -640;//左端
static const int screenTop	  =  360;//上端
static const int screenRight  =  640;//右端
static const int screenBottom =  -360;//下端
class Boss
{
public:
	Boss();
	~Boss();

	void Init();
	void Update();
	void Draw();


	Math::Vector2 bossPos;
	Math::Vector2 bossMove;
	bool bossFlg; //生存フラグ
	int bossHP;

private:
	KdTexture bossTex;
	Math::Matrix bossMat;
	int bossAppearance;


};
