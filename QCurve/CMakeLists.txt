PROJECT(QCurve)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.5)
SET(CMAKE_AUTOMOC TRUE)

FIND_PACKAGE(Qt4 4.7 REQUIRED QtCore QtGui QtXml)

INCLUDE_DIRECTORIES(${QT_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_BINARY_DIR})

SET(QCurve_SRC src/Core/variable.cpp src/Core/parameter.cpp src/Core/point.cpp src/Core/function.cpp
               src/Functions/ellipse.cpp src/Functions/cissoid.cpp src/Functions/hyperbola.cpp src/Functions/lemniscate.cpp
               src/Functions/limacon.cpp src/Functions/parabola.cpp src/Functions/strophoid.cpp
               src/Widgets/qtmmlwidget.cpp src/Widgets/splitter.cpp
               src/Models/treeitem.cpp src/Models/functionitemmodel.cpp
               src/graph2d.cpp src/functionwidget.cpp src/mainwindow.cpp src/main.cpp)

ADD_EXECUTABLE(QCurve ${QCurve_SRC})
TARGET_LINK_LIBRARIES(QCurve ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTXML_LIBRARY})