
from abc import ABC, abstractmethod
from typing import Tuple

from api.interfaces.nodes.base import  BaseNode
from api.interfaces.action import  Action
from api.interfaces.gamestate import  GameState

class ChanceNode(ABC, BaseNode):

    def __init__(self, player_id: int):
        self.player_id = player_id
