#include "pch.h"

namespace IVSDKDotNet
{
	namespace Native
	{
		/// <summary>
		/// This class gives you the possiblity to manually call native functions by their name.
		/// </summary>
		public ref class Function
		{
		internal:
			generic <typename T>
			static T ConvertResult(Object^ result)
			{
				if (!result)
					return T();

				Type^ resultType = result->GetType();
				Type^ targetType = T::typeid;

				// Convert result to Int32 (int)
				if (targetType == System::Int32::typeid
					&& resultType == System::UInt32::typeid)
					return (T)System::Int32::Parse(result->ToString());

				//// Convert result to UInt32 (uint)
				//if (targetType == System::UInt32::typeid)
				//	return safe_cast<T>(0);

				//// Convert result to Single (float)
				//if (targetType == System::Single::typeid)
				//	return safe_cast<T>(Convert::ToSingle(result));

				//// Convert result to Boolean (bool)
				//if (targetType == System::Boolean::typeid)
				//	return safe_cast<T>(Convert::ToBoolean(result));

				//// Convert result to String (string)
				//if (targetType == System::String::typeid)
				//	return safe_cast<T>(Convert::ToString(result));

				return T();
			}

		public:
			/// <summary>
			/// Calls a native function by name and returns the result the native returned.
			/// </summary>
			/// <typeparam name="T">The return type of the native.</typeparam>
			/// <param name="name">The name of the native function to call.</param>
			/// <param name="args">The arguments of the native function.</param>
			/// <returns>The result of the called native function.</returns>
			generic <typename T>
			static T Call(String^ name, ...array<Object^>^ args)
			{
				Type^ type = Natives::typeid;

				// Get all methods
				array<MethodInfo^>^ methodsArray = type->GetMethods(BindingFlags::Public | BindingFlags::Static);

				// Try to find method that match the name and argument count
				MethodInfo^ foundMethod = nullptr;

				for (int i = 0; i < methodsArray->Length; i++)
				{
					MethodInfo^ method = methodsArray[i];

					if (!method)
						continue;

					if (method->Name == name && method->GetParameters()->Length == args->Length)
					{
						foundMethod = method;
						break;
					}
				}

				// Invoke found method
				if (foundMethod)
				{
					// Convert given argument types to expected function types
					array<ParameterInfo^>^ methodParamaters = foundMethod->GetParameters();

					for (int i = 0; i < args->Length; i++)
					{
						Object^ arg = args[i];

						// If given arg is nullptr, this could mean that this is an out parameter
						if (!arg)
							continue;

						ParameterInfo^ methodParamInfo = methodParamaters[i];

						Type^ argType = arg->GetType();

						// Convert arg to Int32 (int)
						if (methodParamInfo->ParameterType == System::Int32::typeid && argType == System::UInt32::typeid)
							args[i] = Convert::ToInt32(arg);

						// Convert arg to UInt32 (uint)
						if (methodParamInfo->ParameterType == System::UInt32::typeid && argType == System::Int32::typeid)
							args[i] = Convert::ToUInt32(arg);

						// Convert arg to Boolean (bool)
						if (methodParamInfo->ParameterType == System::Boolean::typeid && Helper::IsNumericType(argType))
							args[i] = Convert::ToBoolean(arg);
					}

					Object^ n = foundMethod->Invoke(nullptr, args);
					//T res = (T)ConvertResult<T>(n);

					return (T)n;
				}

				return T();
			}

			/// <summary>
			/// Calls a native function by name.
			/// </summary>
			/// <param name="name">The name of the native function to call.</param>
			/// <param name="args">The arguments of the native function.</param>
			static void Call(String^ name, ...array<Object^>^ args)
			{
				Call<Object^>(name, args);
			}

		};
	}
}