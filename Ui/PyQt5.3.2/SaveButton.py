from PyQt4.QtGui import *
from PyQt4.QtCore import *
from PyQt4 import QtCore

class SaveButton(QPushButton):
    def __init__(self, *args, **kwargs):
        super(SaveButton, self).__init__(*args, **kwargs)
        self.setStyleSheet("background-color: white ;border:none;color: #2a98cb ;")
        self.setMinimumSize(70,40)
        self.setText('Save')
        self.setCursor(Qt.PointingHandCursor)
        font=QFont()
        font.setFamily('Roboto Condensed')
        font.setPointSize(14)
        self.setFont(font)

    def getColor(self):
        return Qt.black

    def setColor(self, Color):
        self.setStyleSheet("background-color: rgb({0}, {1}, {2});"
                           "color: #2a98cb ;"
                           "border-radius: 6px;".format(Color.red(), Color.green(), Color.blue()))

    color=QtCore.pyqtProperty(QColor, getColor, setColor)

    def enterEvent(self, event):
        self.anim=QPropertyAnimation(self, "color")
        self.anim.setDuration(200)
        self.anim.setStartValue(QColor("#ffffff"))
        self.anim.setEndValue(QColor("#EDF7FF"))
        self.anim.start()

    def leaveEvent(self, event):
        self.anim=QPropertyAnimation(self, "color")
        self.anim.setDuration(200)
        self.anim.setStartValue(QColor("#eaf6fb"))
        self.anim.setEndValue(QColor("#ffffff"))
        self.anim.start()
