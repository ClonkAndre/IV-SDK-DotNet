class CVisibilityPlugins
{
public:
	static inline float& m_pedLodDistanceHigh = AddressSetter::GetRef<float>("CVisibilityPlugins", "m_pedLodDistanceHigh");
	static inline float& m_pedInCarLodDistanceHigh = AddressSetter::GetRef<float>("CVisibilityPlugins", "m_pedInCarLodDistanceHigh");
	static inline float& m_pedLodDistanceMed = AddressSetter::GetRef<float>("CVisibilityPlugins", "m_pedLodDistanceMed");
	static inline float& m_pedLodDistanceLow = AddressSetter::GetRef<float>("CVisibilityPlugins", "m_pedLodDistanceLow");
	static inline float& m_pedLodDistanceVlow = AddressSetter::GetRef<float>("CVisibilityPlugins", "m_pedLodDistanceVlow");
	static inline float& m_pedLodDistanceSlod = AddressSetter::GetRef<float>("CVisibilityPlugins", "m_pedLodDistanceSlod"); // all non-mission peds change their modelindex to superlod past this distance
	static inline float& m_carLodDistanceHigh = AddressSetter::GetRef<float>("CVisibilityPlugins", "m_carLodDistanceHigh");
	static inline float& m_carLodDistanceMed = AddressSetter::GetRef<float>("CVisibilityPlugins", "m_carLodDistanceMed");

	static inline char*& sStipplePath = AddressSetter::GetRef<char*>("CVisibilityPlugins", "sStipplePath"); // platform:/textures
};