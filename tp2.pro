CONFIG += c++11
CONFIG -= qt

OBJECTS_DIR = obj

INCLUDEPATH += include/lodepng include/glm
SOURCES += include/lodepng/lodepng.cpp

HEADERS += $$files(src/*.h)
SOURCES += $$files(src/*.cpp)
OTHER_FILES += $$files(scenes/*.scn, true)
