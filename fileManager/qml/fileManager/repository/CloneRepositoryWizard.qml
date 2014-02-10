import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

Item {

    // модель, содержащая список view, которые будут
    // отображаться в стек-вью
    ListModel {
        ListElement {
            urlComponent: "bla-bla-bla" // url репозитория, откуда загружать viewer
            name: "Select Type"         // текст сообщения, который отображается когда отображаем этот viewer

        }
        ListElement {
            urlComponent: "bla-bla-bla"
            name: "Options"
        }
        ListElement {
            urlComponent: "bla-bla-bla"
            name: "Reviewer"
        }
    }

    Rectangle {
        radius: 10

        // 4 как бы кнопки
        // 1 - выбор типа репозитория
        // 2 - настройки репозитория(в зависимости от типа репозитория)
        // 3 ... дополнительные поля, если нужно( у репозитория)
        // 3 - общая информация по настройкам где нажимаем начать клонирование

        ListView {
            id: view
        }
    }

    width: 100
    height: 62

    StackView {
        id: stackView;
    }
}


