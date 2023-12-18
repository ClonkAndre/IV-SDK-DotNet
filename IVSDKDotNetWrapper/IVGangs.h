#pragma once

namespace IVSDKDotNet
{
	public ref class IVGangs
	{
	public:
		static property array<IVGangInfo^>^ GangInfo
		{
		public:
			array<IVGangInfo^>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CGangs::Gang, nullptr);

				CGangInfo* ptr = CGangs::Gang;
				array<IVGangInfo^>^ arr = gcnew array<IVGangInfo^>(12);

				for (int i = 0; i < arr->Length; i++)
					arr[i] = gcnew IVGangInfo(&ptr[i]);

				return arr;
			}
			void set(array<IVGangInfo^>^ value)
			{
				NULLPTR_CHECK(CGangs::Gang);
				NULLPTR_CHECK(value);

				CGangInfo* ptr = CGangs::Gang;

				for (int i = 0; i < value->Length; i++)
					ptr[i] = *value[i]->NativeGangInfo;
			}
		}

	public:
		static bool Save();
		static bool Load();
	};
}