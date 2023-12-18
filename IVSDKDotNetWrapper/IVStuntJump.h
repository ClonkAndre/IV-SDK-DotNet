#pragma once

namespace IVSDKDotNet
{
	public ref class IVStuntJump
	{
	public:
		property IVBoundBox^ Start
		{
		public:
			IVBoundBox^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStuntJump, nullptr);
				return gcnew IVBoundBox(&NativeStuntJump->m_bbStart);
			}
			void set(IVBoundBox^ value)
			{
				NULLPTR_CHECK(NativeStuntJump);
				NULLPTR_CHECK(value);
				NativeStuntJump->m_bbStart = *value->NativeBoundBox;
			}
		}
		property IVBoundBox^ End
		{
		public:
			IVBoundBox^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStuntJump, nullptr);
				return gcnew IVBoundBox(&NativeStuntJump->m_bbEnd);
			}
			void set(IVBoundBox^ value)
			{
				NULLPTR_CHECK(NativeStuntJump);
				NULLPTR_CHECK(value);
				NativeStuntJump->m_bbEnd = *value->NativeBoundBox;
			}
		}
		property Vector3 CameraPos
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStuntJump, Vector3::Zero);
				CVector v = NativeStuntJump->m_vecCamera;
				return Vector3(v.x, v.y, v.z);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeStuntJump);
				
				CVector v;
				v.x = value.X;
				v.y = value.Y;
				v.z = value.Z;
				NativeStuntJump->m_vecCamera = v;
			}
		}
		property uint32_t Unk1
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStuntJump, 0);
				return NativeStuntJump->unk1;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeStuntJump);
				NativeStuntJump->unk1 = value;
			}
		}
		property uint32_t Score
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStuntJump, 0);
				return NativeStuntJump->m_iScore;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeStuntJump);
				NativeStuntJump->m_iScore = value;
			}
		}
		property bool Passed
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStuntJump, false);
				return NativeStuntJump->m_bPassed;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeStuntJump);
				NativeStuntJump->m_bPassed = value;
			}
		}
		property bool Found
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStuntJump, false);
				return NativeStuntJump->m_bFound;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeStuntJump);
				NativeStuntJump->m_bFound = value;
			}
		}

	internal:
		IVStuntJump(CStuntJump* nativePtr);

	internal:
		CStuntJump* NativeStuntJump;
	};
}