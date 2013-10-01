#pragma once

// Qt stuff
#include <QObject>
#include <QSharedPointer>
#include <QString>
#include <QVariantList>

#include "../Model/model_repository.h"
namespace GANN_MVC
{

class ControllerRepository: public QObject
{
    Q_OBJECT

public:
    ControllerRepository( );

    Q_PROPERTY(QString currentPathRepo READ GetCurrentPathRepo WRITE SetCurrentPathRepo NOTIFY currentPathRepoChanged)

    QString                 GetCurrentPathRepo() { return currentPathRepo; };
    void                    SetCurrentPathRepo(QString path) { currentPathRepo = path; emit currentPathRepoChanged(path);};


    /** @brief Получить список репозиториев */
    Q_INVOKABLE QVariantList GetListRepository() const;

    /** @brief путь до репозитория по умолчанию */
    Q_INVOKABLE QVariant     GetDefaultRepositoryPath() const;

    /** @brief Начать клонирование репозитория */
    Q_INVOKABLE QVariant    StartCloneRepository(QVariant localUlr, QVariant remoteURL, QVariant nameRepo);

    /** @brief Отмена клонирования репозитория */
    Q_INVOKABLE void        CancelCloneRepository() const;


    /** @brief взять контент у файла(директории)*/
    Q_INVOKABLE QVariant    GetContentDirectory(QVariant dir) const;

    /*Q_INVOKABLE void        Add( );
    Q_INVOKABLE void        Edit( );
    Q_INVOKABLE void        Remove( );
    // ñîõðàíÿåò äàííûå çàïèñè, êîòîðûå áóäåì ðåäàêòèðîâàòü
    Q_INVOKABLE void        StoreBeforeEdit( );

    // ÑÂÎÉÑÒÂÀ
    // èìÿ
    Q_PROPERTY(QString name READ getName WRITE setName);
    // ôàìèëèÿ
    Q_PROPERTY(QString family READ getFamily WRITE setFamily);
    // îò÷åñòâî
    Q_PROPERTY(QString name2 READ getName2 WRITE setName2);
    // êóðñ
    Q_PROPERTY(qint8 cource READ getCource WRITE setCource);
    // ôàêóëüòåò
    Q_PROPERTY(QString faculty READ getFaculty WRITE setFaculty);
    // äåíü ðîæäåíèÿ
    Q_PROPERTY(QDate birthday READ getBirthday WRITE setBirthday);
    // òèï ôàêòè÷åñêîãî àäðåñà ïðîæèâàíèÿ(îáùåæèòèå, ñúåìíàÿ êâàðòèðà, äîì)
    Q_PROPERTY(QString typeAdressFact READ getTypeAdressFact WRITE setTypeAdressFact);
    // ñòóäåí÷åñêàÿ ãðóïïà
    Q_PROPERTY(QString studyGroup READ getStudyGroup WRITE setStudyGroup);
    // íàïðàâëåíèå ïîäãîòîâêè
    Q_PROPERTY(QString directionPreparation READ getDirectionPreparation WRITE setDirectionPreparation);

    // ÀÄÐÅÑ ÏÐÎÆÈÂÀÍÈß
    // ïî ïàñïîðòó
    Q_PROPERTY(QString regionPasp READ getRegionPasp WRITE setRegionPasp);
    // ãîðîä
    Q_PROPERTY(QString cityPasp READ getCityPasp WRITE setCityPasp);
    // óëèöà
    Q_PROPERTY(QString streetPasp READ getStreetPasp WRITE setStreetPasp);
    // íîìåð äîìà
    Q_PROPERTY(QString numberHomePasp READ getNumberHomePasp WRITE setNumberHomePasp);
    // êâàðòèðà
    Q_PROPERTY(quint16 apartmentPasp READ getApartmentPasp WRITE setApartmentPasp);

    // ôàêòè÷åñêèé
    // ðåãèîí, îáëàñòü
    Q_PROPERTY(QString regionFact READ getRegionFact WRITE setRegionFact);
    // ãîðîä
    Q_PROPERTY(QString cityFact READ getCityFact WRITE setCityFact);
    // óëèöà
    Q_PROPERTY(QString streetFact READ getStreetFact WRITE setStreetFact);
    // íîìåð äîìà
    Q_PROPERTY(QString numberHomeFact READ getNumberHomeFact WRITE setNumberHomeFact);
    // êâàðòèðà
    Q_PROPERTY(quint16 apartmentFact READ getApartmentFact WRITE setApartmentFact);

//    Q_PROPERTY(QString cource READ getCource WRITE setCource);

    // ìåòîäû, íóæíûå äëÿ Q_PROPERTY
    QString             getName( ) { return infoOfStudent.name; };
    void                setName( QString& str ) { infoOfStudent.name =  str; };

    QString             getFamily() { return infoOfStudent.family; };
    void                setFamily( QString& str ) { infoOfStudent.family =  str; };

    QString             getName2( ) { return infoOfStudent.name2; };
    void                setName2( QString& str ) { infoOfStudent.name2 =  str; };

    QString             getFaculty( ) { return infoOfStudent.faculty; };
    void                setFaculty( QString& str ) { infoOfStudent.faculty =  str; };

    QDate               getBirthday( ) { return infoOfStudent.birthday; };
    void                setBirthday( QDate& data ) { infoOfStudent.birthday =  data; };

    qint8               getCource( ) { return infoOfStudent.cource; };
    void                setCource( qint8& cource) { infoOfStudent.cource =  cource; };

    QString             getTypeAdressFact( ) { return infoOfStudent.typeAdressFact; };
    void                setTypeAdressFact(QString& str ) { infoOfStudent.typeAdressFact = str; };

    QString             getStudyGroup( ) { return infoOfStudent.studyGroup; };
    void                setStudyGroup(QString& studyGroup ) { infoOfStudent.studyGroup = studyGroup; };

    QString             getDirectionPreparation( ) { return infoOfStudent.directionPreparation; };
    void                setDirectionPreparation(QString& str) { infoOfStudent.directionPreparation = str; };

    // ÀÄÐÅÑ
    // ïî ïàñïîðòó
    QString             getRegionPasp( ) { return infoOfAdressPassport.region; };
    void                setRegionPasp(QString& str) { infoOfAdressPassport.region = str; };

    QString             getCityPasp( ) { return infoOfAdressPassport.city; };
    void                setCityPasp(QString& str) { infoOfAdressPassport.city = str; };

    QString             getStreetPasp( ){ return infoOfAdressPassport.street; };
    void                setStreetPasp(QString &str ) { infoOfAdressPassport.street = str; };

    QString             getNumberHomePasp( ) { return infoOfAdressPassport.numberHome; };
    void                setNumberHomePasp(QString& str) { infoOfAdressPassport.numberHome = str; };

    qint16              getApartmentPasp( ) { return infoOfAdressPassport.apartment; };
    void                setApartmentPasp(quint16& apartment) { infoOfAdressPassport.apartment = apartment; };

    // ôàêòè÷åñêèé
    QString             getRegionFact( ) { return infoOfAdressFact.region; };
    void                setRegionFact(QString& str) { infoOfAdressFact.region = str; };

    QString             getCityFact( ) { return infoOfAdressFact.city; };
    void                setCityFact(QString& str) { infoOfAdressFact.city = str; };

    QString             getStreetFact( ){ return infoOfAdressFact.street; };
    void                setStreetFact(QString &str ) { infoOfAdressFact.street = str; };

    QString             getNumberHomeFact( ) { return infoOfAdressFact.numberHome; };
    void                setNumberHomeFact(QString& str) { infoOfAdressFact.numberHome = str; };

    qint16              getApartmentFact( ) { return infoOfAdressFact.apartment; };
    void                setApartmentFact(quint16& apartment) { infoOfAdressFact.apartment = apartment; };

    void                Execute( );
*/
private:
    const QSharedPointer<ModelQmlAndCRepository>  model;
    QString             currentPathRepo;

signals:
    void                currentPathRepoChanged(QString);
};

}
