import sys
from PySide6.QtWidgets import QMenuBar,QMainWindow,QApplication
from taskmgm.taskmanagement import TaskManager
from App.MenuSetup import MenuSetupManager

class QtApp:
    def __init__(self) -> None:
        QtApp._INSTANCE = self
        self.app = QApplication(sys.argv)
        self.window = QMainWindow()
        self.taskmgr = TaskManager(self.window)
    def setupMenuBar(self):
        self.window.resize(800,600)
        menubar = QMenuBar()
        menusetup = MenuSetupManager(menubar,self)
        menubar.objectName = "MenuBar1"
        menusetup.taskmenu_setup()
        self.window.setMenuBar(menubar)
    def setupUI(self):
        self.setupMenuBar()
        self.window.show()
    def run(self):
        sys.exit(self.app.exec())

app = QtApp()
app.setupUI()
app.run()