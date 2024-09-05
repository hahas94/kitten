import unittest
from components import Action, TileType, Tile, Turtle, Direction, Board
from turtle_master import is_solution_valid
from robot_turtles import create_node, create_plan, a_star_search


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


class TestSearchAlgorithm(unittest.TestCase):
    def test_example_0(self):
        """Easy board."""
        rows_tuple = (
            "........",  # Row 0
            "........",  # Row 1
            "........",  # Row 2
            "...CC...",  # Row 3
            "....D...",  # Row 4
            "........",  # Row 5
            "..IC....",  # Row 6
            "T.C....."   # Row 7
        )
        board = Board(rows_tuple)
        solution_node = a_star_search(board)
        plan = create_plan(solution_node)
        self.assertEqual(solution_node.path_cost, 9)
        self.assertEqual(plan, 'FLFFFRFFF')

    def test_example_1(self):
        rows_tuple = (
            "........",  # Row 0
            "........",  # Row 1
            "........",  # Row 2
            "...CC...",  # Row 3
            "C...D...",  # Row 4
            "C...C...",  # Row 5
            "C.IC....",  # Row 6
            "T.C....."  # Row 7
        )
        board = Board(rows_tuple)
        solution_node = a_star_search(board)
        plan = create_plan(solution_node)
        self.assertEqual(solution_node.path_cost, 9)
        self.assertEqual(plan, 'FLFFFRFFF')

    def test_example_2(self):
        rows_tuple = (
            "........",  # Row 0
            "........",  # Row 1
            "........",  # Row 2
            "...CC...",  # Row 3
            "C...D...",  # Row 4
            ".CCCC...",  # Row 5
            "C.IC....",  # Row 6
            "T....C.."  # Row 7
        )
        board = Board(rows_tuple)
        solution_node = a_star_search(board)
        plan = create_plan(solution_node)
        self.assertEqual(solution_node.path_cost, 13)
        self.assertEqual(plan, 'FFFFLFRFLFFLF')

    def test_example_3(self):
        rows_tuple = (
            "........",  # Row 0
            "........",  # Row 1
            "........",  # Row 2
            "...C....",  # Row 3
            "C..CDC.C",  # Row 4
            ".CCCCC.C",  # Row 5
            "C.IC....",  # Row 6
            "T....C.."  # Row 7
        )
        board = Board(rows_tuple)
        solution_node = a_star_search(board)
        plan = create_plan(solution_node)
        self.assertEqual(solution_node.path_cost, 18)
        self.assertEqual(plan, 'FFFFLFRFFLFFFLFFLF')

    def test_example_4(self):
        rows_tuple = (
            "........",  # Row 0
            "........",  # Row 1
            ".....C..",  # Row 2
            "...C.C..",  # Row 3
            "C..CDC.C",  # Row 4
            "..CCCCCC",  # Row 5
            "C.IC....",  # Row 6
            "T....C.."  # Row 7
        )
        board = Board(rows_tuple)
        solution_node = a_star_search(board)
        plan = create_plan(solution_node)
        self.assertEqual(solution_node.path_cost, 14)
        self.assertEqual(plan, 'FLFFFFFRFFFRFF')

    def test_example_5(self):
        rows_tuple = (
            "........",  # Row 0
            "........",  # Row 1
            ".....C..",  # Row 2
            "...C.C..",  # Row 3
            "C..CDC.C",  # Row 4
            ".C.CCCCC",  # Row 5
            "C.IC....",  # Row 6
            "T....C.."  # Row 7
        )
        board = Board(rows_tuple)
        solution_node = a_star_search(board)
        plan = create_plan(solution_node)
        self.assertEqual(solution_node.path_cost, 15)
        self.assertEqual(plan, 'FFLXFFFFFRFFRFF')
    
    def test_example_6(self):
        rows_tuple = (
            "........",  # Row 0
            "........",  # Row 1
            "....IC..",  # Row 2
            "...CIC..",  # Row 3
            "CIICDC.C",  # Row 4
            ".C.CCCCC",  # Row 5
            "C.IC....",  # Row 6
            "T....C.."  # Row 7
        )
        board = Board(rows_tuple)
        solution_node = a_star_search(board)
        plan = create_plan(solution_node)
        self.assertEqual(solution_node.path_cost, 18)
        self.assertEqual(plan, 'FFLXFFXFFFRFXFRXFF')

    def test_example_7(self):
        rows_tuple = (
            "........",  # Row 0
            "........",  # Row 1
            "....IC..",  # Row 2
            "...CIC..",  # Row 3
            "CIICDC.C",  # Row 4
            ".C.CCCIC",  # Row 5
            "C.IC....",  # Row 6
            "T....C.."  # Row 7
        )
        board = Board(rows_tuple)
        solution_node = a_star_search(board)
        plan = create_plan(solution_node)
        self.assertEqual(solution_node.path_cost, 18)
        self.assertEqual(plan, 'FFLXFFXFFFRFXFRXFF')

    def test_example_8(self):
        rows_tuple = (
            "........",  # Row 0
            "........",  # Row 1
            "....CC..",  # Row 2
            "...CIC..",  # Row 3
            "CIICDC.C",  # Row 4
            ".C.CCCIC",  # Row 5
            "C.IC....",  # Row 6
            "T....C.."  # Row 7
        )
        board = Board(rows_tuple)
        solution_node = a_star_search(board)
        self.assertIsNone(solution_node)

    def test_example_9(self):
        rows_tuple = (
            "......CD",  # Row 0
            "......CC",  # Row 1
            "....CC..",  # Row 2
            "...CIC..",  # Row 3
            "CIIC.C.C",  # Row 4
            ".C.CCCIC",  # Row 5
            "C.IC....",  # Row 6
            "T....C.."  # Row 7
        )
        board = Board(rows_tuple)
        solution_node = a_star_search(board)
        self.assertIsNone(solution_node)

    def test_example_10(self):
        rows_tuple = (
            "......C.",  # Row 0
            "D.....CC",  # Row 1
            "....CC..",  # Row 2
            ".CCCIC..",  # Row 3
            "CIIC.C.C",  # Row 4
            ".C.CCCIC",  # Row 5
            "C.IC....",  # Row 6
            "T....C.."  # Row 7
        )
        board = Board(rows_tuple)
        solution_node = a_star_search(board)
        self.assertIsNone(solution_node)

    def test_example_11(self):
        rows_tuple = (
            "......C.",  # Row 0
            "......CC",  # Row 1
            "....CC..",  # Row 2
            ".CCCIC..",  # Row 3
            "CIIC.C.C",  # Row 4
            ".C.CCCIC",  # Row 5
            "C.IC..C.",  # Row 6
            "T....C.D"  # Row 7
        )
        board = Board(rows_tuple)
        solution_node = a_star_search(board)
        self.assertIsNone(solution_node)

    def test_example_12(self):
        rows_tuple = (
            "........",  # Row 0
            "........",  # Row 1
            ".....C..",  # Row 2
            "...C.C..",  # Row 3
            "C..C.C.C",  # Row 4
            ".C.CCCCC",  # Row 5
            "C.IC....",  # Row 6
            "TD...C.."  # Row 7
        )
        board = Board(rows_tuple)
        solution_node = a_star_search(board)
        plan = create_plan(solution_node)
        self.assertEqual(solution_node.path_cost, 1)
        self.assertEqual(plan, 'F')

    def test_example_13(self):
        rows_tuple = (
            ".......D",  # Row 0
            "........",  # Row 1
            "........",  # Row 2
            "........",  # Row 3
            "........",  # Row 4
            "........",  # Row 5
            "........",  # Row 6
            "T......."   # Row 7
        )
        board = Board(rows_tuple)
        solution_node = a_star_search(board)
        plan = create_plan(solution_node)
        self.assertEqual(solution_node.path_cost, 15)
        self.assertEqual(plan, 'FFFFFFFLFFFFFFF')

    def test_example_14(self):
        rows_tuple = (
            "......CD",  # Row 0
            ".......C",  # Row 1
            "........",  # Row 2
            "........",  # Row 3
            "........",  # Row 4
            "........",  # Row 5
            "........",  # Row 6
            "T......."   # Row 7
        )
        board = Board(rows_tuple)
        solution_node = a_star_search(board)
        self.assertIsNone(solution_node)

    def test_example_15(self):
        rows_tuple = (
            "IIIIIICD",  # Row 0
            "IIIIIIIC",  # Row 1
            "IIIIIIII",  # Row 2
            "IIIIIIII",  # Row 3
            "IIIIIIII",  # Row 4
            "IIIIIIII",  # Row 5
            "IIIIIIII",  # Row 6
            "TIIIIIII"   # Row 7
        )
        board = Board(rows_tuple)
        solution_node = a_star_search(board)
        self.assertIsNone(solution_node)

    def test_example_16(self):
        rows_tuple = (
            "IIIIIIID",  # Row 0
            "IIIIIIII",  # Row 1
            "IIIIIIII",  # Row 2
            "IIIIIIII",  # Row 3
            "IIIIIIII",  # Row 4
            "IIIIIIII",  # Row 5
            "IIIIIIII",  # Row 6
            "TIIIIIII"   # Row 7
        )
        board = Board(rows_tuple)
        solution_node = a_star_search(board)
        plan = create_plan(solution_node)
        self.assertEqual(solution_node.path_cost, 28)
        self.assertEqual(plan, 'XFXFXFXFXFXFXFLXFXFXFXFXFXFF')


# Run the unit tests
if __name__ == '__main__':
    unittest.main()
