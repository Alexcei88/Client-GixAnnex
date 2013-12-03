#include "trepository.h"

// parsing stuff
#include "../parsing_command_out/parsingcommandclone.h"
#include "../parsing_command_out/parsingcommandwhereis.h"
#include "../parsing_command_out/parsingcommandget.h"

using namespace GANN_DEFINE;
//----------------------------------------------------------------------------------------/
TRepository::TRepository(): IRepository()
{}
//----------------------------------------------------------------------------------------/
TRepository::TRepository(const QString& localUrl, const QString& remoteUrl, const QString& nameRepo) :
    IRepository(localUrl, remoteUrl, nameRepo)
{}
//----------------------------------------------------------------------------------------/
TRepository::~TRepository() {}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS TRepository::CloneRepository(QString& localURL, const QString& nameRepo, const QString& remoteURL)
{
    // здесь должны переходить в текущую директорию
    shellCommand->SetWorkingDirectory(localURL);

    QString folderToClone = "";
    RESULT_EXEC_PROCESS result = shellCommand->CloneRepositories(remoteURL, folderToClone, this);
    if(result != int(NO_ERROR))
    {
        printf("Error clone repositories: %s \n", remoteURL.toStdString().c_str());
        return result;
    }
    folderToClone = "/" + folderToClone;
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

    localURL +=folderToClone;
    return result;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS TRepository::DeleteRepository()
{
    this->nameRepo = "";
    this->localURL = "";
    this->remoteURL = "";

    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS TRepository::GetContentFile(const QString& file)
{
    shellCommand->SetWorkingDirectory(this->localURL);
    RESULT_EXEC_PROCESS result = shellCommand->GetContentFile(file, this);
    if(result != NO_ERROR)
    {
        printf("Error git-annex get content of file: %s \n", file.toStdString().c_str());
        return result;
    }
    return result;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS TRepository::DropContentFile(const QString& file)
{
    shellCommand->SetWorkingDirectory(this->localURL);
    RESULT_EXEC_PROCESS result = shellCommand->DropContentFile(file, this);
    if(result != NO_ERROR)
    {
        printf("Error git-annex drop content of file: %s \n", file.toStdString().c_str());
        return result;
    }
    return result;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS TRepository::RemoveFile(const QString& file)
{
    // сначала удалим контент
    DropContentFile(file);
    // а теперь удаляем и сам файл
    shellCommand->SetWorkingDirectory(this->localURL);
    RESULT_EXEC_PROCESS result = shellCommand->RemoveFile(file);
    if(result != NO_ERROR)
    {
        printf("Error git rm file: %s \n", file.toStdString().c_str());
        return result;
    }
    return result;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS TRepository::WhereisFile(const QString& file) const
{
    shellCommand->SetWorkingDirectory(this->localURL);
    RESULT_EXEC_PROCESS result = shellCommand->WhereisFiles(file);
    if(result != NO_ERROR)
    {
        printf("Error git-annex drop content of file: %s \n", file.toStdString().c_str());
        return result;
    }
    return result;
}
//----------------------------------------------------------------------------------------/
GANN_DEFINE::RESULT_EXEC_PROCESS TRepository::SyncRepository() const
{
    shellCommand->SetWorkingDirectory(this->localURL);
    RESULT_EXEC_PROCESS result = shellCommand->Sync();
    if(result != NO_ERROR)
    {
        printf("Error sync repository\n");
        return result;
    }
    return result;
}
//----------------------------------------------------------------------------------------/
