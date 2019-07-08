#pragma once

struct iPoint
{
	float x, y;

	bool operator ==(const iPoint& p);
	bool operator !=(const iPoint& p);

	iPoint operator +(const iPoint& p);
	iPoint operator +=(const iPoint& p);

	iPoint operator -(const iPoint& p);
	iPoint operator -=(const iPoint& p);

	iPoint operator *(const iPoint& p);
	iPoint operator *=(const iPoint& p);

	iPoint operator /(const iPoint& p);
	iPoint operator /=(const iPoint& p);

	iPoint operator *(float f);
	iPoint operator *=(float f);

	iPoint operator /(float f);
	iPoint operator /=(float f);
};
