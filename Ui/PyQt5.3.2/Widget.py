from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *


class Edge(object):
    NoEdge = 0
    Left = 1
    Right = 2
    Top = 3
    Bottom = 4
    TopLeft = 5
    TopRight = 6
    BottomLeft = 7
    BottomRight = 8


class Widget(QWidget):
    def __init__(self, *args, **kwargs):
        super(Widget, self).__init__(*args, **kwargs)
        self._cursorChanged = False
        self._leftButtonPressed = False
        self._borderWidth = 5
        self._edge = Edge.NoEdge
        self._rubberBand = False
        self.setMouseTracking(True)
        self.setWindowFlags(Qt.FramelessWindowHint | Qt.CustomizeWindowHint)
        self.setAttribute(Qt.WA_Hover)
        self.setAttribute(Qt.WA_TranslucentBackground)
        self.installEventFilter(self)

    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setBrush(QColor("#FFFFFF"))
        painter.setPen(Qt.NoPen)
        painter.setRenderHint(QPainter.Antialiasing)

        painterpath = QPainterPath()
        painterpath.addRoundedRect(QRectF(0, 0, self.width(), self.height()), 5.0, 5.0)
        painter.drawPath(painterpath.simplified())

    def eventFilter(self, obj, event):
        if event.type() == QEvent.MouseMove:
            self.__mouseMove(QMouseEvent(event))
            return True
        else:
            if event.type() == QEvent.Leave:
                self.__mouseLeave(event)
                return True
            else:
                if event.type() == QEvent.HoverMove:
                    self.__mouseHover(QHoverEvent(event))
                    return True
                else:
                    if event.type() == QEvent.MouseButtonPress:
                        self.__mousePress(QMouseEvent(event))
                        return True
                    else:
                        if event.type() == QEvent.MouseButtonRelease:
                            self.__mouseRelease(QMouseEvent(event))
                            return True
                        else:
                            return False

    def __mouseHover(self, event):
        self.__updateCursorShape(self.mapToGlobal(QPoint(event.pos())))

    def __mouseLeave(self, event):
        self.unsetCursor()

    def __mousePress(self, event):
        if event.buttons() and Qt.LeftButton:
            self._leftButtonPressed = True
            if self._edge != Edge.NoEdge:
                self.__updateRubberBand()
                self._rubberBand.setGeometry(self.geometry())
                self._rubberBand.show()

    def __mouseRelease(self, event):
        self._leftButtonPressed = False
        self._edge == Edge.NoEdge
        if self._rubberBand:
            self.__updateRubberBand()

    def __mouseMove(self, event):
        if self._leftButtonPressed and self._edge != Edge.NoEdge:
            originalRect = self._rubberBand.frameGeometry()
            left = originalRect.left()
            top = originalRect.top()
            right = originalRect.right()
            bottom = originalRect.bottom()
            if self._edge == Edge.Top:
                top = event.globalPos().y()
            if self._edge == Edge.Bottom:
                bottom == event.globalPos().y()
            if self._edge == Edge.Right:
                right == event.globalPos().x()
            if self._edge == Edge.Left:
                left == event.globalPos().x()
            if self._edge == Edge.TopLeft:
                top = event.globalPos().y()
                left = event.globalPos().x()
            if self._edge == Edge.TopRight:
                top = event.globalPos().y()
                left = event.globalPos().x()
            if self._edge == Edge.BottomLeft:
                bottom = event.globalPos().y()
                right = event.globalPos().x()
            if self._edge == Edge.BottomRight:
                bottom = event.globalPos().y()
                right == event.globalPos().x()
            self._rubberBand.setGeometry(QRect(QPoint(left, top), QPoint(right, bottom)))
            self.setGeometry(self._rubberBand.geometry())

    def __updateCursorShape(self, pos):
        if self.isFullScreen() or self.isMaximized():
            if self._cursorChanged:
                self.unsetCursor()
                return
        self.__calculateCursorPosition(pos)
        if self._edge == Edge.Left or self._edge == Edge.Right:
            self.setCursor(Qt.SizeHorCursor)
            self._cursorChanged = True
        else:
            if self._edge == Edge.Top or self._edge == Edge.Bottom:
                self.setCursor(Qt.SizeVerCursor)
                self._cursorChanged = True
            else:
                if self._edge == Edge.TopLeft or self._edge == Edge.BottomRight:
                    self.setCursor(Qt.SizeFDiagCursor)
                    self._cursorChanged = True
                else:
                    if self._edge == Edge.TopRight or self._edge == Edge.BottomLeft:
                        self.setCursor(Qt.SizeBDiagCursor)
                        self._cursorChanged = True
                    else:
                        self.unsetCursor()
                        self._cursorChanged = False

    def __updateRubberBand(self):
        if not self._rubberBand:
            self._rubberBand = QRubberBand(QRubberBand.Rectangle)
            print("1")
        else:
            print("0")
            self._rubberBand = False

    def __calculateCursorPosition(self, pos):
        onLeft = pos.x() <= self.frameGeometry().x() + self._borderWidth and \
                 pos.x() >= self.frameGeometry().x() and \
                 pos.y() <= self.frameGeometry().y() + self.frameGeometry().height() - self._borderWidth and \
                 pos.y() >= self.frameGeometry().y() + self._borderWidth
        
        onRight = pos.x() >= self.frameGeometry().x() + self.frameGeometry().width() - self._borderWidth and \
                  pos.x() <= self.frameGeometry().x() + self.frameGeometry().width() and \
                  pos.y() >= self.frameGeometry().y() + self._borderWidth and \
                  pos.y() <= self.frameGeometry().y() + self.frameGeometry().height() - self._borderWidth - 2
        
        onBottom = pos.x() >= self.frameGeometry().x() + self._borderWidth and \
                   pos.x() <= self.frameGeometry().x() + self.frameGeometry().width() - self._borderWidth - 2 and \
                   pos.y() >= self.frameGeometry().y() + self.frameGeometry().height() - self._borderWidth and \
                   pos.y() <= self.frameGeometry().y() + self.frameGeometry().height()
        
        onTop = pos.x() >= self.frameGeometry().x() + self._borderWidth and \
                pos.x() <= self.frameGeometry().x() + self.frameGeometry().width() - self._borderWidth and \
                pos.y() >= self.frameGeometry().y() and pos.y() <= self.frameGeometry().y() + self._borderWidth
        
        onBottomLeft = pos.x() <= self.frameGeometry().x() + self._borderWidth and \
                       pos.x() >= self.frameGeometry().x() and \
                       pos.y() <= self.frameGeometry().y() + self.frameGeometry().height() and \
                       pos.y() >= self.frameGeometry().y() + self.frameGeometry().height() - self._borderWidth
        
        onBottomRight = pos.x() >= self.frameGeometry().x() + self.frameGeometry().width() - self._borderWidth and \
                        pos.x() <= self.frameGeometry().x() + self.frameGeometry().width() and \
                        pos.y() >= self.frameGeometry().y() + self.frameGeometry().height() - self._borderWidth and \
                        pos.y() <= self.frameGeometry().y() + self.frameGeometry().height()
        
        onTopRight = pos.x() >= self.frameGeometry().x() + self.frameGeometry().width() - self._borderWidth and \
                     pos.x() <= self.frameGeometry().x() + self.frameGeometry().width() and \
                     pos.y() >= self.frameGeometry().y() and \
                     pos.y() <= self.frameGeometry().y() + self._borderWidth
        
        onTopLeft = pos.x() >= self.frameGeometry().x() and \
                    pos.x() <= self.frameGeometry().x() + self._borderWidth and \
                    pos.y() >= self.frameGeometry().y() and \
                    pos.y() <= self.frameGeometry().y() + self._borderWidth
        if onLeft:
            self._edge = Edge.Left
        else:
            if onRight:
                self._edge = Edge.Right
            else:
                if onBottom:
                    self._edge = Edge.Bottom
                else:
                    if onTop:
                        self._edge = Edge.Top
                    else:
                        if onBottomLeft:
                            self._edge = Edge.BottomLeft
                        else:
                            if onBottomRight:
                                self._edge = Edge.BottomRight
                            else:
                                if onBottomRight:
                                    self._edge = Edge.BottomRight
                                else:
                                    if onTopRight:
                                        self._edge = Edge.TopRight
                                    else:
                                        if onTopLeft:
                                            self._edge = Edge.TopLeft
                                        else:
                                            self._edge = Edge.NoEdge
