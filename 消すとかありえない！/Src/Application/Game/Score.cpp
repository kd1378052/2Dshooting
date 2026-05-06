#include "Score.h"

Score::Score()
{
	score = 0.0f;
}

Score::~Score()
{

}

void Score::Draw()
{
	


}

void Score::Save()
{
	FILE* fp;
	if (fopen_s(&fp, "Texture/Score/score.txt", "a") == 0)
	{
		fprintf(fp, "\n%d", score);
		fclose(fp);
	}
}

void Score::Load()
{
	FILE* fp;
	if ((fp = fopen("Texture/Score/score.txt", "r")) != nullptr)
	{
		int i = 0;
		while (fscanf(fp, "%d", &saveScore[i++]) != EOF) {}
		fclose(fp);
	}
	int i, j, w;

	for (i = 0;i < saveNum - 1;i++)
	{
		for (j = i + 1;j < saveNum;j++) {
			if (saveScore[i] < saveScore[j])
			{
				w = saveScore[i];
				saveScore[i] = saveScore[j];
				saveScore[j] = w;
			}
		}
	}

}
