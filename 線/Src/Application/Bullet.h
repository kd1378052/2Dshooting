#pragma once

const int SCREEN_LEFT = -640;
const int SCREEN_TOP = 360;
const int SCREEN_RIGHT = 640;
const int SCREEN_BOTTOM = -360;

class Bullet
{
public:
	Bullet();
	~Bullet();


	void Init();
	void Update();
	void Draw();

private:

	static const int  bulletNum = 100;

	KdTexture bulletTex;
	Math::Matrix bulletMat[bulletNum];
	int bulletFlg[bulletNum];


};
