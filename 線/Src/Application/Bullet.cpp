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
}

void Bullet::Update()
{
	////待機時間が0の場合
	//if (shotWait == 0)
	//{
	//	for (int bu = 0;bu < bulletNum;bu++)
	//	{
	//		if (bulletFlg[bu] == 0) {//未発射状態
	//			bulletFlg[bu] = 1;//発射状態にする
	//			bulletX[bu] = playerX;
	//			bulletY[bu] = playerY;

	//			//待機時間10フレーム
	//			shotWait = 10;
	//			break;//1発「発射状態」にしたので弾の繰り返しを抜ける
	//		}
	//	}
	//}
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
