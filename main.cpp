#include <QApplication>
#include "virtualpanel.h"

int main(int argc, char *argv[]) {

   QApplication app(argc, argv);

   PSAVirtualPanel window;

   /* Set width and height of window */
   window.resize(438, 588);

   /* Set background color to black */
   window.setStyleSheet("background-color: rgb(46, 52, 54)");
   window.show();

   /* Start the main event loop that handles user actions */
   return app.exec();
}
