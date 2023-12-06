#pragma once

namespace IVSDKDotNet
{
	public ref class IVCheat
	{
	public:
		/// <summary>
		/// Gets or sets if the player has cheated.
		/// </summary>
		static property bool HasPlayerCheated
		{
		public:
			bool get()
			{
				return CCheat::m_bHasPlayerCheated;
			}
			void set(bool value)
			{
				CCheat::m_bHasPlayerCheated = value;
			}
		}
	};
}