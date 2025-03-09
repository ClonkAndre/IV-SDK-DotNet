class CEpisodes
{
public:
	bool IsEpisodeAvailable(int episode)
	{
		return ((bool (__thiscall*)(CEpisodes*, int))(AddressSetter::Get("CEpisodes", "IsEpisodeAvailable")))(this, episode);
	}
};

static CEpisodes*& TheEpisodes = AddressSetter::GetRef<CEpisodes*>("CEpisodes", "TheEpisodes");