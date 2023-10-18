import sys
from PySide6.QtWidgets import QMenuBar,QMainWindow,QApplication
from PySide6.QtGui import QCloseEvent
from taskmgm.taskmanagement import TaskManager
from App import MenuSetup,LayoutSetup

class QtApp:
    def __init__(self) -> None:
        self.app = QApplication(sys.argv)
        self.window = QMainWindow()
        self.taskmgr = TaskManager(self.window)
        self.window.closeEvent = self.close
    def setupMenuBar(self):
        self.window.resize(800,600)
        self.menubar = QMenuBar()
        self.menusetup = MenuSetup.MenuSetupManager(self.menubar,self)
        self.menusetup.taskmenu_setup()
        self.window.setMenuBar(self.menubar)
    def setupLayout(self):
        self.layoutsetup = LayoutSetup.LayoutSetupManager(self)
        self.layoutsetup.mainLayout_setup()
    def setupUI(self):
        self.setupMenuBar()
        self.setupLayout()
        self.window.show()
    def close(self,event:QCloseEvent|None=None):
        print('Preparing for termination')
        if not self.taskmgr.terminate():
            return
        self.window.close()
    def run(self):
        sys.exit(self.app.exec())

app = QtApp()
app.setupUI()
app.run()