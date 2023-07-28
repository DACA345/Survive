#include <QSettings>

#include "../ScalableWidget.h"

class SettingsMenu : public ScalableWidget
{
    public:
        SettingsMenu(QWidget* parent);
        ~SettingsMenu();

    private:
        QSettings* settings;
};