#include <QApplication>
#include <GUI/cgui.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CGUI w;
    w.show();
    
    return a.exec();
}
