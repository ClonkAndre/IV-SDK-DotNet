namespace Manager
{

    public enum RemoteMessageID : ushort
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

        Manager_SendScriptCommandRequest,
        Manager_SendScriptCommandResponse,

        Manager_GetPreferencesRequest,
        Manager_GetPreferencesResponse,

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

    public enum TaskUseCase
    {
        Unknown,
        Timer,
        Custom
    }
    public enum Priority
    {
        Default,
        High
    }
    public enum AbortReason
    {
        /// <summary>
        /// The script was aborted by an API Client.
        /// </summary>
        API,
        /// <summary>
        /// The script was aborted manually by a user.
        /// </summary>
        Manual,

        /// <summary>
        /// The script was aborted by another script (Or by the same script).
        /// </summary>
        Script,
        /// <summary>
        /// The script was aborted because the manager wanted to.
        /// </summary>
        Manager,
        /// <summary>
        /// The script was aborted by the console (Manual).
        /// </summary>
        Console
    }
    public enum NotificationType
    {
        Default,
        Info,
        Warning,
        Error
    }

    public enum ScriptType
    {
        All,
        IVSDKDotNet,
        ScriptHookDotNet,
        Unknown
    }

    public enum SupportedPublicFields
    {
        Unknown,
        _byte,
        _sbyte,
        _short,
        _ushort,
        _int,
        _uint,
        _long,
        _ulong,
        _float,
        _double,
        _decimal,
        _bool,
        _string,
        _Vector2,
        _Vector3,
        _Vector4,
        _Quaternion,
        _Color,
        _Size,
        _SizeF,
        _Point,
        _PointF,
        _IList,
        _ICollection
    }

}