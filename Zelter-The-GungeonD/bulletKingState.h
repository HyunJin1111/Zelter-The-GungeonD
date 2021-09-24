#pragma once

class bulletKing;

class bulletKingState
{
private:
	bulletKing* _bulletKing;
	
public:
	virtual bulletKingState* InputHandle(bulletKing* bulletKing) = 0;
	virtual	void update(bulletKing* bulletKing) = 0;
	virtual	void enter(bulletKing* bulletKing) = 0;
	virtual void render(bulletKing* bulletKing) = 0;
	virtual void exit(bulletKing* bulletKing) = 0;
};

