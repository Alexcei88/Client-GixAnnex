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
    this->nameRepo = nameRepo;
    this->remoteURL = remoteURL;
    this->localURL  = localURL;

    RESULT_EXEC_PROCESS result = shellCommand->CloneRepositories(remoteURL, localURL, facadeAnalyzeCommand.get());
    if(result != int(NO_ERROR))
    {
        printf("Error clone repositories: %s \n", remoteURL.toStdString().c_str());
        return result;
    }
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
RESULT_EXEC_PROCESS TRepository::GetContentFile(const QString& file, const bool mode)
{
    // если репозитория выключен, то ничего не делаем
    if(paramRepo.currentState == "Disable_sincing")
        return IGNORE_COMMAND;

    shellCommand->SetWorkingDirectory(dir.path());
    RESULT_EXEC_PROCESS result = shellCommand->GetContentFile(file, facadeAnalyzeCommand.get(), mode);
    if(result != NO_ERROR)
    {
        printf("Error git-annex get content of file: %s \n", file.toStdString().c_str());
        return result;
    }
    return result;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS TRepository::DropContentFile(const QString& file, const bool mode)
{
    if(paramRepo.currentState == metaEnumState.valueToKey(Disable_sincing))
        return IGNORE_COMMAND;

    shellCommand->SetWorkingDirectory(dir.path());
    RESULT_EXEC_PROCESS result = shellCommand->DropContentFile(file, facadeAnalyzeCommand.get(), mode);
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
    if(paramRepo.currentState == metaEnumState.valueToKey(Disable_sincing))
        return IGNORE_COMMAND;

    // сначала удалим контент
    DropContentFile(file, false);
    // а теперь удаляем и сам файл
    shellCommand->SetWorkingDirectory(dir.path());
    RESULT_EXEC_PROCESS result = shellCommand->RemoveFile(file, paramRepo.directMode, QFileInfo(dir.path() + "/" + file).isDir());
    if(result != NO_ERROR)
    {
        printf("Error git rm file: %s \n", file.toStdString().c_str());
        return result;
    }
    // и теперь нужно давать команду на синхронизацию контента

    return result;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS TRepository::WhereisFile(const QString& file)
{
    if(paramRepo.currentState == metaEnumState.valueToKey(Disable_sincing))
        return IGNORE_COMMAND;

    shellCommand->SetWorkingDirectory(dir.path());
    RESULT_EXEC_PROCESS result = shellCommand->WhereisFiles(file, facadeAnalyzeCommand.get());
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
    if(paramRepo.currentState == metaEnumState.valueToKey(Disable_sincing))
        return IGNORE_COMMAND;

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
