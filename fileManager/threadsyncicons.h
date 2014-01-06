#ifndef THREADSYNCICONS_H
#define THREADSYNCICONS_H
#include <QObject>

namespace GANN_MVC {
    class ControllerIcons;
}

class ThreadSyncIcons: public QObject
{
public:
    ThreadSyncIcons(GANN_MVC::ControllerIcons *controllerIcons);
    ~ThreadSyncIcons();

    void            UpdateFileSyncIcons();
private:
    GANN_MVC::ControllerIcons* controllerIcons;
    bool            exitThread;

};

#endif // THREADSYNCICONS_H
