# Add more folders to ship with the application, here
folder_01.source = qml/fileManager
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01


QT += qml quick

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
    parsing_command_out/parsingcommandclone.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    qml/fileManager/WindowContent.qml \
    qml/fileManager/DirectoryView.qml \
    qml/fileManager/propertyFile/PropertyFile.qml \
    qml/fileManager/getContent/GetContent.qml

RESOURCES += \
    Resource.qrc

HEADERS += \
    shell/tshell.h \
    shell/shellcommand.h \
    repository/trepository.h \
    repository/irepository.h \
    parsing_command_out/iparsingcommandout.h \
    parsing_command_out/parsingcommandclone.h

# Включаем поддержку С++11
QMAKE_CXXFLAGS += -std=c++0x
