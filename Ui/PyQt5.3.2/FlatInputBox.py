from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *

class FlatInputBox(InputBox):
    def __init__(self):
        super(FlatInputBox, self).__init__()
        self.setAlignment(Qt.AlignLeft)
        self.setEchoMode(QLineEdit.Password)
        self.setPlaceholderText(' Flat input box')
        self.setStyleSheet("""
        background-color: white;
        border:none;
        border-bottom : 1px solid  #e0e0e0;
        """)

    def get_border(self):
        return Qt.black

    def set_border(self, Color):
        self.setStyleSheet(" border:none;"
                           "border-bottom : 1.5px solid rgb({0}, {1}, {2});"
                           .format(Color.red(), Color.green(), Color.blue()))

    border=pyqtProperty(QColor, get_border, set_border)

    def focusInEvent(self, event):
        self.anim=QPropertyAnimation(self, "border")
        self.anim.setStartValue(QColor("#e0e0e0"))
        self.anim.setEndValue(QColor("#82CDF8"))
        self.anim.setDuration(230)
        self.anim.start()
        QLineEdit.focusInEvent(self, event)

    def focusOutEvent(self, event):
        self.setStyleSheet("border:none;border-bottom : 1px solid  #e0e0e0;")
        QLineEdit.focusOutEvent(self, event)
