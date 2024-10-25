class GOZMarkerManager 
{
    #ifdef LBmaster_Groups
    protected ref LBServerMarker m_LBMapMarker;
    protected bool isMarkActive = false;
    ref GOZConvoy convoyManaged;
    
    void GOZMarkerManager(GOZConvoy convoy)
    {
        Print("[GOZmission] Creating marker manager for convoy");
        convoyManaged = convoy;
    }

    LBServerMarker CreateLBMapMarker(string name, vector position, string icon, int argb, bool toSurface, bool display3D, bool displayMap, bool displayGPS)
    {
        if (GOZGlobalHelper.IsConvoyActiveOnMap())
        {
            Print("[GOZmission] Creating LB map marker at " + position);
            LBServerMarker marker = LBStaticMarkerManager.Get.AddTempServerMarker(name, position, icon, argb, toSurface, display3D, displayMap, displayGPS);
            m_LBMapMarker = marker;
            isMarkActive = true;
            return marker;
        }
        Print("[GOZmission] Failed to create marker - no active convoy");
        return null;
    }
    
    bool RemoveLBMapMarker()
    {    
        if (isMarkActive)
        {
            Print("[GOZmission] Removing map marker");
            bool success = LBStaticMarkerManager.Get.RemoveServerMarker(m_LBMapMarker);
            isMarkActive = false;
            return success;
        }
        return false;
    }

    void SetLBMapMarker(LBServerMarker markerObject)
    {
        Print("[GOZmission] Setting map marker");
        m_LBMapMarker = markerObject;
    }
    
    LBServerMarker GetLBMapMarker()
    {
        return m_LBMapMarker;
    }
    #endif
}