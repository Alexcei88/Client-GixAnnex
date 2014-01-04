#ifndef THREADSYNCICONS_H
#define THREADSYNCICONS_H

namespace GANN_MVC {
    class ModelQmlAndCIcons;
}

class ThreadSyncIcons
{
public:
    ThreadSyncIcons(GANN_MVC::ModelQmlAndCIcons *modelIcons);
    ~ThreadSyncIcons();

    void            UpdateFileSyncIcons();
private:
    GANN_MVC::ModelQmlAndCIcons* modelIcons;
    bool            exitThread;

};

#endif // THREADSYNCICONS_H
