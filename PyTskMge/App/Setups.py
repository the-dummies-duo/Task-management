from PySide6.QtWidgets import QHBoxLayout,QMainWindow,QWidget,QMenuBar
from PySide6.QtGui import QColor,QPalette

class Color(QWidget):
    def __init__(self, color):
        super(Color, self).__init__()
        self.setAutoFillBackground(True)
        palette = self.palette()
        palette.setColor(QPalette.ColorRole.Window, QColor(color))
        self.setPalette(palette)
class SetupManager:
    def __init__(self,app,menubar:QMenuBar):
        self.app = app
        self.menubar = menubar
    def mainLayout_setup(self):
        print('setting up')
        self.window:QMainWindow = self.app.window
        self.layout = QHBoxLayout()
        self.layout.addWidget(Color('red'))
        self.layout.addWidget(Color('green'))
        self.layout.addWidget(Color('blue'))
        self.window.setLayout(self.layout)
    def taskmenu_setup(self):
        menu = self.menubar.addMenu("Tasks")
        action_new = menu.addAction("&New")
        menu.addSeparator()
        action_quit = menu.addAction("&Quit")
        action_quit.triggered.connect(self.action_quit)

    def action_quit(self):
        print('Preparing for termination...')
        self.app.close()
