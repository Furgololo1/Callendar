#include "base.h"
#include "ui_base.h"


namespace variable {
int i = 0;
int x = 5;
int y = 5;
QString limit = "bis zu 10 Veranstaltungen";
QString pathToRemove;
}


void Base::SaveToFile()
{
    QFile file(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Events/" + filename2 + ".txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    QTextStream in(&file);

    for (int i = 0; i < textarr.size(); i++) {
        in<<textarr[i]<<"\n";
    }

}

void Base::on_savebtn_clicked()
{
    QString text = ui->textcal->text();
    QString textdate = ui->timecal->text();
    textarr.push_back(textdate + "     " + text);
    qDebug()<<textarr.last();
    NewCalendarlbl(textdate + "     " + text);
}

void Base::NewCalendarlbl(QString event)
{
    ui->textcal->clear();

    using variable::i;
    using variable::x;
    using variable::y;
    using variable::limit;

    if(i >= 10){
        ui->textcal->setText(limit);
    }

else{
      //event button
        lbl2[i] = new QLabel(event, ui->gB2);
        lbl2[i]->resize(340,30);
        lbl2[i]->move(x,y);
        lbl2[i]->setStyleSheet("color: #ffffff; font:87 14pt Arial Black;");
        lbl2[i]->setAlignment(Qt::AlignVCenter);
        lbl2[i]->show();
        y += 35;
        i++;

    }
        qDebug()<<i;
}



void Base::ClearLabels()
{
    using variable::i;
    using variable::y;

    for(int j = 0; j < i; j++){
        delete lbl2[j];
    }

    i = 0;
    y = 5;
    QTime time(00,00,00,00);
    ui->timecal->setTime(time);
}

void Base::on_backbtn_clicked()
{
    SaveToFile();
    ClearLabels();

    ui->sW->setCurrentIndex(0);
}


void Base::ReadFromFile(QString path)
{
    using variable::pathToRemove;
    pathToRemove = path;

    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    if(!file.exists()){qDebug()<<"File doesn't exists";}


    else{
    QTextStream out(&file);

    QString event;

        while(!out.atEnd()){
            event = out.readLine();
                if(!event.isEmpty())
                    NewCalendarlbl(event);
        }

    }
}


void Base::ChangeLanguageEng()
{
    using variable::limit;

    int j = 0;
 for(auto i : lbl){
     i->setText(englishName[j]);
     j++;
 }
    ui->displayevents->setText("Show saved events");
    ui->savebtn->setText("Add");
    ui->settingslbl->setText("Settings");
    ui->langlbl->setText("Change language");
    this->setWindowTitle("Calendar");
    limit = "The limit is 10 events per day";

}


void Base::ChangeLanguagePl()
{
    using variable::limit;

    int j = 0;
 for(auto i : lbl){
     i->setText(polishName[j]);
     j++;
 }
    ui->displayevents->setText("Pokaż zapisane wydarzenia");
    ui->savebtn->setText("Dodaj");
    ui->settingslbl->setText("Ustawienia");
    ui->langlbl->setText("Zmień język");
    this->setWindowTitle("Kalendarz");
    limit = "Limit to 10 zdarzeń na dzień";

}


void Base::ChangeLanguageGer()
{
    using variable::limit;

    int j = 0;
 for(auto i : lbl){
     i->setText(germanName[j]);
     j++;
 }
    ui->displayevents->setText("Ereignisse zeigen");
    ui->savebtn->setText("einfügen");
    ui->settingslbl->setText("Einstellungen");
    ui->langlbl->setText("Sprache ändern");
    this->setWindowTitle("Kalender");

    limit = "bis zu 10 Veranstaltungen";
}























