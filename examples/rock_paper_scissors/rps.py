import copy
from typing import Literal, Optional, Self

from api.interfaces import PlayerNode, TerminalNode, Action, GameState

class RpsAction(Action):

    identifier: Literal['r', 'p', 's']

    def __init__(self, action: Literal['r', 'p', 's']):
        self.identifier = action

class Rock(RpsAction):
    def __init__(self):
        super().__init__('r')

class Paper(RpsAction):
    def __init__(self):
        super().__init__('p')

class Scissors(RpsAction):
    def __init__(self):
        super().__init__('s')

class RpsGameState(GameState):

    player_one_action: Optional[RpsAction] = None
    player_two_action: Optional[RpsAction] = None

    def copy(self) -> Self:
        return copy.copy(self)

class Terminal(TerminalNode):
    @staticmethod
    def utility(self, player_id: int, gamestate: RpsGameState):

        first = gamestate.player_one_action
        second = gamestate.player_two_action

        final_utility = 0

        if isinstance(first, Rock) and isinstance(second, Paper):
            final_utility = -1
        elif isinstance(first, Rock) and isinstance(second, Scissors):
            final_utility = 1

        final_utility = -1 * final_utility if player_id == 2 else final_utility
        return final_utility

class Player(PlayerNode):
    @staticmethod
    def available_actions(self, gamestate: RpsGameState):
        return [Rock(), Paper(), Scissors()]

    @staticmethod
    def child(self, action: RpsAction, gamestate: RpsGameState):
        new_gamestate = gamestate.copy()

        if gamestate.player_one_action is None:
            new_gamestate.player_one_action = action
            return PlayerNode(2), new_gamestate

        if gamestate.player_two_action is None:
            new_gamestate.player_two_action = action
            return TerminalNode(), new_gamestate

        raise RuntimeError










