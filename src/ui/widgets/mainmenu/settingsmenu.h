#include <QSettings>

#include "../scalablewidget.h"

class SettingsMenu : public ScalableWidget
{
    public:
        SettingsMenu(QWidget* parent);
        ~SettingsMenu();

    private:
        QSettings* settings;
};