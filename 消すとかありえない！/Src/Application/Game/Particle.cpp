#include "Particle.h"

Particle::Particle()
{
	particleTex.Load("Texture/Game/explosion.png");
}

Particle::~Particle()
{
	particleTex.Release();
}

void Particle::Init()
{
	m_size = 0.0f;
	m_color = 0.0f;
	m_lifespan = 0.0f;
}

void Particle::Update(Math::Vector2 a_Pos)
{
	m_lifespan--;
	if (m_lifespan <= 0)
	{
		if (!m_bRepeat)return;	//リピートなしの場合は戻る

		//パーティクル発生させる
		Emit(
			{ a_Pos.x,a_Pos.y - 30 },
			{ Rnd() * 10 - 5,Rnd() },//移動量
			Rnd() * 5 - 2.5,//サイズ 3 +2→2~5
			{ 1,1,1,0 },//色
			Rnd() * 90 + 10,//有効期限
			true);//繰り返しフラグ
	}

	//座標更新
	m_pos += m_move;

	//サイズ作成
	m_size *= 0.95f;//徐々に小さく
	//m_size *= 1.2f;//徐々に大きく

	

	//行列作成
	Math::Matrix transMat, scaleMat;
	scaleMat = Math::Matrix::CreateScale(m_size, m_size, 0);
	transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);

	//合成 ・・・　かく　かい　い
	// 拡大　回転　移動
	m_matrix = scaleMat * transMat;

}

void Particle::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_matrix);

	Math::Rectangle srcRect = { 0,0,4,4 };
	SHADER.m_spriteShader.DrawTex(&particleTex, 0, 0, &srcRect, &m_color);

	
}

float Particle::Rnd()
{
	return rand() / (float)RAND_MAX;
}

void Particle::Emit(Math::Vector2 a_pos, Math::Vector2 a_move, float a_size, Math::Color a_color, int a_lifespan, bool a_bRepeat)
{
	m_pos = a_pos;
	m_move = a_move;
	m_size = a_size;
	m_color = a_color;
	m_lifespan = a_lifespan;
	m_bRepeat = a_bRepeat;
}
