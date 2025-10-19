from abc import ABC, abstractmethod
from typing import Optional, Self, Tuple

from api.interfaces.gamestate import  GameState
class BaseNode(ABC):

    @abstractmethod
    def children(self, gamestate: GameState) -> list[Tuple[float, Self, GameState]]:
        pass

    @abstractmethod
    def json(self) -> str:
        pass