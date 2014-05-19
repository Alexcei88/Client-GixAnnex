#ifndef PREFERENCESAPPLICATION_H
#define PREFERENCESAPPLICATION_H

#include <memory>

// класс для упралвения свойствами приложения
#include <QObject>

class PreferencesApplication
{
public:
    PreferencesApplication();
    static PreferencesApplication* GetInstance();

    /** @brief directMode */
    bool                GetDirectMode() const;

    /** @brief Возвращает путь к файлу конфигурации приложения */
    const QString       GetPathToFileConfigApp() const;
    /** @brief Генерирует пустой файл конфигурации приложения*/
    void                GenerateEmptyFileConfigApp(const QString file) const;

private:
    Q_DISABLE_COPY(PreferencesApplication);
    static std::unique_ptr<PreferencesApplication> instance;

    /** @brief Структура, описывающая параметры приложения */
    struct PARAMETR_FILEFOLDER_GIT_ANNEX
    {
        // автосинхронизация контента
        bool        directMode;
    };
};

#endif // PREFERENCESAPPLICATION_H
