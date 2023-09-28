namespace IVSDKDotNetAPI
{

    internal enum RemoteMessageID : ushort
    {
        // Manager
        Manager_ReloadScriptsRequest = 1,
        Manager_ReloadScriptsResponse,

        Manager_LoadScriptRequest,
        Manager_LoadScriptResponse,

        Manager_AbortScriptRequest,
        Manager_AbortScriptResponse,

        Manager_GetActiveScriptsInfoRequest,
        Manager_GetActiveScriptsInfoResponse,

        Manager_GetActiveScriptsCountRequest,
        Manager_GetActiveScriptsCountResponse,

        Manager_IsScriptRunningRequest,
        Manager_IsScriptRunningResponse,

        // Game
        Game_GetSessionInfoRequest,
        Game_GetSessionInfoResponse,

        Game_CallNativeRequest,
        Game_CallNativeResponse,
    }

    public enum IVGameMode
    {
        None = -1,
        Deathmatch = 0,
        TeamDeathmatch = 1,
        MafiyaWork = 2,
        TeamMafiyaWork = 3,
        TeamCarJackCity = 4,
        CarJackCity = 5,
        Race = 6,
        GTARace = 7,
        PartyMode = 8,
        CopsAndCrooks = 10,
        TurfWar = 12,
        DealBreaker = 13,
        HangmansNoose = 14,
        BombDaBaseII = 15,
        FreeMode = 16,
        TBoGT_Deathmatch = 26,
        TBoGT_TeamDeathmatch = 27,
        TBoGT_Race = 28,
        TBoGT_GTARace = 29,
        TLaD_Deathmatch = 24,
        TLaD_TeamDeathmatch = 21,
        TLaD_Race = 20,
        TLaD_ClubBusiness = 19,
        TLaD_LoneWolfBiker = 23,
        TLaD_ChopperVsChopper = 17,
        TLaD_WitnessProtection = 18,
        TLaD_OwnTheCity = 22
    }

}
