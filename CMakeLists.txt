cmake_minimum_required(VERSION 3.14)

project(TranslatorPrototype LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Gui Widgets LinguistTools REQUIRED)

set(TRANSLATE_PATH ${CMAKE_CURRENT_LIST_DIR}/translations)

set(TS_FILES ${TRANSLATE_PATH}/zh_CN.ts ${TRANSLATE_PATH}/zh_TW.ts)

set(CREATE_TS_FILES OFF)
if(CREATE_TS_FILES)
    message("=========creating ts files")
    qt5_create_translation(QM_FILES ${CMAKE_CURRENT_LIST_DIR} ${TS_FILES})
else()
    if (QT_VERSION VERSION_LESS 5.15.0)
        message("=====TS_FILES====${TS_FILES}")
        qt5_add_translation(QM_FILES ${TS_FILES})
        message("=====QM FILES====${QM_FILES}")
    else()
        message("=====TS_FILES====${QM_FILES}")
        qt_add_translation(QM_FILES ${TS_FILES})
        message("=====QM FILES====${QM_FILES}")
    endif()
endif(CREATE_TS_FILES)

include(TranslationUtils)

message("=====QM FILES====${QM_FILES}")
add_app_translations_resource(APP_RES ${QM_FILES})
add_qt_translations_resource(QT_RES zh_CN zh_TW)

add_executable(TranslatorPrototype
  main.cpp Translator.h Translator.cpp
  ${APP_RES}
  ${QT_RES}
)

target_link_libraries(TranslatorPrototype
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Quick
)
