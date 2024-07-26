#pragma once

namespace IVSDKDotNet
{
	public ref class IVPedFlags
	{
	public:
		property bool _f0
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._f0;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._f0 = value;
			}
		}
		property bool _f1
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._f1;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._f1 = value;
			}
		}
		property bool NoHeadshots
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags.bNoHeadshots;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags.bNoHeadshots = value;
			}
		}
		property bool _f3
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._f3;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._f3 = value;
			}
		}
		property bool _f4
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._f4;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._f4 = value;
			}
		}
		property bool _f5
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._f5;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._f5 = value;
			}
		}
		property bool _f6
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._f6;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._f6 = value;
			}
		}
		property bool _f7
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._f7;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._f7 = value;
			}
		}
		property bool _f8
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._f8;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._f8 = value;
			}
		}
		property bool _f9
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._f9;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._f9 = value;
			}
		}
		property bool _fa
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._fa;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._fa = value;
			}
		}
		property bool _fb
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._fb;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._fb = value;
			}
		}
		property bool _fc
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._fc;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._fc = value;
			}
		}
		property bool _fd
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._fd;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._fd = value;
			}
		}
		property bool _fe
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._fe;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._fe = value;
			}
		}
		property bool _ff
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._ff;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._ff = value;
			}
		}
		property bool _f10
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._f10;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._f10 = value;
			}
		}
		property bool _f11
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._f11;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._f11 = value;
			}
		}
		property bool _f12
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._f12;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._f12 = value;
			}
		}
		property bool _f13
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._f13;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._f13 = value;
			}
		}
		property bool _f14
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._f14;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._f14 = value;
			}
		}
		property bool _f15
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._f15;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._f15 = value;
			}
		}
		property bool _f16
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._f16;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._f16 = value;
			}
		}
		property bool _f17
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._f17;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._f17 = value;
			}
		}
		property bool _f18
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._f18;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._f18 = value;
			}
		}
		property bool _f19
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._f19;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._f19 = value;
			}
		}
		property bool _f1a
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._f1a;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._f1a = value;
			}
		}
		property bool _f1b
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._f1b;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._f1b = value;
			}
		}
		property bool _f1c
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._f1c;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._f1c = value;
			}
		}
		property bool _f1d
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._f1d;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._f1d = value;
			}
		}
		property bool _f1e
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._f1e;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._f1e = value;
			}
		}
		property bool _f1f
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags._f1f;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags._f1f = value;
			}
		}

	internal:
		IVPedFlags(CPed* nativePtr)
		{
			NativePed = nativePtr;
		}

	internal:
		CPed* NativePed;
	};
	public ref class IVPedFlags2
	{
	public:
		property bool _f0
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._f0;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._f0 = value;
			}
		}
		property bool _f1
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._f1;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._f1 = value;
			}
		}
		property bool _f2
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._f2;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._f2 = value;
			}
		}
		property bool _f3
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._f3;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._f3 = value;
			}
		}
		property bool _f4
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._f4;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._f4 = value;
			}
		}
		property bool _f5
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._f5;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._f5 = value;
			}
		}
		property bool _f6
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._f6;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._f6 = value;
			}
		}
		property bool _f7
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._f7;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._f7 = value;
			}
		}
		property bool WillFlyThroughWindscreen
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2.bWillFlyThroughWindscreen;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2.bWillFlyThroughWindscreen = value;
			}
		}
		property bool _f9
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._f9;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._f9 = value;
			}
		}
		property bool _fa
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._fa;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._fa = value;
			}
		}
		property bool _fb
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._fb;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._fb = value;
			}
		}
		property bool _fc
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._fc;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._fc = value;
			}
		}
		property bool _fd
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._fd;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._fd = value;
			}
		}
		property bool _fe
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._fe;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._fe = value;
			}
		}
		property bool _ff
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._ff;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._ff = value;
			}
		}
		property bool _f10
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._f10;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._f10 = value;
			}
		}
		property bool _f11
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._f11;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._f11 = value;
			}
		}
		property bool _f12
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._f12;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._f12 = value;
			}
		}
		property bool _f13
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._f13;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._f13 = value;
			}
		}
		property bool _f14
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._f14;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._f14 = value;
			}
		}
		property bool _f15
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._f15;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._f15 = value;
			}
		}
		property bool _f16
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._f16;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._f16 = value;
			}
		}
		property bool _f17
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._f17;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._f17 = value;
			}
		}
		property bool _f18
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._f18;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._f18 = value;
			}
		}
		property bool _f19
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._f19;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._f19 = value;
			}
		}
		property bool _f1a
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._f1a;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._f1a = value;
			}
		}
		property bool _f1b
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._f1b;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._f1b = value;
			}
		}
		property bool _f1c
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._f1c;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._f1c = value;
			}
		}
		property bool _f1d
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._f1d;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._f1d = value;
			}
		}
		property bool _f1e
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._f1e;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._f1e = value;
			}
		}
		property bool _f1f
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags2._f1f;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags2._f1f = value;
			}
		}

	internal:
		IVPedFlags2(CPed* nativePtr)
		{
			NativePed = nativePtr;
		}

	internal:
		CPed* NativePed;
	};
	public ref class IVPedFlags3
	{
	public:
		property bool _f0
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._f0;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._f0 = value;
			}
		}
		property bool _f1
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._f1;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._f1 = value;
			}
		}
		property bool _f2
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._f2;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._f2 = value;
			}
		}
		property bool InCar
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3.bInCar;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3.bInCar = value;
			}
		}
		property bool _f4
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._f4;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._f4 = value;
			}
		}
		property bool _f5
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._f5;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._f5 = value;
			}
		}
		property bool _f6
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._f6;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._f6 = value;
			}
		}
		property bool _f7
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._f7;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._f7 = value;
			}
		}
		property bool _f8
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._f8;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._f8 = value;
			}
		}
		property bool _f9
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._f9;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._f9 = value;
			}
		}
		property bool _fa
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._fa;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._fa = value;
			}
		}
		property bool _fb
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._fb;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._fb = value;
			}
		}
		property bool _fc
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._fc;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._fc = value;
			}
		}
		property bool InAir
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3.bInAir;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3.bInAir = value;
			}
		}
		property bool _fe
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._fe;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._fe = value;
			}
		}
		property bool _ff
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._ff;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._ff = value;
			}
		}
		property bool _f10
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._f10;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._f10 = value;
			}
		}
		property bool _f11
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._f11;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._f11 = value;
			}
		}
		property bool _f12
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._f12;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._f12 = value;
			}
		}
		property bool _f13
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._f13;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._f13 = value;
			}
		}
		property bool _f14
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._f14;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._f14 = value;
			}
		}
		property bool _f15
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._f15;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._f15 = value;
			}
		}
		property bool _f16
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._f16;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._f16 = value;
			}
		}
		property bool _f17
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._f17;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._f17 = value;
			}
		}
		property bool _f18
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._f18;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._f18 = value;
			}
		}
		property bool _f19
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._f19;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._f19 = value;
			}
		}
		property bool _f1a
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._f1a;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._f1a = value;
			}
		}
		property bool _f1b
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._f1b;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._f1b = value;
			}
		}
		property bool _f1c
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._f1c;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._f1c = value;
			}
		}
		property bool _f1d
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._f1d;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._f1d = value;
			}
		}
		property bool _f1e
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._f1e;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._f1e = value;
			}
		}
		property bool _f1f
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_nPedFlags3._f1f;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPedFlags3._f1f = value;
			}
		}

	internal:
		IVPedFlags3(CPed* nativePtr)
		{
			NativePed = nativePtr;
		}

	internal:
		CPed* NativePed;
	};

	public ref class IVPed : IVPhysical
	{
	public:
		property bool Dead
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_bDead;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_bDead = value;
			}
		}
		property bool Injured
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_bInjured;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_bInjured = value;
			}
		}
		property bool FatallyInjured
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_bFatallyInjured;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_bFatallyInjured = value;
			}
		}
		property uint8_t pad1
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0);
				return NativePed->pad1;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->pad1 = value;
			}
		}
		property float PedHealth
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0.0F);
				return NativePed->m_fPedHealth;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_fPedHealth = value;
			}
		}
		property uint8_t PlayerIndex
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0);
				return NativePed->m_nPlayerIndex;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nPlayerIndex = value;
			}
		}
		property bool IsPlayer
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, false);
				return NativePed->m_bIsPlayer;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_bIsPlayer = value;
			}
		}
		property IVPedDrawableInfo^ DrawableInfo
		{
		public:
			IVPedDrawableInfo^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativePed->m_pDrawableInfo, nullptr);
				return gcnew IVPedDrawableInfo(NativePed->m_pDrawableInfo);
			}
			void set(IVPedDrawableInfo^ value)
			{
				NULLPTR_CHECK(NativePed);
				NULLPTR_CHECK(value);
				NativePed->m_pDrawableInfo = value->NativePedDrawableInfo;
			}
		}
		property UIntPtr PedIntelligence
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativePed->m_pPedIntelligence, UIntPtr::Zero);
				return UIntPtr(NativePed->m_pPedIntelligence);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativePed);
				UINTPTR_ZERO_CHECK(value);
				NativePed->m_pPedIntelligence = (CPedIntelligenceNY*)value.ToPointer();
			}
		}
		property IVPlayerInfo^ PlayerInfo
		{
		public:
			IVPlayerInfo^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativePed->m_pPlayerInfo, nullptr);
				return gcnew IVPlayerInfo(NativePed->m_pPlayerInfo);
			}
			void set(IVPlayerInfo^ value)
			{
				NULLPTR_CHECK(NativePed);
				NULLPTR_CHECK(value);
				NativePed->m_pPlayerInfo = value->NativePlayerInfo;
			}
		}
		property UIntPtr PedData
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativePed->m_pPedData, UIntPtr::Zero);
				return UIntPtr(NativePed->m_pPedData);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativePed);
				UINTPTR_ZERO_CHECK(value);
				NativePed->m_pPedData = (CPedDataNY*)value.ToPointer();
			}
		}

		property IVPedFlags^ PedFlags
		{
		public:
			IVPedFlags^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, nullptr);
				return gcnew IVPedFlags(NativePed);
			}
		}
		property IVPedFlags2^ PedFlags2
		{
		public:
			IVPedFlags2^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, nullptr);
				return gcnew IVPedFlags2(NativePed);
			}
		}
		property IVPedFlags3^ PedFlags3
		{
		public:
			IVPedFlags3^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, nullptr);
				return gcnew IVPedFlags3(NativePed);
			}
		}

		property float ClimbAnimRate
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0.0F);
				return NativePed->m_fClimbAnimRate;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_fClimbAnimRate = value;
			}
		}
		property IVPedWeapons^ WeaponData
		{
		public:
			IVPedWeapons^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, nullptr);
				return gcnew IVPedWeapons(&NativePed->m_pWeaponData);
			}
		}
		property uint8_t ShootRate
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0);
				return NativePed->m_nShootRate;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nShootRate = value;
			}
		}
		property uint8_t Accuracy
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0);
				return NativePed->m_nAccuracy;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nAccuracy = value;
			}
		}
		property IVEntity^ StandingOnEntity
		{
		public:
			IVEntity^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativePed->m_pStandingOnEntity, nullptr);
				return gcnew IVEntity(NativePed->m_pStandingOnEntity);
			}
			void set(IVEntity^ value)
			{
				NULLPTR_CHECK(NativePed);
				NULLPTR_CHECK(value);
				NativePed->m_pStandingOnEntity = value->NativeEntity;
			}
		}
		property uint32_t VoiceHash
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0);
				return NativePed->m_nVoiceHash;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nVoiceHash = value;
			}
		}
		property UIntPtr Collider
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativePed->m_pCollider, UIntPtr::Zero);
				return UIntPtr(NativePed->m_pCollider);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativePed);
				UINTPTR_ZERO_CHECK(value);
				NativePed->m_pCollider = (rage::phConstrainedCollider*)value.ToPointer();
			}
		}
		property uint32_t RagdollStatus
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0);
				return NativePed->m_nRagdollStatus;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nRagdollStatus = value;
			}
		}
		property uint32_t RagdollTime
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0);
				return NativePed->m_nRagdollTime;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nRagdollTime = value;
			}
		}

		property uint8_t WeaponObjectVisible
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0);
				return NativePed->m_nWeaponObjectVisible;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nWeaponObjectVisible = value;
			}
		}

		property uint8_t CreatedBy
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0);
				return NativePed->m_nCreatedBy;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nCreatedBy = value;
			}
		}
		property uint32_t DeathState
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0);
				return NativePed->m_nDeathState;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nDeathState = value;
			}
		}
		property IVPedMoveBlendOnFoot^ PedMoveBlendOnFoot
		{
		public:
			IVPedMoveBlendOnFoot^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativePed->m_pPedMoveBlendOnFoot, nullptr);
				return gcnew IVPedMoveBlendOnFoot(NativePed->m_pPedMoveBlendOnFoot);
			}
			void set(IVPedMoveBlendOnFoot^ value)
			{
				NULLPTR_CHECK(NativePed);
				NULLPTR_CHECK(value);
				NativePed->m_pPedMoveBlendOnFoot = value->NativePedMoveBlendOnFoot;
			}
		}
		property float MaxHealth
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0.0F);
				return NativePed->m_fMaxHealth;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_fMaxHealth = value;
			}
		}
		property float CurrentHeading
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0.0F);
				return NativePed->m_fCurrentHeading;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_fCurrentHeading = value;
			}
		}
		property float DesiredHeading
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0.0F);
				return NativePed->m_fDesiredHeading;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_fDesiredHeading = value;
			}
		}
		property UIntPtr Vehicle
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativePed->m_pVehicle, UIntPtr::Zero);
				return UIntPtr(NativePed->m_pVehicle);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativePed);
				UINTPTR_ZERO_CHECK(value);
				NativePed->m_pVehicle = (CVehicle*)value.ToPointer();
			}
		}
		property uint32_t UnkPlayerSettingsRelated
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, 0);
				return NativePed->m_nUnkPlayerSettingsRelated;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePed);
				NativePed->m_nUnkPlayerSettingsRelated = value;
			}
		}
		property IVPedComponentModels^ ComponentModels
		{
		public:
			IVPedComponentModels^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePed, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativePed->m_pComponentModels, nullptr);
				return gcnew IVPedComponentModels(NativePed->m_pComponentModels);
			}
			void set(IVPedComponentModels^ value)
			{
				NULLPTR_CHECK(NativePed);
				NULLPTR_CHECK(value);
				NativePed->m_pComponentModels = value->NativePedComponentModels;
			}
		}

	public:
		static IVPed^ FromUIntPtr(UIntPtr ptr);
		UIntPtr GetUIntPtr();

		void ProcessWeaponSwitch();
		IVPad^ GetPadFromPlayer();
		UIntPtr GetVehicle();
		void SetHealth(float health, int unk);
		void AddHealth(float health);
		void ProcessHeading();

	internal:
		IVPed(CPed* nativePtr);

	internal:
		CPed* NativePed;
	};
}