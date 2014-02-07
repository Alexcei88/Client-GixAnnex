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
    parsing_command_out/parsingcommandempty.cpp \
    qml/components/folder_model/folderlistmodel.cpp \
    qml/components/message_box/qmlmessage.cpp \
    parsing_command_out/parsingcommanddirectmode.cpp \
    analyze_execute_command/analyzeexecutecommandget.cpp \
    analyze_execute_command/analyzeexecutecommand.cpp \
    analyze_execute_command/facadeanalyzecommand.cpp \
    analyze_execute_command/analyzeexecutecommanddrop.cpp \
    analyze_execute_command/analizediraction.cpp \
    utils/utils.cpp \
    parsing_command_out/parsingcommandfind.cpp \
    analyze_execute_command/analyzeexecutecommandfind.cpp \
    threadsyncicons.cpp \
    threadsyncrepository.cpp \
    analyze_execute_command/analyzeexecutecommandclone.cpp \
    analyze_execute_command/analyzeexecutecommandinit.cpp

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

QMAKE_LIBDIR += $$_PRO_FILE_PWD_/iniparser/

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
    shell/shelltask.h \
    resourcegenerator.h \
    MVC/Controller/controller_icons.h \
    MVC/Model/model_icons.h \
    iniparser/iniparser.h \
    iniparser/dictionary.h \
    parsing_command_out/parsingcommandempty.h \
    qml/components/folder_model/folderlistmodel.h \
    qml/components/message_box/qmlmessage.h \
    threadmodel.h \
    parsing_command_out/parsingcommanddirectmode.h \
    analyze_execute_command/analyzeexecutecommandget.h \
    analyze_execute_command/analyzeexecutecommand.h \
    analyze_execute_command/facadeanalyzecommand.h \
    utils/utils.h \
    analyze_execute_command/analyzeexecutecommanddrop.h \
    analyze_execute_command/analizediraction.h \
    parsing_command_out/parsingcommandfind.h \
    analyze_execute_command/analyzeexecutecommandfind.h \
    threadsyncicons.h \
    threadsyncrepository.h \
    analyze_execute_command/analyzeexecutecommandclone.h \
    analyze_execute_command/analyzeexecutecommandinit.h

# Включаем поддержку С++11
QMAKE_CXXFLAGS += -std=c++0x


LIBS += -lboost_system \
        -lboost_filesystem \
        -liniparser
