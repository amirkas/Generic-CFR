import copy
from typing import NamedTuple, Literal, Set, Optional, Self, get_args

Suits = Literal['s', 'h', 'c', 'd']
Ranks = Literal['A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2']
class Card(NamedTuple):

    suit: Suits
    rank: Ranks

class HoleCards:

    first_card: Card
    second_card: Card
    def __init__(self, first_card: Card, second_card: Card):
        self.first_card = first_card
        self.second_card = second_card

class Board:

    board: Set[Card]

    def __init__(self, *cards: Card):

        assert 0 <= len(cards) <= 5, "A board can have 0 cards at minimum, and 5 cards at maximum"
        self.board = set(*cards)

    def new_board(self, *new_cards: Card) -> Self:
        drawn_cards = list(self.board) + list(new_cards)
        return Board(*drawn_cards)

class Deck:

    deck: Set[Card]

    def __init__(self, *hole_cards: HoleCards, board: Optional[Board] = None):
        self.reset_deck()

        for hole_card in hole_cards:

            self.remove_card(hole_card.first_card)
            self.remove_card(hole_card.second_card)

        if board:
            for card in board.board:
                self.remove_card(card)

    def reset_deck(self):

        self.deck = set()
        for rank in get_args(Ranks):
            for suit in get_args(Suits):
                curr_card = Card(rank=rank, suit=suit)
                self.deck.add(curr_card)

    def remove_card(self, card: Card):
        self.deck.discard(card)

    def num_cards_remaining(self) -> int:
        return len(self.deck)

    def cards_remaining(self) -> Set[Card]:
        return copy.copy(self.deck)

