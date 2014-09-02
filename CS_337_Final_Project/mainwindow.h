#ifndef MAINWINDOW_H
 #define MAINWINDOW_H

 #include <QMainWindow>

//#typedef QPushButton * Button

 class QAction;
 class QMenu;
 class QPlainTextEdit;

 class MainWindow : public QMainWindow
 {
     Q_OBJECT

 public:
     MainWindow();
     bool B_flag;
     bool I_flag;
     int Font_Size;


 protected:
     void closeEvent(QCloseEvent *event);

 private slots:
     void newFile();
     void open();
     bool save();
     bool saveAs();
     void about();
     void documentWasModified();
     void setItalic();
     void setBold();
     void setSmall();
     void setNormal();
     void setLarge();


 private:
     void createActions();
     void createMenus();
     void createToolBars();
     void createStatusBar();
     void readSettings();
     void writeSettings();
     bool maybeSave();
     void createBoldAndItalic();
     void createSizeChange();
     void loadFile(const QString &fileName);
     bool saveFile(const QString &fileName);
     void setCurrentFile(const QString &fileName);
     QString strippedName(const QString &fullFileName);

     QPlainTextEdit *textEdit;
     QString curFile;

     QMenu *fileMenu;
     QMenu *editMenu;
     QMenu *helpMenu;
     QToolBar *fileToolBar;
     QToolBar *editToolBar;
     QAction *newAct;
     QAction *openAct;
     QAction *saveAct;
     QAction *saveAsAct;
     QAction *exitAct;
     QAction *cutAct;
     QAction *copyAct;
     QAction *pasteAct;
     QAction *aboutAct;
     QAction *aboutQtAct;

 };

 #endif
