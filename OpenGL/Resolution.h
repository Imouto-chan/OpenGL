#ifndef RESOLUTION_H
#define RESOLUTION_H

struct Resolution
{
	int width = 1280;
	int height = 768;
	int fov = 45;

	Resolution(int _width, int _height, int _fov)
	{
		width = _width;
		height = _height;
	}

	Resolution(int _width, int _height)
	{
		width = _width;
		height = _height;
	}

	Resolution()
	{
	}
};

#endif // RESOLUTION_H