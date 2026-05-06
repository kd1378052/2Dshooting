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
	bool effectFlg; //エフェク
	int bossAppearance;

private:
	KdTexture bossTex;
	Math::Matrix bossMat;

	Math::Matrix effectMat;
	KdTexture effectTex;
	float m_alpha;
	float m_alphaAdd;

};
