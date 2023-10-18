from PySide6.QtWidgets import QHBoxLayout,QMainWindow,QWidget
from PySide6.QtGui import QColor,QPalette

class Color(QWidget):

    def __init__(self, color):
        super(Color, self).__init__()
        self.setAutoFillBackground(True)

        palette = self.palette()
        palette.setColor(QPalette.ColorRole.Window, QColor(color))
        self.setPalette(palette)
class LayoutSetupManager:
    def __init__(self,app):
        self.app = app
    def mainLayout_setup(self):
        print('setting up')
        self.window:QMainWindow = self.app.window
        self.layout = QHBoxLayout()
        self.layout.addWidget(Color('red'))
        self.layout.addWidget(Color('green'))
        self.layout.addWidget(Color('blue'))
        self.window.setLayout(self.layout)