import json
from os.path import abspath

class TaskManager:
    _INSTANCE = ...
    def __init__(self,window) -> None:
        TaskManager._INSTANCE = self
        self.tasks = {}
        self.window = window
        self.tasks = json.load(open(abspath('./PyTskMge/data/tasks.json')))
    def update(self,window) -> None:
        self.window = window
    def terminate(self) -> bool:
        return True