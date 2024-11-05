cmake_minimum_required(VERSION 3.16)

project(SufPaint VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SufPaint
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        # enums
        Enums.h
        EnumFunctions.h EnumFunctions.cpp

        # menu and toolbar
        Menu/cmenu.h Menu/cmenu.cpp
        Menu/cmenubase.h Menu/cmenubase.cpp
        Menu/cfilemenu.h Menu/cfilemenu.cpp
        Menu/ceditmenu.h Menu/ceditmenu.cpp
        Menu/cviewmenu.h Menu/cviewmenu.cpp
        Menu/chelpmenu.h Menu/chelpmenu.cpp
        Menu/ctoolbar.h Menu/ctoolbar.cpp
        Menu/cadjustmentmenu.h Menu/cadjustmentmenu.cpp
        Menu/cimagemenu.h Menu/cimagemenu.cpp

        # statusbar
        Statusbar/cstatusbar.h Statusbar/cstatusbar.cpp
        Statusbar/cstatusbartoollabel.h Statusbar/cstatusbartoollabel.cpp
        Statusbar/cstatusbarzoomlabel.h Statusbar/cstatusbarzoomlabel.cpp
        Statusbar/cstatusbarimagelabel.h Statusbar/cstatusbarimagelabel.cpp
		
        #management
        Management/cactionmanager.h Management/cactionmanager.cpp
        Management/ccolormanager.h Management/ccolormanager.cpp
        Management/cimagemanager.h Management/cimagemanager.cpp
        Management/cimageviewmanager.cpp Management/cimageviewmanager.h
        Management/ctoolmanager.h Management/ctoolmanager.cpp

        #widgets
        Widgets/ccolorwidget.cpp Widgets/ccolorwidget.h
        Widgets/cimageview.cpp Widgets/cimageview.h
        Widgets/clayerwidget.cpp Widgets/clayerwidget.h
        Widgets/ctoolwidget.cpp Widgets/ctoolwidget.h
        Widgets/ctoolbutton.h Widgets/ctoolbutton.cpp
        Widgets/ccolorpalettewidget.h Widgets/ccolorpalettewidget.cpp
        Widgets/ccolorpreviewwidget.h Widgets/ccolorpreviewwidget.cpp
        Widgets/ccolorrgbawidget.h Widgets/ccolorrgbawidget.cpp
        Widgets/ccolorhistorywidget.h Widgets/ccolorhistorywidget.cpp

        #dialogues
        Dialogues/cimageresizedialog.h Dialogues/cimageresizedialog.cpp Dialogues/cimageresizedialog.ui
        Dialogues/ccanvasresizedialog.h Dialogues/ccanvasresizedialog.cpp Dialogues/ccanvasresizedialog.ui
        Dialogues/cnewimagedialog.h Dialogues/cnewimagedialog.cpp Dialogues/cnewimagedialog.ui

        #tools
        Tools/ctool.h Tools/ctool.cpp
        Tools/ccolorpickertool.h Tools/ccolorpickertool.cpp
        Tools/crectangleselectiontool.cpp Tools/crectangleselectiontool.h
        Tools/cbrushtool.cpp Tools/cbrushtool.h
        Tools/cpenciltool.cpp Tools/cpenciltool.h
        Tools/cbuckettool.cpp Tools/cbuckettool.h
        Tools/cgradienttool.cpp Tools/cgradienttool.h
        Tools/clinestool.cpp Tools/clinestool.h

        #image processing
        cimageprocessor.h cimageprocessor.cpp

        #icons
        Icons/Brush.png Icons/Pencil.png Icons/Pipette.png

        #misc
        Misc/ccolorpatternimage.h Misc/ccolorpatternimage.cpp
        Misc/debugtools.h Misc/debugtools.cpp
        Misc/cselection.cpp Misc/cselection.h
        Misc/cimageviewtransform.h Misc/cimageviewtransform.cpp
        cconnector.cpp cconnector.h

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SufPaint APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SufPaint SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SufPaint
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(SufPaint PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.SufPaint)
endif()
set_target_properties(SufPaint PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS SufPaint
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SufPaint)
endif()
