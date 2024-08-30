"""
turtle_master.py
----------------

Description:
* Turtle Master (https://open.kattis.com/problems/turtlemaster)
  Given a board and a sequence of actions performed on a turtle, does the
  sequence of actions lead the turtle to the desired goal, i.e. the diamond 
  tile?

Solution:
  Perform each action and test whether a rule is broken by it, in which case
  the sequence does not lead to the goal state. If the diamond tile is reached
  as the last action in the sequence is performed then solution is found, else 
  no solution.
"""
from enum import Enum
from dataclasses import dataclass
from typing import Tuple

from components import Direction, Action, TileType, Tile, Turtle, Board


def is_solution_valid(turtle: Turtle, actions: Tuple[Action], board: Board) -> bool:
	"""Given a sequence of actions and a board, determine whether the actions lead to the goal."""
	for action in actions:
		if action == Action.LEFT:
			turtle.turn_left()
		elif action == Action.RIGHT:
			turtle.turn_right()
		elif action == Action.FORWARD:
			if turtle.can_move_forward(board):
				turtle.move_forward(board)
			else:
				# moved out of border
				return False
		elif action == Action.FIRE:
			if turtle.can_fire(board):
				row, col = turtle.next_tile_pos(board.max_row, board.max_col)
				board.update_ice_tile(row, col)
			else:
				# fired laser at wrong tile
				return False

	goal_reached = board[turtle.row, turtle.col].type == TileType.DIMOND
	return goal_reached


def main():
	"""Read input, construct and solve the problem, output result."""
	# read
	num_rows = 8
	rows = []

	for i in range(num_rows):
		rows.append(input())
	actions = input()

	turtle = Turtle(row=7, col=0, direction=Direction.RIGHT)
	board = Board(tuple(rows))
	actions = tuple(map(lambda s: Action(s), actions))
	solved = is_solution_valid(turtle, actions, board)

	if solved:
		print("Diamond!", flush=True)
	else:
		print("Bug!", flush=True)


if __name__ == '__main__':
	main()


# =============== END OF FILE ===============
