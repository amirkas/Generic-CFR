from api.interfaces import ChanceNode

import itertools

from examples.poker.nodes.player import PokerPlayerNode
from examples.poker.deck import Card, HoleCards, Deck, Board
from examples.poker.gamestate import PokerGameState, Stage


def _flop_or_turn_helper(gamestate: PokerGameState, action_remaining: bool, previous_stage: Stage):

    player_hole_cards = list(gamestate.player_hole_cards.values())
    deck = Deck(*player_hole_cards, board=gamestate.board)

    current_board = gamestate.board
    cards_remaining = deck.cards_remaining()

    uniform_prob = 1 / len(cards_remaining)

    if action_remaining:
        new_stage = Stage.Turn if previous_stage is Stage.Flop else Stage.River
    else:
        new_stage = Stage.Turn if previous_stage is Stage.Flop else Stage.Showdown

    children_lst = []

    for card in cards_remaining:

        drawn_cards = player_hole_cards +[card]

        new_gamestate = gamestate.copy()
        new_gamestate.action_depth = 0
        new_gamestate.board = Board(*drawn_cards)
        new_gamestate.stage = new_stage

        new_node = PokerPlayerNode(new_gamestate.first_player_to_act) if action_remaining else PokerChanceNode()

        child_tuple = (uniform_prob, new_node, new_gamestate)
        children_lst.append(child_tuple)

    return children_lst


def _preflop_helper(gamestate: PokerGameState, action_remaining: bool):

    player_hole_cards = list(gamestate.player_hole_cards.values())
    deck = Deck(*player_hole_cards, board=gamestate.board)

    cards_remaining = deck.cards_remaining()

    board_combinations = list(itertools.combinations(cards_remaining, 3))

    uniform_prob = 1 / len(board_combinations)

    children_lst = []

    for board_combo in board_combinations:

        drawn_cards = player_hole_cards + board_combo

        new_gamestate = gamestate.copy()
        new_gamestate.action_depth = 0
        new_gamestate.board = Board(*drawn_cards)

        new_node = PokerPlayerNode(new_gamestate.first_player_to_act) if action_remaining else PokerChanceNode()

        child_tuple = (uniform_prob, new_node, new_gamestate)
        children_lst.append(child_tuple)

    return children_lst


class PokerChanceNode(ChanceNode):

    def children(self, gamestate: PokerGameState):

        is_action_remaining = gamestate.action_remaining()

        if gamestate.stage is Stage.Preflop:
            return _preflop_helper(gamestate, action_remaining=is_action_remaining)

        elif gamestate.stage is Stage.Flop or gamestate.stage is Stage.Turn:
            return _flop_or_turn_helper(gamestate, action_remaining=is_action_remaining)

        else:
            raise ValueError





