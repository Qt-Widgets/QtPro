from PyQt5.QtWidgets import *
from PyQt5.QtCore import *


class CheckBox(QCheckBox):
    def __init__(self):
        super(CheckBox, self).__init__()
        self.setCheckable(1)
        self.setCursor(Qt.PointingHandCursor)
        self.setStyleSheet(self._qss())

    def _qss(self):
        QSS="""
        QCheckBox::indicator {
        width:  20px;
        height: 20px;
        border : 1.5px solid #D9D9D9;
        border-radius:5px;
        }
        QCheckBox::indicator:checked {
        image: url(E:/Python/PyQt/Pharmacy/Icons/Check#FFFFF.png);
        }
        QCheckBox::indicator::hover {
        border : 1.5px solid #2FA9E2;
        border-radius:5px;
        }
        QCheckBox::indicator::checked {
        background :#2FA9E2;
        }
        QCheckBox::indicator::!hover::checked {
        border : 1.5px solid #2FA9E2;
        border-radius:5px;
        }
        """
        return QSS
