class CEpisodes
{
public:
	bool IsEpisodeAvailable(int episode)
	{
		return ((bool (__thiscall*)(CEpisodes*, int))(AddressSetter::Get(0x414810, 0x490970)))(this, episode);
	}
};

static CEpisodes*& TheEpisodes = AddressSetter::GetRef<CEpisodes*>(0x15AB8F0, 0x15CE57C);