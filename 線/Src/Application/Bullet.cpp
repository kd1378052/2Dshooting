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
}

void Bullet::Draw()
{
	for (int bu = 0;bu < bulletNum;bu++) {
		if (bulletFlg[bu] == 1)//このフラグなに？
		{
			SHADER.m_spriteShader.SetMatrix(bulletMat[bu]);
			SHADER.m_spriteShader.DrawTex(&bulletTex, Math::Rectangle{ 0,0,16,16 }, 1.0f);
		}
	}
}
