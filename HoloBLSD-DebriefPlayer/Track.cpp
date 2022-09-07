//include "Track.h"
//RectF Track::boundingRect()const {
//   return QRectF(0,0,length,height);
//
//oid Track::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
//   Q_UNUSED(widget);
//   painter->setBrush(brush);
//   painter->setPen(pen);
//   painter->drawRoundedRect(boundingRect(),rounded,rounded);
//   painter->setBrush(outlineColor);
//   QFont font=scene->font();
//   QFontMetricsF fontMetrics(font);
//   QString text("tReplaySong1");
//   int heightFont = fontMetrics.boundingRect(text).height();
//   painter->drawText(0,heightFont,text);
////
///////QVariant Track::itemChange(GraphicsItemChange change, const QVariant &value) {
///        if (change == ItemPositionChange && scene()) {
///            // value is the new position.
///            QPointF newPos = value.toPointF();
/////            newPos.setY(y());
///            if(newPos.x() < 0){
///                newPos.setX(0);
///            }
///    //        newPos = qBound(QPointF(0,0),newPos,QPointF(10000,0));
///            return newPos;
///        }
///        return QGraphicsItem::itemChange(change, value);
///    }
//////oid Track::mousePressEvent(QGraphicsSceneMouseEvent *event){
//   qDebug()<<"Press";
//   pressed = true;
//   oldMousePos = event->scenePos();
//   oldPos = scenePos();
//
//oid Track::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
//   qDebug()<<"Move";
////   if (pressed){
//       QPointF newPos = event->scenePos();
//       qDebug()<<newPos;
//       int yDiff = newPos.y() - oldPos.y();
//       qDebug()<<abs(yDiff);
//       int heightDiff=15;
//       if (abs(yDiff) > heightDiff ){
//           heightDiff*=2;
//           heightDiff+=5;
//           int d = (int)(yDiff%heightDiff);
//           newPos.setY(oldPos.y()+(int)(yDiff/heightDiff)*heightDiff);//*((int)(yDiff/30))>0?1:0);
//           setY(newPos.y());
//           //                tempOldPos.setY(newPos.y() - oldPos.y());
//       }else{
//           setY(oldPos.y());
//       }
///////            setPos(pos() +newPos-tempOldPos);
//       int dx = (newPos - oldMousePos).x();
//       setX(oldPos.x()+dx);
///        setY(newPos.y());
//   }
//
//oid Track::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
//   qDebug()<<"Release";
//   pressed = false;
//   oldMousePos = event->scenePos();
//   oldPos = scenePos();
//
//oid Track::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
//   qDebug()<<"Double Click";
//
