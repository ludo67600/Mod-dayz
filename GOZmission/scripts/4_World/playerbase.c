modded class PlayerBase
{
    ref GOZNotificationSystem gozNotifier;

    void ShowGOZNotification(string message, float duration, GOZConvoy convoy)
    {
        if (!GetGame().IsClient()) 
        {
            return;
        }
        
        Print("[GOZmission] Player attempting to show notification");
        
        if (!gozNotifier)
        {
            Print("[GOZmission] Creating new notification system for player");
            gozNotifier = new GOZNotificationSystem();
        }

        if (gozNotifier)
        {
            Print("[GOZmission] Displaying notification to player: " + message);
            gozNotifier.ShowGOZNotification(message, duration, convoy);
            GOZNotifiSound("GOZNotification_SoundSet");
        }
        else
        {
            Print("[GOZmission] ERROR: Failed to create notification system");
        }
    }
}