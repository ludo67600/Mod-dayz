class GOZMissionConfig {
    string Comment_GOZMission;
    int IntervalBetweenEvents;
    int FirstEventTimeToSpawn;
    ref array<ref GOZConvoy> GOZConvoys;
    
    void GOZMissionConfig() {
        Comment_GOZMission = "";
        IntervalBetweenEvents = 30;
        FirstEventTimeToSpawn = 5;
        GOZConvoys = new array<ref GOZConvoy>;
    }
}

class GOZVehicle {
    string VehicleType;
    vector Position;
    vector Orientation;

    void GOZVehicle(string type, vector pos, vector orient) {
        VehicleType = type;
        Position = pos;
        Orientation = orient;
    }
}

class GOZConvoy {
    vector Position;
    ref array<ref GOZVehicle> Vehicles;
    ref array<string> ZombiesToReward;
    string RewardCrate;
    vector RewardCratePosition;
    vector RewardCrateOrientation;
    ref array<string> RewardItems;
    ref array<string> GeneralZombies;
    int ZombieSpawnRadius;
    int TimeToComplete;
    bool Notification;
    string NotificationMessage;
    string NotificationIcon;
    string NotificationBackground;
    bool MarkOnMap;
    string MarkIcon;
    int PlayerDistanceToSpawnZombies;
    
    [NonSerialized()]
    int markerUID = 0;
    [NonSerialized()]
    bool hasConvoyMarker = false;

    void GOZConvoy(vector pos = "0 0 0", array<ref GOZVehicle> vehicles = null, array<string> zToReward = null, string rwCrate = "", vector rwCratePos = "0 0 0", vector rwCrateOri = "0 0 0", array<string> rwItems = null, array<string> genZombies = null, int zmbRadius = 20, int time = 0, bool notifi = false, string ntfMessage = "", string ntfIcon = "", string ntfBackground = "", bool mrkOnMap = true, string mrkIcon = "", int plDistanceToSpawn = 500) {
        Position = pos;
        
        Vehicles = vehicles;
        if (!Vehicles) {
            Vehicles = new array<ref GOZVehicle>;
        }

        ZombiesToReward = zToReward;
        if (!ZombiesToReward) {
            ZombiesToReward = new array<string>;
        }

        RewardCrate = rwCrate;
        RewardCratePosition = rwCratePos;
        RewardCrateOrientation = rwCrateOri;

        RewardItems = rwItems;
        if (!RewardItems) {
            RewardItems = new array<string>;
        }

        GeneralZombies = genZombies;
        if (!GeneralZombies) {
            GeneralZombies = new array<string>;
        }

        ZombieSpawnRadius = zmbRadius;
        TimeToComplete = time;
        Notification = notifi;
        NotificationMessage = ntfMessage;
        NotificationIcon = ntfIcon;
        NotificationBackground = ntfBackground;
        MarkOnMap = mrkOnMap;
        MarkIcon = mrkIcon;
        PlayerDistanceToSpawnZombies = plDistanceToSpawn;
    }
}