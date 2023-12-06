#pragma once

namespace IVSDKDotNet
{
	public ref class IVFrontEnd
	{
	public:
		static property int32_t UserWaypointID
		{
		public:
			int32_t get()
			{
				return CFrontEnd::g_iUserWaypointID;
			}
			void set(int32_t value)
			{
				CFrontEnd::g_iUserWaypointID = value;
			}
		}
		static property Vector2 MapCursor
		{
		public:
			Vector2 get()
			{
				CVector2D vec = CFrontEnd::vMapCursor;
				return Vector2(vec.x, vec.y);
			}
			void set(Vector2 value)
			{
				CVector2D vec;
				vec.x = value.X;
				vec.y = value.Y;
				CFrontEnd::vMapCursor = vec;
			}
		}

	public:
		static void SwitchOnWaypoint(int unk_8, Vector2 pos, bool snapToHoveringBlip, [OutAttribute] Vector3% outPos);
		static void SwitchOnWaypoint(int unk_8, float x, float y, bool snapToHoveringBlip, [OutAttribute] Vector3% outPos);
		static void SwitchOffWaypoint();
		static void ToggleWaypoint();
	};
}