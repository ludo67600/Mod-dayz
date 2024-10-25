void InitGOZMission()
{
    Print("[GOZmission] InitGOZMission called");
    if (!g_GOZMissionHandler && GetGame().IsServer()) 
    {
        Print("[GOZmission] Creating new GOZMission instance");
        g_GOZMissionHandler = new GOZMissionConfigHandler();
    }
}

void main()
{
    Print("[GOZmission] Main function called");
    if (GetGame().IsServer())
    {
        Print("[GOZmission] Server detected - Starting initialization");
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(InitGOZMission, 2000, false);
    }
}