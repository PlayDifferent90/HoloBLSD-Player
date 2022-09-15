#include "GraphicsView.h"
#include <QDebug>
/*Mouse interaction*/
void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(!itemAt(event->pos())){
        std::cout << "Press"<<std::endl;
    }else{
        auto item = this->scene()->itemAt(event->pos(),QTransform());
    }
    QGraphicsView::mousePressEvent(event);
}
/*zoom in, zoom out*/
void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    auto item = this->scene()->itemAt(event->pos(),QTransform());
    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event){
    QGraphicsView::mouseReleaseEvent(event);
}

