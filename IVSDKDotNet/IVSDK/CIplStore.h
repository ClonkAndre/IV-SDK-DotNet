struct IplDef
{
	uint8_t pad[0x60];				// 00-60
};
VALIDATE_SIZE(IplDef, 0x60);

class CIplStore
{
public:
	static inline CQuadTreeNode*& ms_pQuadTree = AddressSetter::GetRef<CQuadTreeNode*>("CIplStore", "ms_pQuadTree");
	static inline CPool<IplDef>*& ms_pPool = AddressSetter::GetRef<CPool<IplDef>*>("CIplStore", "ms_pPool"); // dupe of the one in CPools for convenience

	static inline void LoadIpls(CVector pos, bool unk)
	{
		((void(__cdecl*)(CVector, bool))(AddressSetter::Get("CIplStore", "LoadIpls")))(pos, unk);
	}
	static inline void SetIplsRequired(CVector pos)
	{
		((void(__cdecl*)(CVector))(AddressSetter::Get("CIplStore", "SetIplsRequired")))(pos);
	}
};

inline bool& gbIplsNeededAtPosn = AddressSetter::GetRef<bool>("CIplStore", "gbIplsNeededAtPosn");
inline CVector& gvecIplsNeededAtPosn = AddressSetter::GetRef<CVector>("CIplStore", "gvecIplsNeededAtPosn");

inline void SetIfIplIsRequired(CVector2D* pos, IplDef* def)
{
	((void(__cdecl*)(CVector2D*, IplDef*))(AddressSetter::Get("CIplStore", "SetIfIplIsRequired")))(pos, def);
}

inline void SetIfIplIsRequiredReducedBB(CVector2D* pos, IplDef* def)
{
	((void(__cdecl*)(CVector2D*, IplDef*))(AddressSetter::Get("CIplStore", "SetIfIplIsRequiredReducedBB")))(pos, def);
}