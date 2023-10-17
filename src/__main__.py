import sys,os
import random
from PySide6.QtGui import QGuiApplication
from PySide6.QtQml import QQmlApplicationEngine
from PySide6.QtCore import Slot, QObject
        
os.chdir(os.path.dirname(__file__))

class Manager(QObject):
    def __init__(self, parent: QObject | None = None) -> None:
        super().__init__(parent)
    
    @Slot()
    def setText(self):
        app.setText()

class QMLApp:
    def __init__(self) -> None:
        os.chdir(os.path.dirname(__file__))
        self.app = QGuiApplication(sys.argv)
        self.engine = QQmlApplicationEngine()
        self.manager = Manager()
    def setupUI(self):
        self.engine.load('main.qml')
        self.engine.rootContext().setContextProperty('manager',self.manager)

    def setText(self):
        root = self.engine.rootObjects()[0]
        text = root.findChild(QObject,"text")
        text.setProperty("text",random.choice(["Hallo Welt", "Hei maailma", "Hola Mundo", "Привет мир"]))
    def run(self):
        sys.exit(self.app.exec())

if __name__ == "__main__":
    app = QMLApp()
    app.setupUI()
    app.run()