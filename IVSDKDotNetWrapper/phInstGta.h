#pragma once

namespace rage { class grmShaderGroup; }

class Native_phArchetypeGta
{
public:
	uint8_t pad[0xC];													// 00-0C
	rage::phBound* m_pBounds;											// 0C-10
	uint8_t pad1[0xC];													// 10-1C
	float m_fMass;														// 1C-20 mass of all frag parts added up
	uint8_t pad2[0x8];													// 20-28
	float m_fMaxSpeed;													// 28-2C
};
VALIDATE_OFFSET(Native_phArchetypeGta, m_pBounds, 0xC);
VALIDATE_OFFSET(Native_phArchetypeGta, m_fMaxSpeed, 0x28);
VALIDATE_OFFSET(Native_phArchetypeGta, m_fMass, 0x1C);

namespace rage
{
	struct crSkeletonData
	{
		char* m_sName;									// 00-04
		uint8_t pad[0x10];								// 04-14
		uint16_t m_nBoneID;								// 14-16
		uint8_t pad2[0xCA];								// 16-E0
	};
	VALIDATE_SIZE(crSkeletonData, 0xE0);
	VALIDATE_OFFSET(crSkeletonData, m_nBoneID, 0x14);

	class crSkeleton
	{
	public:
		crSkeletonData* m_aData;						// 00-04 array
		uint8_t pad[0x10];								// 04-14
		uint16_t m_nBoneCount;							// 14-18
		crSkeletonData* GetBoneDataByName(char* sName)
		{
			return ((crSkeletonData * (__thiscall*)(crSkeleton*, char*))(AddressSetter::Get(0x2434F0, 0x4F510)))(this, sName);
		}
	};
	VALIDATE_OFFSET(crSkeleton, m_aData, 0x0);
	VALIDATE_OFFSET(crSkeleton, m_nBoneCount, 0x14);

	class rmcDrawable
	{
	public:
		uint8_t pad[0x8];													// 000-050
		grmShaderGroup* m_pShaderGroup;										// 008-00C
		crSkeleton* m_pSkeleton;											// 00C-010
		uint8_t pad2[0x40];													// 010-050
		float m_fLodDistanceHigh;											// 050-054
		float m_fLodDistanceLow;											// 054-058
		float m_fLodDistanceVLow;											// 058-05C
		float m_fLodDistanceVLow2;											// 05C-060
	};
	VALIDATE_OFFSET(rmcDrawable, m_pShaderGroup, 0x8);
	VALIDATE_OFFSET(rmcDrawable, m_pSkeleton, 0xC);
	VALIDATE_OFFSET(rmcDrawable, m_fLodDistanceHigh, 0x50);
	VALIDATE_OFFSET(rmcDrawable, m_fLodDistanceLow, 0x54);

	class Native_phInst
	{
	public:
		uint8_t pad[0x4];													// 00-04
		Native_phArchetypeGta* m_pArchetype;								// 04-08 peds have phArchetypeGta, cars have phArchetypeDamp
		int16_t m_nRigidBodyIndex;											// 08-0A
		uint8_t pad2[0x2];													// 0A-0C
		Native_CEntity* m_pEntity;											// 0C-10
		uint8_t pad3[0x30];													// 10-40
		Native_CVector m_vPos;												// 40-4C
		uint8_t pad4[0x4];													// 4C-50
	};
	VALIDATE_SIZE(Native_phInst, 0x50);
	VALIDATE_OFFSET(Native_phInst, m_nRigidBodyIndex, 0x8);
	VALIDATE_OFFSET(Native_phInst, m_pEntity, 0xC);
	VALIDATE_OFFSET(Native_phInst, m_vPos, 0x40);
}

class Native_gtaFragType
{
public:
	uint8_t pad[0xB4];													// 000-0B4
	rage::rmcDrawable* m_pDrawable;										// 0B4-0B8
	uint8_t pad2[0x2C];													// 0B8-0E4
	Native_phArchetypeGta* m_pArchetype;								// 0E4-0E8
};
VALIDATE_OFFSET(Native_gtaFragType, m_pDrawable, 0xB4);
VALIDATE_OFFSET(Native_gtaFragType, m_pArchetype, 0xE4);

class Native_phInstGta : public rage::Native_phInst
{
public:																	// 00-50
	uint8_t pad[0xC];													// 50-5C
	uint32_t* m_pUnkImportant;											// 5C-60
	uint8_t pad2[0x0C];													// 60-6C
	Native_gtaFragType* m_pFragType;									// 6C-70

	// this is what's used to detach car parts, groupId is in the same order as groups are in the .oft file
	// use tDoor->m_nGroupID for vehicle doors, haven't found a way to see the rest of the bones, or anything for other entity types other than guessing
	Native_phInstGta* DetachFragmentGroup(uint32_t groupId)
	{
		return ((Native_phInstGta * (__thiscall*)(Native_phInstGta*, signed int))(AddressSetter::Get(0x117D30, 0x245C10)))(this, groupId);
	}
};
VALIDATE_OFFSET(Native_phInstGta, m_pFragType, 0x6C);
VALIDATE_OFFSET(Native_phInstGta, m_pUnkImportant, 0x5C);

namespace IVSDKDotNet
{

	public ref class phArchetypeGta
	{
	public:
		phArchetypeGta(Native_phArchetypeGta* nativePtr);

		property float Mass {
			float get()
			{
				return m_cNativeArchetypeGta->m_fMass;
			}
			void set(float value)
			{
				m_cNativeArchetypeGta->m_fMass = value;
			}
		}

		property float MaxSpeed {
			float get()
			{
				return m_cNativeArchetypeGta->m_fMaxSpeed;
			}
			void set(float value)
			{
				m_cNativeArchetypeGta->m_fMaxSpeed = value;
			}
		}

	private:
		Native_phArchetypeGta* m_cNativeArchetypeGta;
	};

	public ref class phInst
	{
	public:
		phInst(rage::Native_phInst* nativePtr);

		property phArchetypeGta^ Archetype {
			phArchetypeGta^ get()
			{
				Native_phArchetypeGta* ptr = m_cNativeInst->m_pArchetype;

				if (ptr)
					return gcnew phArchetypeGta(ptr);

				return nullptr;
			}
		}

		property int16_t RigidBodyIndex {
			int16_t get()
			{
				return m_cNativeInst->m_nRigidBodyIndex;
			}
			void set(int16_t value)
			{
				m_cNativeInst->m_nRigidBodyIndex = value;
			}
		}

		property UIntPtr Entity {
			UIntPtr get()
			{
				return UIntPtr(m_cNativeInst->m_pEntity);
			}
			void set(UIntPtr value)
			{
				if (value == UIntPtr::Zero)
					return;

				m_cNativeInst->m_pEntity = (Native_CEntity*)value.ToPointer();
			}
		}

		property Vector3 Pos {
			Vector3 get()
			{
				Native_CVector vec = m_cNativeInst->m_vPos;
				return Vector3(vec.x, vec.y, vec.z);
			}
			void set(Vector3 value)
			{
				m_cNativeInst->m_vPos = Native_CVector(value);
			}
		}

	private:
		rage::Native_phInst* m_cNativeInst;
	};

	public ref class gtaFragType
	{
	public:
		gtaFragType(Native_gtaFragType* nativePtr);

		property phArchetypeGta^ Archetype {
			phArchetypeGta^ get()
			{
				Native_phArchetypeGta* ptr = m_cNativeGtaFragType->m_pArchetype;

				if (ptr)
					return gcnew phArchetypeGta(ptr);

				return nullptr;
			}
		}

	private:
		Native_gtaFragType* m_cNativeGtaFragType;
	};

	public ref class phInstGta : phInst
	{
	public:
		phInstGta(Native_phInstGta* nativePtr);

		static phInstGta^ FromPointer(UIntPtr ptr);
		UIntPtr GetUIntPtr();

		/// <summary>
		/// This is what's used to detach car parts, groupId is in the same order as groups are in the .oft file.
		/// Use tDoor->m_nGroupID for vehicle doors, haven't found a way to see the rest of the bones, or anything for other entity types other than guessing.
		/// </summary>
		/// <param name="groupId"></param>
		/// <returns></returns>
		phInstGta^ DetachFragmentGroup(uint32_t groupId);

		property UIntPtr UnkImportant {
			UIntPtr get()
			{
				return UIntPtr(InstGtaPointer->m_pUnkImportant);
			}
			void set(UIntPtr value)
			{
				if (value == UIntPtr::Zero)
					return;

				InstGtaPointer->m_pUnkImportant = (uint32_t*)value.ToPointer();
			}
		}

		property gtaFragType^ FragType {
			gtaFragType^ get()
			{
				Native_gtaFragType* ptr = InstGtaPointer->m_pFragType;

				if (ptr)
					return gcnew gtaFragType(ptr);

				return nullptr;
			}
		}

		property Native_phInstGta* InstGtaPointer {
			public:
				Native_phInstGta*	get() { return m_cNativeInstGta; }
				void				set(Native_phInstGta* value) { m_cNativeInstGta = value; }
		}

	private:
		Native_phInstGta* m_cNativeInstGta;
	};

}