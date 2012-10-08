cmake_minimum_required(VERSION 2.8)

project(MMTI)
find_package(Qt4 REQUIRED)

set(EXECUTABLE_OUTPUT_PATH bin)
set(Qt_HEADERS MMTI_GUI/MainWindow.h)
set(Qt_FORMS MMTI_GUI/MainWindow.ui)


QT4_WRAP_CPP(Qt_HEADERS_MOC ${Qt_HEADERS})
QT4_WRAP_UI(Qt_FORMS_HEADERS ${Qt_FORMS})

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

add_definitions(-Wall -g -DPATH_DATA=\"data/\")

include_directories(src)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(
	GLOB_RECURSE
	mmti_sources
	./src/*.cpp
	./MMTI_GUI/main.cpp
	./MMTI_GUI/MainWindow.cpp
	
)

add_executable(projet ${mmti_sources} ${Qt_HEADERS_MOC} ${Qt_FORMS_HEADERS})

TARGET_LINK_LIBRARIES(projet ${QT_LIBRARIES})
