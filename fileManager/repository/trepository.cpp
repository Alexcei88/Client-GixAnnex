#include "trepository.h"

using namespace GANN_DEFINE;
//----------------------------------------------------------------------------------------/
TRepository::TRepository(): IRepository()
{
}
TRepository::TRepository(const QString& localUrl, const QString& remoteUrl, const QString& nameRepo) :
    IRepository(localUrl, remoteUrl, nameRepo)
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

    // переходим в директорию
    this->nameRepo = nameRepo;
    this->remoteURL = remoteURL;
    this->localURL  = localURL + folderToClone;

    result = shellCommand->SetWorkingDirectory(this->localURL);
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
int TRepository::GetContentFile(const QString& file) const
{
    shellCommand->SetWorkingDirectory(this->localURL);
    int result = shellCommand->GetContentFile(file);
    if(result != NO_ERROR)
    {
        printf("Error git-annex get content of file: %s \n", file.toStdString().c_str());
        return result;
    }
    return result;
}
//----------------------------------------------------------------------------------------/
int TRepository::DropContentFile(const QString& file) const
{
    int result = shellCommand->DropContentFile(file);
    if(result != NO_ERROR)
    {
        printf("Error git-annex drop content of file: %s \n", file.toStdString().c_str());
        return result;
    }
    return result;
}
//----------------------------------------------------------------------------------------/
int TRepository::WhereisFile(const QString& file) const
{
    int result = shellCommand->WhereisFiles(file);
    if(result != NO_ERROR)
    {
        printf("Error git-annex drop content of file: %s \n", file.toStdString().c_str());
        return result;
    }
    return result;
}
//----------------------------------------------------------------------------------------/
