from PySide6.QtWidgets import QMenuBar

__all__ = ['MenuSetupManager']
class MenuSetupManager:
    def __init__(self,menubar:QMenuBar,app) -> None:
        self.menubar = menubar
        self.app = app
    def taskmenu_setup(self):
        menu = self.menubar.addMenu("Tasks")
        action_new = menu.addAction("&New")
        menu.addSeparator()
        action_quit = menu.addAction("&Quit")
        action_quit.triggered.connect(self.action_quit)

    def action_quit(self):
        print('Preparing for termination...')
        self.app.close()
