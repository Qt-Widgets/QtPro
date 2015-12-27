from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *


class ComboBox(QComboBox):
    def __init__(self):
        super(ComboBox, self).__init__()
        font=QFont()
        font.setPointSize(11)
        font.setFamily('Calibri')
        font.setKerning(1)
        view = QListView()
        view.setCursor(Qt.PointingHandCursor)
        view.setFont(font)
        view.setStyleSheet(self.__list_qss())
        self.setView(view)
        self.setFont(font)
        self.setCursor(Qt.PointingHandCursor)
        self.setStyleSheet(self.__combo_box_qss())

    def __list_qss(self):
        QSS = """
        QListView::item {
        padding: 5px;
        }
        QListView::item:selected:active {
        background: #e1f2fa;
        color     : black;
        }  """
        return QSS

    def __combo_box_qss(self):
        qss = """
        QComboBox {
        border : none;
        font   : 12pt 'Calibri';
        }
        QComboBox::down-arrow {
        image: url(E:/Python/PyQt/Pharmacy/Icons/DownArrow#2FA9E2.png);
        }
        QComboBox:!editable:focus{
        background: #d1d1d1 ;
        }
        QComboBox:!editable ,QComboBox::drop-down:editable {
        background: #e9e9e9 ;
        border-radius:4px;
        }
        QComboBox::drop-down::on{
        margin :0px;
        border-left-color: #2FA9E2 ;
        image : url(E:/Python/PyQt/Pharmacy/Icons/DownArrow#2a98cb.png);
        }
        QComboBox::drop-down {
        width : 22px;
        margin: 2.5 px;
        border-left-width: 1.6 px;
        border-left-color: #8e8e8e;
        border-left-style: solid ;
        }
        QComboBox::drop-down::hover {
        border-left-color: #2FA9E2 ;
        margin: 0px;
	    image : url(E:/Python/PyQt/Pharmacy/Icons/DownArrow#2a98cb.png);
        }
        QComboBox QAbstractItemView {
        outline: none;
        }
        """
        return qss
