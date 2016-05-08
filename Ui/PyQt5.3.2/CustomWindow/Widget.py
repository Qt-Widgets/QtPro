from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *


class Edge(object):
    NoEdge = 0x0
    Left = 0x1
    Right = 0x2
    Top = 0x3
    Bottom = 0x4
    TopLeft = 0x5
    TopRight = 0x6
    BottomLeft = 0x7
    BottomRight = 0x8


class Widget(QMainWindow):
    def __init__(self, borderwidth = None, radius = None, *args, **kwargs):
        super(Widget, self).__init__(*args, **kwargs)
        self._cursorChanged = False
        self._leftButtonPressed = False
        self._rubberBand = QRubberBand(QRubberBand.Rectangle)
        self._mouseMove = Edge.NoEdge
        self._mousePress = Edge.NoEdge
        if borderwidth:
            self._borderWidth = borderwidth
        else:
            self._borderWidth = 5
        if radius:
            self._radius = radius
        else:
            self._radius = 5.0
        self.setWindowFlags(Qt.FramelessWindowHint | Qt.CustomizeWindowHint)
        self.setAttribute(Qt.WA_Hover)
        self.setAttribute(Qt.WA_TranslucentBackground)
        self.setMouseTracking(True)
        self.installEventFilter(self)

    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setBrush(QColor("#FFFFFF"))
        painter.setPen(Qt.NoPen)
        painter.setRenderHint(QPainter.Antialiasing)

        painterpath = QPainterPath()
        painterpath.addRoundedRect(QRectF(0, 0, self.width(), self.height()), self._radius, self._radius)
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
        self.__updateCursorShape(self.mapToGlobal(event.pos()))

    def __mouseLeave(self, event):
        if self._leftButtonPressed:
            self.unsetCursor()

    def __mousePress(self, event):
        if event.button() == Qt.LeftButton:
            self._leftButtonPressed = True
            self._mousePress = self.__calculateCursorPosition(event.globalPos(), self.frameGeometry())
            if self._mousePress != Edge.NoEdge:
                self._rubberBand.setGeometry(self.frameGeometry())

    def __mouseRelease(self, event):
        if event.button() == Qt.LeftButton:
            self._leftButtonPressed = False

    def __mouseMove(self, event):
        if self._leftButtonPressed:
            if self._mousePress != Edge.NoEdge:
                originalRect = self._rubberBand.frameGeometry()
                left = originalRect.left()
                top = originalRect.top()
                right = originalRect.right()
                bottom = originalRect.bottom()
                if self._mousePress == Edge.Top:
                    top = event.globalPos().y()
                else:
                    if self._mousePress == Edge.Bottom:
                        bottom = event.globalPos().y()
                    else:
                        if self._mousePress == Edge.Right:
                            right = event.globalPos().x()
                        else:
                            if self._mousePress == Edge.Left:
                                left = event.globalPos().x()
                            else:
                                if self._mousePress == Edge.TopRight:
                                    top = event.globalPos().y()
                                    right = event.globalPos().x()
                                else:
                                    if self._mousePress == Edge.TopLeft:
                                        top = event.globalPos().y()
                                        left = event.globalPos().x()
                                    else:
                                        if self._mousePress == Edge.BottomLeft:
                                            bottom = event.globalPos().y()
                                            left = event.globalPos().x()
                                        else:
                                            if self._mousePress == Edge.BottomRight:
                                                bottom = event.globalPos().y()
                                                right = event.globalPos().x()

                newrect = QRect(QPoint(left, top), QPoint(right, bottom))
                if newrect.width() < self.minimumWidth():
                    left = self.frameGeometry().x()
                else:
                    if newrect.height() < self.minimumHeight():
                        top = self.frameGeometry().y()
                self.setGeometry(QRect(QPoint(left, top), QPoint(right, bottom)))
                self._rubberBand.setGeometry(QRect(QPoint(left, top), QPoint(right, bottom)))

    def __updateCursorShape(self, pos):
        if self.isFullScreen() or self.isMaximized():
            if self._cursorChanged:
                self.unsetCursor()
                return
        self._mouseMove = self.__calculateCursorPosition(pos, self.frameGeometry())
        if self._mouseMove == Edge.Left or self._mouseMove == Edge.Right:
            self.setCursor(Qt.SizeHorCursor)
            self._cursorChanged = True
        else:
            if self._mouseMove == Edge.Top or self._mouseMove == Edge.Bottom:
                self.setCursor(Qt.SizeVerCursor)
                self._cursorChanged = True
            else:
                if self._mouseMove == Edge.TopLeft or self._mouseMove == Edge.BottomRight:
                    self.setCursor(Qt.SizeFDiagCursor)
                    self._cursorChanged = True
                else:
                    if self._mouseMove == Edge.TopRight or self._mouseMove == Edge.BottomLeft:
                        self.setCursor(Qt.SizeBDiagCursor)
                        self._cursorChanged = True
                    else:
                        self.unsetCursor()
                        self._cursorChanged = False

    def __updateRubberBand(self):
        if not self._rubberBand:
            self._rubberBand = QRubberBand(QRubberBand.Rectangle)
            self._rubberBand.show()
        else:
            self._rubberBand = False

    def __calculateCursorPosition(self, pos, framerect):
        onLeft = pos.x() <= framerect.x() + self._borderWidth and \
                 pos.x() >= framerect.x() and \
                 pos.y() <= framerect.y() + framerect.height() - self._borderWidth and \
                 pos.y() >= framerect.y() + self._borderWidth

        onRight = pos.x() >= framerect.x() + framerect.width() - self._borderWidth and \
                  pos.x() <= framerect.x() + framerect.width() and \
                  pos.y() >= framerect.y() + self._borderWidth and \
                  pos.y() <= framerect.y() + framerect.height() - self._borderWidth - 2

        onBottom = pos.x() >= framerect.x() + self._borderWidth and \
                   pos.x() <= framerect.x() + framerect.width() - self._borderWidth - 2 and \
                   pos.y() >= framerect.y() + framerect.height() - self._borderWidth and \
                   pos.y() <= framerect.y() + framerect.height()

        onTop = pos.x() >= framerect.x() + self._borderWidth and \
                pos.x() <= framerect.x() + framerect.width() - self._borderWidth and \
                pos.y() >= framerect.y() and pos.y() <= framerect.y() + self._borderWidth

        onBottomLeft = pos.x() <= framerect.x() + self._borderWidth and \
                       pos.x() >= framerect.x() and \
                       pos.y() <= framerect.y() + framerect.height() and \
                       pos.y() >= framerect.y() + framerect.height() - self._borderWidth

        onBottomRight = pos.x() >= framerect.x() + framerect.width() - self._borderWidth and \
                        pos.x() <= framerect.x() + framerect.width() and \
                        pos.y() >= framerect.y() + framerect.height() - self._borderWidth and \
                        pos.y() <= framerect.y() + framerect.height()

        onTopRight = pos.x() >= framerect.x() + framerect.width() - self._borderWidth and \
                     pos.x() <= framerect.x() + framerect.width() and \
                     pos.y() >= framerect.y() and \
                     pos.y() <= framerect.y() + self._borderWidth

        onTopLeft = pos.x() >= framerect.x() and \
                    pos.x() <= framerect.x() + self._borderWidth and \
                    pos.y() >= framerect.y() and \
                    pos.y() <= framerect.y() + self._borderWidth

        if onLeft:
            return Edge.Left
        else:
            if onRight:
                return Edge.Right
            else:
                if onBottom:
                    return Edge.Bottom
                else:
                    if onTop:
                        return Edge.Top
                    else:
                        if onBottomLeft:
                            return Edge.BottomLeft
                        else:
                            if onBottomRight:
                                return Edge.BottomRight
                            else:
                                if onBottomRight:
                                    return Edge.BottomRight
                                else:
                                    if onTopRight:
                                        return Edge.TopRight
                                    else:
                                        if onTopLeft:
                                            return Edge.TopLeft
                                        else:
                                            return Edge.NoEdge

    def setBorderWidth(self, borderWidth):
        self._borderWidth = borderWidth

    def borderWidth(self):
        return self._borderWidth

    def setRadius(self, radius):
        self._radius = radius

    def radius(self):
        return self.radius()
