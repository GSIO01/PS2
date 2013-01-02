ADD_SUBDIRECTORY(Core)
ADD_SUBDIRECTORY(Export)
ADD_SUBDIRECTORY(Functions)
ADD_SUBDIRECTORY(Models)
ADD_SUBDIRECTORY(Primitives)
ADD_SUBDIRECTORY(Widgets)

SET (QCURVE_SRCS ${QCURVE_SRCS}
                 src/parameteredit.cpp
                 src/variableedit.cpp
                 src/graph2d.cpp
                 src/functionwidget.cpp
                 src/mainwindow.cpp
                 src/main.cpp)

SET (QCURVE_SRCS ${QCURVE_SRCS} PARENT_SCOPE)