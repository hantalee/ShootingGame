#include "iPoint.h"

bool iPoint::operator ==(const iPoint& p)
{
	return (x==p.x)&&(y==p.y);
}

bool iPoint::operator !=(const iPoint& p)
{
	return (x!=p.x)||(y!=p.y);
}

iPoint iPoint::operator +(const iPoint& p)
{
	iPoint temp;
	temp.x = x + p.x;
	temp.y = y + p.y;

	return temp;
}
iPoint iPoint::operator +=(const iPoint& p)
{
	x +=  p.x;
	y +=  p.y;

	return(*this);
}

iPoint iPoint::operator -(const iPoint& p)
{
	iPoint temp;
	temp.x = x - p.x;
	temp.y = y - p.y;

	return temp;
}
iPoint iPoint::operator -=(const iPoint& p)
{
	x -=  p.x;
	y -=  p.y;

	return(*this);
}

iPoint iPoint::operator *(const iPoint& p)
{
	iPoint temp;
	temp.x = x * p.x;
	temp.y = y * p.y;

	return temp;
}
iPoint iPoint::operator *=(const iPoint& p)
{
	x *=  p.x;
	y *=  p.y;

	return(*this);
}

iPoint iPoint::operator /(const iPoint& p)
{
	iPoint temp;
	temp.x = x / p.x;
	temp.y = y / p.y;

	return temp;
}
iPoint iPoint::operator /=(const iPoint& p)
{
	x /=  p.x;
	y /=  p.y;

	return(*this);
}

iPoint iPoint::operator *(float f)
{
	iPoint temp;
	temp.x = x * f;
	temp.y = y * f;

	return temp;
}
iPoint iPoint::operator *=(float f)
{
	x *=  f;
	y *=  f;

	return(*this);
}

iPoint iPoint::operator /(float f)
{
	iPoint temp;
	temp.x = x / f;
	temp.y = y / f;

	return temp;
}
iPoint iPoint::operator /=(float f)
{
	x /=  f;
	y /=  f;

	return(*this);
}
