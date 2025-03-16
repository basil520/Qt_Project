cmake_minimum_required(VERSION 3.16)
project(Qt_Project LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

set(Qt5_DIR /home/lofge/Qt/5.15.2/gcc_64/lib/cmake/Qt5)
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

include_directories(uDDS/include)

link_directories(uDDS/debug)

set(HEADERS
        src/MainWindow.h
        src/MyWidget.h
        src/TableWidget.h
        src/TreeWidget.h
        src/DDSTextWidget.h
        src/IDL/IDL_DataReader.h
        src/IDL/IDL_DataWriter.h
        src/IDL/IDL_StringMessage.h
        src/IDL/IDL_TypeSupport.h
)
set(SOURCES
        main.cpp
        src/MainWindow.cpp
        src/MyWidget.cpp
        src/TableWidget.cpp
        src/TreeWidget.cpp
        src/DDSTextWidget.cpp
        src/IDL/IDL_DataReader.cpp
        src/IDL/IDL_DataWriter.cpp
        src/IDL/IDL_StringMessage.cpp
)
set(FORMS
)
set(RESOURCES
        res.qrc
)

QT5_WRAP_CPP(HEADERS_MOC ${HEADERS})
QT5_WRAP_UI(FORMS_HEADERS ${FORMS})
QT5_ADD_RESOURCES(RESOURCES_RCC ${RESOURCES})

add_executable(${PROJECT_NAME}
        ${FORMS_HEADERS}
        ${RESOURCES_RCC}
        ${HEADERS_MOC}
        ${SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        uDDSd
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
