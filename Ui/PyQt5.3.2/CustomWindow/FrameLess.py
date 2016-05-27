"""
CustomWindow is a simple, native and easy to use custom top-level window created by Python Qt Binding (PyQt5.3.2)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details
Full License:https://github.com/QtTools/CustomWindow/blob/master/LICENSE

Copyright (c) 2016 Iman Ahmadvand (IMAN4K), Contact:iman72411@yahoo.com
"""

from PyQt5.QtWidgets import QWidget, QRubberBand
from PyQt5.QtCore import QObject, QEvent, QRect, QPoint , Qt
from PyQt5.QtGui import QHoverEvent, QMouseEvent


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


class FrameLess(QObject):
    def __init__(self, parent):
        super(FrameLess, self).__init__(parent)
        self._parent = parent
        self._cursorChanged = False
        self._leftButtonPressed = False
        self._mouseMove = Edge.NoEdge
        self._mousePress = Edge.NoEdge
        self._borderWidth = 5
        self._rubberBand = QRubberBand(QRubberBand.Rectangle)
        self._parent.setWindowFlags(Qt.FramelessWindowHint | Qt.CustomizeWindowHint | Qt.Window)
        self._parent.setAttribute(Qt.WA_Hover)
        self._parent.setMouseTracking(True)
        self._parent.installEventFilter(self)

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
        self.__updateCursorShape(self._parent.mapToGlobal(event.pos()))

    def __mouseLeave(self, event):
        if not self._leftButtonPressed:
            self._parent.unsetCursor()

    def __mousePress(self, event):
        if event.button() == Qt.LeftButton:
            self._leftButtonPressed = True
            self._mousePress = self.__calculateCursorPosition(event.globalPos(), self._parent.frameGeometry())
            if self._mousePress != Edge.NoEdge:
                self._rubberBand.setGeometry(self._parent.frameGeometry())

    def __mouseRelease(self, event):
        if event.button() == Qt.LeftButton:
            self._leftButtonPressed = False

    def __mouseMove(self, event):
        if self._leftButtonPressed:
            if self._mousePress != Edge.NoEdge:
                left = self._rubberBand.frameGeometry().left()
                top = self._rubberBand.frameGeometry().top()
                right = self._rubberBand.frameGeometry().right()
                bottom = self._rubberBand.frameGeometry().bottom()
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

                newRect = QRect(QPoint(left, top), QPoint(right, bottom))
                if newRect.width() < self._parent.minimumWidth():
                    left = self.frameGeometry().x()
                else:
                    if newRect.height() < self._parent.minimumHeight():
                        top = self.frameGeometry().y()
                self._parent.setGeometry(QRect(QPoint(left, top), QPoint(right, bottom)))
                self._rubberBand.setGeometry(QRect(QPoint(left, top), QPoint(right, bottom)))
        else:
            self.__updateCursorShape(event.globalPos())

    def __updateCursorShape(self, pos):
        if self._parent.isFullScreen() or self._parent.isMaximized():
            if self._cursorChanged:
                self._parent.unsetCursor()
                return
        self._mouseMove = self.__calculateCursorPosition(pos, self._parent.frameGeometry())
        if self._mouseMove == Edge.Left or self._mouseMove == Edge.Right:
            self._parent.setCursor(Qt.SizeHorCursor)
            self._cursorChanged = True
        else:
            if self._mouseMove == Edge.Top or self._mouseMove == Edge.Bottom:
                self._parent.setCursor(Qt.SizeVerCursor)
                self._cursorChanged = True
            else:
                if self._mouseMove == Edge.TopLeft or self._mouseMove == Edge.BottomRight:
                    self._parent.setCursor(Qt.SizeFDiagCursor)
                    self._cursorChanged = True
                else:
                    if self._mouseMove == Edge.TopRight or self._mouseMove == Edge.BottomLeft:
                        self._parent.setCursor(Qt.SizeBDiagCursor)
                        self._cursorChanged = True
                    else:
                        self._parent.unsetCursor()
                        self._cursorChanged = False

    def __calculateCursorPosition(self, pos, framerect):
        onLeft = pos.x() <= framerect.x() + self._borderWidth and \
                 pos.x() >= framerect.x() and \
                 pos.y() <= framerect.y() + framerect.height() - self._borderWidth and \
                 pos.y() >= framerect.y() + self._borderWidth

        onRight = pos.x() >= framerect.x() + framerect.width() - self._borderWidth and \
                  pos.x() <= framerect.x() + framerect.width() and \
                  pos.y() >= framerect.y() + self._borderWidth and \
                  pos.y() <= framerect.y() + framerect.height() - self._borderWidth 

        onBottom = pos.x() >= framerect.x() + self._borderWidth and \
                   pos.x() <= framerect.x() + framerect.width() - self._borderWidth  and \
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
