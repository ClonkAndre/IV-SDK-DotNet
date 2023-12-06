#include "pch.h"
#include "IVQuadTreeNode.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVQuadTreeNode::IVQuadTreeNode(CQuadTreeNode* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeQuadTreeNode = nativePtr;
	}

	// - - - Methods / Functions - - -
	IVQuadTreeNode^ IVQuadTreeNode::Create(RectangleF rect, int levels)
	{
		CRect* nRect = new CRect();
		nRect->bottom = rect.Bottom;
		nRect->left = rect.X;
		nRect->right = rect.Right;
		nRect->top = rect.Y;

		CQuadTreeNode* ptr = new CQuadTreeNode(nRect, levels);
		
		delete nRect;
		NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);

		return gcnew IVQuadTreeNode(ptr);
	}

}