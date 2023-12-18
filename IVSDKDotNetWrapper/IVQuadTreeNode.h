#pragma once

namespace IVSDKDotNet
{
	public ref class IVQuadTreeNode
	{
	public:
		property RectangleF Rect
		{
		public:
			RectangleF get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeQuadTreeNode, RectangleF::Empty);

				CRect nRect = NativeQuadTreeNode->m_sRect;
				return RectangleF(nRect.left, nRect.top, nRect.right, nRect.bottom);
			}
			void set(RectangleF value)
			{
				NULLPTR_CHECK(NativeQuadTreeNode);

				CRect nRect;
				nRect.bottom = value.Bottom;
				nRect.left = value.X;
				nRect.right = value.Right;
				nRect.top = value.Y;
				NativeQuadTreeNode->m_sRect = nRect;
			}
		}
		property UIntPtr ItemList
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeQuadTreeNode, UIntPtr::Zero);
				return UIntPtr(NativeQuadTreeNode->m_pItemList);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativeQuadTreeNode);
				UINTPTR_ZERO_CHECK(value);
				NativeQuadTreeNode->m_pItemList = (uint32_t*)value.ToPointer();
			}
		}
		property array<IVQuadTreeNode^>^ Children
		{
		public:
			array<IVQuadTreeNode^>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeQuadTreeNode, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativeQuadTreeNode->m_pChildren, nullptr);
				
				array<IVQuadTreeNode^>^ arr = gcnew array<IVQuadTreeNode^>(4);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = gcnew IVQuadTreeNode(NativeQuadTreeNode->m_pChildren[i]);

				return arr;
			}
			void set(array<IVQuadTreeNode^>^ value)
			{
				NULLPTR_CHECK(NativeQuadTreeNode);
				NULLPTR_CHECK(NativeQuadTreeNode->m_pChildren);
				NULLPTR_CHECK(value);

				for(int i = 0; i < value->Length; i++)
					NativeQuadTreeNode->m_pChildren[i] = value[i]->NativeQuadTreeNode;
			}
		}
		property uint32_t Level
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeQuadTreeNode, 0);
				return NativeQuadTreeNode->m_nLevel;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeQuadTreeNode);
				NativeQuadTreeNode->m_nLevel = value;
			}
		}

	public:
		static IVQuadTreeNode^ Create(RectangleF rect, int levels);

	internal:
		IVQuadTreeNode(CQuadTreeNode* nativePtr);

	internal:
		CQuadTreeNode* NativeQuadTreeNode;
	};
}