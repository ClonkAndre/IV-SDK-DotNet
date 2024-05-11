#pragma once

namespace IVSDKDotNet
{
	public ref class IVVehicleWheelFlags
	{
	public:
		/// <summary>
		/// False if in air.
		/// </summary>
		property bool SpringsAreActive
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags.bSpringsAreActive;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags.bSpringsAreActive = value;
			}
		}
		/// <summary>
		/// False if in air.
		/// </summary>
		property bool NotInAir
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags.bNotInAir;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags.bNotInAir = value;
			}
		}
		property bool GasPedalPressed
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags.bGasPedalPressed;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags.bGasPedalPressed = value;
			}
		}
		property bool WheelOnFire
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags.bWheelOnFire;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags.bWheelOnFire = value;
			}
		}
		property bool _f4
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags._f4;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags._f4 = value;
			}
		}
		property bool _f5
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags._f5;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags._f5 = value;
			}
		}
		property bool _f6
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags._f6;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags._f6 = value;
			}
		}
		property bool _f7
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags._f7;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags._f7 = value;
			}
		}
		property bool _f8
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags._f8;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags._f8 = value;
			}
		}
		property bool _f9
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags._f9;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags._f9 = value;
			}
		}
		property bool _fa
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags._fa;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags._fa = value;
			}
		}
		property bool _fb
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags._fb;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags._fb = value;
			}
		}
		/// <summary>
		/// This can make a double track for the front wheel and turn it off for the rear. Also if == false the handbrake for this wheel does not work
		/// </summary>
		property bool IsRearWheel
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags.bIsRearWheel;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags.bIsRearWheel = value;
			}
		}
		property bool FrontWheelSteer
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags.bFrontWheelSteer;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags.bFrontWheelSteer = value;
			}
		}
		property bool RearWheelSteer
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags.bRearWheelSteer;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags.bRearWheelSteer = value;
			}
		}
		property bool DriveWheel
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags.bDriveWheel;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags.bDriveWheel = value;
			}
		}
		/// <summary>
		/// False for wheels that have an axle (transmission_f, transmission_r or transmission_m).
		/// </summary>
		property bool RightWheelSuspension
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags.bRightWheelSuspension;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags.bRightWheelSuspension = value;
			}
		}
		/// <summary>
		/// False for wheels that have an axle (transmission_f, transmission_r or transmission_m).
		/// </summary>
		property bool LeftWheelSuspension
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags.bLeftWheelSuspension;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags.bLeftWheelSuspension = value;
			}
		}
		property bool _f12
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags._f12;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags._f12 = value;
			}
		}
		property bool _f13
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags._f13;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags._f13 = value;
			}
		}
		property bool _f14
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags._f14;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags._f14 = value;
			}
		}
		property bool _f15
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags._f15;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags._f15 = value;
			}
		}
		property bool MirrorWheel
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags.bMirrorWheel;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags.bMirrorWheel = value;
			}
		}
		property bool _f17
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags._f17;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags._f17 = value;
			}
		}
		/// <summary>
		/// For example, the rear wheel airtug is larger than the front.
		/// </summary>
		property bool ScaleWheelByCollision
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags.bScaleWheelByCollision;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags.bScaleWheelByCollision = value;
			}
		}
		property bool _f19
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags._f19;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags._f19 = value;
			}
		}
		property bool RaiseSuspension1
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags.bRaiseSuspension1;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags.bRaiseSuspension1 = value;
			}
		}
		property bool RaiseSuspension2
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags.bRaiseSuspension2;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags.bRaiseSuspension2 = value;
			}
		}
		property bool _f1c
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags._f1c;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags._f1c = value;
			}
		}
		property bool _f1d
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags._f1d;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags._f1d = value;
			}
		}
		property bool _f1e
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags._f1e;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags._f1e = value;
			}
		}
		property bool _f1f
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, false);
				return NativeVehicleWheel->m_nFlags._f1f;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nFlags._f1f = value;
			}
		}

	internal:
		IVVehicleWheelFlags(CVehicleWheel* nativePtr);

	internal:
		CVehicleWheel* NativeVehicleWheel;
	};

	public ref class IVVehicleWheel
	{
	public:
		/// <summary>
		/// In the order from IVVehicleStruct.
		/// </summary>
		property uint32_t BoneID
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0);
				return NativeVehicleWheel->m_nBoneID;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nBoneID = value;
			}
		}
		/// <summary>
		/// Group for detach, needs to be higher than 0.
		/// </summary>
		property uint16_t GroupID
		{
		public:
			uint16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0);
				return NativeVehicleWheel->m_nGroupID;
			}
			void set(uint16_t value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_nGroupID = value;
			}
		}
		property uint16_t pad
		{
		public:
			uint16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0);
				return NativeVehicleWheel->pad;
			}
			void set(uint16_t value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->pad = value;
			}
		}
		property float Radius
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->m_fRadius;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_fRadius = value;
			}
		}
		/// <summary>
		/// From veh.ide.
		/// </summary>
		property float DiscRadius
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->m_fDiscRadius;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_fDiscRadius = value;
			}
		}
		/// <summary>
		/// Margin or AABB * 2.
		/// </summary>
		property float Margin
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->m_fMargin;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_fMargin = value;
			}
		}
		property uint32_t _f14
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0);
				return NativeVehicleWheel->_f14;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f14 = value;
			}
		}
		/// <summary>
		/// Same values ​​for l and r wheels.
		/// </summary>
		property float _f18
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f18;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f18 = value;
			}
		}
		/// <summary>
		/// CurvedEdges unk_F?
		/// </summary>
		property float _f1c
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f1c;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f1c = value;
			}
		}
		/// <summary>
		/// Z for suspension?
		/// </summary>
		property float _f20
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f20;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f20 = value;
			}
		}
		/// <summary>
		/// Has to do with suspension or wheel stability.
		/// </summary>
		property float _f24
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f24;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f24 = value;
			}
		}
		/// <summary>
		/// Same values ​​for l and r wheels.
		/// </summary>
		property float _f28
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f28;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f28 = value;
			}
		}
		property float _f2c
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f2c;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f2c = value;
			}
		}
		property Vector3 MatrixRight
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, Vector3::Zero);
				return CVectorPadToVector(NativeVehicleWheel->matrix_right);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->matrix_right = VectorToCVectorPad(value);
			}
		}
		property Vector3 MatrixAt
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, Vector3::Zero);
				return CVectorPadToVector(NativeVehicleWheel->matrix_at);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->matrix_at = VectorToCVectorPad(value);
			}
		}
		/// <summary>
		/// Duplicates position.
		/// </summary>
		property Vector3 _f50
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, Vector3::Zero);
				return CVectorToVector(NativeVehicleWheel->_f50);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f50 = VectorToCVector(value);
			}
		}
		property uint32_t _f5c
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0);
				return NativeVehicleWheel->_f5c;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f5c = value;
			}
		}
		property Vector3 Position
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, Vector3::Zero);
				return CVectorToVector(NativeVehicleWheel->m_vPosition);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_vPosition = VectorToCVector(value);
			}
		}
		property uint32_t _f6c
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0);
				return NativeVehicleWheel->_f6c;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f6c = value;
			}
		}
		property float _f70
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f70;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f70 = value;
			}
		}
		property float _f74
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f74;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f74 = value;
			}
		}
		/// <summary>
		/// z position? y angle?
		/// </summary>
		property float _f78
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f78;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f78 = value;
			}
		}
		property float RotationX
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->m_fRotationX;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_fRotationX = value;
			}
		}
		property float Speed
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->m_fSpeed;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_fSpeed = value;
			}
		}
		/// <summary>
		/// Duplicate.
		/// </summary>
		property float Speed2
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->m_fSpeed2;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_fSpeed2 = value;
			}
		}
		/// <summary>
		/// Has to do with wheel speed.
		/// </summary>
		property float _f88
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f88;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f88 = value;
			}
		}
		property Vector3 _f90
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, Vector3::Zero);
				return CVectorPadToVector(NativeVehicleWheel->_f90);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f90 = VectorToCVectorPad(value);
			}
		}
		property Vector3 _fa0
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, Vector3::Zero);
				return CVectorPadToVector(NativeVehicleWheel->_fa0);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_fa0 = VectorToCVectorPad(value);
			}
		}
		property Vector3 _fb0
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, Vector3::Zero);
				return CVectorPadToVector(NativeVehicleWheel->_fb0);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_fb0 = VectorToCVectorPad(value);
			}
		}
		property float _fc8
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_fc8;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_fc8 = value;
			}
		}
		property float _fe0
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_fe0;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_fe0 = value;
			}
		}
		property float _fe4
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_fe4;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_fe4 = value;
			}
		}
		/// <summary>
		/// Has to do with suspension. 0 if the wheel is in the air.
		/// </summary>
		property float _ff0
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_ff0;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_ff0 = value;
			}
		}
		/// <summary>
		/// Has to do with suspension. 0 if the wheel is in the air.
		/// </summary>
		property float _ff4
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_ff4;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_ff4 = value;
			}
		}
		/// <summary>
		/// Has to do with suspension. 0 if the wheel is in the air.
		/// </summary>
		property float _ff8
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_ff8;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_ff8 = value;
			}
		}
		property uint32_t _ffc
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0);
				return NativeVehicleWheel->_ffc;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_ffc = value;
			}
		}
		property float _f100
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f100;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f100 = value;
			}
		}
		property float _f104
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f104;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f104 = value;
			}
		}
		/// <summary>
		/// Has to do with suspension. 0 if the wheel is in the air.
		/// </summary>
		property float _f108
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f108;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f108 = value;
			}
		}
		/// <summary>
		/// Has to do with suspension. 0 if the wheel is in the air.
		/// </summary>
		property float _f10c
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f10c;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f10c = value;
			}
		}
		/// <summary>
		/// Has to do with suspension. 0 if the wheel is in the air.
		/// </summary>
		property float _f110
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f110;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f110 = value;
			}
		}
		property float _f114
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f114;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f114 = value;
			}
		}
		property float _f118
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f118;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f118 = value;
			}
		}
		/// <summary>
		/// Always -1.
		/// </summary>
		property float _f11c
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f11c;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f11c = value;
			}
		}
		property float _f120
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f120;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f120 = value;
			}
		}
		property float _f124
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f124;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f124 = value;
			}
		}
		property float TrackIntensity
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->m_fTrackIntensity;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_fTrackIntensity = value;
			}
		}
		/// <summary>
		/// Brake mult?
		/// </summary>
		property float _f134
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f134;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f134 = value;
			}
		}
		/// <summary>
		/// Related to wheel steering.
		/// </summary>
		property float _f138
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f138;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f138 = value;
			}
		}
		/// <summary>
		/// Rotation in z-axis.
		/// </summary>
		property float RotationZ
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->m_fRotationZ;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_fRotationZ = value;
			}
		}
		property float _f140
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f140;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f140 = value;
			}
		}
		property float _f144
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f144;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f144 = value;
			}
		}
		property float _f148
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f148;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f148 = value;
			}
		}
		property float RotationZ2
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->m_fRotationZ2;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_fRotationZ2 = value;
			}
		}
		property float _f150
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f150;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f150 = value;
			}
		}
		property float _f154
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f154;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f154 = value;
			}
		}
		property float _f158
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->_f158;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->_f158 = value;
			}
		}
		property float Health
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->m_fHealth;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_fHealth = value;
			}
		}
		property float TireHealth
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, 0.0F);
				return NativeVehicleWheel->m_fTireHealth;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeVehicleWheel);
				NativeVehicleWheel->m_fTireHealth = value;
			}
		}
		property IVVehicleWheelFlags^ Flags
		{
		public:
			IVVehicleWheelFlags^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleWheel, nullptr);
				return gcnew IVVehicleWheelFlags(NativeVehicleWheel);
			}
		}

	internal:
		IVVehicleWheel(CVehicleWheel* nativePtr);

	internal:
		CVehicleWheel* NativeVehicleWheel;
	};
}