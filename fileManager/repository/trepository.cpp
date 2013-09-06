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
    int result = shellCommand->SetWorkingDirectory(localURL);

    QString folderToClone = "";
    result = shellCommand->CloneRepositories(remoteURL, folderToClone);
    if(result != int(NO_ERROR))
    {
        printf("Error clone repositories: %s \n", remoteURL.toStdString().c_str());
        return result;
    }
    shellCommand->SetWorkingDirectory(localURL + folderToClone);

    result = shellCommand->InitRepositories(nameRepo);
    if(result != int(NO_ERROR))
    {
        printf("Error git-annex init repositories: %s \n", localURL.toStdString().c_str());
        return result;
    }
    this->nameRepo = nameRepo;
    this->remoteURL = remoteURL;
    this->localURL  = localURL + folderToClone;

    return result;
}
//----------------------------------------------------------------------------------------/
int TRepository::DeleteRepository(const QString &localURL)
{
    this->nameRepo = "";
    this->localURL = "";
    this->remoteURL = "";
    return 0;
}
//----------------------------------------------------------------------------------------/
//----------------------------------------------------------------------------------------/
//----------------------------------------------------------------------------------------/
