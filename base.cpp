#include "base.h"
#include "ui_base.h"
#include "ui_mess.h"

Base::Base(QWidget *parent)
    : QMainWindow(parent, Qt::FramelessWindowHint )
    , ui(new Ui::Base)
{
    ui->setupUi(this);

  if(M == 1)
        prevdate = new QDate(Y-1, 12,1);
  else
        prevdate = new QDate(Y, M-1,1);

    ui->sW->setCurrentIndex(0);
    SetUpLblDate();
    CreateButtons();
    CreateLabels();
    CreateDir();

}

Base::~Base()
{
    //delete btn[i][j];
    delete ui;
}

void Base::CreateLabels()
{

    int x = 5, y = 0;
    for (int i = 0; i < 7; i++) {
        lbl[i] = new QLabel(englishName[i], ui->gB);
        lbl[i]->resize(45,45);
        lbl[i]->move(x,y);
        lbl[i]->setStyleSheet("color: #ffffff; font:87 12pt Arial Black;");
        lbl[i]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        lbl[i]->show();
        x += 50;
    }

}

void Base::CreateButtons()
{

    QIcon icon(":/new/prefix1/Icons/arr.ico");
    ui->backbtn->setIcon(icon);
    ui->backbtn->setIconSize(QSize(45,45));

    ui->backbtn_2->setIcon(icon);
    ui->backbtn_2->setIconSize(QSize(45,45));

    QIcon icon2(":/new/prefix1/Icons/op.ico");
    ui->optionbtn->setIcon(icon2);
    ui->optionbtn->setIconSize(QSize(35,35));


    QIcon icon3(":/new/prefix1/Icons/x.ico");
    ui->closebtn->setIcon(icon3);
    ui->closebtn->setIconSize(QSize(33,33));

    int x = 5, y = 45;

    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 7; j++){

                        btn[i][j] = new QPushButton("a", ui->gB);
                        btn[i][j]->resize(45,45);
                        btn[i][j]->move(x,y);
                        btn[i][j]->show();
                        btn[i][j]->setEnabled(true);
                        connect(btn[i][j], &QPushButton::clicked, this, [=]{ QString b = btn[i][j]->text(); on_GetClickedDay(b); });
                        x += 50;
        }
        y+=50;
        x = 5;
    }

CheckDay();
}


void Base::CheckDay()
{

    int i;
    QDate *foo = new QDate(Y, M, 1);

   switch(foo->dayOfWeek()){
   case 1:
       i=0;
   break;
   case 2:
       i=1;
   break;
   case 3:
       i=2;
   break;
   case 4:
       i=3;
   break;
   case 5:
       i=4;
   break;
   case 6:
       i=5;
   break;
   case 7:
       i=6;
   break;
       }

   delete foo;

    SetNumber(i);



}

void Base::SetUpLblDate()
{
    QDate foo2(QDate::currentDate());
    ui->uplbl->setText( foo2.toString(Qt::ISODate));
}



void Base::SetNumber(int day)
{

    int count = 1;
    int countafter = 1, countbefore = prevdate->daysInMonth();

    D = date.daysInMonth();

countbefore -= day - 1;

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {

            if((j >= day) && (i == 0)){
                btn[0][j]->setText(QString::number(count++));
                btn[0][j]->setStyleSheet(normalday);
                      }

            else if((j < day) && (i == 0)){
                btn[0][j]->setStyleSheet(otherday);
                btn[0][j]->setText(QString::number(countbefore++));
                btn[0][j]->setEnabled(false);
            }

            else if(i > 0){
                btn[i][j]->setText(QString::number(count++));
                btn[i][j]->setStyleSheet(normalday);
                      }

            if(TodaysDay == count-1 && Month == M && Year == Y){
                btn[i][j]->setStyleSheet(currentday);
            }

            if(count-1 > D){
               btn[i][j]->setStyleSheet(otherday);
               btn[i][j]->setText(QString::number(countafter++));
               btn[i][j]->setEnabled(false);
                         }

            if(!btn[i][j]->isEnabled())
                    btn[i][j]->setStyleSheet(otherday);

        }
    }



ui->lbl->setText(QString::number(date.month())+ " " + QString::number(date.year()));


}


void Base::on_prevmonth_clicked()
{

    prevdate->setDate(Y,M,1);

    M -= 1;
    if(M == 0){
        M = 12;
        Y -= 1;
    }
    date.setDate(Y,M,1);
    D = date.daysInMonth();

    if(M == 1)
        prevdate->setDate(Y-1, 12,1);

    for(int i = 0; i < 6; i++){
             for(int j = 0; j < 7; j++){
                    btn[i][j]->setEnabled(true);
             }
        }

    CheckDay();

}

void Base::on_nextmonth_clicked()
{

    prevdate->setDate(Y,M,1);

    M += 1;
    if(M == 13){
        M = 1;
        Y += 1;
    }
    date.setDate(Y,M,1);
    D = date.daysInMonth();

    if(M == 1)
       prevdate->setDate(Y, 12,1);

    for(int i = 0; i < 6; i++){
             for(int j = 0; j < 7; j++){
                    btn[i][j]->setEnabled(true);
             }
        }


   CheckDay();
}


void Base::on_closebtn_clicked()
{
    this->close();
}


void Base::on_GetClickedDay(QString get)
{

    if(get.size() == 1){
        get = "0" + get;
    }

    QString m = QString::number(M);

    if(m.size() == 1){
        m = "0" + m;
    }

    QString y = QString::number(Y);
    //QString y = QVariant(Y).toString();

    qDebug()<<M<<" "<<Y;

    QString datetodisplay = get+"."+m+"."+y;
    QString namefile = get+"_"+m+"_"+y;
    qDebug()<<m<<" "<<y;//datetodisplay;

    ui->sW->setCurrentIndex(1);
    ui->lbl2->setText(datetodisplay);
    filename2 = namefile;

    ReadFromFile(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Events/" + namefile + ".txt");
}


void Base::on_optionbtn_clicked()
{
    ui->sW->setCurrentIndex(2);
}

void Base::on_backbtn_2_clicked()
{
    ui->sW->setCurrentIndex(0);
}

void Base::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0)
        ChangeLanguageEng();
    else if(index == 1)
        ChangeLanguagePl();
    else
        ChangeLanguageGer();
}

void Base::CreateDir()
{
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    dir.mkdir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Events");

}

