from abc import ABC, abstractmethod
from typing import Tuple

from api.interfaces.nodes.base import  BaseNode
from api.interfaces.action import  Action
from api.interfaces.gamestate import  GameState

class TerminalNode(ABC, BaseNode):

    @staticmethod
    def children(gamestate: GameState):
        return []

    @abstractmethod
    def utility(self, player_id: int, gamestate: GameState) -> float:
        pass
