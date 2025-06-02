class CControlledByInfo
{
public:
	CControlledByInfo(bool isNetwork, bool isPlayer)
		:
		m_isControlledByNetwork(isNetwork),
		m_isPlayer(isPlayer)
	{
		;
	}
	CControlledByInfo(const CControlledByInfo& rhs)
		:
		m_isControlledByNetwork(rhs.m_isControlledByNetwork),
		m_isPlayer(rhs.m_isPlayer)
	{
		;
	}

	void Set(const CControlledByInfo& rhs)
	{
		m_isControlledByNetwork = rhs.m_isControlledByNetwork;
		m_isPlayer = rhs.m_isPlayer;
	}

	bool IsControlledByNetwork() const
	{
		return m_isControlledByNetwork;
	}
	bool IsControlledByLocalAi() const
	{
		return (!m_isControlledByNetwork && !m_isPlayer);
	}
	bool IsControlledByNetworkAi() const
	{
		return (m_isControlledByNetwork && !m_isPlayer);
	}
	bool IsControlledByLocalOrNetworkAi() const
	{
		return !m_isPlayer;
	}
	bool IsControlledByLocalPlayer() const
	{
		return (!m_isControlledByNetwork && m_isPlayer);
	}
	bool IsControlledByNetworkPlayer()	 const
	{
		return (m_isControlledByNetwork && m_isPlayer);
	}
	bool IsControlledByLocalOrNetworkPlayer() const
	{
		return m_isPlayer;
	}

public:
	bool m_isControlledByNetwork;
	bool m_isPlayer;
};

class CPedFactory
{
public:
	int DeletePed(CPed* ped)
	{
		return ((int(__thiscall*)(CPedFactory*, CPed*))(*(void***)this)[3])(this, ped);
	}
	CPed* CreatePed(CControlledByInfo* pSpawnData, int32_t model, CMatrix* mat, bool bNetwork, bool bUnk1)
	{
		return ((CPed * (__thiscall*)(CPedFactory*, CControlledByInfo*, int32_t, CMatrix*, bool, bool))(*(void***)this)[5])(this, pSpawnData, model, mat, bNetwork, bUnk1);
	}

};
class CPedFactoryNY : public CPedFactory
{
public:

};

CPedFactoryNY*& PedFactory = AddressSetter::GetRef<CPedFactoryNY*>("CPedFactory", "PedFactory");