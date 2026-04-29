#pragma once

class Particle
{
public:
	Particle();
	~Particle();

	void Init();
	void Update(Math::Vector2 a_Pos);
	void Draw();

	float Rnd();
	//パーティクル発生関数
	void Emit(Math::Vector2 a_pos, Math::Vector2 a_move, float a_size,
		Math::Color a_color, int a_lifespan, bool a_bRepeat);

private:
	Math::Vector2 m_pos;//座標
	Math::Vector2 m_move;//移動量
	float		m_size;//サイズ
	Math::Color m_color;//色
	float		m_lifespan;//有効期間
	bool		m_bRepeat;//繰り返しフラグ
	Math::Matrix m_matrix;//行列
	KdTexture particleTex;//テクスチャ

};
