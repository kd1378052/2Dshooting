#pragma once

class Bullet
{
public:
	Bullet();
	~Bullet();


	void Init();
	void Update();
	void Draw();

	void SetPlayerPos(float x, float y);

private:

	static const int  bulletNum = 100;

	int posX;
	int posY;
	KdTexture bulletTex;
	Math::Matrix bulletMat[bulletNum];
	float bulletX[bulletNum];
	float bulletY[bulletNum];
	int bulletFlg[bulletNum];

	int  shotWait;//発射待期時間



};
