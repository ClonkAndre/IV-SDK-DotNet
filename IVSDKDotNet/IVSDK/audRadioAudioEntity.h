class audRadioAudioEntity
{
public:
	uint8_t pad[0x6C];
	uint32_t m_nRadioState;
	uint32_t m_nRadioState2;
	uint8_t pad2[0x4];

	//uint8_t pad[0x78];								// 00-78

	uint32_t m_nCurrentRadioStationPriority;
	uint32_t m_nCurrentRadioStation;				// 78-7C
	uint32_t m_nStationIndex;
};
// VALIDATE_OFFSET(audRadioAudioEntity, m_nCurrentRadioStation, 0x78);

audRadioAudioEntity& RadioAudioEntity = AddressSetter::GetRef<audRadioAudioEntity>(0xDA3700, 0xD71F48);