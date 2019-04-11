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
    Entities/IA/IA_Sequencer.cpp \
    System/AnimationKey.cpp \
    System/AnimationKey/RotationKey.cpp \
    System/AnimationKey/TranslationKey.cpp \
    System/EventsGenerator/MiddleGroundGenerator.cpp \
    System/EventsGenerator/GameEvent.cpp \
    System/AnimationKey/ScaleKey.cpp \
    System/Ressources/RessourceHolder.inl \
    System/Scene/SceneNode.cpp

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
    Entities/IA/IA_Sequencer.h \
    System/AnimationKey.h \
    System/AnimationKey/RotationKey.h \
    System/AnimationKey/TranslationKey.h \
    System/AnimationKey/ScaleKey.h \
    System/EventsGenerator/MiddleGroundGenerator.h \
    System/Ressources/RessourceHolder.h \
    System/EventsGenerator/GameEvent.h \
    System/Scene/SceneNode.h \
    System/Ressources/ResourcesIdentifiers.h


win32{
INCLUDEPATH += ../SFML-2.5.0/include
DEPENDPATH += ../SFML-2.5.0/include

CONFIG(release, debug|release): LIBS += -L$$PWD/../../SFML-2.5.0/lib/ -lsfml-system
else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../SFML-2.5.0/lib/ -lsfml-system-d

CONFIG(release, debug|release): LIBS += -L$$PWD/../../SFML-2.5.0/lib/ -lsfml-window
else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../SFML-2.5.0/lib/ -lsfml-window-d

CONFIG(release, debug|release): LIBS += -L$$PWD/../../SFML-2.5.0/lib/ -lsfml-graphics
else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../SFML-2.5.0/lib/ -lsfml-graphics-d

}

unix{
INCLUDEPATH += $$PWD../SFML-2.3.2/include
DEPENDPATH += $$PWD../SFML-2.3.2/include

CONFIG(release, debug|release): LIBS += -L$$PWD/../SFML-2.3.2/lib -lsfml-system-
CONFIG(release, debug|release): LIBS += -L$$PWD/../SFML-2.3.2/lib -lsfml-window-
CONFIG(release, debug|release): LIBS += -L$$PWD/../SFML-2.3.2/lib -lsfml-graphics-


#CONFIG(debug, debug|release): LIBS += -L/usr/lib/x86_64-linux-gnu/ -ljpeg

CONFIG(debug, debug|release): LIBS += -L$$PWD/../SFML-2.3.2/lib -lsfml-system
CONFIG(debug, debug|release): LIBS += -L$$PWD/../SFML-2.3.2/lib -lsfml-window
CONFIG(debug, debug|release): LIBS += -L$$PWD/../SFML-2.3.2/lib -lsfml-graphics

}
