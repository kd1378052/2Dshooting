#pragma once

class State
{
public:
	State(){}
	~State(){}

	virtual void Init() = 0;//ƒˆ‰¼‘zŠÖ”
	virtual void Update() = 0;//ƒˆ‰¼‘zŠÖ”
	virtual void Draw() = 0;//ƒˆ‰¼‘zŠÖ”
	//â‘Îã‘‚«‚µ‚È‚¢‚Æ‚¢‚¯‚ñ

private:

};
