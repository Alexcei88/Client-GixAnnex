#ifndef IPARSINGCOMMANDOUT_H
#define IPARSINGCOMMANDOUT_H

#include <iostream>

//  Qt stuff
#include <QStringList>
#include <QRegExp>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QProcess>

#include "../define.h"

class IRepository;
class TShell;

namespace AnalyzeCommand
{
    class AnalyzeExecuteCommand;
}

class IParsingCommandOut
{
public:
    IParsingCommandOut();
    IParsingCommandOut(boost::shared_ptr<AnalyzeCommand::AnalyzeExecuteCommand> analyzeCommand);
    virtual ~IParsingCommandOut();

    /** @brief действия перед запуском команды */
    virtual void        SetParamBeforeStartCommand();

    /** @brief действия по окончанию выполнения команды */
    virtual void        SetParamAfterEndCommand(int exitCode);

    /** @brief действия команда при выполнении команды возникла ошибка */
    virtual void        SetParamErrorExecuteCommand(QProcess::ProcessError& error);

    /**
     * @brief слот, в который будут поступать данные со стандартного потока вывода при выполнении команды
     * @param listData - список данных, заполненный согласно протоколу парсинга каждой команды
     * @return 0 - нет ошибок
     */
    void                SetNewDataStdOut();

    /** @brief функция парсинга, у каждого класса будет своя реализация */
    virtual void        ParsingData() = 0;

    /** @brief возвращает код ошибки, полученной в результате парсинга */
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS GetCodeError() const;

    /** @brief установка shellа, откуда будут браться данные */
    void                SetShell(TShell *shell);

protected:
    /** @brief список данных, поступивших на входной поток данных */
    QStringList         dataStdOut;

    /** @brief команда стартовала */
    bool                commandStart;
    /** @brief команда завершилась */
    bool                commandEnd;
    /** @brief код завершения процесса 0 - нет ошибок, иначе с ошибкой */
    int                 exitCodeCommand;

    /** @brief ошибка при выполнении всей команды */
    bool                wasErrorCommand;

    /** @brief класс, выполняющий команду shell*/
    TShell*             shell;
    /** @brief анализатор команды, если таковой имеется */
    boost::shared_ptr<AnalyzeCommand::AnalyzeExecuteCommand> analyzeCommand;

    // QJSON документы
    // вектор документов, которые пропарсины(или начат их парсинг), этот вектор документов уже далее в подклассах анализируется
    std::vector<QJsonDocument> arrayJSONDocument;
    QJsonDocument       lastJSONDocument;
    // временная JSON строка, которая накапливается, пока не будет получен вся JSON строка
    QString             strJSONData;

    /** @brief закончилась ли промежуточная команда
     *  @param ок - удачно, неудачно закончилась
        @return true - команда закночилась, false - не закончилась
    */
    bool                IsEndMiniCommand(const QJsonDocument &doc, bool& ok) const;

    /** @brief ключи начала/окончания команды */
    const QString       keyStartDoc;
    const QString       keyEndDoc;

private:
    /** @brief функция фильтр строки, которая отбрасывает все, что не относиться к JSON-формату */
    void                FilterInputString(const QString &str);

    /** @brief функция обработки ошибок в парсинге JSON
    \details обрабатывает ошибки и заполняет поле класса strJSONData
    @return возвращает строку, с которой документ обязательно создаться */
    QString             ProcessingErrorString(const QString& str, const QJsonParseError* parseError);

    // флаги управления начала/окончания создания нового документа
    bool                startNewDocument;
};
#endif // IPARSINGCOMMANDOUT_H
