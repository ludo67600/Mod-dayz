class GOZGlobalHelper 
{
    static ref array<ref GOZConvoy> gozConvoysGlobal;
    static bool convoyActiveOnMap = false;
    static vector convoyActivePosition = "0 0 0";
    static string convoyActiveMarkIcon = "";

    static void SetConfigConvoys(array<ref GOZConvoy> gozConvoys)
    {
        Print("[GOZmission] Setting global convoys config");
        gozConvoysGlobal = gozConvoys;
    }

    static ref array<ref GOZConvoy> GetConfigConvoys()
    {
        return gozConvoysGlobal;
    }

    static void SetActiveConvoyGlobal(GOZConvoy convoy)
    {
        Print("[GOZmission] Setting active convoy");
        if (convoy.MarkOnMap)
        {
            convoyActiveOnMap = true;
        }
        
        convoyActivePosition = convoy.Position;
        convoyActiveMarkIcon = convoy.MarkIcon;
        Print("[GOZmission] Convoy set: Position=" + convoy.Position + ", Icon=" + convoy.MarkIcon);
    }

    static void ResetActiveConvoyGlobal()
    {
        Print("[GOZmission] Resetting active convoy");
        convoyActiveOnMap = false;
        convoyActivePosition = "0 0 0";
        convoyActiveMarkIcon = "";
    }

    static bool IsConvoyActiveOnMap()
    {
        return convoyActiveOnMap;
    }
}