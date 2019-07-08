#include "iSize.h"

bool iSize::operator ==(const iSize& s)
{
	return (width==s.width)&&(height==s.height);
}

bool iSize::operator !=(const iSize& s)
{
	return (width!=s.width)||(height!=s.height);
}

iSize iSize::operator +(const iSize& s)
{
	iSize temp;
	temp.width = width + s.width;
	temp.height = height + s.height;

	return temp;
}
iSize iSize::operator +=(const iSize& s)
{
	width += s.width;
	height += s.height;

	return (*this);
}

iSize iSize::operator -(const iSize& s)
{
	iSize temp;
	temp.width = width - s.width;
	temp.height = height - s.height;

	return temp;
}
iSize iSize::operator -=(const iSize& s)
{
	width -= s.width;
	height -= s.height;

	return (*this);
}

iSize iSize::operator *(const iSize& s)
{
	iSize temp;
	temp.width = width * s.width;
	temp.height = height * s.height;

	return temp;
}
iSize iSize::operator *=(const iSize& s)
{
	width *= s.width;
	height *= s.height;

	return (*this);
}

iSize iSize::operator /(const iSize& s)
{
	iSize temp;
	temp.width = width / s.width;
	temp.height = height / s.height;

	return temp;
}
iSize iSize::operator /=(const iSize& s)
{
	width /= s.width;
	height /= s.height;

	return (*this);
}

iSize iSize::operator *(float f)
{
	iSize temp;
	temp.width = width * f;
	temp.height = height * f;

	return temp;
}
iSize iSize::operator *=(float f)
{
	width *= f;
	height *= f;

	return (*this);
}

iSize iSize::operator /(float f)
{
	iSize temp;
	temp.width = width / f;
	temp.height = height / f;

	return temp;
}
iSize iSize::operator /=(float f)
{
	width /= f;
	height /= f;

	return (*this);
}





