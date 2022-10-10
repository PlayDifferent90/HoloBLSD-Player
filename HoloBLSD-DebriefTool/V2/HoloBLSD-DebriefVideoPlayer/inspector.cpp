#include "inspector.h"
#include "qapplication.h"
Inspector::Inspector(QWidget *parent, int _width, int _height, FileOpener* _fileOpener)
    : QWidget{parent}
{
    //inspector
    inspectorTabs = new QTabWidget(this);
    inspectorTabs->setMaximumSize(_width,_height);

    inspectorLabel = new QLabel("Inspector");
    inspectorLabel->setMaximumSize(_width,_height/8);


    localLayout = new QVBoxLayout(this);
    localLayout->addWidget(inspectorLabel);
    localLayout->addWidget(inspectorTabs);

    localWidget = new QWidget(this);
    localWidget->setLayout(localLayout);
    localWidget->setMaximumSize(_width,_height);

    fo=_fileOpener;
}

Inspector::~Inspector(){
    delete this;
}

QWidget* Inspector::InspectorWidget(){
    return localWidget;
}

//todo: quando si apre il masterlog si deve creare una tab per ciascun file
void Inspector::PopulateInspector(){

    QApplication::setOverrideCursor(Qt::WaitCursor);
    userInspectorTab = new  QWidget(this);
    inspectorLayout = new QGridLayout(userInspectorTab);
    inspectorTabs->addTab(userInspectorTab,fo->GetUser());

    int i=0;
    QString vis = "";
    foreach (Activity* act , fo->GetActivities()) {
        i++;
        if(act->GetVisibility())
            vis="true";
        else
            vis="false";

        QLabel* inspectorText= new QLabel(" infos will be displayed here;");
        inspectorText->setText("Activity: " + act->GetName() + "\n"+"ID : "+ QString::number(act->GetActID()) +  "\n" +
                               "Is visible in timeline : " +  vis + "\n"+
                               "\n" );
        foreach (Node* nn, act->GetNodesByUser(fo->GetUser())) {
                inspectorText->setText(inspectorText->text() +
                                       "Activity started at: " + QDateTime::fromMSecsSinceEpoch(nn->GetStart()->GetTime()).toString("mm:ss")+" , finished at: " + QDateTime::fromMSecsSinceEpoch(nn->GetFinish()->GetTime()).toString("mm:ss") +"\n" +
                                       "Errors: " + QString::number( nn->GetErr()) + "; Warning " + QString::number(nn->GetWar()) + "\n");
            }
        inspectorLayout->addWidget(inspectorText,i,0,1,1);
    }

    SelectText(""); // empty inspector on start

    QApplication::restoreOverrideCursor();
}

void Inspector::SelectText(QString  _actListText){
    int i =0;
    foreach (Activity* act, fo->GetActivities()) {
        qDebug()<<"current Widget is "<<  inspectorTabs->currentWidget()->layout();
       inspectorTabs->currentWidget()->layout()->itemAt(i)->widget()->hide();
        if(act->GetName() ==_actListText){
            //todo: controllare indici di masterlog
            inspectorTabs->currentWidget()->layout()->itemAt(i)->widget()->show();
        }
        i++;
    }

}
