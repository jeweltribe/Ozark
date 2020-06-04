#include "virtualpanel.h"
#include <QVBoxLayout>
#include <QPainter>
#include <QTextStream>
#include <QPixmap>

PSAVirtualPanel::PSAVirtualPanel(QWidget *parent)
	: QWidget(parent) {	

   /* Pause Button */
   pauseButton = new QPushButton("Pause", this);
   pauseButton->setGeometry(110, 60, 100, 30);
   pauseButton->setStyleSheet("background-color: rgb(78, 154, 6); color: rgb(255, 255, 255)");

   /* Formfeed button */
   formFeedButton = new QPushButton("Form feed", this);
   formFeedButton->setGeometry(230, 60, 100, 30);
   formFeedButton->setStyleSheet("color: rgb(255, 255, 255); background-color: rgb(32, 74, 135)");

   /* Left soft key button */
   leftSoftKeyButton = new QPushButton(" ", this);
   leftSoftKeyButton->setGeometry(50, 385, 40, 90);
   leftSoftKeyButton->setStyleSheet("background-color: rgb(46, 52, 54)");

   /* Right soft key button */
   rightSoftKeyButton = new QPushButton(" ", this);
   rightSoftKeyButton->setGeometry(330, 385, 40, 90);
   rightSoftKeyButton->setStyleSheet("background-color: rgb(46, 52, 54)");
   
   /* Up key button */
   upKeyButton = new QPushButton("Up", this);
   upKeyButton->setGeometry(165, 360, 90, 30);
   upKeyButton->setStyleSheet("background-color: rgb(46, 52, 54); color: rgb(255, 255, 255)");
   
   /* Down key button */
   downKeyButton = new QPushButton("Down", this);
   downKeyButton->setGeometry(165, 470, 90, 30);
   downKeyButton->setStyleSheet("background-color: rgb(46, 52, 54); color: rgb(255, 255, 255)");
   
   /* Left key button */
   leftKeyButton = new QPushButton("L", this);
   leftKeyButton->setGeometry(130, 380, 30, 100);
   leftKeyButton->setStyleSheet("background-color: rgb(46, 52, 54); color: rgb(255, 255, 255)");
   
   /* Right key button */
   rightKeyButton = new QPushButton("R", this);
   rightKeyButton->setGeometry(260, 380, 30, 100);
   rightKeyButton->setStyleSheet("background-color: rgb(46, 52, 54); color: rgb(255, 255, 255)");
   
   /* Enter button */
   enterKeyButton = new QPushButton("Enter", this);
   enterKeyButton->setGeometry(175, 400, 70, 60);
   enterKeyButton->setStyleSheet("background-color: rgb(46, 52, 54); color: rgb(255, 255, 255)");
   
   /* Initialize lcd panel frame */
   lcdFrame = new QFrame(this);
   QGridLayout *grid = new QGridLayout(lcdFrame);

   /* Set absolute position of frame and set width and height */
   lcdFrame->setGeometry(70, 120, 291, 221);

   /* Background color of lcd frame is white */
   lcdFrame->setStyleSheet("background-color: white");

   /* Initialize label components */
   ipAddrLabel = new QLabel("192.168.201.197");
   statusLabel = new QLabel("ONLINE");
   serverNameLabel = new QLabel("P-90a311");
   modelStringLabel = new QLabel("T8204");
   stringThingyLabel = new QLabel("ETHERNET/PGL/LP+");
   configLabel = new QLabel("Config");
   activeConfigLabel = new QLabel("Factory");
   printHeadLabel = new QLabel("Print Head");
   ribbonLabel = new QLabel("Ribbon");
   /* Set print head progress bar */
   printHeadPBar = new QProgressBar();
   printHeadPBar->setValue(95);
   /* Set ribbon progress bar */
   ribbonLifePBar = new QProgressBar();
   ribbonLifePBar->setValue(45);

   /* Initialize the icon images for the offline menu */
   QPixmap wizardPng("icons/icon_Setup-wizard_normal.png");
   QPixmap settingsPng("icons/icon_Settings_normal.png");
   QPixmap calibratePng("icons/icon_Calibrate_normal.png");

   /* Set the icons for the label */
   wizardPixmap = new QLabel();
   wizardPixmap->setPixmap(wizardPng);
   wizardPixmap->setMinimumSize(90, 90);

   settingsPixmap = new QLabel();
   settingsPixmap->setPixmap(settingsPng);
   settingsPixmap->setStyleSheet("background-color: rgb(187, 247, 161)");
   settingsPixmap->setMinimumSize(90, 90);

   calibratePixmap = new QLabel();
   calibratePixmap->setPixmap(calibratePng);
   calibratePixmap->setMinimumSize(90, 90);

   wizardLabel = new QLabel("Wizard");
   wizardLabel->setStyleSheet("color: rgb(77, 153, 176)");
   settingsLabel = new QLabel("Settings");
   settingsLabel->setStyleSheet("color: rgb(77, 153, 176)");
   calibrateLabel = new QLabel("Calibrate");
   calibrateLabel->setStyleSheet("color: rgb(77, 153, 176)");

   QLabel *dummy = new QLabel();
   dummy->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
   dummy->setText("OFFLINE");
   dummy->setAlignment(Qt::AlignRight);
   dummy->setStyleSheet("background-color: rgb(80, 153, 199); color: white");

   QLabel *dummy2 = new QLabel();
   dummy2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
   dummy2->setText("Info");
   dummy2->setAlignment(Qt::AlignRight);
   dummy2->setStyleSheet("background-color: grey");

   grid->addWidget(dummy, 0, 0, 1, 3);

   grid->addWidget(wizardPixmap, 1, 0, Qt::AlignCenter);
   grid->addWidget(wizardLabel, 2, 0, Qt::AlignHCenter);

   grid->addWidget(settingsPixmap, 1, 1, Qt::AlignCenter);
   grid->addWidget(settingsLabel, 2, 1, Qt::AlignHCenter);

   grid->addWidget(calibratePixmap, 1, 2, Qt::AlignCenter);
   grid->addWidget(calibrateLabel, 2, 2, Qt::AlignHCenter);

   grid->addWidget(dummy2, 3, 0, 1, 3);

   /* Connect the button signals and slots */
   connect(pauseButton, &QPushButton::clicked, this, &PSAVirtualPanel::pause);
   connect(formFeedButton, &QPushButton::clicked, this, &PSAVirtualPanel::formFeed);
   connect(leftSoftKeyButton, &QPushButton::clicked, this, &PSAVirtualPanel::leftSoftKey);
   connect(rightSoftKeyButton, &QPushButton::clicked, this, &PSAVirtualPanel::rightSoftKey);
   connect(upKeyButton, &QPushButton::clicked, this, &PSAVirtualPanel::upKey);
   connect(downKeyButton, &QPushButton::clicked, this, &PSAVirtualPanel::downKey);
   connect(leftKeyButton, &QPushButton::clicked, this, &PSAVirtualPanel::leftKey);
   connect(rightKeyButton, &QPushButton::clicked, this, &PSAVirtualPanel::rightKey);
   connect(enterKeyButton, &QPushButton::clicked, this, &PSAVirtualPanel::enterKey);

   /* Set the title and size of the QWidget window */
   setWindowTitle("PSA Virtual Panel");
   
}

void PSAVirtualPanel::pause() {
   QTextStream out(stdout);
   out << "pause" << endl;
}

void PSAVirtualPanel::formFeed() {
   QTextStream out(stdout);
   out << "form feed" << endl;
}

void PSAVirtualPanel::arrowKeyEvent(int currSelection, int key) {
   QTextStream out(stdout);
   out << "arrow key" << endl;

   if (currSelection <= 2 && key != UP_KEY && key != DOWN_KEY) {
      if (currSelection == SETTINGS) {
         /* reset the background-color */
         settingsPixmap->setStyleSheet("");
         if (key == LEFT_KEY) {
            selection--;
            wizardPixmap->setStyleSheet("background-color: rgb(187, 247, 161)"); 
         } else if (key == RIGHT_KEY) {
            selection++;
            calibratePixmap->setStyleSheet("background-color: rgb(187, 247, 161)");
         }
      } else if (currSelection == WIZARD) {
         wizardPixmap->setStyleSheet("");
         if (key == LEFT_KEY) {
            selection = 2;
	    calibratePixmap->setStyleSheet("background-color: rgb(187, 247, 161)");
         } else if (key == RIGHT_KEY) {
            selection++;
	    settingsPixmap->setStyleSheet("background-color: rgb(187, 247, 161)");
         }

      } else if (currSelection == CALIBRATE) {
         calibratePixmap->setStyleSheet("");
         if (key == LEFT_KEY) {
            selection--;
	    settingsPixmap->setStyleSheet("background-color: rgb(187, 247, 161)");
         } else if (key == RIGHT_KEY) {
            selection = 0;
            wizardPixmap->setStyleSheet("background-color: rgb(187, 247, 161)");
         }
      }
   }
}

void PSAVirtualPanel::leftSoftKey() {
   QTextStream out(stdout);
   out << "left soft key" << endl;
}

void PSAVirtualPanel::rightSoftKey() {
   QTextStream out(stdout);
   out << "right soft key" << endl;
}

void PSAVirtualPanel::enterKey() {
   QTextStream out(stdout);
   out << "enter key" << endl;
}

void PSAVirtualPanel::upKey() {
   arrowKeyEvent(selection, UP_KEY);
}

void PSAVirtualPanel::downKey() {
   arrowKeyEvent(selection, DOWN_KEY);
}

void PSAVirtualPanel::leftKey() {
   arrowKeyEvent(selection, LEFT_KEY);
}

void PSAVirtualPanel::rightKey() {
   arrowKeyEvent(selection, RIGHT_KEY);
}
