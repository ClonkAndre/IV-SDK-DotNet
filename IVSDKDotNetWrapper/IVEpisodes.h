#pragma once

namespace IVSDKDotNet
{
	public ref class IVEpisodes
	{
	public:
		static property IVEpisodes^ TheEpisodesManager
		{
		public:
			IVEpisodes^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(TheEpisodes, nullptr);
				return gcnew IVEpisodes(TheEpisodes);
			}
			void set(IVEpisodes^ value)
			{
				NULLPTR_CHECK(value);
				TheEpisodes = value->NativePtr;
			}
		}

	public:
		bool IsEpisodeAvailable(int episodeId);

	internal:
		IVEpisodes(CEpisodes* ptr);

	internal:
		CEpisodes* NativePtr;
	};
}