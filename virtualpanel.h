#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QProgressBar>
#include <QGridLayout>
#include <QPixmap>
#include <QString>
#include <QListWidget>
#include <QSignalMapper>

class PSAVirtualPanel : public QWidget {

   public: 
      PSAVirtualPanel(QWidget *parent = 0);
 
      /* Menu selection values */
      enum menus {
         WIZARD,
	 SETTINGS,
	 CALIBRATE,
	 QUICK_SETUP,
	 MEDIA,
         SENSORS,
	 SYSTEM,
	 HOST,
	 NETWORK,
	 APPLICATION,
	 ODV2D,
	 TOOLS,
	 CONFIGS,
	 MEDIA_SUB,
	 SENSORS_SUB,
	 APP_SUB,
	 CONFIGS_SUB,
	 ADMIN_SUB,
	 IMAGE_SUB,
	 SPEED_SUB,
	 HANDLING_SUB,
	 RIBBON_SUB,
	 TOF_SUB,
	 FAULT_SUB,
	 AUTO_LBL_SUB,
	 SENSORS_CONTROL_SUB,
	 CALIBRATE_SUB,
	 SENSORS_DIAG_SUB,
         SYSTEM_CONTROL_SUB,
	 ENERGY_STAR_SUB,
	 FLASH_FILE_VIEW_SUB,
	 FLASH_FILE_EDIT_SUB,
	 SD_FILE_VIEW_SUB,
	 SD_FILE_EDIT_SUB,
	 PTR_MGMT_SUB,
	 DATE_SUB,
	 HOST_CONTROL_SUB,
	 USB_PORT_SUB,
	 SERIAL_PORT_SUB,
	 NETWORK_CONTROL_SUB,
	 WLAN_SUB,
	 WLAN_PARAMS_SUB,
	 WLAN_EAP_SUB,
	 APP_CONTROL_SUB,
	 PGL_SETUP_SUB,
	 LP_SETUP_SUB,
         PSERIES_SUB,
	 FONTS_SUB,
	 PRINT_TESTS_SUB,
	 TOOLS_DIAG_SUB,
	 STATS_SUB,
	 ABOUT_SUB,
	 CONFIGS_CONTROL_SUB,
	 CUSTOM_SUB,
	 WIZARD_SUB,
	 WEB_LINKS_SUB,
	 ORDER_SUPPLIES_SUB,
	 MAINT_SUB,
	 REGISTER_PRODUCT_SUB,
	 CONTACT_US_SUB
      };
 
      /* Soft Key Values */
      enum soft {
         BLANK,
	 HOME,
	 INFO,
	 NEXT,
	 PREV,
	 QUIT
      };
 
      /* Arrow Key Values */
      enum arrows {
         UP_KEY,
	 LEFT_KEY,
	 RIGHT_KEY,
	 DOWN_KEY,
	 ENTER_KEY,
	 PAUSE_KEY,
	 FEED_KEY
      };
 
      /* Default selection is Settings */
      int topSelection = SETTINGS;
      int currSelection = topSelection;

      /* Selection for sub menus */
      int subSelection;

      /* Current values for the left and right soft key */
      int leftSoftVal;
      int rightSoftVal;

      /* Stylesheet colors for widgets */ 
      QString background = "background-color: rgb(187, 247, 161)";
      QString defaultColor = "color: rgb(77, 153, 176)";
      QString selected = background + ";" + defaultColor; 
      QString listSelection = "selection-background-color: rgb(187, 247, 161)";
      QString itemColor = "color: rgb(47, 63, 245)";
      QString boldFont = "font-weight: bold";

      QColor select = QColor(187, 247, 161);
        
      /* Hardcoded string lists for the sub menus */
      QStringList quickList= {"Media", "Sensors", "Application", "Configs", "Admin User"};
      QStringList mediaList = {"Print Intensity", "Media Handling", "Paper Feed Shift", "Label Width", "Label Length", "Vertical Shift", "Horizontal Shift"};
      QStringList sensorsList = {"Gap/Mark Sensor", "Auto Calibrate"};
      QStringList appList = {"Active ICP Emul", "PGL Diagnostics"};
      QStringList configsList = {"Save Config", "Power-Up Config", "Load Config"};
      QStringList adminList = {"Set Password", "Enter Safe Mode"};

      QStringList mediaList2 = {"Image", "Speed", "Handling", "Ribbon", "TOF", "Fault", "Auto Label Map"};
      QStringList imageList = {"Print Intensity", "Intensity Shift", "Paper Feed Shift", "Label Length", "Set Label Length", "Clip Page", "Vertical Shift", "Horizontal Shift", "Orientation", "Print Direction", "Vertical DPI Adj"};
      QStringList speedList = {"Print Speed", "Reverse Speed", "Slew Speed Control"};
      QStringList handlingList = {"Print Mode", "Media Handling", "Continuous Mode", "Peel Present", "Cal in Peel Mode", "Label Wait TIme"};
      QStringList ribbonList = {"Ribbon Low"};
      QStringList tofList = {"TOF Detect Fault", "Ticket Save Mode", "TOF Adjust Mode", "TOF Adjust Dist"};
      QStringList faultList = {"Label Missing", "Error Recover", "Head Warning"};
      QStringList autoLblList = {"Select", "Auto Label Width", "Number Labels"};

      QStringList sensorsList2 = {"Control", "Calibrate", "Diagnostics"};
      QStringList sensorsControlList = {"Gap/Mark Sensor", "Auto Calibrate", "Sensed Distance", "Gap/Mark Thresh", "Paper Out Thresh"};
      QStringList calibrateList = {"Auto Calibrate", "Power-Up Action", "HeadClose Action", "Online Action", "Gap Windowing", "Gap Length", "Minimum Delta", "Use Label Length", "Threshold Range", "Mark TOF Detect", "Label Window", "Lbl Win Len"};
      QStringList sensorsDiagList = {"Media Profile", "Manual Calibrate"};

      QStringList systemsList = {"Control", "Energy Star", "Flash File View", "Flash File Edit", "SD File View", "SD File Edit", "Printer Mgmt", "Date"};
      QStringList sysControlList = {"Display Language", "LCD Brightness", "Power-up State", "Alarm", "Media Units", "Batch Counter", "Feed Key Online", "Cancel Operation", "Auto Locking", "Set Lock Key"};
      QStringList energyStarList = {"Pwr Saver Time", "Pwr Saver Active"};
      QStringList flashFileViewList = {"93779.sf", "93952.sf", "91409.sf", "90993.sf", "92250.sf", "92500.sf", "92244.sf", "add18030.tab", "g180302u.dat", "gb2u7.dat", "sjs2u.dat", "cacert.pem"};
      QStringList flashFileEditList = {"Overwrite Files", "Delete Files", "Available Space", "Flash Reclaimable", "Optimize & Reboot", "Copy To SD", "Print File List"};
      QStringList sdFileViewList = {"COMBO.PRG"};
      QStringList sdFileEditList = {"Overwrite Files", "Delete Files", "Print Files", "Available Space", "Copy From SD", "Print File List"};
      QStringList ptrMgmtList = {"Rcv. Status Port", "Ret. Status Port", "Status Port Number", "PNE Port Choice", "Mgmt Port Number", "Mgmt Protocol"};
      QStringList dateList = {"Hour", "Minute", "Year", "Month", "Day", "Time Zone Offset"};

      QStringList hostList = {"Control", "USB Port", "Serial Port"};
      QStringList hostControlList = {"Interface"};
      QStringList usbPortList = {"Buffer (Kbytes)", "AutoSW Timeout", "USB Protocol"};
      QStringList serialPortList = {"Buffer (Kbytes)", "Baud Rate", "Word Length", "Stop Bits", "Parity", "Data Protocol", "Data Term Ready", "Poll Character", "Poll Response", "Idle Response", "One Char Enquiry", "Printer Status", "Framing Errors", "Offline Process", "Report Status", "Trickle Time", "AutoSW Timeout"};
      
      QStringList networkList = {"Control", "WLAN", "WLAN Params", "WLAN EAP"};
      QStringList networkControlList = {"ASCII Data Port", "Keep Alive Timer", "Job Control", "Offline Process", "AutoSW Timeout", "AutoSW Out", "Active Interface", "E-Net To Default"};
      QStringList wlanList = {"IP Address", "Subnet Mask", "Gateway Address", "MAC Address", "DHCP", "BootP"};
      QStringList wlanParamsList = {"SSID Name", "Reset SSID Name", "Min Xfer Rate", "Power Mgmt", "Internat. Mode", "WEP Key 1 Format", "WEP Key 1 Width", "WEP Key 1", "WEP Key 2 Format", "WEP Key 2 Width","WEP Key 2", "WEP Key 3 Format", "WEP Key 3 Width", "WEP Key 3", "WEP Key 4 Format", "WEP Key 4 Width", "WEP Key 4", "Default WEP Key", "Reset WEP Keys", "WPA Mode", "WPA Cipher", "WPA Pass-Phrase", "Reset Pass-Phrase"};
      QStringList wlanEapList = {"EAP Mode", "EAP User", "Reset EAP User", "EAP Password", "Reset EAP Psswd"};

      QStringList appList2 = {"Control", "PGL Setup", "LP+ Setup", "P-Series Setup", "Fonts"};
      QStringList appControlList = {"Active IGP Emul", "PGL Diagnostics", "Active LP+ Emul", "PTX Setup SFCC", "Compatability", "PJL Control"};
      QStringList pglList = {"Character Group", "Standard Sets", "Select LPI", "Define CR Code", "Define LF Code", "Autowrap", "Auto UpperCase", "Slash 0", "Select SFCC", "Host Form Length", "Var Form Adjust", "Var Form Type", "Skip Cmd Prefix", "Ignore Text", "Ext Execute Copy"};
      QStringList lpList = {"Select CPI", "Select LPI", "Host Command", "Typeface", "Prop. Spacing", "Bold", "Italic Print", "Slashed Zero", "Text Position", "Form Length", "Form Length", "Form Length", "Form Width", "Form Width", "Form Width", "Left Margin", "Right Margin", "Top Margin", "Bottom Margin", "Print Char. Set", "Reset Cmd CFG Ld"};
      QStringList pSeriesList = {"Character Group", "Character Set", "Primary Subset", "Extended Subset", "Horizontal DPI", "Vertical DPI", "Define CR code", "Auto LF", "Define LC code", "Control Code 06", "Control Code 08", "Overstrike", "Select SFCC", "EVFU Select", "Alt. Set 80-9F"};
      QStringList fontsList = {"Standard Chars.", "Bold Chars.", "Extra Bold Chars.", "OCR-A Chars.", "OCR-B Chars.", "TT Reg Chars.", "TT Bold Chars.", "Tall Characters"};

      QStringList toolsList = {"Print Tests", "Diagnostics", "Statistics", "About"};
      QStringList printTestList = {"Run Tests", "Test Count"};
      QStringList diagnosticsList = {"Print Error Log", "Clear Error Log", "Hex Dump Mode", "Job Capture", "Page Dump Mode", "Auto Dump"};
      QStringList statsList = {"Printer On Time", "Total Media Dist", "Total Label Count", "Head On Time", "Head Print Dist", "Head Life (Durable)"};
      QStringList aboutList = {"Controller Board Version", "Head DPI", "FLASH Installed", "DRAM Installed", "CPU Clock", "Printer F/W"};

      QStringList configsList2 = {"Control", "Custom"};
      QStringList configsControlList = {"Save Config", "Load Config", "Print Config", "Delete Config", "Power-Up Config", "Auto Save"};
      QStringList customList = {"Name Config 1", "Name Config 2", "Name Config 3", "Name Config 4", "Name Config 5", "Name Config 6", "Name Config 7", "Name Config 8", "Reset Cfg Names"};

      QStringList wizardList = {"Wizards", "Web Links", "Order Supplies", "Maintenance", "Register Product", "Contact Us"};
      QStringList wizardsList = {"Printer Setup", "Print Quality", "Application", "WLAN"};
      QStringList webLinksList = {"How-To Videos", "Drivers", "PNE Suite", "SAP/ERP Support", "Manuals"};
      QStringList orderSuppliesList = {"Online Store", "Sales/How to Buy"};
      QStringList maintList = {"Pringhead Change", "Printer Cleaning", "Media Loading", "Ribbon Loading", "Label Jams", "Manuals"};
      QStringList registerProductList = {"Online Registration"};
      QStringList contactList = {"Contact Us", "Request Service Call"};
      
   private:
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

      /* Top menu Components */
      QLabel *wizardIcon;
      QLabel *settingsIcon;
      QLabel *calibrateIcon;

      /* Settings Submenu */
      QLabel *quickIcon;
      QLabel *mediaIcon;
      QLabel *sensorIcon;
      QLabel *systemIcon;
      QLabel *hostIcon;
      QLabel *networkIcon;
      QLabel *appIcon;
      QLabel *odvIcon;
      QLabel *toolsIcon;
      QLabel *configsIcon;

      QLabel *topLabel;
      QLabel *bottomLabel;

      QListWidget *topMenuList;
      QListWidget *subMenuList;
      QListWidget *fullMenuList;

      /* Functions for creating menus */
      void buildSettingsMenu();
      void buildWizardMenu();
      void buildSettingsMenu2();
      void selectMenu(int select);
      void hideSettings1();
      void hideSettings2();
      void buildQuickSetup();
      void buildMedia();
      void buildSensors();
      void buildSystem();
      void buildHost();
      void buildNetwork();
      void buildApplication();
      void buildODV2D();
      void buildTools();
      void buildConfigs();
      void buildSubMenu(int select, QString topString, QStringList topList, QStringList subList);
      void buildSubListMenu(int currSelection);
      void buildListMenu(QListWidget *list, QStringList strList);
      void buildOfflineMenu();
      QPixmap mergeOnTop(const QPixmap &pix, const QString text);
      QPushButton *createButtonImage(QString dir, int x, int y, int width, int height);
      void changeButtonPix(QPushButton *btn, QString dir, int width, int height);
      QLabel *createLabel(QString path, QString text);

   private slots:
      /* Event handlers for the buttons */
      void pause();
      void formFeed();
      void upKey();
      void downKey();
      void leftKey();
      void rightKey();
      void arrowKeyEvent(int key);
      void leftSoftKey();
      void rightSoftKey();
      void enterKey();
      void traverseSubMenu(int key);
      /* Functions below are not efficient, need to use SignalMapper */

      /* pressed slot */
      void enterHold(); 
      void upHold();
      void downHold();
      void rightHold();
      void pauseHold();
      void feedHold();
      void leftHold();

      /* released slot */
      void enterRelease();
      void upRelease();
      void downRelease();
      void rightRelease();
      void pauseRelease();
      void feedRelease();
      void leftRelease();
};
