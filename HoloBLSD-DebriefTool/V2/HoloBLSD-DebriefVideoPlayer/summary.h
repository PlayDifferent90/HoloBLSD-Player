#ifndef SUMMARY_H
#define SUMMARY_H

#include "qboxlayout.h"
#include "qlabel.h"
#include "qscrollarea.h"
#include "qdatetime.h"
#include "fileopener.h"
#include <QObject>
#include <QWidget>

class Summary : public QWidget
{
    Q_OBJECT
public:
    explicit Summary(QWidget *parent = nullptr);

    Summary(QWidget *parent, int _width, int _height,QString _text);

    QLabel *Label();
    QScrollArea *Body();
    QBoxLayout *SummaryLayout();
    QWidget *SummaryWidget();
    ~Summary();
    void SetText(FileOpener *_fo);
private:
    QLabel* summaryLabel;
    QLabel* summaryText;
    QScrollArea* summaryScroll;
    QBoxLayout* localLayout;
    QWidget* localWidget;
signals:

};

#endif // SUMMARY_H
