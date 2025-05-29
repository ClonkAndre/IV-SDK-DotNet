class CVector4
{
public:
	float x, y, z, w;

public:
	CVector4()
	{
		x = 0.0F;
		y = 0.0F;
		z = 0.0F;
		w = 0.0F;
	}
	CVector4(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
};