class GOZMissionConfigHandler
{
    static const string GOZ_FOLDER = "$profile:GOZmission";
    static const string GOZ_CONFIG_FILE = "$profile:GOZmission\\GOZMissionConfig.json";
    static ref GOZMissionConfig m_GOZGeneralConfig;
    protected ref Timer m_MissionTimer;

    void GOZMissionConfigHandler();
    static void Init();
    protected void InitTimer();
    static void GOZEnsureDirectoriesExist();
    static int GOZGetIntervalTime();
    static int GOZGetFirstEventSpawnTime();
}