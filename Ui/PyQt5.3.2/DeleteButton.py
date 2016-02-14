from PyQt4.QtGui import *
from PyQt4.QtCore import *
from PyQt4 import QtCore
from SaveButton import *

class DeleteButton(SaveButton):
    def __init__(self):
        super(DeleteButton, self).__init__()
        self.setStyleSheet("border:none;color: #EA4B2F ;")
        self.setText('Delete')

    def getColor(self):
        return Qt.black

    def setColor(self, Color):
        self.setStyleSheet("background-color: rgb({0}, {1}, {2});"
                           "color: #EA4B2F ;"
                           "border-radius: 6px;".format(Color.red(), Color.green(), Color.blue()))

    color=QtCore.pyqtProperty(QColor, getColor, setColor)

    def enterEvent(self, event):
        self.anim=QPropertyAnimation(self, "color")
        self.anim.setDuration(200)
        self.anim.setStartValue(QColor("#ffffff"))
        self.anim.setEndValue(QColor("#FFF0ED"))
        self.anim.start()

    def leaveEvent(self, event):
        self.anim=QPropertyAnimation(self, "color")
        self.anim.setDuration(200)
        self.anim.setStartValue(QColor("#FFF0ED"))
        self.anim.setEndValue(QColor("#FFFFFF"))
        self.anim.start()
