# Add more folders to ship with the application, here
folder_01.source = qml/fileManager
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01


QT += qml quick \
        widgets \
        xml


# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    shell/tshell.cpp \
    shell/shellcommand.cpp \
    repository/trepository.cpp \
    parsing_command_out/iparsingcommandout.cpp \
    parsing_command_out/parsingcommandclone.cpp \
    parsing_command_out/parsingcommandget.cpp \
    parsing_command_out/parsingcommandwhereis.cpp \
    parsing_command_out/parsingcommanddrop.cpp \
    systemtray.cpp \
    repository/irepository.cpp \
    facadeapplication.cpp \
    MVC/Controller/controller_repository.cpp \
    MVC/Model/model_repository.cpp \
    shell/shelltask.cpp \
    resourcegenerator.cpp \
    MVC/Controller/controller_icons.cpp \
    MVC/Model/model_icons.cpp \
    qml/components/error_message/qmlerrormessage.cpp \
    parsing_command_out/parsingcommandempty.cpp \
   # qml/components/folder_model/myqdeclarativefolderlistmodelprivate.cpp
    qml/components/folder_model/folderlistmodel.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    qml/fileManager/WindowContent.qml \
    qml/fileManager/DirectoryView.qml \
    qml/fileManager/propertyFile/PropertyFile.qml \
    qml/fileManager/getContent/GetContent.qml \
    qml/fileManager/repository/Clone.qml \

INCLUDEPATH += iniparser/

RESOURCES += \
    Resource.qrc \
    ResourceIcons.qrc

HEADERS += \
    shell/tshell.h \
    shell/shellcommand.h \
    repository/trepository.h \
    repository/irepository.h \
    parsing_command_out/iparsingcommandout.h \
    parsing_command_out/parsingcommandclone.h \
    parsing_command_out/parsingcommandget.h \
    parsing_command_out/parsingcommandwhereis.h \
    parsing_command_out/parsingcommanddrop.h \
    systemtray.h \
    facadeapplication.h \
    MVC/Controller/controller_repository.h \
    MVC/Model/model_repository.h \
    define.h \
    MVC/Model/model_updateviewer.h \
    shell/shelltask.h \
    resourcegenerator.h \
    MVC/Controller/controller_icons.h \
    MVC/Model/model_icons.h \
    iniparser/iniparser.h \
    iniparser/dictionary.h \
    qml/components/error_message/qmlerrormessage.h \
    parsing_command_out/parsingcommandempty.h \
  #  qml/components/folder_model/myqdeclarativefolderlistmodelprivate.h
    qml/components/folder_model/folderlistmodel.h

# Включаем поддержку С++11
QMAKE_CXXFLAGS += -std=c++0x

LIBS += -lboost_system \
        -lboost_filesystem \
        libiniparser.a
