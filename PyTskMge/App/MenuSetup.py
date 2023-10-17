from PySide6.QtCore import Slot
from PySide6.QtWidgets import QMenu,QWidget,QMenuBar,QApplication
from PySide6.QtGui import QAction
from PyTskMge.taskmgm.taskmanagement import TaskManager

__all__ = ['MenuSetupManager']
class MenuSetupManager(QWidget):
    def __init__(self,menubar:QMenuBar,app) -> None:
        super().__init__()
        self.menubar = menubar
        self.app = app
        self._acwrapper = ActionConnectWrapper(self.app)
    def taskmenu_setup(self) -> QMenu:
        menu = self.menubar.addMenu("Tasks")
        action_new = QAction("&New...",self.app.window)
        print(self.app.window)
        action_quit = QAction("&Quit",self.app.window,triggered=self.action_quit)
        menu.addAction(action_new)
        menu.addSeparator()
        menu.addAction(action_quit)
    @Slot()
    def action_quit(self):
        print('called')
        TaskManager._INSTANCE.terminate() if TaskManager._INSTANCE != ... else None
        self.app.window.close()

class ActionConnectWrapper(QWidget):
    def __init__(self, app, parent: QWidget | None=None) -> None:
        self.app = app
        super().__init__(parent)
    
    @Slot()
    def action_quit(self):
        print('called')
        TaskManager._INSTANCE.terminate() if TaskManager._INSTANCE != ... else None
        self.app.window.close()