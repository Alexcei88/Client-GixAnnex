#include "trepository.h"
//----------------------------------------------------------------------------------------/
TRepository::TRepository(): IRepository()
{
}
//----------------------------------------------------------------------------------------/
TRepository::~TRepository() {}
//----------------------------------------------------------------------------------------/
int TRepository::CloneRepository(const QString &nameRepo, const QString &remoteURL, const QString &localURL)
{
    // здесь должны переходить в текущую директорию
    int result = shellCommand->CD(localURL);
    if(result != int(NO_ERROR))
    {
        printf("Error cd localURL: %s \n", localURL.toStdString().c_str());
        return result;
    }

    result = shellCommand->CloneRepositories(remoteURL, localURL);
    if(result != int(NO_ERROR))
    {
        printf("Error clone repositories: %s \n", remoteURL.toStdString().c_str());
        return result;
    }

    result = shellCommand->InitRepositories(nameRepo);
    if(result != int(NO_ERROR))
    {
        printf("Error git-annex init repositories: %s \n", localURL.toStdString().c_str());
        return result;
    }

    return result;
}
//----------------------------------------------------------------------------------------/
int TRepository::DeleteRepository(const QString &localURL)
{
    return 0;
}
//----------------------------------------------------------------------------------------/
//----------------------------------------------------------------------------------------/
//----------------------------------------------------------------------------------------/
