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
    boost::shared_ptr<TShell> shell(new TShell());

    // здесь должны переходить в текущую директорию
    RESULT_EXEC_PROCESS result = shellCommand->SetWorkingDirectory(localURL, shell.get());

    QString folderToClone = "";
    result = shellCommand->CloneRepositories(remoteURL, folderToClone, shell);
    folderToClone = "/" + folderToClone;
    if(result != int(NO_ERROR))
    {
        printf("Error clone repositories: %s \n", remoteURL.toStdString().c_str());
        return result;
    }
    shellCommand->SetWorkingDirectory(localURL + folderToClone, shell.get());

    result = shellCommand->InitRepositories(nameRepo, shell.get());
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
RESULT_EXEC_PROCESS TRepository::DeleteRepository(const QString &localURL)
{
    this->nameRepo = "";
    this->localURL = "";
    this->remoteURL = "";

    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS TRepository::GetContentFile(const QString& file)
{
    boost::shared_ptr<TShell> shell(new TShell());
    shellCommand->SetWorkingDirectory(this->localURL, shell.get());
    RESULT_EXEC_PROCESS result = shellCommand->GetContentFile(file, shell, this);
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
    boost::shared_ptr<TShell> shell(new TShell());
    shellCommand->SetWorkingDirectory(this->localURL, shell.get());
    RESULT_EXEC_PROCESS result = shellCommand->DropContentFile(file, shell, this);
    if(result != NO_ERROR)
    {
        printf("Error git-annex drop content of file: %s \n", file.toStdString().c_str());
        return result;
    }
    return result;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS TRepository::WhereisFile(const QString& file) const
{
    boost::shared_ptr<TShell> shell(new TShell());
    shellCommand->SetWorkingDirectory(this->localURL, shell.get());
    RESULT_EXEC_PROCESS result = shellCommand->WhereisFiles(file, shell);
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
    boost::shared_ptr<TShell> shell(new TShell());
    shellCommand->SetWorkingDirectory(this->localURL, shell.get());
    RESULT_EXEC_PROCESS result = shellCommand->Sync(shell);
    if(result != NO_ERROR)
    {
        printf("Error sync repository\n");
        return result;
    }
    return result;
}
//----------------------------------------------------------------------------------------/
