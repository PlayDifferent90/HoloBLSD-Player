#include "inspector.h"
#include "qapplication.h"
#include "qtabbar.h"
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

void Inspector::PopulateInspector(){

    QApplication::setOverrideCursor(Qt::WaitCursor);
    userInspectorTab = new  QWidget(this);
    inspectorLayout = new QGridLayout(userInspectorTab);
    inspectorTabs->addTab(userInspectorTab,fo->GetUser());

    int i=0;
    QString vis = "";
    foreach (Activity* act , fo->GetActivities()) {
        i++;

        QLabel* inspectorText= new QLabel(" infos will be displayed here;");
        inspectorText->setText("Activity: " + act->GetName() + "\n"+"ID : "+ QString::number(act->GetActID()) +  "\n" +
                               "\n" );

        foreach (Node* nn, act->GetNodesByUser(fo->GetUser())) {
                inspectorText->setText(inspectorText->text() +
                                       "Activity started at: " + QDateTime::fromMSecsSinceEpoch(nn->GetStart()->GetTime()).toString("mm:ss")+" , finished at: " + QDateTime::fromMSecsSinceEpoch(nn->GetFinish()->GetTime()).toString("mm:ss") +"\n" +
                                       "Errors: " + QString::number( nn->GetErr()) + "; Warning " + QString::number(nn->GetWar()) + "\n");
            }
        inspectorLayout->addWidget(inspectorText,i,0,1,1);
    }


    QApplication::restoreOverrideCursor();
}

void Inspector::PopulateMasterInspector(){
    QApplication::setOverrideCursor(Qt::WaitCursor);
    userInspectorTab = new  QWidget(this);
    inspectorLayout = new QGridLayout(userInspectorTab);
    inspectorTabs->addTab(userInspectorTab,fo->GetUser());

    int i=0;
    QString vis = "";
    foreach (Activity* act , fo->GetActivities()) {
        i++;
        QLabel* inspectorText= new QLabel(" infos will be displayed here;");
        inspectorText->setText("Activity: " + act->GetName() + "\n"+"ID : "+ QString::number(act->GetActID()) +  "\n" +
                               "Executed by " + QString::number(act->GetUsersNumber()) + " users;\n"+
                               "\n" );
        foreach (Node* nn, act->GetNodes()) {
                inspectorText->setText(inspectorText->text() +
                                       nn->GetUserID()+ ":\n"+
                                       "Activity started " + " at: " + QDateTime::fromMSecsSinceEpoch(nn->GetStart()->GetTime()).toString("mm:ss")+" , finished at: " + QDateTime::fromMSecsSinceEpoch(nn->GetFinish()->GetTime()).toString("mm:ss") +"\n" +
                                       "Errors: " + QString::number( nn->GetErr()) + "; Warning " + QString::number(nn->GetWar()) + "\n\n");
            }
        inspectorLayout->addWidget(inspectorText,2*i,0,1,1);
    }

    inspectorTabs->tabBar()->moveTab(inspectorTabs->count()-1,0);
    inspectorTabs->setCurrentIndex(0);

    QApplication::restoreOverrideCursor();
}

void Inspector::SelectText(QString  _actListText){
    int item =0;
    foreach (Activity* act, fo->GetActivities()) {
        for( int tab =0;tab<inspectorTabs->tabBar()->count(); tab++){
            if(inspectorTabs->widget(tab)->layout()->itemAt(item)==nullptr){

            }else{
                inspectorTabs->widget(tab)->layout()->itemAt(item)->widget()->hide();
                if(act->GetName() ==_actListText){
                    inspectorTabs->widget(tab)->layout()->itemAt(item)->widget()->show();
                }
            }
        }
        item++;
    }
}
