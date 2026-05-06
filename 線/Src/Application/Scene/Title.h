#pragma once
#include "../State.h"

class Title : public State
{
public:
	Title();
	~Title();

	void Init()override;
	void Update()override;
	void Draw()override;

private:
	//背景
	Math::Matrix TitlebackMat1;
	Math::Matrix TitlebackMat2;
	KdTexture TitlebackTex;
	float TitlebackX;

	//タイトルロゴ
	Math::Matrix TitleMat;
	KdTexture TitleTex;
	float titlecount;

	//タイトルプレイヤー
	Math::Matrix T_playerMat;
	KdTexture T_playerTex;
	float T_playercount;

	//タイトルボス
	Math::Matrix T_bossMat;
	KdTexture T_bossTex;
	float T_bosscount;

	//スタートボタン
	Math::Matrix startMat;
	KdTexture startTex;
	float startalpha;
	float startalphaAdd;
};
