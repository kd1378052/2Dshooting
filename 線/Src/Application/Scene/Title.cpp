#include "Title.h"
#include "../SceneManager.h"


Title::Title()
{
	TitlebackTex.Load("Texture/Title/titleback.png");
	TitleTex.Load("Texture/Title/titlelogo.png");
	T_playerTex.Load("Texture/Title/titleplayer.png");
	T_bossTex.Load("Texture/Title/titleboss.png");
	startTex.Load("Texture/Title/startbutton.png");
	titlecount = 0.0f;
	T_playercount = 0.0f;
	T_bosscount = 0.0f;
	startalpha = 0.0f;
	startalphaAdd = 0.01f;
}

Title::~Title()
{
	startTex.Release();
	T_bossTex.Release();
	T_playerTex.Release();
	TitleTex.Release();
	TitlebackTex.Release();
	TitlebackX = 0.0f;
}

void Title::Init()
{
	titlecount = 0.0f;
	T_playercount = 0.0f;
	T_bosscount = 0.0f;
	startalpha = 1.0f;
	startalphaAdd = -0.01f;
}

void Title::Update()
{
	//タイトルアニメーションの繰り返し
	titlecount += 0.1f;
	if (titlecount >= 6)//6枚の画像を順番に表示する
	{
		titlecount = 0;
	}
	//プレイヤー
	T_playercount += 0.1f;
	if (T_playercount >= 2)//画像を順番に表示する
	{
		T_playercount = 0;
	}
	//エネミー
	T_bosscount += 0.1f;
	if (T_bosscount >= 2)//画像を順番に表示する
	{
		T_bosscount = 0;
	}
	//背景
	TitlebackX -= 5;
	if (TitlebackX < -1280)
	{
		TitlebackX = 0;
	}
	//スタートボタン
	//ここで不透明度いじる
	startalpha += startalphaAdd;

	if (startalpha < 0.5f)
	{
		startalpha = 0.5f;
		startalphaAdd *= -1;

	}
	else if (startalpha > 1.0f)
	{
		startalpha = 1.0f;
		startalphaAdd *= -1;
	}

	//背景
	TitlebackMat1 = Math::Matrix::CreateTranslation(TitlebackX, 0, 0);
	TitlebackMat2 = Math::Matrix::CreateTranslation(TitlebackX + 1280, 0, 0);

	//タイトルロゴ
	TitleMat = Math::Matrix::CreateTranslation(0, 200, 0);
	//プレイヤー
	T_playerMat = Math::Matrix::CreateTranslation(100, -50, 0);
	//エネミー
	T_bossMat = Math::Matrix::CreateTranslation(-100, -50, 0);
	//スタートボタン
	startMat = Math::Matrix::CreateTranslation(0, -250, 0);

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		SCENEMANAGER.ChangState(new GameScene());
	}

}

void Title::Draw()
{
	//背景 (一枚目)
	SHADER.m_spriteShader.SetMatrix(TitlebackMat1);
	SHADER.m_spriteShader.DrawTex(&TitlebackTex, Math::Rectangle{ 0,0,1280,720 }, 1.0f);
	//背景（二枚目）
	SHADER.m_spriteShader.SetMatrix(TitlebackMat2);
	SHADER.m_spriteShader.DrawTex(&TitlebackTex, Math::Rectangle{ 0,0,1280,720 }, 1.0f);

	//タイトルロゴ
	SHADER.m_spriteShader.SetMatrix(TitleMat);
	SHADER.m_spriteShader.DrawTex(&TitleTex, Math::Rectangle{ (int)titlecount * 750,0,750,350 }, 1.0f);
	//プレイヤー
	SHADER.m_spriteShader.SetMatrix(T_playerMat);
	SHADER.m_spriteShader.DrawTex(&T_playerTex, Math::Rectangle{ (int)T_playercount * 90,0,90,90 }, 1.0f);
	//エネミー
	SHADER.m_spriteShader.SetMatrix(T_bossMat);
	SHADER.m_spriteShader.DrawTex(&T_bossTex, Math::Rectangle{ (int)T_bosscount * 210,0,210,210 }, 1.0f);
	//スタートボタン
	SHADER.m_spriteShader.SetMatrix(startMat);
	SHADER.m_spriteShader.DrawTex(&startTex, Math::Rectangle{ 0,0,400,200 }, startalpha);

}
