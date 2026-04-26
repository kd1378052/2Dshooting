#pragma once

class Enemy;

class Bullet
{
public:
	Bullet();
	~Bullet();


	void Init();
	void Update();
	void Draw();

	void Flring();

	void SetPlayerPos(Math::Vector2 pos);

	void Bullet::SetEnemy(Enemy* enemy)
	{
		m_enemy = enemy;
	}

private:
	Enemy* m_enemy;


	static const int  bulletNum = 100;

	Math::Vector2 m_Pos;

	KdTexture bulletTex;
	Math::Matrix bulletMat[bulletNum];
	Math::Vector2 bulletPos[bulletNum];
	bool bulletFlg[bulletNum];

	int  shotWait;//発射待期時間



};
