#pragma once
#include "pch.h"

namespace IVSDKDotNet
{
	namespace Native
	{
		public value struct NativeArg
		{
		public:
			property System::Type^ Type
			{
			public:
				System::Type^ get()
				{
					return type;
				}
			}
			property Object^ Value
			{
			public:
				Object^ get()
				{
					return value;
				}
			}
			property bool IsOutArgument
			{
			public:
				bool get()
				{
					return isOutArgument;
				}
			}

		public:
			NativeArg(bool outArgument, System::Type^ argumentType)
			{
				type = argumentType;
				value = nullptr;
				isOutArgument = outArgument;
			}

		private:
			NativeArg(System::Type^ argumentType, Object^ v)
			{
				type = argumentType;
				value = v;
				isOutArgument = false;
			}

		public:
			void SetValue(Object^ value)
			{
				this->value = value;
			}

			generic <typename T>
			T GetValue()
			{
				if (!value)
					return T();

				return (T)value;
			}

			/// <summary>
			/// Unpoints this native arg if it was previously set as a out-argument (basically a pointer).
			/// </summary>
			/// <returns></returns>
			NativeArg Unpoint()
			{
				isOutArgument = false;
				return this;
			}

		public:
			static operator NativeArg (int value)
			{
				return NativeArg(int::typeid, value);
			}
			static operator NativeArg (uint32_t value)
			{
				return NativeArg(uint32_t::typeid, value);
			}
			static operator NativeArg (float value)
			{
				return NativeArg(float::typeid, value);
			}
			static operator NativeArg (double value)
			{
				return NativeArg(float::typeid, (float)value);
			}
			static operator NativeArg (bool value)
			{
				return NativeArg(bool::typeid, value);
			}
			static operator NativeArg (String^ value)
			{
				return NativeArg(String::typeid, value);
			}
			static operator NativeArg (Vector2 value)
			{
				return NativeArg(Vector2::typeid, value);
			}
			static operator NativeArg (Vector3 value)
			{
				return NativeArg(Vector3::typeid, value);
			}
			static operator NativeArg (Vector4 value)
			{
				return NativeArg(Vector4::typeid, value);
			}
			static operator NativeArg (Quaternion value)
			{
				return NativeArg(Quaternion::typeid, value);
			}

			static operator int(NativeArg source)
			{
				return source.GetValue<int>();
			}
			static operator uint32_t(NativeArg source)
			{
				return source.GetValue<uint32_t>();
			}
			static operator float(NativeArg source)
			{
				return source.GetValue<float>();
			}
			static operator double(NativeArg source)
			{
				return source.GetValue<float>();
			}
			static operator bool(NativeArg source)
			{
				return source.GetValue<bool>();
			}
			static operator String ^ (NativeArg source)
			{
				return source.GetValue<String^>();
			}

		private:
			System::Type^ type;
			Object^ value;
			bool isOutArgument;
		};
	}
}