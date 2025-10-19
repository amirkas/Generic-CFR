from api.cfr import CFR
from examples.rock_paper_scissors.rps import Player, RpsGameState

if __name__ == "__main__":

    cfr = CFR()

    root_node = Player(1)
    initial_gamestate = RpsGameState()

    cfr.construct_tree(root_node, initial_gamestate)



