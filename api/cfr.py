

from api.interfaces.nodes.base import BaseNode
from api.interfaces.nodes import PlayerNode, ChanceNode, TerminalNode
from api.interfaces.gamestate import GameState
from api.navigator import Navigator


class CFR:

    def __init__(self):
        #TODO: Initialize C++ CFR object
        pass

    def construct_tree(self, root_node: BaseNode, initial_gamestate: GameState):
        self._construct_tree_helper(root_node, initial_gamestate)

    def run_cfr(self, iterations: int, chance_sampling: bool = False):
        pass

    def run_cfr_to_accuracy(self, accuracy: float, chance_sampling: bool = False):
        pass

    def get_navigator(self) -> Navigator:
        pass

    def _construct_tree_helper(self, curr_node: BaseNode, curr_gamestate: GameState):

        if isinstance(curr_node, PlayerNode):
            pass

        elif isinstance(curr_node, ChanceNode):
            pass

        elif isinstance(curr_node, TerminalNode):
            pass

        else:
            raise NotImplementedError(f"Node of type {type(curr_node)} cannot be used")







