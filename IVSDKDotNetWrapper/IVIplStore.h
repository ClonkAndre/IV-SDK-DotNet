#pragma once

namespace IVSDKDotNet
{
	public ref class IVIplStore
	{
	public:
		static property IVQuadTreeNode^ QuadTree
		{
		public:
			IVQuadTreeNode^ get()
			{
				CQuadTreeNode*& ptr = CIplStore::ms_pQuadTree;
				NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);
				return gcnew IVQuadTreeNode(ptr);
			}
			void set(IVQuadTreeNode^ value)
			{
				NULLPTR_CHECK(value);

				CQuadTreeNode*& ptr = CIplStore::ms_pQuadTree;
				NULLPTR_CHECK(ptr);

				ptr = value->NativeQuadTreeNode;
			}
		}
		// TODO: Add ms_pPool property here

		static property bool IplsNeededAtPosn
		{
		public:
			bool get()
			{
				return gbIplsNeededAtPosn;
			}
			void set(bool value)
			{
				gbIplsNeededAtPosn = value;
			}
		}
		static property Vector3 VecIplsNeededAtPosn
		{
		public:
			Vector3 get()
			{
				CVector& v = gvecIplsNeededAtPosn;
				return Vector3(v.x, v.y, v.z);
			}
			void set(Vector3 value)
			{
				CVector v;
				v.x = value.X;
				v.y = value.Y;
				v.z = value.Z;
				gvecIplsNeededAtPosn = v;
			}
		}

	public:
		static void LoadIpls(Vector3 pos, bool unk);
		static void SetIplsRequired(Vector3 pos);

		static void SetIfIplIsRequiredAtPos(Vector2 pos, UIntPtr def);
		static void SetIfIplIsRequiredAtPosReducedBB(Vector2 pos, UIntPtr def);
	};
}