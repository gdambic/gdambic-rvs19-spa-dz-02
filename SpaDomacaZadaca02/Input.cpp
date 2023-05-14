#include "Input.h"

// private functions
void Input::setWidth()
{
	this->width = 1536;
}

void Input::setHeight()
{
	this->height = 768;
}

// constructor
Input::Input()
{
	setWidth();
	setHeight();
}

// public functions
int Input::getWidth()
{
	return width;
}

int Input::getHeight()
{
	return height;
}
