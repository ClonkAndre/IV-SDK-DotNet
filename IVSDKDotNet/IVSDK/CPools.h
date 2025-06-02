class CPed;
class CVehicle;
class CBuilding;
class CObject;
class CCam;
class CTask;
class CInteriorInst;
class CVehicleStructure;
class CPedMoveBlendOnFoot;
class CDummyPed;
class CDummyTask;
class tPedData;
class CPedIntelligenceNY;
class CAnimBlender;
class fragInstNMGta;
class CPedDataNY;
class CTxdFile;
struct TxdDef;
struct IplDef;
class CQuadTreeNode;
class CPedTargetting;

class CScriptStore;

class CPools
{
public:
	static inline auto& ms_pPedPool = AddressSetter::GetRef<CPool<CPed>*>("CPools", "ms_pPedPool");
	static inline auto& ms_pVehiclePool = AddressSetter::GetRef<CPool<CVehicle>*>("CPools", "ms_pVehiclePool");
	static inline auto& ms_pBuildingPool = AddressSetter::GetRef<CPool<CBuilding>*>("CPools", "ms_pBuildingPool");
	static inline auto& ms_pObjectPool = AddressSetter::GetRef<CPool<CObject>*>("CPools", "ms_pObjectPool");
	static inline auto& ms_pCameraPool = AddressSetter::GetRef<CPool<CCam>*>("CPools", "ms_pCameraPool");
	static inline auto& ms_pTaskPool = AddressSetter::GetRef<CPool<CTask>*>("CPools", "ms_pTaskPool");
	static inline auto& ms_pInteriorInstPool = AddressSetter::GetRef<CPool<CInteriorInst>*>("CPools", "ms_pInteriorInstPool");
	static inline auto& ms_pVehicleStructPool = AddressSetter::GetRef<CPool<CVehicleStructure>*>("CPools", "ms_pVehicleStructPool");
	static inline auto& ms_pPedMoveBlendPool = AddressSetter::GetRef<CPool<CPedMoveBlendOnFoot>*>("CPools", "ms_pPedMoveBlendPool");
	static inline auto& ms_pDummyPedPool = AddressSetter::GetRef<CPool<CDummyPed>*>("CPools", "ms_pDummyPedPool");
	static inline auto& ms_pDummyTaskPool = AddressSetter::GetRef<CPool<CDummyTask>*>("CPools", "ms_pDummyTaskPool");
	static inline auto& ms_pUnkPedDataPool = AddressSetter::GetRef<CPool<tPedData>*>("CPools", "ms_pUnkPedDataPool");
	static inline auto& ms_pPedIntelligencePool = AddressSetter::GetRef<CPool<CPedIntelligenceNY>*>("CPools", "ms_pPedIntelligencePool");
	static inline auto& ms_pAnimBlenderPool = AddressSetter::GetRef<CPool<CAnimBlender>*>("CPools", "ms_pAnimBlenderPool");
	static inline auto& ms_pFragInstNMGtaPool = AddressSetter::GetRef<CPool<fragInstNMGta>*>("CPools", "ms_pFragInstNMGtaPool");
	static inline auto& ms_pPedDataPool = AddressSetter::GetRef<CPool<CPedDataNY>*>("CPools", "ms_pPedDataPool");
	static inline auto& ms_pQuadTreeNodePool = AddressSetter::GetRef<CPool<CQuadTreeNode>*>("CPools", "ms_pQuadTreeNodePool");
	static inline auto& ms_pTxdPool = AddressSetter::GetRef<CPool<TxdDef>*>("CPools", "ms_pTxdPool");
	static inline auto& ms_pIplPool = AddressSetter::GetRef<CPool<IplDef>*>("CPools", "ms_pIplPool");
	static inline auto& ms_pPedTargettingPool = AddressSetter::GetRef<CPool<CPedTargetting>*>("CPools", "ms_pPedTargettingPool");

	static inline auto& ms_pScriptStorePool = AddressSetter::GetRef<CPool<CScriptStore>*>("CPools", "ms_pScriptStorePool");
};