class CMatrix
{
public:
	//CVector_pad right; // 00-10
	//CVector_pad up; // 10-20
	//CVector_pad at; // 20-30
	//CVector_pad pos; // 30-40

	CVector4 right; // 00-10
	CVector4 up; // 10-20
	CVector4 at; // 20-30
	CVector4 pos; // 30-40

public:
	CMatrix(CVector4 _right, CVector4 _up, CVector4 _at, CVector4 _pos)
	{
		right = _right;
		up = _up;
		at = _at;
		pos = _pos;
	}
};