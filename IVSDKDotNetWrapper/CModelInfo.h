#pragma once

class Native_CBaseModelInfo
{
public:
	uint8_t pad[0x4];								// 00-04
	Native_phArchetypeGta* m_pArchetype;			// 04-08
	Native_gtaFragType* m_pFragType;				// 08-0C only valid if model's loaded
	//tDrawableStruct* m_pDrawableStruct;			// 0C-10 only valid if model's loaded
	uint8_t pad1[0x10];								// 10-20
	Native_CVector m_vMinBounds;					// 20-2C
	float m_fDrawDistance;							// 2C-30
	Native_CVector m_vMaxBounds;					// 30-3C
	uint32_t m_nHash;								// 3C-40
	uint32_t m_nIDEFlags;							// 40-44
	uint32_t m_nReferencesThisFrame;				// 44-48
	int16_t m_nTexDictionary;						// 48-4A -1 or index in the txd pool
	uint8_t pad2[0xC];								// 4A-56
	int8_t m_nAnimIndex;							// 56-58
	uint8_t pad3[0x8];								// 58-60

	uint8_t GetModelType()
	{
		return ((uint8_t(__thiscall*)(Native_CBaseModelInfo*))(*(void***)this)[3])(this);
	}

	void SetAnimGroup(char* group)
	{
		((void(__thiscall*)(Native_CBaseModelInfo*, char*))(AddressSetter::Get(0x58F3F0, 0x63D400)))(this, group);
	}
	void SetTexDictionary(char* txd)
	{
		((void(__thiscall*)(Native_CBaseModelInfo*, char*))(AddressSetter::Get(0x58EE30, 0x63CE40)))(this, txd);
	}
};
//VALIDATE_SIZE(Native_CBaseModelInfo, 0x60);
//VALIDATE_OFFSET(Native_CBaseModelInfo, m_pFragType, 0x8);
//VALIDATE_OFFSET(Native_CBaseModelInfo, m_pDrawableStruct, 0xC);
//VALIDATE_OFFSET(Native_CBaseModelInfo, m_vMinBounds, 0x20);
//VALIDATE_OFFSET(Native_CBaseModelInfo, m_fDrawDistance, 0x2C);
//VALIDATE_OFFSET(Native_CBaseModelInfo, m_vMaxBounds, 0x30);
//VALIDATE_OFFSET(Native_CBaseModelInfo, m_nHash, 0x3C);
//VALIDATE_OFFSET(Native_CBaseModelInfo, m_nAnimIndex, 0x56);
//VALIDATE_OFFSET(Native_CBaseModelInfo, m_nIDEFlags, 0x40);

class Native_CPedModelInfo : public Native_CBaseModelInfo
{
public:
	uint8_t pad[0x20];								// 60-80
	int32_t m_nGestureAnimIndex;					// 80-84
	int32_t m_nFacialAnimIndex;						// 84-88
	int32_t m_nVisemesAnimIndex;					// 88-8C
	uint8_t m_bStreamedPed;							// 8C-8D load from player:/
	uint8_t pad2[0x3];								// 8C-90
	uint32_t m_nPedType;							// 90-94
	uint8_t pad3[0x28];								// 94-BC
	uint32_t m_nVoiceHash;							// BC-C0
};
//VALIDATE_OFFSET(Native_CPedModelInfo, m_bStreamedPed, 0x8C);
//VALIDATE_OFFSET(Native_CPedModelInfo, m_nPedType, 0x90);
//VALIDATE_OFFSET(Native_CPedModelInfo, m_nGestureAnimIndex, 0x80);
//VALIDATE_OFFSET(Native_CPedModelInfo, m_nFacialAnimIndex, 0x84);
//VALIDATE_OFFSET(Native_CPedModelInfo, m_nVisemesAnimIndex, 0x88);
//VALIDATE_OFFSET(Native_CPedModelInfo, m_nVoiceHash, 0xBC);

class Native_CVehicleStructure
{
public:
	uint32_t m_nBones[102];							// 000-198
	uint8_t pad[0x74];								// 198-20C
};
VALIDATE_SIZE(Native_CVehicleStructure, 0x20C);

class Native_CVehicleModelInfo : public Native_CBaseModelInfo
{
public:
	char m_sGameName[12];							// 060-06C
	eVehicleType m_nVehicleType;					// 06C-070
	uint8_t pad[0x1C];								// 070-08C
	uint32_t m_nHandlingId;							// 08C-090
	uint8_t pad2[0x4];								// 090-094
	struct
	{
		unsigned int bSmallWorker : 1;
		unsigned int bBig : 1;
		unsigned int bNoBoot : 1;
		unsigned int bOnlyDuringOfficeHours : 1;
		unsigned int bBootInFront : 1;
		unsigned int bIsVan : 1;
		unsigned int bAvoidTurns : 1;
		unsigned int bLivery : 1;
		unsigned int bLiveryExtra : 1;
		unsigned int bSports : 1;
		unsigned int bDelivery : 1;
		unsigned int bNoAmbOcc : 1;
		unsigned int bOnlyOnHighways : 1;
		unsigned int bTallship : 1;
		unsigned int bTruckEngineFx : 1;
		unsigned int bTruckExhaustFx : 1;
		unsigned int bExtGang : 1;
		unsigned int bExtConv : 1;
		unsigned int bExtTaxi : 1;
		unsigned int bExtRare : 1;
		unsigned int bExtRequi : 1;
		unsigned int bExtStrong : 1;
		unsigned int bExtScript : 1;
		unsigned int bExtAll : 1;
		unsigned int bExtSunroof : 1;
		unsigned int bTruckFireFx : 1;
		unsigned int bBangerExhaustFx : 1;
		unsigned int pad : 5;
	} m_nVehicleFlags;				// 094-098
	uint8_t pad3[0x28];								// 098-0C0
	int16_t m_nAnimIndex2;							// 0C0-0C2
	uint8_t padC2[0xA];								// 0C2-0CC
	Native_CVehicleStructure* m_pVehicleStruct;		// 0CC-0D0
	uint8_t pad4[0x6C];								// 070-13C
	uint32_t m_nLiveryHashes[4];					// 13C-14C
	uint8_t pad5[0x284];							// 14C-3D0

	// sets center of mass and mass in the phBound based on the center of mass param and fMass off handling
	void SetHandlingParams(Native_tHandlingData* pHandling, Native_CVector* pCenterOfMass)
	{
		((void(__thiscall*)(Native_CBaseModelInfo*, Native_tHandlingData*, Native_CVector*))(AddressSetter::Get(0x7E7D70, 0x6477B0)))(this, pHandling, pCenterOfMass);
	}

	static int GetNumberOfSeats(int modelIndex)
	{
		return ((int(__cdecl*)(int))(AddressSetter::Get(0x7E6A60, 0x6464A0)))(modelIndex);
	}

	void ChooseVehicleColour(uint8_t* color1, uint8_t* color2, uint8_t* color3, uint8_t* color4, int startingColor)
	{
		((void(__thiscall*)(Native_CVehicleModelInfo*, uint8_t*, uint8_t*, uint8_t*, uint8_t*, int))(AddressSetter::Get(0x7E6930, 0x646370)))(this, color1, color2, color3, color4, startingColor);
	}

	void SetSecondaryAnimGroup(char* group)
	{
		((void(__thiscall*)(Native_CVehicleModelInfo*, char*))(AddressSetter::Get(0x7EAC80, 0x64A6C0)))(this, group);
	}

	static inline Native_CRGBA* ms_vehicleColourTable = (Native_CRGBA*)AddressSetter::Get(0x12D65A8, 0x1001BE0); // ms_vehicleColourTable[196]
};
//VALIDATE_SIZE(Native_CVehicleModelInfo, 0x3D0);
//VALIDATE_OFFSET(Native_CVehicleModelInfo, m_nHandlingId, 0x8C);
//VALIDATE_OFFSET(Native_CVehicleModelInfo, m_sGameName, 0x60);
//VALIDATE_OFFSET(Native_CVehicleModelInfo, m_nVehicleType, 0x6C);
//VALIDATE_OFFSET(Native_CVehicleModelInfo, m_nLiveryHashes, 0x13C);
//VALIDATE_OFFSET(Native_CVehicleModelInfo, m_pVehicleStruct, 0xCC);
//VALIDATE_OFFSET(Native_CVehicleModelInfo, m_nVehicleFlags, 0x94);
//VALIDATE_OFFSET(Native_CVehicleModelInfo, m_nAnimIndex2, 0xC0);

class Native_CModelInfo
{
public:
	static inline Native_CBaseModelInfo** ms_modelInfoPtrs = (Native_CBaseModelInfo**)AddressSetter::Get(0x11F73B0, 0xE2C168); // ms_modelInfoPtrs[31000]

	static Native_CBaseModelInfo* GetModelInfo(uint32_t hashKey, int* index)
	{
		return ((Native_CBaseModelInfo* (__cdecl*)(uint32_t, int*))(AddressSetter::Get(0x58AAE0, 0x4DD2D0)))(hashKey, index);
	}
	static Native_CPedModelInfo* AddPedModel(char* modelName)
	{
		return ((Native_CPedModelInfo* (__cdecl*)(char*))(AddressSetter::Get(0x58AE90, 0x4DD680)))(modelName);
	}
	static Native_CVehicleModelInfo* AddVehicleModel(char* modelName)
	{
		return ((Native_CVehicleModelInfo* (__cdecl*)(char*))(AddressSetter::Get(0x58AE20, 0x4DD610)))(modelName);
	}
};

namespace IVSDKDotNet {

	public ref class CBaseModelInfo
	{
	public:
		CBaseModelInfo(Native_CBaseModelInfo* nativePtr);

		uint8_t GetModelType();
		void SetAnimGroup(String^ group);
		void SetTexDictionary(String^ txd);

		property phArchetypeGta^ Archetype {
			public:
				phArchetypeGta^ get()
				{
					Native_phArchetypeGta* ptr = NativePointer->m_pArchetype;

					if (ptr)
						return gcnew phArchetypeGta(ptr);

					return nullptr;
				}
		}

		property gtaFragType^ FragType {
			public:
				gtaFragType^ get()
				{
					Native_gtaFragType* ptr = NativePointer->m_pFragType;

					if (ptr)
						return gcnew gtaFragType(ptr);

					return nullptr;
				}
		}

		property Vector3 MinBounds {
			public:
				Vector3	get()
				{
					Native_CVector v = NativePointer->m_vMinBounds;
					return Vector3(v.x, v.y, v.z);
				}
				void	set(Vector3 value) { NativePointer->m_vMinBounds = Native_CVector(value); }
		}

		property float DrawDistance {
			public:
				float	get()				{ return NativePointer->m_fDrawDistance; }
				void	set(float value)	{ NativePointer->m_fDrawDistance = value; }
		}

		property Vector3 MaxBounds {
			public:
				Vector3	get()
				{
					Native_CVector v = NativePointer->m_vMaxBounds;
					return Vector3(v.x, v.y, v.z);
				}
				void	set(Vector3 value) { NativePointer->m_vMaxBounds = Native_CVector(value); }
		}

		property uint32_t Hash {
			public:
				uint32_t	get()				{ return NativePointer->m_nHash; }
				void		set(uint32_t value) { NativePointer->m_nHash = value; }
		}

		property uint32_t IDEFlags {
			public:
				uint32_t	get()				{ return NativePointer->m_nIDEFlags; }
				void		set(uint32_t value) { NativePointer->m_nIDEFlags = value; }
		}

		property uint32_t ReferencesThisFrame {
			public:
				uint32_t	get() { return NativePointer->m_nReferencesThisFrame; }
				void		set(uint32_t value) { NativePointer->m_nReferencesThisFrame = value; }
		}

		property int16_t TexDictionary {
			public:
				int16_t	get()				{ return NativePointer->m_nTexDictionary; }
				void	set(int16_t value)	{ NativePointer->m_nTexDictionary = value; }
		}

		property int8_t AnimIndex {
			public:
				int8_t	get()				{ return NativePointer->m_nAnimIndex; }
				void	set(int8_t value)	{ NativePointer->m_nAnimIndex = value; }
		}

		property Native_CBaseModelInfo* NativePointer {
			public:
				Native_CBaseModelInfo*		get()								{ return m_cNativeBaseModelInfo; }
				void						set(Native_CBaseModelInfo* value)	{ m_cNativeBaseModelInfo = value; }
		}

	private:
		Native_CBaseModelInfo* m_cNativeBaseModelInfo;
	};

	public ref class CPedModelInfo : CBaseModelInfo
	{
	public:
		CPedModelInfo(Native_CPedModelInfo* nativePtr);

		property uint32_t GestureAnimIndex {
			public:
				uint32_t	get()				{ return NativePointer->m_nGestureAnimIndex; }
				void		set(uint32_t value) { NativePointer->m_nGestureAnimIndex = value; }
		}

		property uint32_t FacialAnimIndex {
			public:
				uint32_t	get() { return NativePointer->m_nFacialAnimIndex; }
				void		set(uint32_t value) { NativePointer->m_nFacialAnimIndex = value; }
		}

		property uint32_t VisemesAnimIndex {
			public:
				uint32_t	get() { return NativePointer->m_nVisemesAnimIndex; }
				void		set(uint32_t value) { NativePointer->m_nVisemesAnimIndex = value; }
		}

		/// <summary>
		/// Load from player:/
		/// </summary>
		property uint8_t StreamedPed {
			public:
				uint8_t		get()				{ return NativePointer->m_bStreamedPed; }
				void		set(uint8_t value)	{ NativePointer->m_bStreamedPed = value; }
		}

		property uint32_t PedType {
			public:
				uint32_t	get()				{ return NativePointer->m_nPedType; }
				void		set(uint32_t value) { NativePointer->m_nPedType = value; }
		}

		property uint32_t VoiceHash {
			public:
				uint32_t	get()				{ return NativePointer->m_nVoiceHash; }
				void		set(uint32_t value) { NativePointer->m_nVoiceHash = value; }
		}

		property Native_CPedModelInfo* NativePointer {
			public:
				Native_CPedModelInfo*		get()								{ return m_cNativePedModelInfo; }
				void						set(Native_CPedModelInfo* value)	{ m_cNativePedModelInfo = value; }
		}

	private:
		Native_CPedModelInfo* m_cNativePedModelInfo;
	};

	public ref class CVehicleStructure
	{
	public:
		CVehicleStructure(Native_CVehicleStructure* nativePtr);

		property array<uint32_t>^ Bones {
			public:
				array<uint32_t>^ get()
				{
					array<uint32_t>^ arr = gcnew array<uint32_t>(4);

					for (int i = 0; i < arr->Length; i++)
					{
						arr[i] = NativePointer->m_nBones[i];
					}

					return arr;
				}
				void set(array<uint32_t>^ value)
				{
					for (int i = 0; i < value->Length; i++)
					{
						NativePointer->m_nBones[i] = value[i];
					}
				}
		}

		property Native_CVehicleStructure* NativePointer {
			public:
				Native_CVehicleStructure*	get()									{ return m_cNativeVehicleStructure; }
				void						set(Native_CVehicleStructure* value)	{ m_cNativeVehicleStructure = value; }
		}

	private:
		Native_CVehicleStructure* m_cNativeVehicleStructure;
	};

	public ref class CVehicleModelInfo : CBaseModelInfo
	{
	public:
		CVehicleModelInfo(Native_CVehicleModelInfo* nativePtr);

		void SetHandlingParams(UIntPtr handlingData, Vector3 pCenterOfMass);

		static int GetNumberOfSeats(int modelIndex);

		void SetSecondaryAnimGroup(String^ group);

		property String^ GameName {
			public: String^ get() { return gcnew String(NativePointer->m_sGameName); }
		}

		property eVehicleType VehicleType {
			public: eVehicleType get() { return NativePointer->m_nVehicleType; }
		}

		property uint32_t HandlingId {
			public:
				uint32_t	get()				{ return NativePointer->m_nHandlingId; }
				void		set(uint32_t value) { NativePointer->m_nHandlingId = value; }
		}

		property int16_t AnimIndex2 {
			public:
				int16_t		get()				{ return NativePointer->m_nAnimIndex2; }
				void		set(int16_t value)	{ NativePointer->m_nAnimIndex2 = value; }
		}

		property CVehicleStructure^ VehicleStruct {
			public: CVehicleStructure^ get()
			{
				Native_CVehicleStructure* ptr = NativePointer->m_pVehicleStruct;

				if (ptr)
					return gcnew CVehicleStructure(ptr);

				return nullptr;
			}
		}

		property array<uint32_t>^ LiveryHashes {
			public:
				array<uint32_t>^ get()
				{
					array<uint32_t>^ arr = gcnew array<uint32_t>(4);

					for (int i = 0; i < arr->Length; i++)
					{
						arr[i] = NativePointer->m_nLiveryHashes[i];
					}

					return arr;
				}
				void set(array<uint32_t>^ value)
				{
					for (int i = 0; i < value->Length; i++)
					{
						NativePointer->m_nLiveryHashes[i] = value[i];
					}
				}
		}

		property Native_CVehicleModelInfo* NativePointer {
			public:
				Native_CVehicleModelInfo*	get()									{ return m_cNativeVehicleModelInfo; }
				void						set(Native_CVehicleModelInfo* value)	{ m_cNativeVehicleModelInfo = value; }
		}

	private:
		Native_CVehicleModelInfo* m_cNativeVehicleModelInfo;
	};

	public ref class CModelInfo
	{
	public:

		static CBaseModelInfo^ GetModelInfo(uint32_t hashKey, [OutAttribute] int% index);
		static CPedModelInfo^ AddPedModel(String^ modelName);
		static CVehicleModelInfo^ AddVehicleModel(String^ modelName);

	};

}