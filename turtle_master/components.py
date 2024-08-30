"""
components.py
-------------

Description:
  Implements all the classes and functions needed to solve the Turtle Master problems.
"""

from enum import Enum
from dataclasses import dataclass
from typing import Tuple


class OutOfBorderError(Exception):
    """Can be used to raise error when turtle attempts to move out of border."""
    pass


class Direction(Enum):
    RIGHT = 0
    UP = 1
    LEFT = 2
    DOWN = 3


class Action(Enum):
    LEFT = 'L'
    RIGHT = 'R'
    FORWARD = 'F'
    FIRE = 'X'


class TileType(Enum):
    EMPTY = '.'
    ICE = 'I'
    CASTLE = 'C'
    DIMOND = 'D'
    TURTLE = 'T'


@dataclass(frozen=True)
class Tile:
    """
    Representation of a single tile in a board. Has row,
    column and type fields only.
    """
    row: int
    col: int
    type: TileType


class Board:
    """Representation of the game board constructed as a matrix of Tiles."""

    def __init__(self, rows_tuple: Tuple[str]):
        """
        Create a board instance from a sequence of rows,
        each provided as a string.
        """
        self._board: List[List[Tile]] = [
            [Tile(row=r, col=c, type=TileType(rows_tuple[r][c])) for c in range(len(rows_tuple[r]))]
            for r in range(len(rows_tuple))
        ]

        self._max_row = len(self._board)
        self._max_col = len(self._board[0])

    def __getitem__(self, indices: Tuple[int, int]) -> Tile:
        """Access a single tile using row and column data."""
        row, col = indices  # Unpack the tuple
        if not (0 <= row < self._max_row) or not (0 <= col < self._max_col):
            raise IndexError("Tile indices are out of range")
        return self._board[row][col]

    @property
    def max_row(self):
        return self._max_row

    @property
    def max_col(self):
        return self._max_col

    def update_ice_tile(self, row: int, col: int):
        """Turn an ice castle into empty tile."""
        new_tile = Tile(row, col, TileType.EMPTY)
        self._board[row][col] = new_tile


@dataclass
class Turtle:
    """
    An object representing the Turtle in the game, having location, direction
    and ability to perform certain actions.
    """
    row: int
    col: int
    direction: Direction

    def can_move_forward(self, board: Board) -> bool:
        """
        Whether the turtle can move one step in the direction it is facing.
        Move allowed iff next tile is empty.
        """
        try:
            row, col = self.next_tile_pos(board.max_row, board.max_col)
        except OutOfBorderError:
            return False
        return True if board[row, col].type == TileType.EMPTY or board[row, col].type == TileType.DIMOND else False

    def move_forward(self, board: Board):
        """Move the turtle forward one step in the direction it is facing."""
        row, col = self.next_tile_pos(board.max_row, board.max_col)
        self.row, self.col = row, col

    def can_fire(self, board: Board) -> bool:
        """Whether it is allowed to fire the laser. Allowed iff next tile is ice castle."""
        try:
            row, col = self.next_tile_pos(board.max_row, board.max_col)
        except OutOfBorderError:
            return False
        return True if board[row, col].type == TileType.ICE else False

    def turn_left(self):
        self.direction = Direction((self.direction.value + 1) % len(Direction))

    def turn_right(self):
        self.direction = Direction((self.direction.value - 1) % len(Direction))

    def next_tile_pos(self, max_row: int, max_col: int) -> (int, int):
        """Return row and col if it were to move turtle one step. Raises OutOfBorderError."""
        row, col = self.row, self.col

        match self.direction:
            case Direction.RIGHT:
                col += 1 if not col + 1 >= max_col else 0

            case Direction.UP:
                row -= 1 if not row - 1 < 0 else 0

            case Direction.LEFT:
                col -= 1 if not col - 1 < 0 else 0

            case Direction.DOWN:
                row += 1 if not row + 1 >= max_row else 0

        if (row, col) == (self.row, self.col):
            # row and col were not updated, because it would be out of border
            raise OutOfBorderError
        return row, col

# =============== END OF FILE ===============