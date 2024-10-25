#ifdef VanillaPPMap
modded class VPPMapMenu extends UIScriptedMenu 
{
    private MapWidget gozMapWidget;
    vector gozMarkPosition;
    string gozMarkIcon;

    override Widget Init() 
    {
        super.Init();
        Print("[GOZmission] Initializing map markers");

        if (!gozMapWidget) 
        {
            gozMapWidget = MapWidget.Cast(layoutRoot.FindAnyWidget("Map_Widget"));
            Print("[GOZmission] Map widget obtained");

            if (GOZGlobalHelper.IsConvoyActiveOnMap()) 
            {
                gozMarkPosition = GOZGlobalHelper.convoyActivePosition;
                gozMarkIcon = GOZGlobalHelper.convoyActiveMarkIcon;    
                
                if (gozMapWidget && gozMarkPosition != "0 0 0" && gozMarkIcon != "") 
                {
                    Print("[GOZmission] Adding marker to map at: " + gozMarkPosition.ToString());
                    gozMapWidget.AddUserMark(gozMarkPosition, "", ARGB(255, 255, 255, 0), gozMarkIcon);
                }
                else 
                {
                    Print("[GOZmission] Failed to add marker - invalid parameters");
                }
            }
            else 
            {
                Print("[GOZmission] No active convoy to mark on map");
            }
        }

        return layoutRoot;
    }

    override void DisplayClientMarkers() 
    {
        super.DisplayClientMarkers();
        Print("[GOZmission] Updating client markers");

        gozMarkPosition = GOZGlobalHelper.convoyActivePosition;
        gozMarkIcon = GOZGlobalHelper.convoyActiveMarkIcon;

        if (GOZGlobalHelper.IsConvoyActiveOnMap())
        {
            if (gozMapWidget && gozMarkPosition != "0 0 0" && gozMarkIcon != "")
            {
                Print("[GOZmission] Refreshing marker on map at: " + gozMarkPosition.ToString());
                gozMapWidget.AddUserMark(gozMarkPosition, "", ARGB(255, 255, 255, 0), gozMarkIcon);            
            }
            else 
            {
                Print("[GOZmission] Failed to refresh marker - invalid parameters");
            }
        }
    }
}
#endif