class ChooseButton(QPushButton):
    def __init__(self, *args, **kwargs):
        super(ChooseButton, self).__init__(*args, **kwargs)
        self.setMinimumSize(160,40)
        self.setCursor(Qt.PointingHandCursor)
        self.setText('Choose')
        self.font=QFont()
        self.font.setFamily('Open Sans')
        self.font.setPointSize(14)
        self.setFont(self.font)
        self.setStyleSheet("""background:white;color: #0071FF;border : 0.5px solid #0071FF;border-radius:5px;""")

    def getColor(self):
        return Qt.black

    def setColor(self, Color):
        self.setStyleSheet("background-color: rgb({0}, {1}, {2});"
                           "color: white ;"
                           "border-radius:5px".format(Color.red(), Color.green(), Color.blue()))

    def get(self):
        return Qt.black

    def set(self, Color):
        self.setStyleSheet("border: 0.5px solid rgb({0}, {1}, {2});"
                           "color: rgb({0}, {1}, {2}) ;"
                           "border-radius:5px".format(Color.red(), Color.green(), Color.blue()))

    color=QtCore.pyqtProperty(QColor, getColor, setColor)
    color0=QtCore.pyqtProperty(QColor, get, set)

    def enterEvent(self, event):
        self.anim=QPropertyAnimation(self, "color")
        self.anim.setDuration(200)
        self.anim.setStartValue(QColor("#FFFFFF"))
        self.anim.setEndValue(QColor("#007AFF"))
        self.anim.start()
        QPushButton.enterEvent(self, event)

    def leaveEvent(self, event):
        self.anim=QPropertyAnimation(self, "color")
        self.anim0=QPropertyAnimation(self, 'color0')
        self.anim0.setDuration(200)
        self.anim.setDuration(200)
        self.anim0.setStartValue(QColor('#FFFFFF'))
        self.anim0.setEndValue(QColor('#0071FF'))
        self.anim.setStartValue(QColor("#007AFF"))
        self.anim.setEndValue(QColor("#FFFFFF"))
        self.anim.start()
        self.anim0.start()
        QPushButton.leaveEvent(self, event)
