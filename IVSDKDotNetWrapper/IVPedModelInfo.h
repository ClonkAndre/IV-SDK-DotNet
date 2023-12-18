#pragma once

namespace IVSDKDotNet
{
	public ref class IVPedModelInfo : IVBaseModelInfo
	{
	public:
		property int32_t GestureAnimIndex
		{
		public:
			int32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedModelInfo, 0);
				return NativePedModelInfo->m_nGestureAnimIndex;
			}
			void set(int32_t value)
			{
				NULLPTR_CHECK(NativePedModelInfo);
				NativePedModelInfo->m_nGestureAnimIndex = value;
			}
		}
		property int32_t FacialAnimIndex
		{
		public:
			int32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedModelInfo, 0);
				return NativePedModelInfo->m_nFacialAnimIndex;
			}
			void set(int32_t value)
			{
				NULLPTR_CHECK(NativePedModelInfo);
				NativePedModelInfo->m_nFacialAnimIndex = value;
			}
		}
		property int32_t VisemesAnimIndex
		{
		public:
			int32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedModelInfo, 0);
				return NativePedModelInfo->m_nVisemesAnimIndex;
			}
			void set(int32_t value)
			{
				NULLPTR_CHECK(NativePedModelInfo);
				NativePedModelInfo->m_nVisemesAnimIndex = value;
			}
		}
		property int32_t StreamedPed
		{
		public:
			int32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedModelInfo, 0);
				return NativePedModelInfo->m_bStreamedPed;
			}
			void set(int32_t value)
			{
				NULLPTR_CHECK(NativePedModelInfo);
				NativePedModelInfo->m_bStreamedPed = value;
			}
		}
		property uint32_t PedType
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedModelInfo, 0);
				return NativePedModelInfo->m_nPedType;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePedModelInfo);
				NativePedModelInfo->m_nPedType = value;
			}
		}
		property uint32_t VoiceHash
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedModelInfo, 0);
				return NativePedModelInfo->m_nVoiceHash;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePedModelInfo);
				NativePedModelInfo->m_nVoiceHash = value;
			}
		}

	internal:
		IVPedModelInfo(CPedModelInfo* nativePtr);

	internal:
		CPedModelInfo* NativePedModelInfo;
	};
}