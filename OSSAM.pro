TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    Entity.cpp \
    Entities/Player.cpp \
    Items/Weapons/Weapon.cpp \
    Items/Weapons/Bullet.cpp \
    Game.cpp \
    Entities/Spaceship.cpp \
    Entities/Ennemy.cpp \
    System/Timer.cpp \
    System/Animation.cpp \
    System/ATH.cpp \
    Items/Shield.cpp \
    Items/Item.cpp \
    System/Inventory.cpp \
    System/UserInterface.cpp \
    System/UI/UI_Button.cpp \
    System/UI/UI_Slot.cpp \
    Items/Weapons/Bullet/Missile.cpp \
    Items/Weapons/Bullet/Laser.cpp \
    Entities/IA/IA_Node.cpp \
    Entities/IA/IA_Sequencer.cpp

include(deployment.pri)
qtcAddDeployment()

INCLUDEPATH += C:/SFML/SFML_Build/SFML-2.3.2-sources-Debug-4.9.1/include
DEPENDPATH += C:/SFML/SFML_Build/SFML-2.3.2-sources-Debug-4.9.1/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../SFML_Build/SFML-2.3.2-Build-Debug-4.9.1/lib/ -lsfml-system-
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../SFML_Build/SFML-2.3.2-Build-Debug-4.9.1/lib/ -lsfml-system-d

INCLUDEPATH += $$PWD/../../../SFML_Build/SFML-2.3.2-Build-Debug-4.9.1/lib
DEPENDPATH += $$PWD/../../../SFML_Build/SFML-2.3.2-Build-Debug-4.9.1/lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../SFML_Build/SFML-2.3.2-Build-Debug-4.9.1/lib/ -lsfml-window-
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../SFML_Build/SFML-2.3.2-Build-Debug-4.9.1/lib/ -lsfml-window-d
else:unix: LIBS += -L$$PWD/../../../SFML_Build/SFML-2.3.2-Build-Debug-4.9.1/lib/ -lsfml-window-

INCLUDEPATH += $$PWD/../../../SFML_Build/SFML-2.3.2-Build-Debug-4.9.1/lib
DEPENDPATH += $$PWD/../../../SFML_Build/SFML-2.3.2-Build-Debug-4.9.1/lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../SFML_Build/SFML-2.3.2-Build-Debug-4.9.1/lib/ -lsfml-graphics-
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../SFML_Build/SFML-2.3.2-Build-Debug-4.9.1/lib/ -lsfml-graphics-d
else:unix: LIBS += -L$$PWD/../../../SFML_Build/SFML-2.3.2-Build-Debug-4.9.1/lib/ -lsfml-graphics-

INCLUDEPATH += $$PWD/../../../SFML_Build/SFML-2.3.2-Build-Debug-4.9.1/include/
DEPENDPATH += $$PWD/../../../SFML_Build/SFML-2.3.2-Build-Debug-4.9.1/include/

HEADERS += \
    Entity.h \
    Entities/Player.h \
    Items/Weapons/Weapon.h \
    Items/Weapons/Bullet.h \
    Game.h \
    main.h \
    Entities/Spaceship.h \
    Entities/Ennemy.h \
    System/Timer.h \
    System/Animation.h \
    System/ATH.h \
    Items/Shield.h \
    Items/Item.h \
    System/Inventory.h \
    System/UserInterface.h \
    System/UI/UI_Button.h \
    System/UI/UI_Slot.h \
    Items/Weapons/Bullet/Missile.h \
    Items/Weapons/Bullet/Laser.h \
    Entities/IA/IA_Node.h \
    Entities/IA/IA_Sequencer.h
