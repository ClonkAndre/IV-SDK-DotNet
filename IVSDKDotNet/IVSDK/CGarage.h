class CStoredCar
{
public:
	// the pad spaces here are completely unused
	float CoorX;								// 00-04
	float CoorY;								// 04-08
	float CoorZ;								// 08-0C
	uint32_t FlagsLocal;						// 0C-10
	uint16_t ModelIndex;						// 10-12
	uint8_t pad2[0x1D];							// 12-30
	uint16_t Bits;								// 30-32
	uint8_t Colour1;							// 32-33
	uint8_t Colour2;							// 33-34
	uint8_t Colour3;							// 34-35
	uint8_t Colour4;							// 35-36
	uint8_t pad3[0x2];							// 36-38
	uint32_t Extras;							// 38-3C CVehicle+0xE20
	uint32_t PaintJob;							// 3C-40
	uint8_t pad4[0x2];							// 40-42
	uint8_t unk2;								// 42-33 CVehicle+0x10C2
	int8_t iFrontX;								// 43-44
	int8_t iFrontY;								// 44-45
	int8_t iFrontZ;								// 45-46
	uint8_t pad5[0x2];							// 46-48

	void StoreCar(CVehicle* pCar)
	{
		((void(__thiscall*)(CStoredCar*, CVehicle*))(AddressSetter::Get("CStoredCar", "StoreCar")))(this, pCar);
	}
	void RestoreCar()
	{
		((void(__thiscall*)(CStoredCar*))(AddressSetter::Get("CStoredCar", "RestoreCar")))(this);
	}
};
VALIDATE_SIZE(CStoredCar, 0x48);
VALIDATE_OFFSET(CStoredCar, CoorX, 0);
VALIDATE_OFFSET(CStoredCar, FlagsLocal, 0xC);
VALIDATE_OFFSET(CStoredCar, ModelIndex, 0x10);
VALIDATE_OFFSET(CStoredCar, Bits, 0x30);
VALIDATE_OFFSET(CStoredCar, Colour1, 0x32);
VALIDATE_OFFSET(CStoredCar, PaintJob, 0x3C);
VALIDATE_OFFSET(CStoredCar, iFrontX, 0x43);
VALIDATE_OFFSET(CStoredCar, iFrontZ, 0x45);
VALIDATE_OFFSET(CStoredCar, unk2, 0x42);

class CGarage
{
public:
	float BaseX;								// 00-04
	float BaseY;								// 04-08
	float BaseZ;								// 08-0C
	float Delta1X;								// 0C-10
	float Delta1Y;								// 10-14
	float Delta2X;								// 14-18
	float Delta2Y;								// 18-1C
	float CeilingZ;								// 1C-20
	float Delta1Length;							// 20-24
	float Delta2Length;							// 24-28
	float MinX;									// 28-2C
	float MaxX;									// 2C-30
	float MinY;									// 30-34
	float MaxY;									// 34-38
	uint32_t TimeOfNextEvent;					// 38-3C
	CVehicle* pCarToCollect;					// 3C-40
	uint32_t NameHash;							// 40-44
	uint8_t pad3[0x4];							// 44-48
	uint8_t Type;								// 48-49
	uint8_t State;								// 49-4A
	uint8_t pad4[0x1];							// 4A-4B
	uint8_t OriginalType;						// 4B-4C
	uint8_t Flags;								// 4C-4D
	uint8_t pad5[0x1F];							// 4D-6C

	bool IsPointInsideGarage(CVector Point)
	{
		return ((bool(__thiscall*)(CGarage*))(AddressSetter::Get("CGarage", "IsPointInsideGarage")))(this);
	}
	void PlayerArrestedOrDied()
	{
		((void(__thiscall*)(CGarage*))(AddressSetter::Get("CGarage", "PlayerArrestedOrDied")))(this);
	}
	void StoreAndRemoveCarsForThisHideOut(CStoredCar* aStoredCars, bool unk)
	{
		((void(__thiscall*)(CGarage*, CStoredCar*, bool))(AddressSetter::Get("CGarage", "StoreAndRemoveCarsForThisHideOut")))(this, aStoredCars, unk);
	}
	void TidyUpGarageClose()
	{
		((void(__thiscall*)(CGarage*))(AddressSetter::Get("CGarage", "TidyUpGarageClose")))(this);
	}
	void Update()
	{
		((void(__thiscall*)(CGarage*))(AddressSetter::Get("CGarage", "Update")))(this);
	}
};
VALIDATE_SIZE(CGarage, 0x6C);
VALIDATE_OFFSET(CGarage, BaseZ, 0x8);
VALIDATE_OFFSET(CGarage, Delta2Length, 0x24);
VALIDATE_OFFSET(CGarage, CeilingZ, 0x1C);
VALIDATE_OFFSET(CGarage, Delta1Length, 0x20);
VALIDATE_OFFSET(CGarage, MinX, 0x28);
VALIDATE_OFFSET(CGarage, TimeOfNextEvent, 0x38);
VALIDATE_OFFSET(CGarage, pCarToCollect, 0x3C);
VALIDATE_OFFSET(CGarage, NameHash, 0x40);
VALIDATE_OFFSET(CGarage, Type, 0x48);
VALIDATE_OFFSET(CGarage, State, 0x49);
VALIDATE_OFFSET(CGarage, OriginalType, 0x4B);
VALIDATE_OFFSET(CGarage, Flags, 0x4C);

class CSaveGarage
{
public:
	uint8_t Type;								// 00-01
	uint8_t State;								// 01-02
	uint8_t Flags;								// 02-03
	uint8_t pad;								// 03-04
	float BaseX;								// 04-08
	float BaseY;								// 08-0C
	float BaseZ;								// 0C-10
	float Delta1X;								// 10-14
	float Delta1Y;								// 14-18
	float Delta2X;								// 18-1C
	float Delta2Y;								// 1C-20
	float CeilingZ;								// 20-24
	float Delta1Length;							// 24-28
	float Delta2Length;							// 28-2C
	float MinX;									// 2C-30
	float MaxX;									// 30-34
	float MinY;									// 34-38
	float MaxY;									// 38-3C
	int32_t TimeOfNextEvent;					// 3C-40
	uint32_t NameHash;							// 40-44
	uint8_t unk1;								// 44-45
	uint8_t OriginalType;						// 45-46
	uint8_t pad2[0x2];							// 46-48

	void CopyGarageIntoSaveGarage(CGarage* pGarage)
	{
		((void(__thiscall*)(CSaveGarage*, CGarage*))(AddressSetter::Get("CSaveGarage", "CopyGarageIntoSaveGarage")))(this, pGarage);
	}
	void CopyGarageOutOfSaveGarage(CGarage* pGarage)
	{
		((void(__thiscall*)(CSaveGarage*, CGarage*))(AddressSetter::Get("CSaveGarage", "CopyGarageOutOfSaveGarage")))(this, pGarage);
	}
};
VALIDATE_SIZE(CSaveGarage, 0x48);
VALIDATE_OFFSET(CSaveGarage, Flags, 0x2);
VALIDATE_OFFSET(CSaveGarage, BaseX, 0x4);
VALIDATE_OFFSET(CSaveGarage, TimeOfNextEvent, 0x3C);
VALIDATE_OFFSET(CSaveGarage, NameHash, 0x40);

class CGarages
{
public:

	static inline auto& bCamShouldBeOutside = AddressSetter::GetRef<bool>("CGarages", "bCamShouldBeOutside");
	static inline auto& bHasResprayHappened = AddressSetter::GetRef<bool>("CGarages", "bHasResprayHappened");
	static inline auto& MessageStartTime = AddressSetter::GetRef<uint32_t>("CGarages", "MessageStartTime");
	static inline auto& MessageEndTime = AddressSetter::GetRef<uint32_t>("CGarages", "MessageEndTime");
	static inline auto& LastGaragePlayerWasIn = AddressSetter::GetRef<int32_t>("CGarages", "LastGaragePlayerWasIn");
	static inline auto& LastTimeHelpMessage = AddressSetter::GetRef<uint32_t>("CGarages", "LastTimeHelpMessage");

	static inline auto& BombsAreFree = AddressSetter::GetRef<bool>("CGarages", "BombsAreFree");
	static inline auto& RespraysAreFree = AddressSetter::GetRef<bool>("CGarages", "RespraysAreFree");
	static inline auto& NoResprays = AddressSetter::GetRef<bool>("CGarages", "NoResprays");

	static inline auto& NumGarages = AddressSetter::GetRef<uint32_t>("CGarages", "NumGarages");
	static inline auto& NumSafehouseGarages = AddressSetter::GetRef<uint32_t>("CGarages", "NumSafehouseGarages");
	static inline CGarage* aGarages = (CGarage*)AddressSetter::Get("CGarages", "aGarages"); // aGarages[40]
	static inline CStoredCar* aCarsInSafeHouse = (CStoredCar*)AddressSetter::Get("CGarages", "aCarsInSafeHouse"); // aCarsInSafeHouse[20]

	static bool CameraShouldBeOutside()
	{
		return ((bool(__cdecl*)())(AddressSetter::Get("CGarages", "CameraShouldBeOutside")))();
	}
	static void CloseHideOutGaragesBeforeSave(bool unk)
	{
		((void(__cdecl*)(bool))(AddressSetter::Get("CGarages", "CloseHideOutGaragesBeforeSave")))(unk);
	}
	static void Init()
	{
		((void(__cdecl*)())(AddressSetter::Get("CGarages", "Init")))();
	}
	static bool Load()
	{
		return ((bool(__cdecl*)())(AddressSetter::Get("CGarages", "Load")))();
	}
	static void PlayerArrestedOrDied()
	{
		((void(__cdecl*)())(AddressSetter::Get("CGarages", "PlayerArrestedOrDied")))();
	}
	static bool Save()
	{
		return ((bool(__cdecl*)())(AddressSetter::Get("CGarages", "Save")))();
	}
	static void Shutdown()
	{
		((void(__cdecl*)())(AddressSetter::Get("CGarages", "Shutdown")))();
	}
	static void Update()
	{
		((void(__cdecl*)())(AddressSetter::Get("CGarages", "Update")))();
	}
};