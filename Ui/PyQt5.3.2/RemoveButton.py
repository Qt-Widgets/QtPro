from PyQt4.QtGui import *
from PyQt4.QtCore import *
from PyQt4 import QtCore
from InsertButton import *

class RemoveButton(InsertButton):
    def __init__(self):
        super(RemoveButton, self).__init__()
        self.setStyleSheet("background: #DB6352;border:none;color:white;")
        self.setText('Remove')

    def enterEvent(self, event):
        self.anim=QPropertyAnimation(self, "color")
        self.anim.setDuration(200)
        self.anim.setStartValue(QColor("#DB6352"))
        self.anim.setEndValue(QColor("#bc5040"))
        self.anim.start()

    def leaveEvent(self, event):
        self.anim=QPropertyAnimation(self, "color")
        self.anim.setDuration(200)
        self.anim.setStartValue(QColor("#bc5040"))
        self.anim.setEndValue(QColor("#DB6352"))
        self.anim.start()

    def mousePressEvent(self, event):
        if event.button()==Qt.LeftButton:
            self.setStyleSheet("""
            QPushButton:hover:pressed {
            padding-top: 4px ;
            background: #bc5040;
            border:none;
            color:white;
            }
            QPushButton:hover:!pressed {
            background: #bc5040;
            color:white;
            border:none;
            }
            """)
        QPushButton.mousePressEvent(self, event)
