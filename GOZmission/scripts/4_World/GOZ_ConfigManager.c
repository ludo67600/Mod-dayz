modded class GOZMissionConfigHandler
{
    void GOZMissionConfigHandler() 
    {
        Print("[GOZmission] GOZMissionConfigHandler constructor called");
        if (GetGame().IsServer()) 
        {
            Print("[GOZmission] Server detected - Initializing config");
            Init();
            m_GOZGeneralConfig = new GOZMissionConfig();
            GOZEnsureGeneralConfigExists();
            InitTimer();
        }
    }

    static void Init()
    {
        Print("[GOZmission] GOZConfig Init called");
        GOZEnsureDirectoriesExist();
    }

    protected void InitTimer() 
    {
        Print("[GOZmission] Initializing timer");
        if (GetGame().IsServer()) 
        {
            m_MissionTimer = new Timer();
            float firstDelay = GOZGetFirstEventSpawnTime() * 60;
            Print("[GOZmission] First mission will start in: " + firstDelay.ToString() + " seconds");
            m_MissionTimer.Run(firstDelay, this, "StartMissionCycle", null, false);
        }
    }

    void StartMissionCycle() 
    {
        if (GetGame().IsServer()) 
        {
            Print("[GOZmission] Starting mission cycle");
            SpawnRandomMission();
            float interval = GOZGetIntervalTime() * 60;
            Print("[GOZmission] Next mission will spawn in: " + interval.ToString() + " seconds");
            m_MissionTimer.Run(interval, this, "StartMissionCycle", null, false);
        }
    }

    void SpawnRandomMission() 
    {
        if (!GetGame().IsServer()) return;
        
        Print("[GOZmission] Starting mission spawn process");
        array<ref GOZConvoy> missions = GOZGetConvoysConfig();
        if (missions && missions.Count() > 0) 
        {
            Print("[GOZmission] Available missions: " + missions.Count().ToString());
            int randomIndex = Math.RandomInt(0, missions.Count());
            GOZConvoy selectedMission = missions.Get(randomIndex);
            if (selectedMission) 
            {
                Print("[GOZmission] Selected mission position: " + selectedMission.Position.ToString());
                GOZGlobalHelper.SetConfigConvoys(missions);
                GOZGlobalHelper.SetActiveConvoyGlobal(selectedMission);
                SpawnMissionElements(selectedMission);
            }
        }
        else
        {
            Print("[GOZmission] ERROR: No missions available in config");
        }
    }

    private void SpawnMissionElements(GOZConvoy mission) 
    {
        if (!GetGame().IsServer()) return;
        Print("[GOZmission] Starting to spawn mission elements");

        foreach (string zombieType : mission.GeneralZombies) 
        {
            vector zombiePos = mission.Position + Vector(Math.RandomFloat(-mission.ZombieSpawnRadius, mission.ZombieSpawnRadius), 0, Math.RandomFloat(-mission.ZombieSpawnRadius, mission.ZombieSpawnRadius));
            if (GetGame().CreateObject(zombieType, zombiePos, false, true))
            {
                Print("[GOZmission] Successfully spawned zombie: " + zombieType + " at " + zombiePos.ToString());
            }
            else
            {
                Print("[GOZmission] ERROR: Failed to spawn zombie: " + zombieType);
            }
        }

        foreach (string rewardZombie : mission.ZombiesToReward) 
        {
            vector rewardPos = mission.Position + Vector(Math.RandomFloat(-mission.ZombieSpawnRadius, mission.ZombieSpawnRadius), 0, Math.RandomFloat(-mission.ZombieSpawnRadius, mission.ZombieSpawnRadius));
            if (GetGame().CreateObject(rewardZombie, rewardPos, false, true))
            {
                Print("[GOZmission] Successfully spawned reward zombie: " + rewardZombie + " at " + rewardPos.ToString());
            }
            else
            {
                Print("[GOZmission] ERROR: Failed to spawn reward zombie: " + rewardZombie);
            }
        }

        Print("[GOZmission] Mission elements spawned successfully");
    }

    static void GOZEnsureDirectoriesExist() 
    {
        if (GetGame().IsServer()) 
        {
            if (!FileExist(GOZ_FOLDER)) 
            {
                Print("[GOZmission] Creating config directory: " + GOZ_FOLDER);
                MakeDirectory(GOZ_FOLDER);
            }
        }
    }

    private void GOZEnsureGeneralConfigExists() 
    {
        if (GetGame().IsServer()) 
        {
            Print("[GOZmission] Checking config existence");
            if (!FileExist(GOZ_CONFIG_FILE)) 
            {
                Print("[GOZmission] Creating new config file");
                GOZMissionConfig config = new GOZMissionConfig();
                config.Comment_GOZMission = "Simple zombie elimination missions";
                config.IntervalBetweenEvents = 30;
                config.FirstEventTimeToSpawn = 5;

                array<string> rewardZombies = new array<string>;
                rewardZombies.Insert("ZmbM_SoldierNormal");

                array<string> rewardItems = new array<string>;
                rewardItems.Insert("AKM");
                rewardItems.Insert("Mag_AKM_30Rnd");

                array<string> generalZombies = new array<string>;
                generalZombies.Insert("ZmbM_PatrolNormal_Autumn");
                generalZombies.Insert("ZmbM_PatrolNormal_Autumn");

                config.GOZConvoys.Insert(new GOZConvoy(
                    "11945.5 140.2 12420.1",
                    null,
                    rewardZombies,
                    "SeaChest",
                    "11945.5 140.2 12420.1",
                    "0 0 0",
                    rewardItems,
                    generalZombies,
                    20,
                    15,
                    true,
                    "Groupe de zombies repéré!",
                    "GOZmission/layouts/icons/Camp.edds",
                    "GOZmission/layouts/NotifiConvoy.edds",
                    true,
                    "GOZmission\\data\\MarkCamp.paa",
                    100));

                JsonFileLoader<GOZMissionConfig>.JsonSaveFile(GOZ_CONFIG_FILE, config);
            }
            GOZLoadGeneralConfig();
        }
    }

    private void GOZLoadGeneralConfig() 
    {
        if (GetGame().IsServer() && FileExist(GOZ_CONFIG_FILE)) 
        {
            Print("[GOZmission] Loading config from: " + GOZ_CONFIG_FILE);
            if (!m_GOZGeneralConfig) 
            {
                m_GOZGeneralConfig = new GOZMissionConfig();
            }
            JsonFileLoader<GOZMissionConfig>.JsonLoadFile(GOZ_CONFIG_FILE, m_GOZGeneralConfig);
            Print("[GOZmission] Config loaded successfully");
        }
    }

    static array<ref GOZConvoy> GOZGetConvoysConfig() 
    {
        return m_GOZGeneralConfig.GOZConvoys;
    }

    override static int GOZGetIntervalTime() 
    {
        if (m_GOZGeneralConfig)
            return m_GOZGeneralConfig.IntervalBetweenEvents;
        return 30;
    }

    override static int GOZGetFirstEventSpawnTime() 
    {
        if (m_GOZGeneralConfig)
            return m_GOZGeneralConfig.FirstEventTimeToSpawn;
        return 5;
    }
}