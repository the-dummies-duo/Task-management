from PySide6.QtWidgets import QHBoxLayout,QMainWindow,QWidget,QMenuBar,QGridLayout
from PySide6.QtGui import QColor,QPalette

class Color(QWidget):
    def __init__(self, color):
        super(Color, self).__init__()
        self.setAutoFillBackground(True)
        palette = self.palette()
        palette.setColor(QPalette.ColorRole.Window, QColor(color))
        self.setPalette(palette)
class SetupManager:
    def __init__(self,app,menubar:QMenuBar=None):
        self.app = app
        self.menubar = menubar
    def update(self,menubar):
        self.menubar = menubar
    def mainLayout_setup(self):
        self.window:QMainWindow = self.app.window
        self.layout = QGridLayout()
        self.layout.addWidget(Color('red'),0,0)
        self.layout.addWidget(Color('green'),0,1)
        self.layout.addWidget(Color('blue'),0,2)
        self.layout.addWidget(Color('red'),1,0)
        self.layout.addWidget(Color('green'),1,1)
        self.layout.addWidget(Color('blue'),1,2)
        self.central = QWidget()
        self.central.setLayout(self.layout)
        self.window.setCentralWidget(self.central)
    def taskmenu_setup(self):
        menu = self.menubar.addMenu("Tasks")
        action_new = menu.addAction("&New")
        menu.addSeparator()
        action_quit = menu.addAction("&Quit")
        action_quit.triggered.connect(self.quit)

    def quit(self):
        self.app.close()
