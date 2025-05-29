#include "pch.h"
#include "NativeFunction.h"

namespace IVSDKDotNet
{
	namespace Native
	{

		// ======================================================================
		// ============================= Function ===============================
		// ======================================================================
		void Function::Init()
		{
			if (natives)
				return;

			natives = gcnew Dictionary<uint32_t, List<MethodInfo^>^>();

			// Get all the methods within Natives class
			Type^ type = Natives::typeid;
			array<MethodInfo^>^ methodsArray = type->GetMethods(BindingFlags::Public | BindingFlags::Static);

			// Populate dict
			for (int i = 0; i < methodsArray->Length; i++)
			{
				MethodInfo^ method = methodsArray[i];

				if (!method)
					continue;

				System::String^ mName = method->Name->ToUpperInvariant(); // was ->ToLower() before

				if (mName->StartsWith("_"))
					mName = mName->Remove(0, 1);

				// Generate unique hash for this native for faster lookups
				uint32_t hash = RAGE::AtStringHash(mName);

				if (natives->ContainsKey(hash))
				{
					// Native with this hash was already added, must be an overload method
					natives[hash]->Add(method);
				}
				else
				{
					List<MethodInfo^>^ list = gcnew List<MethodInfo^>();
					list->Add(method);
					natives->Add(hash, list);
				}
			}
		}

		generic <typename T>
		T Function::ConvertResult(Object^ result)
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

		generic <typename T>
		T Function::Call(String^ name, ...array<Object^>^ args)
		{
			name = name->ToUpperInvariant()->Trim();

			// Generate unique hash for this native based on the name and parameter count for faster lookups
			uint32_t hash = RAGE::AtStringHash(name);

			// Check if native method exists
			if (!natives->ContainsKey(hash))
			{
				throw gcnew IVSDKDotNet::Exceptions::NativeNotFoundException(name);
			}

			// Get the found methods based on the hash
			List<MethodInfo^>^ foundMethods = natives[hash];

			// Now try to find the right method
			MethodInfo^ foundMethod = nullptr;

			// Only enter loop if there are more then 1 methods with the same name
			if (foundMethods->Count > 1)
			{
				for (int i = 0; i < foundMethods->Count; i++)
				{
					MethodInfo^ method = foundMethods[i];

					if (method->GetParameters()->Length == args->Length)
					{
						foundMethod = method;
						break;
					}
				}
			}
			else
			{
				// Just use the first method
				foundMethod = foundMethods[0];
			}

			//name = name->ToUpperInvariant(); // ->ToLower()

			//Type^ type = Natives::typeid;

			//// Get all methods
			//array<MethodInfo^>^ methodsArray = type->GetMethods(BindingFlags::Public | BindingFlags::Static);

			//// Try to find method that match the name and argument count
			//MethodInfo^ foundMethod = nullptr;

			//for (int i = 0; i < methodsArray->Length; i++)
			//{
			//	MethodInfo^ method = methodsArray[i];

			//	if (!method)
			//		continue;

			//	System::String^ mName = method->Name; // ->ToLower()

			//	if (mName->StartsWith("_"))
			//		mName = mName->Remove(0, 1);

			//	if (mName == name && method->GetParameters()->Length == args->Length)
			//	{
			//		foundMethod = method;
			//		break;
			//	}
			//}

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
					if (methodParamInfo->ParameterType == System::Int32::typeid
						&& (argType == System::UInt32::typeid || argType == System::Boolean::typeid))
						args[i] = Convert::ToInt32(arg);

					// Convert arg from float to Int32 (int)
					if (methodParamInfo->ParameterType == System::Int32::typeid
						&& argType == System::Single::typeid)
						args[i] = Convert::ToInt32(arg);

					// Convert arg from float to UInt32 (uint)
					if (methodParamInfo->ParameterType == System::UInt32::typeid
						&& argType == System::Single::typeid)
						args[i] = Convert::ToUInt32(arg);

					// Convert arg to UInt32 (uint)
					if (methodParamInfo->ParameterType == System::UInt32::typeid && argType == System::Int32::typeid)
						args[i] = Convert::ToUInt32(arg);

					// Convert arg to Boolean (bool)
					if (methodParamInfo->ParameterType == System::Boolean::typeid && Helper::IsNumericType(argType))
						args[i] = Convert::ToBoolean(arg);
				}

				// Resize array to the correct size if the given array is smaller then the expected parameter count
				if (args->Length < methodParamaters->Length)
				{
					Array::Resize(args, methodParamaters->Length);
				}

				Object^ n = foundMethod->Invoke(nullptr, args);
				//T res = (T)ConvertResult<T>(n);

				return (T)n;
			}
#if _DEBUG
			else
			{
				throw gcnew Exception("Could not find right native to call!");
			}
#endif // _DEBUG

			return T();
		}
		void Function::Call(String^ name, ...array<Object^>^ args)
		{
			Call<Object^>(name, args);
		}


		// ======================================================================
		// ============================ FunctionV2 ==============================
		// ======================================================================
		generic <typename T>
		T FunctionV2::Call(uint32_t hash, ...array<NativeArg>^ args)
		{
			return GetManagerScript()->CallNativeUsingManagedNativeCaller<T>(hash, args);
		}
		void FunctionV2::Call(uint32_t hash, ...array<NativeArg>^ args)
		{
			Call<uint32_t>(hash, args);
		}

		generic <typename T>
		T FunctionV2::Call(eNativeHash hash, ...array<NativeArg>^ args)
		{
			return Call<T>((uint32_t)hash, args);
		}
		void FunctionV2::Call(eNativeHash hash, ...array<NativeArg>^ args)
		{
			Call<uint32_t>((uint32_t)hash, args);
		}

	}
}