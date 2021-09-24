#pragma once

class ammoconda;

class ammocondaState
{
private:
	
protected:

public:
	virtual ammocondaState* InputHandle(ammoconda* ammoconda) = 0;
	virtual	void update(ammoconda* ammoconda) = 0;
	virtual	void enter(ammoconda* ammoconda) = 0;
	virtual void render(ammoconda* ammoconda) = 0;
	virtual void exit(ammoconda* ammoconda) = 0;
};

