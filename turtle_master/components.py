from __future__ import annotations

"""
components.py
-------------

Description:
  Implements all the classes and functions needed to solve the Turtle Master problems.
"""

from enum import Enum
from dataclasses import dataclass, field
from typing import Tuple, Union, List


class OutOfBorderError(Exception):
    """Can be used to raise error when turtle attempts to move out of border."""
    pass


class Direction(Enum):
    """The possible facing directions of the turtle agent."""
    RIGHT = 0
    UP = 1
    LEFT = 2
    DOWN = 3


class Action(Enum):
    """The possible actions of the turtle agent."""
    LEFT = 'L'
    RIGHT = 'R'
    FORWARD = 'F'
    FIRE = 'X'


class TileType(Enum):
    """The possible tile types in the game board."""
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


@dataclass
class Board:
    """Representation of the game board constructed as a matrix of Tiles."""
    rows_tuple: Tuple[str] = field(repr=False, hash=False, compare=False)
    board: List[List[Tile]] = field(init=False)
    max_row: int = field(init=False)
    max_col: int = field(init=False)

    def __post_init__(self):
        """
        Create a board instance from a sequence of rows,
        each provided as a string.
        """
        self.max_row = len(self.rows_tuple)
        self.max_col = len(self.rows_tuple[0])
        self._goal_r, self._goal_c = None, None

        self.board: List[List[Tile]] = []

        for r in range(self.max_row):
            row = []
            for c in range(self.max_col):
                tile = Tile(row=r, col=c, type=TileType(self.rows_tuple[r][c]))
                row.append(tile)
                if tile.type == TileType.DIMOND:
                    self._goal_r, self._goal_c = r, c
            self.board.append(row)

    def __getitem__(self, indices: Tuple[int, int]) -> Tile:
        """Access a single tile using row and column data."""
        row, col = indices  # Unpack the tuple
        if not (0 <= row < self.max_row) or not (0 <= col < self.max_col):
            raise IndexError("Tile indices are out of range")
        return self.board[row][col]

    def update_ice_tile(self, row: int, col: int):
        """Turn an ice castle into empty tile."""
        new_tile = Tile(row, col, TileType.EMPTY)
        self.board[row][col] = new_tile

    def get_goal_loc(self) -> (int, int):
        """Get the row and column position of the diamond."""
        return self._goal_r, self._goal_c


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
