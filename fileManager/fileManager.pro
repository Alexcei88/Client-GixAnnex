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
    analyze_execute_command/analyzeexecutecommandinit.cpp \
    analyze_execute_command/analyzeexecutecommandchangedirectmode.cpp \
    MVC/Controller/controllerpreferencesapp.cpp \
    MVC/Model/model_preferencesapp.cpp \
    MVC/Controller/controlleraddrepository.cpp \
    MVC/Model/AddRepository/imodel_addrepository.cpp \
    MVC/Model/AddRepository/model_addrepository_remoteserver.cpp \
    qml/components/validatorfilesystem.cpp \
    MVC/Model/AddRepository/model_addrepository_other.cpp \
    qml/components/treemodel.cpp \
    analyze_execute_command/analyzeexecutecommandcopy.cpp \
    parsing_command_out/parsingcommandcopy.cpp \
    shell/facade_shellcommand.cpp \
    analyze_execute_command/parsing_error_execute_command/parsingerrorexecutecommand.cpp \
    analyze_execute_command/parsing_error_execute_command/parsingerrorexecutecommandget.cpp \
    analyze_execute_command/parsing_error_execute_command/parsingerrorexecutecommanddrop.cpp \
    analyze_execute_command/parsing_error_execute_command/parsingerrorexecutecommandwithfiles.cpp \
    parsing_command_out/parsingcommandstatus.cpp \
    analyze_execute_command/analizeexecutecommandstatus.cpp \
    preferencesapplication.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    qml/fileManager/WindowContent.qml \
    qml/fileManager/DirectoryView.qml \
    qml/fileManager/propertyFile/PropertyFile.qml \
    qml/fileManager/repository/wait_finish_command.qml \
    qml/fileManager/repository/PropertyInputValue.qml \
    qml/fileManager/repository/wait_clone.qml \
    qml/fileManager/repository/ReviewData.qml \
    qml/fileManager/preferences_repository.qml

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
    analyze_execute_command/analyzeexecutecommandinit.h \
    analyze_execute_command/analyzeexecutecommandchangedirectmode.h \
    MVC/Controller/controllerpreferencesapp.h \
    MVC/Model/model_preferencesapp.h \
    analyze_execute_command/analyzeexecutecommandcopy.h \
    parsing_command_out/parsingcommandcopy.h \
    shell/facade_shellcommand.h \
    MVC/Controller/controlleraddrepository.h \
    MVC/Model/AddRepository/imodel_addrepository.h \
    MVC/Model/AddRepository/model_addrepository_remoteserver.h \
    qml/components/validatorfilesystem.h \
    MVC/Model/AddRepository/model_addrepository_other.h \
    qml/components/treemodel.h \
    analyze_execute_command/parsing_error_execute_command/parsingerrorexecutecommand.h \
    analyze_execute_command/parsing_error_execute_command/parsingerrorexecutecommandget.h \
    analyze_execute_command/parsing_error_execute_command/parsingerrorexecutecommanddrop.h \
    analyze_execute_command/parsing_error_execute_command/parsingerrorexecutecommandwithfiles.h \
    parsing_command_out/parsingcommandstatus.h \
    analyze_execute_command/analizeexecutecommandstatus.h \
    preferencesapplication.h

# Включаем поддержку С++11
QMAKE_CXXFLAGS += -std=c++0x

LIBS += -lboost_system \
        -lboost_filesystem \
        -liniparser
