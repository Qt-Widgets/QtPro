from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *

class SearchBox(QLineEdit):
    def __init__(self):
        super(SearchBox, self).__init__()
        self.setMinimumHeight(30)
        self.setPlaceholderText(' Search box....')
        # ---Search icon---
        self.search_button=QToolButton(self)
        self.search_button.setFocusPolicy(Qt.NoFocus)
        self.search_button.setIcon(QIcon('E:/Python/PyQt/Pharmacy/Icons/Search#7e7e7e.png'))
        self.search_button.setStyleSheet("border: 0px; padding: 0px;")

        self.clear_button=QToolButton(self)
        self.clear_button.setShortcut("F8")
        self.clear_button.setFocusPolicy(Qt.NoFocus)
        self.clear_button.setCursor(Qt.PointingHandCursor)
        self.clear_button.setStyleSheet("QToolButton {border: 0px; padding: 0px;}"
                                        " QToolButton::hover {image:url(E:/Python/PyQt/Pharmacy/Icons/ClearToolButton#8C8C8C.png);}")
        self.clear_button.setIcon(QIcon('E:/Python/PyQt/Pharmacy/Icons/ClearToolButton#8C8C8C.png'))
        self.clear_button.hide()
        self.clear_button.clicked.connect(self.clear)
        self.textChanged.connect(self.__update_clear_button)

        # self.setMinimumSize(max(self.minimumSizeHint().width(),self._size()[1]+self._size()[0]*2+2),
        #                     max(self.minimumSizeHint().height(),self._size()[2]+self._size()[0]*2+2))
        self.setStyleSheet("border:none;border-bottom : 1px solid  #e0e0e0;padding-left: {0}px;padding-right: {1}px;"
                           .format(self.__size()[0] + self.__size()[1] + 5, self.__size()[3]))
        font=QFont()
        font.setFamily('Roboto ')
        font.setPointSize(12)
        self.setFont(font)

    def __size(self):
        return self.style().pixelMetric(QStyle.PM_DefaultFrameWidth)\
            ,self.search_button.sizeHint().width()\
            ,self.search_button.sizeHint().height() \
            ,self.clear_button.sizeHint().width() \
            ,self.clear_button.sizeHint().height()

    def resizeEvent(self, event):
        self.search_button.move(6, (self.rect().bottom() - self.__size()[2] + 1)/2)
        self.clear_button.move(self.rect().right() - self.__size()[0] - self.__size()[3], (self.rect().bottom() - self.__size()[4] +1)/2)
        super(SearchBox, self).resizeEvent(event)

    def __update_clear_button(self, text):
        if text=="":
            self.clear_button.setVisible(0)
        else:
            self.clear_button.setVisible(1)

    def get_border(self):
        return Qt.black

    def set_border(self, Color):
        self.setStyleSheet(" border:none;"
                           "border-bottom : 1.5px solid rgb({0}, {1}, {2});"
                           "padding-left: {3}px;padding-right: {4}px;"
                           .format(Color.red(), Color.green(), Color.blue(),
                                   self.__size()[0] + self.__size()[1] + 5, self.__size()[3]))

    border=pyqtProperty(QColor, get_border, set_border)
            
    def focusInEvent(self, event):
        self.anim=QPropertyAnimation(self, "border")
        self.anim.setStartValue(QColor("#e0e0e0"))
        self.anim.setEndValue(QColor("#82CDF8"))
        self.anim.setDuration(230)
        self.anim.start()
        self.search_button.setIcon(QIcon('E:/Python/PyQt/Pharmacy/Icons/Search#2FA9E2.png'))
        QLineEdit.focusInEvent(self, event)

    def focusOutEvent(self, event):
        self.setStyleSheet("border:none;border-bottom : 1px solid  #e0e0e0;padding-left: {0}px;padding-right: {1}px;"
                           .format(self.__size()[0] + self.__size()[1] + 5, self.__size()[3]))
        self.search_button.setIcon(QIcon('E:/Python/PyQt/Pharmacy/Icons/Search#7e7e7e.png'))
        QLineEdit.focusOutEvent(self, event)

    def keyPressEvent(self, event):
        if event.type()==QEvent.KeyPress:
            if event.key()==Qt.Key_Up:
                self.setPlaceholderText(' Search....')
        if event.type()==QEvent.KeyPress:
            if event.key()==Qt.Key_Down:
                self.setPlaceholderText(' Find....')
        QLineEdit.keyPressEvent(self, event)
