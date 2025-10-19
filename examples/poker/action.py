from api.interfaces import Action
class BaseBet(Action):

    pot_addition: float
    def __init__(self, pot_addition: float):
        self.pot_addition = pot_addition

    def new_pot(self, old_pot: float):
        return old_pot + self.pot_addition

class Check(BaseBet):

    def __init__(self):
        super().__init__(pot_addition=0)

class Raise(BaseBet):
    pass

class Call(BaseBet):
    pass
