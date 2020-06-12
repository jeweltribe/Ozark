#include "virtualpanel.h"
#include <QVBoxLayout>
#include <QPainter>
#include <QTextStream>
#include <QPixmap>

PSAVirtualPanel::PSAVirtualPanel(QWidget *parent)
	: QWidget(parent) {	

   /* Front Panel Buttons */
   pauseButton = createButtonImage("icons/PanelPause.png", 100, 60, 100, 30);
   formFeedButton = createButtonImage("icons/PanelFeed.png", 230, 60, 100, 30);
   upKeyButton = createButtonImage("icons/PanelUp.png", 165, 360, 90, 30);
   downKeyButton = createButtonImage("icons/PanelDown.png", 165, 470, 90, 30);
   leftKeyButton = createButtonImage("icons/PanelLeft.png", 130, 380, 30, 100);
   rightKeyButton = createButtonImage("icons/PanelRight.png", 260, 380, 30, 100);
   enterKeyButton = createButtonImage("icons/PanelEnter.png", 175, 400, 70, 60);

   /* Left soft key button */
   leftSoftKeyButton = new QPushButton(" ", this);
   leftSoftKeyButton->setGeometry(50, 385, 40, 90);
   leftSoftKeyButton->setStyleSheet("background-color: rgb(46, 52, 54)");

   /* Right soft key button */
   rightSoftKeyButton = new QPushButton(" ", this);
   rightSoftKeyButton->setGeometry(330, 385, 40, 90);
   rightSoftKeyButton->setStyleSheet("background-color: rgb(46, 52, 54)");
   
   /* Initialize lcd panel frame */
   lcdFrame = new QFrame(this);
   grid = new QGridLayout(lcdFrame);

   /* Set absolute position of frame and set width and height */
   lcdFrame->setGeometry(70, 120, 291, 221);

   /* Background color of lcd frame is white */
   lcdFrame->setStyleSheet("background-color: white");

   /* Set the icons for top level menus */
   wizardIcon = createLabel("icons/icon_Setup-wizard_normal.png", "   Wizard  ");
   calibrateIcon = createLabel("icons/icon_Calibrate_normal.png", " Calibrate ");
   settingsIcon = createLabel("icons/icon_Settings_normal.png", " Settings  ");

   /* Set the icons for sub level menus */
   quickIcon = createLabel("icons/icon_Quick_normal.png", "Quick Setup");
   mediaIcon = createLabel("icons/icon_Media_normal.png", "   Media   ");
   sensorIcon = createLabel("icons/icon_Sensors_normal.png", "  Sensors  ");
   systemIcon = createLabel("icons/icon_System_normal.png", "  System   ");
   hostIcon = createLabel("icons/icon_HostIO_normal.png", " Host I/O  ");
   networkIcon = createLabel("icons/icon_Network_normal.png", "  Network  ");

   appIcon = createLabel("icons/icon_Applications_normal.png", "Application");
   odvIcon = createLabel("icons/icon_Validator2D_normal.png", "   ODV2D   ");
   toolsIcon = createLabel("icons/icon_Tools_normal.png", "   Tools   ");
   configsIcon = createLabel("icons/icon_Configuration_normal.png", "  Configs  ");

   topLabel = new QLabel();
   topLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
   topLabel->setStyleSheet("background-color: rgb(80, 153, 199); color: white");

   bottomLabel = new QLabel();
   bottomLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
   bottomLabel->setStyleSheet("background-color: grey");
  
   /* Config printout */ 
   cfg = new QTextEdit();

   buildOfflineMenu();

   topMenuList = new QListWidget();
   topMenuList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   topMenuList->setStyleSheet(boldFont + ";" + itemColor + ";" + listSelection);
   subMenuList = new QListWidget();
   subMenuList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   subMenuList->setStyleSheet(boldFont + ";" + itemColor + ";" + listSelection);
   fullMenuList = new QListWidget();
   fullMenuList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   fullMenuList->setStyleSheet(boldFont + ";" + itemColor + ";" + listSelection);

   /* Connect the button signals and slots for click actions*/
   connect(pauseButton, &QPushButton::clicked, this, &PSAVirtualPanel::pause);
   connect(formFeedButton, &QPushButton::clicked, this, &PSAVirtualPanel::formFeed);
   connect(leftSoftKeyButton, &QPushButton::clicked, this, &PSAVirtualPanel::leftSoftKey);
   connect(rightSoftKeyButton, &QPushButton::clicked, this, &PSAVirtualPanel::rightSoftKey);
   connect(upKeyButton, &QPushButton::clicked, this, &PSAVirtualPanel::upKey);
   connect(downKeyButton, &QPushButton::clicked, this, &PSAVirtualPanel::downKey);
   connect(leftKeyButton, &QPushButton::clicked, this, &PSAVirtualPanel::leftKey);
   connect(rightKeyButton, &QPushButton::clicked, this, &PSAVirtualPanel::rightKey);
   connect(enterKeyButton, &QPushButton::clicked, this, &PSAVirtualPanel::enterKey);
   
   /* pressed actions */
   connect(enterKeyButton, &QPushButton::pressed, this, &PSAVirtualPanel::enterHold);
   connect(upKeyButton, &QPushButton::pressed, this, &PSAVirtualPanel::upHold);
   connect(downKeyButton, &QPushButton::pressed, this, &PSAVirtualPanel::downHold);
   connect(leftKeyButton, &QPushButton::pressed, this, &PSAVirtualPanel::leftHold);
   connect(rightKeyButton, &QPushButton::pressed, this, &PSAVirtualPanel::rightHold);
   connect(pauseButton, &QPushButton::pressed, this, &PSAVirtualPanel::pauseHold);
   connect(formFeedButton, &QPushButton::pressed, this, &PSAVirtualPanel::feedHold);

   /* released actions */
   connect(enterKeyButton, &QPushButton::released, this, &PSAVirtualPanel::enterRelease);
   connect(upKeyButton, &QPushButton::released, this, &PSAVirtualPanel::upRelease);
   connect(downKeyButton, &QPushButton::released, this, &PSAVirtualPanel::downRelease);
   connect(leftKeyButton, &QPushButton::released, this, &PSAVirtualPanel::leftRelease);
   connect(rightKeyButton, &QPushButton::released, this, &PSAVirtualPanel::rightRelease);
   connect(pauseButton, &QPushButton::released, this, &PSAVirtualPanel::pauseRelease);
   connect(formFeedButton, &QPushButton::released, this, &PSAVirtualPanel::feedRelease);

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

void PSAVirtualPanel::arrowKeyEvent(int key) {

   if (currSelection <= 2 && key != UP_KEY && key != DOWN_KEY) {

      switch (currSelection) {
	 case SETTINGS:
            settingsIcon->setStyleSheet(defaultColor);
	    switch (key) {
               case LEFT_KEY:
	          selectMenu(WIZARD);
		  break;
	       case RIGHT_KEY:
		  selectMenu(CALIBRATE);
		  break;
	    }
	    break;
	 case WIZARD:
	    wizardIcon->setStyleSheet(defaultColor);
	    switch (key) {
               case LEFT_KEY:
		  selectMenu(CALIBRATE);
	          break;
	       case RIGHT_KEY:
		  selectMenu(SETTINGS);
		  break;
	    }
	    break;
	 case CALIBRATE:
	    calibrateIcon->setStyleSheet(defaultColor);
	    switch (key) {
               case LEFT_KEY:
		  selectMenu(SETTINGS);
	          break;
	       case RIGHT_KEY:
		  selectMenu(WIZARD);
		  break;
	    }
	    break;
      }
   } else if (currSelection >= 3 && currSelection <= 8) {

      switch (currSelection) {
         case QUICK_SETUP:
	    quickIcon->setStyleSheet(defaultColor);
	    switch (key) {
               case UP_KEY:
	       case DOWN_KEY:
	          selectMenu(SYSTEM);
		  break;
	       case RIGHT_KEY:
		  selectMenu(MEDIA);
		  break;
	       case LEFT_KEY:
		  buildSettingsMenu2();
		  break;
	    }
            break;
	 case MEDIA:
	    mediaIcon->setStyleSheet(defaultColor);
	    switch (key) {
	       case UP_KEY:
	       case DOWN_KEY:
	          selectMenu(HOST);
		  break;
	       case LEFT_KEY:
		  selectMenu(QUICK_SETUP);
		  break;
	       case RIGHT_KEY:
		  selectMenu(SENSORS);
		  break;
	    }
	    break;
	 case SENSORS:
	    sensorIcon->setStyleSheet(defaultColor);
	    switch (key) {
               case UP_KEY:
	       case DOWN_KEY:
	          selectMenu(NETWORK);
		  break;
	       case LEFT_KEY:
                  selectMenu(MEDIA);
		  break;
	       case RIGHT_KEY:
		  selectMenu(SYSTEM);
		  break;
	    }
	    break;
	 case SYSTEM:
	    systemIcon->setStyleSheet(defaultColor);
	    switch (key) {
               case UP_KEY:
	       case DOWN_KEY:
	          selectMenu(QUICK_SETUP);
		  break;
	       case LEFT_KEY:
		  selectMenu(SENSORS);
		  break;
	       case RIGHT_KEY:
		  selectMenu(HOST);
		  break;
	    }
	    break;
	 case HOST:
	    hostIcon->setStyleSheet(defaultColor);
	    switch (key) {
               case UP_KEY:
	       case DOWN_KEY:
	          selectMenu(MEDIA);
		  break;
	       case LEFT_KEY:
		  selectMenu(SYSTEM);
		  break;
	       case RIGHT_KEY:
		  selectMenu(NETWORK);
		  break;
	    }
	    break;
	 case NETWORK:
	    networkIcon->setStyleSheet(defaultColor);
	    switch (key) {
               case UP_KEY:
	       case DOWN_KEY:
	          selectMenu(SENSORS);
		  break;
	       case LEFT_KEY:
		  selectMenu(HOST);
		  break;
	       case RIGHT_KEY:
		  buildSettingsMenu2();
		  break;
	    }
	    break;
      }
   } else if (currSelection >= 9 && currSelection <= 12) {

      switch (currSelection) {
         case APPLICATION:
            appIcon->setStyleSheet(defaultColor);
	    switch (key) {
               case UP_KEY:
	       case DOWN_KEY:
	          selectMenu(CONFIGS);
		  break;
	       case LEFT_KEY:
		  buildSettingsMenu();
		  break;
	       case RIGHT_KEY:
		  selectMenu(ODV2D);
		  break;
	    }
            break;
	 case ODV2D:
	    odvIcon->setStyleSheet(defaultColor);
	    switch (key) {
               case LEFT_KEY:
		  selectMenu(APPLICATION);
	          break;
	       case RIGHT_KEY:
		  selectMenu(TOOLS);
		  break;
	    }
	    break;
	 case TOOLS:
	    toolsIcon->setStyleSheet(defaultColor);
	    switch (key) {
               case LEFT_KEY:
		  selectMenu(ODV2D);
	          break;
	       case RIGHT_KEY:
		  selectMenu(CONFIGS);
		  break;
	    }
	    break;
	 case CONFIGS:
	    configsIcon->setStyleSheet(defaultColor);
	    switch (key) {
               case LEFT_KEY:
		  selectMenu(TOOLS);
	          break;
	       case RIGHT_KEY:
		  buildSettingsMenu();
		  break;
	       case UP_KEY:
	       case DOWN_KEY:
		  selectMenu(APPLICATION);
		  break;
	    }
	    break;
      }
   } else if (currSelection >= 13 && currSelection <= 58) {
      traverseSubMenu(key); 
   }
}

void PSAVirtualPanel::leftSoftKey() {
   QTextStream out(stdout);
   out << "left soft key" << endl;
  
   switch (leftSoftVal) {
      case HOME:  
         if (topSelection >= 3 && topSelection <= 8) {
            hideSettings1();
         } else if (topSelection >= 9 && topSelection <= 12) {
            hideSettings2();
         }
	 
	 if (currSelection > 12) {
            topMenuList->hide();
	    subMenuList->hide();
	 }
	 buildOfflineMenu();
         break;
      case PREV:
	 buildSettingsMenu();
	 break;
   }
}

void PSAVirtualPanel::rightSoftKey() {
   QTextStream out(stdout);
   out << "right soft key" << endl;

   switch (rightSoftVal) {
      case INFO:
	 buildConfigPrintout();
         break;
      case NEXT:
	 buildSettingsMenu2();
	 break;
   }
}

void PSAVirtualPanel::enterKey() {
   QTextStream out(stdout);
   out << "enter key" << endl;

   switch (topSelection) {
      case SETTINGS:
         out << "enter SETTINGS menu" << endl;
         buildSettingsMenu();
         break;
      case WIZARD:
	 out << "enter WIZARD menu" << endl;
	 buildWizardMenu();
	 break;
      case CALIBRATE:
	 out << "enter CALIBRATE menu" << endl;
	 break;
      case QUICK_SETUP:
	 out << "enter QUICK_SETUP menu" << endl;
	 buildQuickSetup();
	 break;
      case MEDIA:
	 out << "enter MEDIA menu" << endl;
	 buildMedia();
	 break;
      case SENSORS:
	 out << "enter SENSORS menu" << endl;
	 buildSensors();
	 break;
      case SYSTEM:
	 out << "enter SYSTEM menu" << endl;
	 buildSystem();
	 break;
      case HOST:
	 out << "enter HOST menu" << endl;
	 buildHost();
	 break;
      case NETWORK:
	 out << "enter NETWORK menu" << endl;
	 buildNetwork();
	 break;
      case APPLICATION:
	 out << "enter APPLICATION menu" << endl;
	 buildApplication();
	 break;
      case ODV2D:
	 out << "enter ODV2D menu" << endl;
	 buildODV2D();
	 break;
      case TOOLS:
	 out << "enter TOOLS menu" << endl;
	 buildTools();
	 break;
      case CONFIGS:
	 out << "enter CONFIGS menu" << endl;
	 buildConfigs();
	 break;
   }
}

void PSAVirtualPanel::upKey() {
 
   QTextStream out(stdout);
   out << "up key" << endl;
   arrowKeyEvent(UP_KEY);
}

void PSAVirtualPanel::downKey() {
   
   QTextStream out(stdout);
   out << "down key" << endl;
   arrowKeyEvent(DOWN_KEY);
}

void PSAVirtualPanel::leftKey() {
       
   QTextStream out(stdout);
   out << "left key" << endl;
   arrowKeyEvent(LEFT_KEY);
}

void PSAVirtualPanel::rightKey() {
     
   QTextStream out(stdout);
   out << "right key" << endl;
   arrowKeyEvent(RIGHT_KEY);
}

void PSAVirtualPanel::buildSettingsMenu() {

   QTextStream out(stdout);
   out << "Build Settings Page 1" << endl;

   topLabel->setText("Settings");
   topLabel->setAlignment(Qt::AlignLeft);

   bottomLabel->setText("Home                                                     Next >");
   bottomLabel->setAlignment(Qt::AlignLeft);

   leftSoftVal = HOME;
   rightSoftVal = NEXT;

   settingsIcon->setStyleSheet(defaultColor);
   grid->setVerticalSpacing(0);

   if (topSelection == SETTINGS) {
      settingsIcon->setStyleSheet(defaultColor);
      selectMenu(QUICK_SETUP);

      wizardIcon->hide();
      settingsIcon->hide();
      calibrateIcon->hide();

      grid->addWidget(quickIcon, 1, 0);
      grid->addWidget(mediaIcon, 1, 1);
      grid->addWidget(sensorIcon, 1, 2);
      grid->addWidget(systemIcon, 2, 0);
      grid->addWidget(hostIcon, 2, 1);
      grid->addWidget(networkIcon, 2, 2);

   } else {
       if (topSelection == CONFIGS) {
          selectMenu(QUICK_SETUP);
       } else if (topSelection == APPLICATION) {
          selectMenu(NETWORK);
       } else {
          selectMenu(topSelection);
       }
       
       hideSettings2();
   }
    
   quickIcon->show();
   mediaIcon->show();
   sensorIcon->show();
   systemIcon->show();
   hostIcon->show();
   networkIcon->show();
}

void PSAVirtualPanel::buildWizardMenu() {
   wizardIcon->setStyleSheet(defaultColor);
   grid->setVerticalSpacing(0);

   wizardIcon->hide();
   settingsIcon->hide();
   calibrateIcon->hide();

   buildSubMenu(WIZARD_SUB, "Wizards", wizardList, wizardsList);
}

void PSAVirtualPanel::buildSettingsMenu2() {

   QTextStream out(stdout);
   out << "Build Settings Page 2" << endl;
  
   bottomLabel->setText("< Prev");
   bottomLabel->setAlignment(Qt::AlignLeft);

   leftSoftVal = PREV;
   rightSoftVal = 0;

   hideSettings1();
 
   grid->setVerticalSpacing(0);
   grid->addWidget(appIcon, 1, 0);
   grid->addWidget(odvIcon, 1, 1);
   grid->addWidget(toolsIcon, 1, 2);
   grid->addWidget(configsIcon, 2, 0); 
 
   if (topSelection == QUICK_SETUP) {
      selectMenu(CONFIGS);
   } else if (topSelection == NETWORK) {
      selectMenu(APPLICATION);
   } else {
      selectMenu(topSelection);
   }

   appIcon->show();
   odvIcon->show();
   toolsIcon->show();
   configsIcon->show();  
}

void PSAVirtualPanel::selectMenu(int select) {
   topSelection = select;
   currSelection = topSelection;

   switch (select) {
      case WIZARD:
         wizardIcon->setStyleSheet(selected);
	 break;
      case SETTINGS:
	 settingsIcon->setStyleSheet(selected);
	 break;
      case CALIBRATE:
	 calibrateIcon->setStyleSheet(selected);
	 break;
      case QUICK_SETUP:
	 quickIcon->setStyleSheet(selected);
	 break;
      case MEDIA:
	 mediaIcon->setStyleSheet(selected);
	 break;
      case SENSORS:
	 sensorIcon->setStyleSheet(selected);
	 break;
      case SYSTEM:
	 systemIcon->setStyleSheet(selected);
	 break;
      case HOST:
	 hostIcon->setStyleSheet(selected);
	 break;
      case NETWORK:
	 networkIcon->setStyleSheet(selected);
	 break;
      case APPLICATION:
	 appIcon->setStyleSheet(selected);
	 break;
      case ODV2D:
	 odvIcon->setStyleSheet(selected);
	 break;
      case TOOLS:
	 toolsIcon->setStyleSheet(selected);
	 break;
      case CONFIGS:
	 configsIcon->setStyleSheet(selected);
	 break;
   }
}

void PSAVirtualPanel::hideSettings1() {
   quickIcon->hide();
   mediaIcon->hide();
   sensorIcon->hide();
   systemIcon->hide();
   hostIcon->hide();
   networkIcon->hide();
}

void PSAVirtualPanel::hideSettings2() {
   appIcon->hide();
   odvIcon->hide();
   toolsIcon->hide();
   configsIcon->hide();
}

void PSAVirtualPanel::buildSubMenu(int select, QString topString, QStringList topList, QStringList subList) {
   subSelection = currSelection = select;
   topLabel->setText(topString);
   topLabel->setAlignment(Qt::AlignLeft);
   bottomLabel->setText("Home");
   bottomLabel->setAlignment(Qt::AlignLeft);
   leftSoftVal = HOME;
   rightSoftVal = BLANK;

   buildListMenu(topMenuList, topList);
   buildListMenu(subMenuList, subList);
   topMenuList->setCurrentRow(0);

   grid->addWidget(topMenuList, 1, 0);
   grid->addWidget(subMenuList, 1, 1);

   topMenuList->show();
   subMenuList->show();
}

void PSAVirtualPanel::buildQuickSetup() {
   hideSettings1();
   buildSubMenu(MEDIA_SUB, "Settings > Quick Setup", quickList, mediaList);
}

void PSAVirtualPanel::buildMedia() {
   hideSettings1();
   buildSubMenu(IMAGE_SUB, "Settings > Media", mediaList2, imageList);
}

void PSAVirtualPanel::buildSensors() {
   hideSettings1();
   buildSubMenu(SENSORS_CONTROL_SUB, "Settings > Sensors", sensorsList2, sensorsControlList);
}

void PSAVirtualPanel::buildSystem() {
   hideSettings1();
   buildSubMenu(SYSTEM_CONTROL_SUB, "Settings > System", systemsList, sysControlList);
}

void PSAVirtualPanel::buildHost() {
   hideSettings1();
   buildSubMenu(HOST_CONTROL_SUB, "Settings > Host I/O", hostList, hostControlList);
}

void PSAVirtualPanel::buildNetwork() {
   hideSettings1();
   buildSubMenu(NETWORK_CONTROL_SUB, "Settings > Network", networkList, networkControlList);
}

void PSAVirtualPanel::buildApplication() {
   hideSettings2();
   buildSubMenu(APP_CONTROL_SUB, "Settings > Application", appList2, appControlList);
}

void PSAVirtualPanel::buildODV2D() {
   
}

void PSAVirtualPanel::buildTools() {
   hideSettings2();
   buildSubMenu(PRINT_TESTS_SUB, "Settings > Tools", toolsList, printTestList);
}

void PSAVirtualPanel::buildConfigs() {
   hideSettings2();
   buildSubMenu(CONFIGS_CONTROL_SUB, "Settings > Configs", configsList2, configsControlList);
}

void PSAVirtualPanel::buildListMenu(QListWidget *list, QStringList strList) {
   if (list->count() != 0) {
      list->clear();
   }
   list->addItems(strList);
}

void PSAVirtualPanel::traverseSubMenu(int key) {
   QTextStream out(stdout);
   out << "traverse sub menu" << endl;
   int currItem = topMenuList->currentRow();

   if (key == UP_KEY) {
      if (currItem == 0) {
         topMenuList->setCurrentRow(topMenuList->count() - 1);
	 currSelection = subSelection + (topMenuList->count() - 1);
      } else {
         topMenuList->setCurrentRow(--currItem);
	 currSelection--;
      }
   } else if (key == DOWN_KEY) {
      if (currItem == topMenuList->count() - 1) {
         topMenuList->setCurrentRow(0);
	 currSelection = subSelection - (topMenuList->count() - 1);
      } else {
         topMenuList->setCurrentRow(++currItem);
	 currSelection++;
      }
   } else if (key == RIGHT_KEY) {
      /* Go into sub-menu*/
      return;
      	   
   } else if (key == LEFT_KEY) {
      /* Go back to one level */
      subMenuList->hide();
      topMenuList->hide();
      if (topSelection >= 3 && topSelection <=8) {
         buildSettingsMenu();
      } else {
         buildSettingsMenu2();
      }
      return;
   }

   subSelection = currSelection;
   buildSubListMenu(subSelection);
}

void PSAVirtualPanel::buildSubListMenu(int subSelect) {
   switch (subSelect) {
      case MEDIA_SUB:
	 buildListMenu(subMenuList, mediaList);
         break;
      case SENSORS_SUB:
	 buildListMenu(subMenuList, sensorsList);
	 break;
      case APP_SUB:
	 buildListMenu(subMenuList, appList);
	 break;
      case CONFIGS_SUB:
	 buildListMenu(subMenuList, configsList);
	 break;
      case ADMIN_SUB:
	 buildListMenu(subMenuList, adminList);
	 break;
      case IMAGE_SUB:
	 buildListMenu(subMenuList, imageList);
	 break;
      case SPEED_SUB:
	 buildListMenu(subMenuList, speedList);
	 break;
      case HANDLING_SUB:
	 buildListMenu(subMenuList, handlingList);
	 break;
      case RIBBON_SUB:
	 buildListMenu(subMenuList, ribbonList);
	 break;
      case TOF_SUB:
	 buildListMenu(subMenuList, tofList);
	 break;
      case FAULT_SUB:
	 buildListMenu(subMenuList, faultList);
	 break;
      case AUTO_LBL_SUB:
	 buildListMenu(subMenuList, autoLblList);
	 break;
      case SENSORS_CONTROL_SUB:
	 buildListMenu(subMenuList, sensorsControlList);
	 break;
      case CALIBRATE_SUB:
	 buildListMenu(subMenuList, calibrateList);
	 break;
      case SENSORS_DIAG_SUB:
	 buildListMenu(subMenuList, sensorsDiagList);
	 break;
      case SYSTEM_CONTROL_SUB:
	 buildListMenu(subMenuList, sysControlList);
	 break;
      case ENERGY_STAR_SUB:
	 buildListMenu(subMenuList, energyStarList);
	 break;
      case FLASH_FILE_VIEW_SUB:
	 buildListMenu(subMenuList, flashFileViewList);
	 break;
      case FLASH_FILE_EDIT_SUB:
	 buildListMenu(subMenuList, flashFileEditList);
	 break;
      case SD_FILE_VIEW_SUB:
	 buildListMenu(subMenuList, sdFileViewList);
	 break;
      case SD_FILE_EDIT_SUB:
	 buildListMenu(subMenuList, sdFileEditList);
	 break;
      case PTR_MGMT_SUB:
	 buildListMenu(subMenuList, ptrMgmtList);
	 break;
      case DATE_SUB:
	 buildListMenu(subMenuList, dateList);
	 break;
      case HOST_CONTROL_SUB:
	 buildListMenu(subMenuList, hostControlList);
	 break;
      case USB_PORT_SUB:
	 buildListMenu(subMenuList, usbPortList);
	 break;
      case SERIAL_PORT_SUB:
	 buildListMenu(subMenuList, serialPortList);
	 break;
      case NETWORK_CONTROL_SUB:
	 buildListMenu(subMenuList, networkControlList);
	 break;
      case WLAN_SUB:
	 buildListMenu(subMenuList, wlanList);
	 break;
      case WLAN_PARAMS_SUB:
	 buildListMenu(subMenuList, wlanParamsList);
	 break;
      case WLAN_EAP_SUB:
	 buildListMenu(subMenuList, wlanEapList);
	 break;
      case APP_CONTROL_SUB:
	 buildListMenu(subMenuList, appControlList);
	 break;
      case PGL_SETUP_SUB:
	 buildListMenu(subMenuList, pglList);
	 break;
      case LP_SETUP_SUB:
	 buildListMenu(subMenuList, lpList);
	 break;
      case PSERIES_SUB:
	 buildListMenu(subMenuList, pSeriesList);
	 break;
      case FONTS_SUB:
	 buildListMenu(subMenuList, fontsList);
	 break;
      case PRINT_TESTS_SUB:
	 buildListMenu(subMenuList, printTestList);
	 break;
      case TOOLS_DIAG_SUB:
	 buildListMenu(subMenuList, toolsList);
	 break;
      case STATS_SUB:
	 buildListMenu(subMenuList, statsList);
	 break;
      case ABOUT_SUB:
	 buildListMenu(subMenuList, aboutList);
	 break;
      case CONFIGS_CONTROL_SUB:
	 buildListMenu(subMenuList, configsList2);
	 break;
      case CUSTOM_SUB:
	 buildListMenu(subMenuList, customList);
	 break;
      case WIZARD_SUB:
	 buildListMenu(subMenuList, wizardsList);
	 break;
      case WEB_LINKS_SUB:
	 buildListMenu(subMenuList, webLinksList);
	 break;
      case ORDER_SUPPLIES_SUB:
	 buildListMenu(subMenuList, orderSuppliesList);
	 break;
      case MAINT_SUB:
	 buildListMenu(subMenuList, maintList);
	 break;
      case REGISTER_PRODUCT_SUB:
	 buildListMenu(subMenuList, registerProductList);
	 break;
      case CONTACT_US_SUB:
	 buildListMenu(subMenuList, contactList);
	 break;
   }
}

void PSAVirtualPanel::buildOfflineMenu() {
     	
   settingsIcon->setStyleSheet(selected);
   topSelection = currSelection = SETTINGS;

   topLabel->setText("Home                                                  OFFLINE");
   topLabel->setAlignment(Qt::AlignLeft);
   bottomLabel->setText("Info");
   bottomLabel->setAlignment(Qt::AlignBottom | Qt::AlignRight);

   leftSoftVal = 0;
   rightSoftVal = INFO;

   grid->setVerticalSpacing(20);
   grid->addWidget(topLabel, 0, 0, 1, 3);
   grid->addWidget(wizardIcon, 1, 0);
   grid->addWidget(settingsIcon, 1, 1);
   grid->addWidget(calibrateIcon, 1, 2);
   grid->addWidget(bottomLabel, 3, 0, 1, 3);

   topLabel->show();
   wizardIcon->show();
   settingsIcon->show();
   calibrateIcon->show();
   bottomLabel->show();
}
    
QPixmap PSAVirtualPanel::mergeOnTop(const QPixmap &pix, const QString text) {

   QPainter p;
   int strWidth, strHeight;
   int pixWidth, pixHeight;
   QFontMetrics fm(this->font());

   /* Get width of string */
   strWidth = fm.width(text);
   strHeight = fm.height();

   /* Get width and height of pixmap */
   pixWidth = pix.width();
   pixHeight = pix.height();

   /* Initialize the new pixmap with width and height */
   QPixmap res( qMax(strWidth, pixWidth), strHeight + pixHeight + 10);
   res.fill(Qt::transparent);
   p.begin(&res);
   int start = 0;
   if ( pixWidth < strWidth)
      start = (strWidth-pixWidth) / 2;

   /* Draw the pixmap first, then draw the text */
   p.drawPixmap(start, 0, pix);
   p.setPen(QColor(77, 153, 176));
   p.drawText( QRect(0, pixHeight + 3, qMax(pixWidth, strWidth), strHeight), Qt::AlignCenter, text);
   p.end();

   return res;
}

QPushButton *PSAVirtualPanel::createButtonImage(QString dir, int x, int y, int width, int height) {

   QTextStream out(stdout);

   QPushButton *btn = new QPushButton(this);
   btn->setGeometry(x, y, width, height);
   changeButtonPix(btn, dir, width, height);

   return btn;
}

void PSAVirtualPanel::changeButtonPix(QPushButton *btn, QString dir, int width, int height) {

   QPixmap pix(dir);
   QPixmap scale = pix.scaled(QSize(width, height));

   QIcon icon(scale);
   btn->setIcon(icon);
   btn->setIconSize(QSize(width, height));
}

QLabel *PSAVirtualPanel::createLabel(QString path, QString text) {

   QLabel *label = new QLabel();
   label->setPixmap(mergeOnTop(QPixmap(path), text));

   return label;
}


void PSAVirtualPanel::enterHold() {
   changeButtonPix(enterKeyButton, "icons/PanelEnterOn.png", 70, 60); 
}

void PSAVirtualPanel::enterRelease() {
   changeButtonPix(enterKeyButton, "icons/PanelEnter.png", 70, 60);
}

void PSAVirtualPanel::upHold() {
   changeButtonPix(upKeyButton, "icons/PanelUpOn.png", 90, 30); 
}

void PSAVirtualPanel::upRelease() {
   changeButtonPix(upKeyButton, "icons/PanelUp.png", 90, 30);
}

void PSAVirtualPanel::downHold() {
   changeButtonPix(downKeyButton, "icons/PanelDownOn.png", 90, 30);
}

void PSAVirtualPanel::downRelease() {
   changeButtonPix(downKeyButton, "icons/PanelDown.png", 90, 30);
}

void PSAVirtualPanel::rightHold() {
   changeButtonPix(rightKeyButton, "icons/PanelRightOn.png", 30, 100);
}

void PSAVirtualPanel::rightRelease() {
   changeButtonPix(rightKeyButton, "icons/PanelRight.png", 30, 100);
}

void PSAVirtualPanel::pauseHold() {
   changeButtonPix(pauseButton, "icons/PanelPauseOn.png", 100, 30);
}

void PSAVirtualPanel::pauseRelease() {
   changeButtonPix(pauseButton, "icons/PanelPause.png", 100, 30);
}

void PSAVirtualPanel::feedHold() {
   changeButtonPix(formFeedButton, "icons/PanelFeedOn.png", 100, 30);
}

void PSAVirtualPanel::feedRelease() {
   changeButtonPix(formFeedButton, "icons/PanelFeed.png", 100, 30);
}

void PSAVirtualPanel::leftHold() {
   changeButtonPix(leftKeyButton, "icons/PanelLeftOn.png", 30, 100);
}

void PSAVirtualPanel::leftRelease() {
   changeButtonPix(leftKeyButton, "icons/PanelLeft.png", 30, 100);
}

void PSAVirtualPanel::buildConfigPrintout() {
   cfg->setText(configPrint);
   cfg->setReadOnly(true);
   cfg->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
   cfg->setLineWrapMode(QTextEdit::NoWrap);

   topLabel->setText("Info");
   topLabel->setAlignment(Qt::AlignLeft);

   bottomLabel->setText("Home                                                         Print");
   bottomLabel->setAlignment(Qt::AlignLeft);

   leftSoftVal = HOME;
   rightSoftVal = PRINT;

   wizardIcon->hide();
   settingsIcon->hide();
   calibrateIcon->hide();
  
   grid->setVerticalSpacing(0); 
   grid->addWidget(cfg, 1, 0);
   cfg->show();   
}
