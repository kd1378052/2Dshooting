#pragma once

class Score
{
public:
	Score();
	~Score();

	void GetScore(int& hitscore) { score = hitscore; }

private:
	int score;
};
