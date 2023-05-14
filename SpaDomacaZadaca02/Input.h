#pragma once
class Input
{
private:
	int width;
	int height;
	void setWidth();
	void setHeight();
public:
	Input();
	int getWidth();
	int getHeight();
};