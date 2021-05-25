#ifndef BASE_H
#define BASE_H

#include <QMainWindow>
#include <QWidget>
#include <QDate>
#include <QDateTime>
#include <QLocale>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QStandardPaths>
#include <QMessageBox>


QT_BEGIN_NAMESPACE
namespace Ui { class Base; }
QT_END_NAMESPACE

class Base : public QMainWindow
{
    Q_OBJECT


public:
    Base(QWidget *parent = nullptr);
    ~Base();


  //sets current date on the top of app
    void SetUpLblDate();
  //creates
    void CreateButtons();
    void CreateLabels();
  //sets number on push buttons
    void SetNumber(int);
  //checks which week day is in the 1st day of month
    void CheckDay();
  //labels after click some day in calendar
    void NewCalendarlbl(QString);
  //saves to file if you click "back" button
    void SaveToFile();
  //clears labels from NewCalendarlbl
    void ClearLabels();
  //changes language
    void ChangeLanguageEng();
    void ChangeLanguagePl();
    void ChangeLanguageGer();
  //creates directory
    void CreateDir();

private slots:

    void on_prevmonth_clicked();
    void on_nextmonth_clicked();
    void on_closebtn_clicked();
    void on_GetClickedDay(QString);
    //void on_RemoveLbl(int);
    void on_backbtn_clicked();
    void on_savebtn_clicked();
    void on_optionbtn_clicked();
    void on_backbtn_2_clicked();
    void on_comboBox_currentIndexChanged(int index);

private:

  //english date name
    QLocale locale = QLocale(QLocale::English);

  //object QDate date sets on current day
    QDate date = QDate::currentDate();

    QVector<QString> textarr;
    QString filename2;

  //variable for current days, month and year
    short TodaysDay = date.day();
    short DayInWeek = date.dayOfWeek();
    short Month = date.month();
    short Year = date.year();

        //new
           QPushButton *btn[6][7];
           QLabel *lbl[7];
           QLabel *lbl2[10];
           QPushButton *rbtn[10];

       //variable for previous or next day, month and year
         int M = date.month();
         int D = date.daysInMonth();
         int Y = date.year();
         QDate *prevdate;

       //stylesheets of button
         QString const normalday = "QPushButton{background-color: rgba(54,54,54, 100) ; color: #ffffff; font:87 18pt Arial Black; border: none;} QPushButton:hover{background-color: rgba(74,74,74,100) ; color: #ffffff; font:87 18pt Arial Black; border: none;}";
         QString const currentday = "QPushButton{background-color: #49B6FF; color: rgb(24,24,24); font:87 18pt Arial Black; border: none;} QPushButton:hover{background-color: rgba(73, 182, 255, 0.75); color: rgb(24,24,24); font:87 18pt Arial Black; border: none;}";
         QString const otherday = "background-color: rgba(44,44,44,40); color: #ffffff; font:87 18pt Arial Black; border: none;";
         QString const removeButton = "QPushButton{background-color: #E84855; color: white; border: none; font:87 14pt Arial Black;} QPushButton:hover{background-color: rgba(232, 72, 85, 0.75); color: white; border: none; font:87 14pt Arial Black;}";

       //array to name labels for days in week
         QString const polishName[7] = {"Pn", "Wt", "Śr", "Cz", "Pt", "Sb", "Nd"};
         QString const englishName[7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
         QString const germanName[7] = {"Mo", "Di", "Mi", "Do", "Fr", "Sa", "So"};

         //private functions

         void ReadFromFile(QString);


    Ui::Base *ui;
};
#endif // BASE_H
