class CCamera
{
public:
	static inline CCam*& g_pFinalCam = AddressSetter::GetRef<CCam*>("CCamera", "g_pFinalCam"); // CCamFinal

	uint8_t pad[0x4];					// 00-04
	CCam* m_pFinalCam;					// 04-08
	uint8_t pad2[0x4];					// 08-0C
	CCam* m_pGameCam;					// 0C-10
	CCamFollowVehicle* m_pVehicleCam;	// 10-14
	CCam* m_pOnFootCam;					// 14-18

	CCam* CreateCam(int type, CCam* unk, CCam* unk2)
	{
		return ((CCam*(__thiscall*)(CCamera*, int, CCam*, CCam*))(AddressSetter::Get("CCamera", "CreateCam")))(this, type, unk, unk2);
	}
};
static CCamera& TheCamera = AddressSetter::GetRef<CCamera>("CCamera", "TheCamera");

VALIDATE_OFFSET(CCamera, m_pFinalCam, 0x4);
VALIDATE_OFFSET(CCamera, m_pGameCam, 0xC);