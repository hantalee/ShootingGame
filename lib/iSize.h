#pragma once

struct iSize
{
	float width, height;

	bool operator ==(const iSize& s);
	bool operator !=(const iSize& s);

	iSize operator +(const iSize& s);
	iSize operator +=(const iSize& s);

	iSize operator -(const iSize& s);
	iSize operator -=(const iSize& s);

	iSize operator *(const iSize& s);
	iSize operator *=(const iSize& s);

	iSize operator /(const iSize& s);
	iSize operator /=(const iSize& s);

	iSize operator *(float f);
	iSize operator *=(float f);

	iSize operator /(float f);
	iSize operator /=(float f);
};
