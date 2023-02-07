#include "summary.h"

Summary::Summary(QWidget *parent, int _width,int _height,QString _text)
    : QWidget{parent}
{
    summaryLabel= new QLabel("Summary");
    summaryLabel->setMaximumSize(_width,_height/8);

    summaryText= new QLabel(_text);
    summaryText ->setMinimumSize(200,100);  // should be dynamic

    summaryScroll = new QScrollArea(this);
    summaryScroll ->setMaximumSize(_width,_height/8*1*7);
    summaryScroll->setWidget(summaryText);
    summaryScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    localLayout = new QVBoxLayout(this);
    localLayout->addWidget(summaryLabel);
    localLayout->addWidget(summaryScroll);

    localWidget = new QWidget(this);
    localWidget->setLayout(localLayout);
    localWidget->setMaximumSize(_width,_height);
}

QLabel* Summary::Label(){
    return summaryLabel;
}

QScrollArea* Summary::Body(){
    return summaryScroll;
}

QBoxLayout* Summary::SummaryLayout(){
    return localLayout;
}

QWidget* Summary::SummaryWidget(){
    return localWidget;
}

Summary::~Summary(){
    delete this;
}

void Summary::SetText(FileOpener* _fo){
   /* summaryText->setText("   User " + _fo->GetUser() + "\n" +
                         "   This session lasted : "  + QDateTime::fromMSecsSinceEpoch(_fo->GetDuration()).toString("mm:ss") + "\n" +
                         "   Total Errors : " + QString::number(_fo->GetErrors()) + "\n" +
                         "   Total Warning : " + QString::number(_fo->GetWarnings()) + "\n");*/
    summaryText->setText("   User: " + _fo->GetUser() + "\n" +
                         "   This session lasted : "  + QDateTime::fromMSecsSinceEpoch(_fo->GetDuration()).toString("mm:ss") + "\n");
    foreach (QString q, _fo->GetSummary()) {
        summaryText->setText(summaryText->text() + q + "\n");
    }

}
