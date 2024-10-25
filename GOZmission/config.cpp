class CfgPatches
{
    class GOZmission
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {
            "DZ_Data",
            "DZ_Scripts",
            "BZ_NVG"  // Ajout de la dépendance ici
        };
    };
};

class CfgMods
{
    class GOZmission
    {
        dir = "GOZmission";
        picture = "";
        action = "";
        hideName = 0;
        hidePicture = 0;
        name = "GOZmission";
        credits = "LG";
        author = "LG";
        authorID = "0";
        version = "0.1";
        extra = 0;
        type = "mod";
        dependencies[] = {"Game", "World", "Mission"};
        
        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"GOZmission/scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"GOZmission/scripts/4_World"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"GOZmission/scripts/5_Mission"};
            };
        };
    };
};

class CfgSoundShaders
{
    class GOZNotification_SoundShader
    {
        samples[]=
        {
            {
                "GOZmission\\data\\GOZNotification.ogg",
                1
            }
        };
        range=5;
        volume=2;
    };
};

class CfgSoundSets
{
    class GOZNotification_SoundSet
    {
        soundShaders[]=
        {
            "GOZNotification_SoundShader"
        };
    };
};