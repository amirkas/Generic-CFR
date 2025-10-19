import copy
from enum import Enum
from typing import Mapping, Self
from api.interfaces import GameState

from examples.poker.deck import Card, HoleCards, Board, Deck
class Stage(Enum):

    Preflop = "Preflop"
    Flop = "Flop"
    Turn = "Turn"
    River = "River"
    Showdown = "Showdown"


class PokerGameState(GameState):

    stage: Stage
    board: Board
    pot: float
    effective_stack: float
    action_depth: int
    player_hole_cards: Mapping[int, HoleCards]
    player_investments: Mapping[int, float]
    first_player_to_act: int

    def __init__(
            self,
            stage: Stage,
            board: Board,
            pot: float,
            effective_stack: float,
            action_depth: int,
            player_hole_cards: Mapping[int, HoleCards],
            player_investments: Mapping[int, float],
            first_player_to_act,
    ):

        self.stage = stage
        self.board = board
        self.pot = pot
        self.effective_stack = effective_stack
        self.action_depth = action_depth
        self.player_hole_cards = player_hole_cards
        self.player_investments = player_investments
        self.first_player_to_act = first_player_to_act

    def copy(self) -> Self:
        return copy.copy(self)

    def action_remaining(self) -> bool:

        filter_fn = lambda investment: investment != self.effective_stack

        non_all_in_investments = list(filter(filter_fn, self.player_investments.values()))

        return len(non_all_in_investments) == 0
