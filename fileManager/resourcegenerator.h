#ifndef RESOURCEGENERATOR_H
#define RESOURCEGENERATOR_H

/*
 * Генератор ресурсов для различных тем(поддержка пока тока Linux)
*/
// Qt Stuff
#include <QIcon>
#include <QResource>


#include <boost/shared_ptr.hpp>

class ResourceGenerator
{
public:
    static ResourceGenerator*   getInstance();
    ~ResourceGenerator();

private:
    static boost::shared_ptr<ResourceGenerator> instance;
    ResourceGenerator();
    QResource*          resourceFileIcon;

    void                GenerateResource();

};

#endif // RESOURCEGENERATOR_H
