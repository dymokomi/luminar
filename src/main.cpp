#include "viewer.h" 
#include <QApplication>

int main(int argc, char *argv[]) {

    colorama::Color c(0.25, 0.5, 0.75); // Color in linear RGB
    colorama::Color xyz = c.to_xyz();

    std::cout << "Original: " << c.r() << " " << c.g() << " " << c.b() << std::endl;
    std::cout << "XYZ: " << xyz.x() << " " << xyz.y() << " " << xyz.z() << std::endl;

    QApplication app(argc, argv);
    Viewer viewer;
    viewer.show();
    return app.exec();
}