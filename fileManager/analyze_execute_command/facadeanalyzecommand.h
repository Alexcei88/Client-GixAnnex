#ifndef FACADEANALYZECOMMAND_H
#define FACADEANALYZECOMMAND_H

#include <QList>
#include <QString>

/* КЛАСС ФАСАД, В КОТОРОМ СОБИРАЕТСЯ ВСЯ ИНФА ПО АНАЛИЗУ ВЫПОЛНЕНИЯ КОМАНДЫ */

namespace AnalyzeCommand
{

class FacadeAnalyzeCommand
{
public:
    FacadeAnalyzeCommand();

    void                OnStartGetContentFile(const QString&);
    void                OnEndGetContentFile(const QString&);
    void                OnErrorGetContentFile(const QString&, const QString&);



private:
    // вектор, содержащий файлы, которые сейчас скачиваются(или дано задание на скачивание)
    QList<QString>      gettingContentFile;

};

}

#endif // FACADEANALYZECOMMAND_H
