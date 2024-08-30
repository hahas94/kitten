import unittest
from components import Action, TileType, Tile, Turtle, Direction, Board
from turtle_master import is_solution_valid


# Unit tests for the Turtle class
class TestTurtle(unittest.TestCase):
    def setUp(self):
        # Set up a board for testing
        rows_tuple = (
            "........",  # Row 0
            "........",  # Row 1
            "........",  # Row 2
            "...CC...",  # Row 3
            "..C.DC..",  # Row 4
            ".C..C...",  # Row 5
            "C.IC....",  # Row 6
            "T.C....."   # Row 7
        )
        self.board = Board(rows_tuple)

    def test_can_move_forward(self):
        # RIGHT side
        turtle = Turtle(7, 1, Direction.RIGHT)
        self.assertFalse(turtle.can_move_forward(self.board))  # Next tile is castle

        turtle = Turtle(6, 1, Direction.RIGHT)
        self.assertFalse(turtle.can_move_forward(self.board))  # Next tile is ice castle

        turtle = Turtle(7, 7, Direction.RIGHT)
        self.assertFalse(turtle.can_move_forward(self.board))  # Next tile is out of bounds

        turtle = Turtle(0, 0, Direction.RIGHT)
        self.assertTrue(turtle.can_move_forward(self.board))  # Next tile is empty

        turtle = Turtle(4, 3, Direction.RIGHT)
        self.assertTrue(turtle.can_move_forward(self.board))  # Next tile is diamond

        # UPSIDE
        turtle = Turtle(7, 0, Direction.UP)
        self.assertFalse(turtle.can_move_forward(self.board))  # Next tile is castle

        turtle = Turtle(7, 2, Direction.UP)
        self.assertFalse(turtle.can_move_forward(self.board))  # Next tile is ice castle

        turtle = Turtle(0, 0, Direction.UP)
        self.assertFalse(turtle.can_move_forward(self.board))  # Next tile is out of bounds

        turtle = Turtle(1, 0, Direction.UP)
        self.assertTrue(turtle.can_move_forward(self.board))  # Next tile is empty

        # LEFT side
        turtle = Turtle(6, 1, Direction.LEFT)
        self.assertFalse(turtle.can_move_forward(self.board))  # Next tile is castle

        turtle = Turtle(6, 3, Direction.LEFT)
        self.assertFalse(turtle.can_move_forward(self.board))  # Next tile is ice castle

        turtle = Turtle(0, 0, Direction.LEFT)
        self.assertFalse(turtle.can_move_forward(self.board))  # Next tile is out of bounds

        turtle = Turtle(0, 1, Direction.LEFT)
        self.assertTrue(turtle.can_move_forward(self.board))  # Next tile is empty

        # DOWNSIDE
        turtle = Turtle(5, 0, Direction.DOWN)
        self.assertFalse(turtle.can_move_forward(self.board))  # Next tile is castle

        turtle = Turtle(5, 2, Direction.DOWN)
        self.assertFalse(turtle.can_move_forward(self.board))  # Next tile is ice castle

        turtle = Turtle(7, 0, Direction.DOWN)
        self.assertFalse(turtle.can_move_forward(self.board))  # Next tile is out of bounds

        turtle = Turtle(6, 6, Direction.DOWN)
        self.assertTrue(turtle.can_move_forward(self.board))  # Next tile is empty

    def test_move_forward(self):
        turtle = Turtle(2, 7, Direction.LEFT)
        turtle.move_forward(self.board)
        self.assertEqual((turtle.row, turtle.col), (2, 6))  # Moved to (2, 6)

        turtle.direction = Direction.UP
        turtle.move_forward(self.board)
        self.assertEqual((turtle.row, turtle.col), (1, 6))

    def test_can_fire(self):
        # FIRE AT EMPTY TILE
        turtle = Turtle(1, 1, Direction.RIGHT)
        self.assertFalse(turtle.can_fire(self.board))

        turtle = Turtle(1, 1, Direction.UP)
        self.assertFalse(turtle.can_fire(self.board))

        turtle = Turtle(1, 1, Direction.LEFT)
        self.assertFalse(turtle.can_fire(self.board))

        turtle = Turtle(1, 1, Direction.DOWN)
        self.assertFalse(turtle.can_fire(self.board))

        # FIRE AT CASTLE
        turtle = Turtle(7, 1, Direction.RIGHT)
        self.assertFalse(turtle.can_fire(self.board))

        turtle = Turtle(7, 0, Direction.UP)
        self.assertFalse(turtle.can_fire(self.board))

        turtle = Turtle(6, 1, Direction.LEFT)
        self.assertFalse(turtle.can_fire(self.board))

        turtle = Turtle(4, 1, Direction.DOWN)
        self.assertFalse(turtle.can_fire(self.board))

        # FIRE AT DIAMOND
        turtle = Turtle(4, 3, Direction.RIGHT)
        self.assertFalse(turtle.can_fire(self.board))

        turtle = Turtle(5, 4, Direction.UP)
        self.assertFalse(turtle.can_fire(self.board))

        turtle = Turtle(4, 5, Direction.LEFT)
        self.assertFalse(turtle.can_fire(self.board))

        turtle = Turtle(3, 4, Direction.DOWN)
        self.assertFalse(turtle.can_fire(self.board))

        # FIRE AT OUT OF BOUNDS
        turtle = Turtle(7, 7, Direction.RIGHT)
        self.assertFalse(turtle.can_fire(self.board))

        turtle = Turtle(0, 0, Direction.UP)
        self.assertFalse(turtle.can_fire(self.board))

        turtle = Turtle(0, 0, Direction.LEFT)
        self.assertFalse(turtle.can_fire(self.board))

        turtle = Turtle(7, 7, Direction.DOWN)
        self.assertFalse(turtle.can_fire(self.board))

        # FIRE AT ICE CASTLE
        turtle = Turtle(6, 1, Direction.RIGHT)
        self.assertTrue(turtle.can_fire(self.board))

        turtle = Turtle(7, 2, Direction.UP)
        self.assertTrue(turtle.can_fire(self.board))

        turtle = Turtle(6, 3, Direction.LEFT)
        self.assertTrue(turtle.can_fire(self.board))

        turtle = Turtle(5, 2, Direction.DOWN)
        self.assertTrue(turtle.can_fire(self.board))
 
    def test_turn_left(self):
        # Start facing RIGHT and turn left
        turtle = Turtle(0, 0, Direction.RIGHT)
        turtle.turn_left()
        self.assertEqual(turtle.direction, Direction.UP)

        # Continue turning left
        turtle.turn_left()
        self.assertEqual(turtle.direction, Direction.LEFT)

        turtle.turn_left()
        self.assertEqual(turtle.direction, Direction.DOWN)

        turtle.turn_left()
        self.assertEqual(turtle.direction, Direction.RIGHT)  # Wraps around to RIGHT

    def test_turn_right(self):
        # Start facing RIGHT and turn right
        turtle = Turtle(0, 0, Direction.RIGHT)
        turtle.turn_right()
        self.assertEqual(turtle.direction, Direction.DOWN)

        # Continue turning right
        turtle.turn_right()
        self.assertEqual(turtle.direction, Direction.LEFT)

        turtle.turn_right()
        self.assertEqual(turtle.direction, Direction.UP)

        turtle.turn_right()
        self.assertEqual(turtle.direction, Direction.RIGHT)  # Wraps around to RIGHT


class TestValidSolutions(unittest.TestCase):
    def setUp(self):
        # Set up a board for testing
        rows_tuple = (
            "........",  # Row 0
            "........",  # Row 1
            "........",  # Row 2
            "...CC...",  # Row 3
            "..C.DC..",  # Row 4
            ".C..C...",  # Row 5
            "..IC....",  # Row 6
            "T.C....."   # Row 7
        )
        self.board = Board(rows_tuple)
        self.turtle = Turtle(row=7, col=0, direction=Direction.RIGHT)

    def test_reach_goal(self):
        """Sequence of actions lead to goal."""
        actions = tuple(map(lambda s: Action(s), 'LFRFXFLFRFLFRF'))
        self.assertTrue(is_solution_valid(self.turtle, actions, self.board))

    def test_move_on_castle(self):
        """Sequence of actions move onto the castle at (4, 2)"""
        actions = tuple(map(lambda s: Action(s), 'LFFFRFFFF'))
        self.assertFalse(is_solution_valid(self.turtle, actions, self.board))

    def test_move_on_ice(self):
        """Sequence of actions move onto ice castle."""
        actions = tuple(map(lambda s: Action(s), 'LFRFFLFRFLFRF'))
        self.assertFalse(is_solution_valid(self.turtle, actions, self.board))

    def test_fire_at_castle(self):
        """Sequence of actions fire laser at castle."""
        actions = tuple(map(lambda s: Action(s), 'FXFFLFRFLFRF'))
        self.assertFalse(is_solution_valid(self.turtle, actions, self.board))

    def test_fire_at_empty_tile(self):
        """Sequence of actions fire laser at empty tile."""
        actions = tuple(map(lambda s: Action(s), 'XFFLFRFLFRF'))
        self.assertFalse(is_solution_valid(self.turtle, actions, self.board))

    def test_fire_at_diamond(self):
        """Sequence of actions fire laser at the diamond tile."""
        actions = tuple(map(lambda s: Action(s), 'LFRFXFLFRFLFRX'))
        self.assertFalse(is_solution_valid(self.turtle, actions, self.board))

    def test_fire_out_of_border_right(self):
        """Sequence of actions fire out of border facing right."""
        actions = tuple(map(lambda s: Action(s), 'LFFFFFFRFFFFFFFX'))
        self.assertFalse(is_solution_valid(self.turtle, actions, self.board))

    def test_fire_out_of_border_left(self):
        """Sequence of actions fire out of border facing left."""
        actions = tuple(map(lambda s: Action(s), 'RRRXFLFRFLFRX'))
        self.assertFalse(is_solution_valid(self.turtle, actions, self.board))

    def test_fire_out_of_border_down(self):
        """Sequence of actions fire out of border facing down."""
        actions = tuple(map(lambda s: Action(s), 'LLLXFLFRFLFRX'))
        self.assertFalse(is_solution_valid(self.turtle, actions, self.board))

    def test_fire_out_of_border_up(self):
        """Sequence of actions fire out of border facing up."""
        actions = tuple(map(lambda s: Action(s), 'LFFFFFFRFFFFFFFLFX'))
        self.assertFalse(is_solution_valid(self.turtle, actions, self.board))

    def test_move_out_of_border_right(self):
        """Sequence of actions move out of border facing right."""
        actions = tuple(map(lambda s: Action(s), 'LFFFFFFRFFFFFFFF'))
        self.assertFalse(is_solution_valid(self.turtle, actions, self.board))

    def test_move_out_of_border_left(self):
        """Sequence of actions move out of border facing left."""
        actions = tuple(map(lambda s: Action(s), 'LLFFFFFFRFFFFFFFF'))
        self.assertFalse(is_solution_valid(self.turtle, actions, self.board))

    def test_move_out_of_border_down(self):
        """Sequence of actions move out of border facing down."""
        actions = tuple(map(lambda s: Action(s), 'LFFRRFFFFRFFFFFFFF'))
        self.assertFalse(is_solution_valid(self.turtle, actions, self.board))

    def test_move_out_of_border_up(self):
        """Sequence of actions move out of border facing up."""
        actions = tuple(map(lambda s: Action(s), 'LFFFFFFRFFFFFLFFF'))
        self.assertFalse(is_solution_valid(self.turtle, actions, self.board))


# Run the unit tests
if __name__ == '__main__':
    unittest.main()
