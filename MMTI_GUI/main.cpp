#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"

#include "MainWindow.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
/*    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/MMTI_GUI/main.qml"));
    viewer.showExpanded();

    QString nomImage("src_name");
    //viewer.rootContext()->setContextProperty("src_name", nomImage);


    return app->exec();*/

    QApplication app(argc, argv);
    MainWindow m;
    m.show();
    return app.exec();



}
