#include "Bullet.h"

Bullet::Bullet()
{
	bulletTex.Load("Texture/bullet.png");

}

Bullet::~Bullet()
{
	bulletTex.Release();
}

void Bullet::Init()
{
	shotWait = 0;

	//球の初期化
	for (int be = 0;be < bulletNum;be++) {
		bulletX[be] = 0;
		bulletY[be] = 0;
		bulletFlg[be] = 0;
	}
}

void Bullet::Update()
{
	if (shotWait == 0)
	{
		for (int bu = 0;bu < bulletNum;bu++)
		{
			if (bulletFlg[bu] == 0) {//未発射状態
				bulletFlg[bu] = 1;//発射状態にする
				bulletY[bu] = posY;
				bulletX[bu] = posX;

				//待機時間10フレーム
				shotWait = 10;
				break;//1発「発射状態」にしたので弾の繰り返しを抜ける
			}
		}
	}
	//}

	for (int bu = 0;bu < bulletNum;bu++)
	{
		//発射後の処理
		if (bulletFlg[bu] == 1)
		{
			bulletX[bu] += 15;

			//弾が画面外に出たら未発射状態に戻す
			if (bulletX[bu] > 1280 + 8)
			{
				bulletFlg[bu] = 0;
			}
		}
	}
	shotWait--;
	if (shotWait < 0)
	{
		shotWait = 0;
	}
	//球
	for (int bu = 0;bu < bulletNum;bu++) {
		bulletMat[bu] = Math::Matrix::CreateTranslation(bulletX[bu], bulletY[bu], 0);
	}
}

void Bullet::Draw()
{
	for (int bu = 0;bu < bulletNum;bu++) {
		if (bulletFlg[bu] == 1)
		{
			SHADER.m_spriteShader.SetMatrix(bulletMat[bu]);
			SHADER.m_spriteShader.DrawTex(&bulletTex, Math::Rectangle{ 0,0,16,16 }, 1.0f);
		}
	}
}

void Bullet::SetPlayerPos(float x, float y)
{
	posX = x;
	posY = y;	
}
