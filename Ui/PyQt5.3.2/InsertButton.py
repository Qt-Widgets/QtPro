from PyQt4.QtGui import *
from PyQt4.QtCore import *
from PyQt4 import QtCore

class InsertButton(QPushButton):
    def __init__(self):
        super(InsertButton, self).__init__()
        self.setStyleSheet("background: #2FA9E2;border:none;color:white;")
        self.setText('Insert')
        self.setMinimumSize(150, 50)
        font=QFont()
        font.setFamily('Roboto Condensed')
        font.setPointSize(14)
        self.setFont(font)
        self.setCursor(Qt.PointingHandCursor)

    def getColor(self):
        return Qt.black

    def setColor(self, Color):
        self.setStyleSheet("background-color: rgb({0}, {1}, {2});"
                           "color: white ;"
                           "border:none;".format(Color.red(), Color.green(), Color.blue()))

    color=QtCore.pyqtProperty(QColor, getColor, setColor)

    def enterEvent(self, event):
        self.anim=QPropertyAnimation(self, "color")
        self.anim.setDuration(200)
        self.anim.setStartValue(QColor("#2FA9E2"))
        self.anim.setEndValue(QColor("#238abb"))
        self.anim.start()

    def leaveEvent(self, event):
        self.anim=QPropertyAnimation(self, "color")
        self.anim.setDuration(200)
        self.anim.setStartValue(QColor("#238abb"))
        self.anim.setEndValue(QColor("#2FA9E2"))
        self.anim.start()

    def mousePressEvent(self, event):
        if event.button()==Qt.LeftButton:
            self.setStyleSheet("""
            QPushButton:hover:pressed {
            padding-top: 4px ;
            background: #238abb;
            border:none;
            color:white;
            }
            QPushButton:hover:!pressed {
            background: #238abb;
            color:white;
            border:none;
            }
            """)
        QPushButton.mousePressEvent(self, event)
