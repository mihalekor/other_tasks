QT += quick network sql

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        CoreEngine.cpp \
        main.cpp

RESOURCES += qml.qrc

#OPENSSL_LINKING_MODE = "-linked"
#INSTALLS += openssl

#LIBS += /home/mihalekor/code/githab/other_tasks/RekSoftTest/libcrypto.so \
#        /home/mihalekor/code/githab/other_tasks/RekSoftTest/libssl.so

#LIBS += -lssl -lcrypto

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
  CoreEngine.h

LIBS += -L$$PWD -lCommonMobiled1
