class CBoundBox
{
public:
	CVector_pad m_vecMin;
	CVector_pad m_vecMax;
}; 

class CStuntJump
{
public:
	CBoundBox m_bbStart;						// 00-20
	CBoundBox m_bbEnd;							// 20-40
	CVector m_vecCamera;						// 40-4C
	uint32_t unk1;								// 4C-50
	uint32_t m_iScore;							// 50-54
	uint8_t m_bPassed;							// 54-55
	uint8_t m_bFound;							// 55-56
	uint8_t pad[0xA];							// 56-60
};
VALIDATE_SIZE(CStuntJump, 0x60);
VALIDATE_OFFSET(CStuntJump, m_vecCamera, 0x40);
VALIDATE_OFFSET(CStuntJump, m_iScore, 0x50);
VALIDATE_OFFSET(CStuntJump, m_bPassed, 0x54);

class CStuntJumpManager
{
public:
	static inline auto& m_bActive = AddressSetter::GetRef<bool>("CStuntJumpManager", "m_bActive");
	static inline auto& m_iNumCompleted = AddressSetter::GetRef<uint32_t>("CStuntJumpManager", "m_iNumCompleted");
	static inline auto& m_iNumJumps = AddressSetter::GetRef<uint32_t>("CStuntJumpManager", "m_iNumJumps");
	static inline auto& mp_poolStuntJumps = AddressSetter::GetRef<CPool<CStuntJump>*>("CStuntJumpManager", "mp_poolStuntJumps");

	static bool Save()
	{
		return ((int(__cdecl*)())(AddressSetter::Get("CStuntJumpManager", "Save")))();
	}
	static bool Load()
	{
		return ((int(__cdecl*)())(AddressSetter::Get("CStuntJumpManager", "Load")))();
	}
};