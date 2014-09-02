
#include <QtGui>
#include <QString>
#include <QPlainTextEdit>
#include "mainwindow.h"
#include <QMessageBox>
#include <QtWidgets>
#include <QToolBar>
#include <QPushButton>
#include <QRadioButton>
#include <QGroupBox>


MainWindow::MainWindow()
 {
     textEdit = new QPlainTextEdit;
     setCentralWidget(textEdit);//Sets TextEdit To Be Located In Central Layout

     createActions();//Create Icons and Connect Action Listener to Them
     createMenus();//Create Menu ToolBar
     createToolBars();//Create Those Tool Bars Under Menue Bar
     createStatusBar();//Create Status Bar Under On Buttom Of Our main Window

     readSettings();//Set Setting Of Windows Size And It's Position

     createBoldAndItalic();
     createSizeChange();

     connect(textEdit->document(), SIGNAL(contentsChanged()),//document() Return Pointer To That TextFile
             this, SLOT(documentWasModified()));

     //contentsChanged is Just a Class of textEdit->document()->contentsChanged()
     //documentWasModified is Just a Class of textEdit->document()->documentWasModified()

     setCurrentFile("");//Setting Current File Directory To The Directoty In Which Program Runs
     setUnifiedTitleAndToolBarOnMac(true);//Same As editToolBar->setMovable(true); For Mac


     this->B_flag=false;
     this->I_flag=false;
     this->Font_Size=15;

     QFont newFont("Courier", this->Font_Size, QFont::Normal, false);
     textEdit->setFont(newFont);

 }

 void MainWindow::closeEvent(QCloseEvent *event)
 {
     if (maybeSave()) {
         writeSettings();
         event->accept();
     } else {
         event->ignore();
     }
 }

 void MainWindow::newFile()
 {
     if (maybeSave()) {
         textEdit->clear();
         setCurrentFile("");
     }
 }

 void MainWindow::open()
 {
     if (maybeSave()) {
         QString fileName = QFileDialog::getOpenFileName(this);
         if (!fileName.isEmpty())
             loadFile(fileName);
     }
 }

 bool MainWindow::save()
 {
     if (curFile.isEmpty()) {
         return saveAs();
     } else {
         return saveFile(curFile);
     }
 }

 bool MainWindow::saveAs()
 {
     QString fileName = QFileDialog::getSaveFileName(this);
     if (fileName.isEmpty())
         return false;

     return saveFile(fileName);
 }

 void MainWindow::about()
 {
    QMessageBox::about(this, tr("About Application"),
             tr("<p><em><strong>SEYEDAMIRHOSSEIN HESAMIAN<br />CS ~ 337 FINAL PROJECT<br />QT TEXTEDITOR&nbsp;<br />SPRING 2013&nbsp;</strong></em></p>"));
 }

 void MainWindow::documentWasModified()
 {
     setWindowModified(textEdit->document()->isModified());
 }

 void MainWindow::setItalic()
 {
     QFont newFont("Courier", this->Font_Size);
     if(this->I_flag==false){
         newFont.setItalic(true);
         this->I_flag=true;
     }
     else{
         newFont.setItalic(false);
         this->I_flag=false;
     }
     newFont.setBold(this->B_flag);
     textEdit->setFont(newFont);
 }

 void MainWindow::setBold()
 {
    QFont newFont("Courier", this->Font_Size);
     if(this->B_flag==false){
         newFont.setBold(true);
         this->B_flag=true;
     }
     else{
         newFont.setBold(false);
         this->B_flag=false;
     }
     newFont.setItalic(this->I_flag);
     textEdit->setFont(newFont);
 }

 void MainWindow::setSmall()
 {
     this->Font_Size=15;
     QFont newFont("Courier", Font_Size);
     newFont.setBold(this->B_flag);
     newFont.setItalic(this->I_flag);
     textEdit->setFont(newFont);
 }

 void MainWindow::setNormal()
 {
     this->Font_Size=25;
     QFont newFont("Courier", Font_Size);
     newFont.setBold(this->B_flag);
     newFont.setItalic(this->I_flag);
     textEdit->setFont(newFont);
 }

 void MainWindow::setLarge()
 {
     this->Font_Size=35;
     QFont newFont("Courier", Font_Size);
     newFont.setBold(this->B_flag);
     newFont.setItalic(this->I_flag);
     textEdit->setFont(newFont);
 }


 void MainWindow::createActions()
 {
     //Same In Java We Used Action Listener To Handle Events
     newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);//& is Just In Case We Have Translator And If We Skip it Nothing Will Happen
     newAct->setShortcuts(QKeySequence::New);//This New ACtion Is Noew Called NEW
     newAct->setStatusTip(tr("Create a new file"));
     connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));//'This' Here Means MainWindow*
     //'Tr' means Translate If Synonyms In Other Languages Are Available

     openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
     openAct->setShortcuts(QKeySequence::Open);
     openAct->setStatusTip(tr("Open an existing file"));
     connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

     saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
     saveAct->setShortcuts(QKeySequence::Save);
     saveAct->setStatusTip(tr("Save the document to disk"));
     connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

     saveAsAct = new QAction(tr("Save &As..."), this);
     saveAsAct->setShortcuts(QKeySequence::SaveAs);
     saveAsAct->setStatusTip(tr("Save the document under a new name"));
     connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

     exitAct = new QAction(tr("E&xit"), this);
     exitAct->setShortcuts(QKeySequence::Quit);
     exitAct->setStatusTip(tr("Exit the application"));
     connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

     cutAct = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
     cutAct->setShortcuts(QKeySequence::Cut);
     cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                             "clipboard"));
     connect(cutAct, SIGNAL(triggered()), textEdit, SLOT(cut()));

     copyAct = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
     copyAct->setShortcuts(QKeySequence::Copy);
     copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                              "clipboard"));
     connect(copyAct, SIGNAL(triggered()), textEdit, SLOT(copy()));

     pasteAct = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
     pasteAct->setShortcuts(QKeySequence::Paste);
     pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                               "selection"));
     connect(pasteAct, SIGNAL(triggered()), textEdit, SLOT(paste()));

     aboutAct = new QAction(tr("&About"), this);
     aboutAct->setStatusTip(tr("Show the application's About box"));
     connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

     aboutQtAct = new QAction(tr("About &Qt"), this);
     aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
     connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));//qApp is Actually A Pointer To Qt Documentations

     cutAct->setEnabled(false);//When Nothing Is In TextFile Then What Should be Cuted
     copyAct->setEnabled(false);//When Nothing Is In TextFile Then What Should be Copied
     connect(textEdit, SIGNAL(copyAvailable(bool)),
             cutAct, SLOT(setEnabled(bool)));//If There is Some text That Can Be Cuted Then Set Cut to Available
     connect(textEdit, SIGNAL(copyAvailable(bool)),
             copyAct, SLOT(setEnabled(bool)));//If There is Some text That Can Be Copied Then Set Copy to Available
 }

 void MainWindow::createMenus()
 {
     fileMenu = menuBar()->addMenu(tr("&File"));
     fileMenu->addAction(newAct);//We Call New By Saying newAct
     fileMenu->addAction(openAct);
     fileMenu->addAction(saveAct);
     fileMenu->addAction(saveAsAct);
     fileMenu->addSeparator();//By Default This Is Separable So No Need For An Extra Line
     fileMenu->addAction(exitAct);

     editMenu = menuBar()->addMenu(tr("&Edit"));
     editMenu->addAction(cutAct);
     editMenu->addAction(copyAct);
     editMenu->addAction(pasteAct);

     menuBar()->addSeparator();

     helpMenu = menuBar()->addMenu(tr("&Help"));
     helpMenu->addAction(aboutAct);
     helpMenu->addAction(aboutQtAct);
 }

 void MainWindow::createToolBars()
 {
     fileToolBar = addToolBar(tr("File"));
     fileToolBar->setMovable(true);
     fileToolBar->addAction(newAct);
     fileToolBar->addAction(openAct);
     fileToolBar->addAction(saveAct);
     fileToolBar->setMovable(false);

     editToolBar = addToolBar(tr("Edit"));
     editToolBar->setMovable(true);
     editToolBar->addAction(cutAct);
     editToolBar->addAction(copyAct);
     editToolBar->addAction(pasteAct);
     editToolBar->setMovable(false);
 }

 void MainWindow::createStatusBar()
 {
     statusBar()->showMessage(tr("Ready"));//statusBar() is in QMainApplications that we Included
 }

 void MainWindow::readSettings()
 {
     QSettings settings("Amir", "QT TextEditor");//We Expect Application To Remember Setting But In Qt not Unless we Use QSettings
     QPoint pos = settings.value("Position", QPoint(100, 100)).toPoint();//Point In Which MainWindow Opens
     QSize size = settings.value("Size", QSize(500, 400)).toSize();//Size Of Window
     resize(size);//Holds The Size Of Widget
     move(pos);//Holds The Point Of Widget
 }

 void MainWindow::writeSettings()
 {
     QSettings settings("Trolltech", "Application Example");
     settings.setValue("pos", pos());
     settings.setValue("size", size());
 }
 void MainWindow::createBoldAndItalic()
 {
     QPushButton* Italic = new QPushButton(tr("I"),this);
     QPushButton* Bold = new QPushButton(tr("B"),this);

     Italic->setGeometry(QRect(QPoint(230,22),
                                      QSize(30, 30)));
     Bold->setGeometry(QRect(QPoint(260,22),
                                      QSize(30, 30)));
     Italic->setStatusTip("Italic");
     Bold->setStatusTip("Bold");

     Italic->setCheckable(true);
     Bold->setCheckable(true);



     Italic->setAutoRepeat(true);
     Bold->setAutoRepeat(true);

     connect(Italic,SIGNAL(clicked()),this,SLOT(setItalic()));
     connect(Bold,SIGNAL(clicked()),this,SLOT(setBold()));
 }

 void MainWindow::createSizeChange()
 {
     QRadioButton * Size_Small =new QRadioButton("Small",this);
     Size_Small->setGeometry((QRect(QPoint(297,22),QSize(50, 30))));
     QRadioButton * Size_Normal =new QRadioButton("Normal",this);
     Size_Normal->setGeometry((QRect(QPoint(347,22),QSize(55, 30))));
     QRadioButton * Size_Large =new QRadioButton("Large",this);
     Size_Large->setGeometry((QRect(QPoint(408,22),QSize(55, 30))));

     Size_Small->setChecked(true);

     connect(Size_Small,SIGNAL(clicked()),this,SLOT(setSmall()));
     connect(Size_Normal,SIGNAL(clicked()),this,SLOT(setNormal()));
     connect(Size_Large,SIGNAL(clicked()),this,SLOT(setLarge()));
 }

 bool MainWindow::maybeSave()
 {
     if (textEdit->document()->isModified()) {
         QMessageBox::StandardButton ret;
         ret = QMessageBox::warning(this, tr("Application"),
                      tr("The document has been modified.\n"
                         "Do you want to save your changes?"),
                      QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
         if (ret == QMessageBox::Save)//We Are Actually Overriding Defult Action Of save
             return save();
         else if (ret == QMessageBox::Cancel)
             return false;
     }
     return true;
 }

 void MainWindow::loadFile(const QString &fileName)
 {
     QFile file(fileName);
     if (!file.open(QFile::ReadOnly | QFile::Text)) {// ^ bitwise XOR |	bitwise OR
         QMessageBox::warning(this, tr("Application"),
                              tr("Cannot read file %1:\n%2.")
                              .arg(fileName)
                              .arg(file.errorString()));
         return;
     }

     QTextStream in(&file);
 #ifndef QT_NO_CURSOR
     QApplication::setOverrideCursor(Qt::WaitCursor);
 #endif
     textEdit->setPlainText(in.readAll());
 #ifndef QT_NO_CURSOR
     QApplication::restoreOverrideCursor();
 #endif

     setCurrentFile(fileName);
     statusBar()->showMessage(tr("File loaded"), 2000);
 }

 bool MainWindow::saveFile(const QString &fileName)
 {
     QFile file(fileName);
     if (!file.open(QFile::WriteOnly | QFile::Text)) {
         QMessageBox::warning(this, tr("Application"),
                              tr("Cannot write file %1:\n%2.")
                              .arg(fileName)
                              .arg(file.errorString()));
         return false;
     }

     QTextStream out(&file);
 #ifndef QT_NO_CURSOR
     QApplication::setOverrideCursor(Qt::WaitCursor);
 #endif
     out << textEdit->toPlainText();
 #ifndef QT_NO_CURSOR
     QApplication::restoreOverrideCursor();
 #endif

     setCurrentFile(fileName);
     statusBar()->showMessage(tr("File Saved"), 2000);
     return true;
 }

 void MainWindow::setCurrentFile(const QString &fileName)
 {
     curFile = fileName;
     textEdit->document()->setModified(false);
     setWindowModified(false);

     QString shownName = curFile;
     if (curFile.isEmpty())
         shownName = "No_Title_Text_file.txt";
     setWindowFilePath(shownName);
 }

 QString MainWindow::strippedName(const QString &fullFileName)
 {
     return QFileInfo(fullFileName).fileName();
 }
