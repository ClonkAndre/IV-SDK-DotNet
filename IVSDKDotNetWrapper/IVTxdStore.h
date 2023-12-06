#pragma once

namespace IVSDKDotNet
{
	public ref class IVTxdStore
	{
	public:
		static void AddRef(int slot);
		static int AddTxdSlot(String^ sName);
		static int FindTxdSlot(uint32_t nHash);
		static int FindTxdSlot(String^ sName);
		static bool LoadTxd(int slot, String^ sName);
		static void PushCurrentTxd();
		static void SetCurrentTxd(int slot);
		static void PopCurrentTxd();
		static IVSprite2D^ GetTexture(String^ sName);
	};
}