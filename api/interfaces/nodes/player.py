
from abc import ABC, abstractmethod
from typing import Tuple

from api.interfaces.nodes.base import  BaseNode
from api.interfaces.action import  Action
from api.interfaces.gamestate import  GameState

class PlayerNode(ABC, BaseNode):

    player_id: int

    def __init__(self, player_id: int):
        self.player_id = player_id

    def children(self, gamestate: GameState):

        child_lst = []
        for action in self.available_actions(gamestate):
            child_node, child_gamestate = self.child(action, gamestate)
            child_tup = (1, child_node, child_gamestate)
            child_lst.append(child_tup)
        return child_lst

    def player_id(self) -> int:
        return self.player_id

    @abstractmethod
    def available_actions(self, gamestate: GameState) -> list[Action]:
        pass

    @abstractmethod
    def child(self, action : Action, gamestate : GameState) -> Tuple[BaseNode, GameState]:
        pass

    @abstractmethod
    def player_view_hash(self, gamestate: GameState) -> str:
        pass
