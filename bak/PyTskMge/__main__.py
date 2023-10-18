import sys
from PySide6.QtWidgets import QMenuBar,QMainWindow,QApplication
from PySide6.QtGui import QCloseEvent
from taskmgm.taskmanagement import TaskManager
from App.Setups import SetupManager

class QtApp:
    def __init__(self) -> None:
        self.app = QApplication(sys.argv)
        self.window = QMainWindow()
        self.taskmgr = TaskManager(self.window)
        self.window.closeEvent = self.close
        self.sumgr = SetupManager(self)
        self.terminating = False
    def setupMenuBar(self):
        self.window.resize(800,600)
        self.menubar = QMenuBar()
        self.sumgr.update(self.menubar)
        self.sumgr.taskmenu_setup()
        self.window.setMenuBar(self.menubar)
    def setupLayout(self):
        self.sumgr.mainLayout_setup()
    def setupUI(self):
        self.setupMenuBar()
        self.setupLayout()
        self.window.show()
    def close(self,event:QCloseEvent|None=None):
        if self.terminating:
            return
        print('Preparing for termination')
        self.terminating = True
        if not self.taskmgr.terminate():
            self.terminating = False
            return
        self.window.close()
    def run(self):
        sys.exit(self.app.exec())

app = QtApp()
app.setupUI()
app.run()