void GOZNotifiSound(string soundSetName) 
{
    if ((GetGame().IsClient() || !GetGame().IsMultiplayer()) && GetGame().GetPlayer()) 
    {
        SEffectManager.PlaySoundOnObject(soundSetName, GetGame().GetPlayer());
    }
}