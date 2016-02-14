from PyQt5.QtWidgets import *
from PyQt5.QtCore import *


class RadioButton(QRadioButton):
    def __init__(self):
        super(RadioButton, self).__init__()
        self.setCursor(Qt.PointingHandCursor)
        self.setCheckable(1)
        self.setChecked(0)
        self.setStyleSheet(self.__qss())

    def __qss(self):
        qss = """
        QRadioButton {
        font : 12pt 'Calibri';
        }
        QRadioButton::focus {
        outline : none ;
        }
        QRadioButton::indicator {
        width: 22px;
        height:22px;
        image: url(E:/Python/PyQt/Pharmacy/Icons/Circle#D9D9D9.png) ;
        }
        QRadioButton::indicator::hover {
        width: 22px;
        height:22px;
        image: url(E:/Python/PyQt/Pharmacy/Icons/Circle#bfbfbf.png) ;
        }
        QRadioButton::indicator:checked {
        image: url(E:/Python/PyQt/Pharmacy/Icons/RadioButton#2F.png) ;
        }
        """
        return qss
