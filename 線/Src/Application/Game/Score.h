#pragma once

class Score
{
public:
	Score();
	~Score();

	void Draw();

	void Save();
	void Load();

	void GetScore(int& hitscore) { score = hitscore; }

	static const int saveNum = 50;//セーブ数
	int saveScore[saveNum];
private:
	int score;
	
};
