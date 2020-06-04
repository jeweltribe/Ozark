#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QProgressBar>
#include <QGridLayout>

class PSAVirtualPanel : public QWidget {

   public: 
      PSAVirtualPanel(QWidget *parent = 0);

   private:
      /* Default selection is Settings */
      int selection = 1;

      /* Selection constants */
      const int WIZARD = 0;
      const int SETTINGS = 1;
      const int CALIBRATE = 2;

      /* Key Constants */
      const int UP_KEY = 0;
      const int LEFT_KEY = 1;
      const int RIGHT_KEY = 2;
      const int DOWN_KEY = 3;

      /* Front Panel Buttons */
      QPushButton *pauseButton;
      QPushButton *formFeedButton;
      QPushButton *leftSoftKeyButton;
      QPushButton *rightSoftKeyButton;
      QPushButton *upKeyButton;
      QPushButton *downKeyButton;
      QPushButton *leftKeyButton;
      QPushButton *rightKeyButton;
      QPushButton *enterKeyButton;

      /* LCD Panel */
      QFrame *lcdFrame;

      /* Layout for lcdFrame */
      QGridLayout *grid;

      /* Online components for LCD */
      QLabel *ipAddrLabel;
      QLabel *statusLabel;
      QLabel *serverNameLabel;
      QLabel *modelStringLabel;
      QLabel *stringThingyLabel;
      QLabel *configLabel;
      QLabel *activeConfigLabel;
      QLabel *printHeadLabel;
      QLabel *ribbonLabel;

      QProgressBar *printHeadPBar;
      QProgressBar *ribbonLifePBar;

      /* Offline Components */
      QLabel *wizardPixmap;
      QLabel *settingsPixmap;
      QLabel *calibratePixmap;

      QLabel *wizardLabel;
      QLabel *settingsLabel;
      QLabel *calibrateLabel;

   private slots:
      /* Event handlers for the buttons */
      void pause();
      void formFeed();
      void upKey();
      void downKey();
      void leftKey();
      void rightKey();
      void arrowKeyEvent(int currSelection, int key);
      void leftSoftKey();
      void rightSoftKey();
      void enterKey();
};
