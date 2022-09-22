#include "summary.h"

Summary::Summary(QWidget *parent, int _width,int _height,QString _text)
    : QWidget{parent}
{
    //todo: delegare proporzioni a chiamata
    summaryLabel= new QLabel("Summary");
    summaryLabel->setMaximumSize(_width,_height/8);

    summaryText= new QLabel(_text);
    summaryText ->setMaximumWidth(_width-30);

    summaryScroll = new QScrollArea(this);
    summaryScroll ->setMaximumSize(_width,_height/8*1*7);
    summaryScroll->setWidget(summaryText);

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
