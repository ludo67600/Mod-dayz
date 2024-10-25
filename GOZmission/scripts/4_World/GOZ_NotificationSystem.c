class GOZNotificationSystem
{
    protected Widget m_NotificationRoot;
    protected MultilineTextWidget m_NotificationText;
    protected ImageWidget m_ImageFont;
    protected ImageWidget m_ConvoyLogo;
    ref Timer m_NotificationTimer;

    void GOZNotificationSystem()
    {
        Print("[GOZmission] Initializing notification system");
        m_NotificationTimer = new Timer(CALL_CATEGORY_GUI);
        m_NotificationRoot = GetGame().GetWorkspace().CreateWidgets("GOZmission/layouts/GOZNotification.layout");
        m_NotificationText = MultilineTextWidget.Cast(m_NotificationRoot.FindAnyWidget("NotificationText"));
        m_ImageFont = ImageWidget.Cast(m_NotificationRoot.FindAnyWidget("ImageFont"));
        m_ConvoyLogo = ImageWidget.Cast(m_NotificationRoot.FindAnyWidget("ConvoyLogo"));
        
        if (!m_NotificationRoot)
        {
            Print("[GOZmission] ERROR: Failed to create notification widget");
            return;
        }
        
        if (!m_NotificationText || !m_ImageFont || !m_ConvoyLogo)
        {
            Print("[GOZmission] ERROR: Failed to find required widgets");
            return;
        }
        
        m_NotificationRoot.Show(false);
        Print("[GOZmission] Notification system initialized");
    }

    void ShowGOZNotification(string message, float duration = 5.0, GOZConvoy convoy = null)
    {
        Print("[GOZmission] Showing notification: " + message);
        
        if (convoy)
        {
            Print("[GOZmission] Loading convoy notification assets");
            m_ConvoyLogo.LoadImageFile(0, convoy.NotificationIcon);
            m_ImageFont.LoadImageFile(0, convoy.NotificationBackground);
        }

        m_NotificationText.SetText(message);
        m_NotificationRoot.Show(true);
        m_NotificationTimer.Run(duration, this, "HideNotification");
    }

    void HideNotification()
    {
        Print("[GOZmission] Hiding notification");
        if (m_NotificationRoot)
        {
            m_NotificationRoot.Show(false);
        }
    }

    void ~GOZNotificationSystem()
    {
        Print("[GOZmission] Cleaning up notification system");
        if (m_NotificationTimer)
        {
            m_NotificationTimer.Stop();
        }
        
        if (m_NotificationRoot)
        {
            m_NotificationRoot.Unlink();
        }
    }
}