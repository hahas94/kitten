"""
robot_turtles.py
----------------

Description:
* Robot Turtles (https://open.kattis.com/problems/robotturtles)
  Given a board, find a sequence of actions that lead a turtle to the
  diamond node, or determine that it is impossible to reach there.
  The sequence of actions must be optimal.

Solution:
  Using A* search algorithm, we can find the optimal sequence of
  actions, or state that it is not possible. The algorithm expands
  nodes successively until reaching the goal. Each node has a state
  that can be compared to other nodes, where the state is the location
  of the agent and its facing.
  Moreover, the Manhattan distance is used as a heuristic for estimating
  the distance between any position and the goal position.
"""
import copy
import queue
from typing import Tuple, Union
from components import Direction, Action, TileType, Tile, Turtle, Board, Node, OutOfBorderError


def distance(curr_row: int, curr_col: int, goal_row: int, goal_col: int) -> int:
    """A heuristic function that returns the Manhattan distance between two points."""
    return abs(goal_row - curr_row) + abs(goal_col - curr_col)


def create_node(parent: Node, action: Action, board: Board, goal_row: int, goal_col: int) -> Union[None, Node]:
    """
    Given a node and an action, perform the action on that node
    and create and return the resulting node, or return None if
    the action is not possible to be executed.
    """
    turtle = Turtle(row=parent.tile.row, col=parent.tile.col, direction=parent.agent_dir)
    tile = parent.tile
    fired_locations = parent.fired_locations

    if action == Action.LEFT and parent.action not in [Action.RIGHT, Action.FIRE]:
        if parent.parent and (parent.parent.action, parent.action) == (Action.FORWARD, Action.LEFT):
            # 'FLL' action sequence will make agent turn to a tile it has already been at
            return None

        turtle.turn_left()

        try:
            _ = turtle.next_tile_pos(board.max_row, board.max_col)
        except OutOfBorderError:
            # facing out of border, no point in expanding
            return None

    elif action == Action.RIGHT and parent.action not in [Action.LEFT, Action.FIRE]:
        if parent.parent and (parent.parent.action, parent.action) == (Action.FORWARD, Action.RIGHT):
            # 'FRR' action sequence will make agent turn to a tile it has already been at
            return None

        turtle.turn_right()

        try:
            _ = turtle.next_tile_pos(board.max_row, board.max_col)
        except OutOfBorderError:
            # facing out of border, no point in expanding
            return None

    elif action == Action.FORWARD:
        try:
            row, col = turtle.next_tile_pos(board.max_row, board.max_col)
        except OutOfBorderError:
            return None
        if (row, col) in fired_locations or turtle.can_move_forward(board):
            tile = Tile(row=row, col=col, type=TileType.EMPTY)
        else:
            # next tile must be a castle, therefore not possible to move onto
            return None

    elif action == Action.FIRE and parent.action != Action.FIRE:
        try:
            row, col = turtle.next_tile_pos(board.max_row, board.max_col)
        except OutOfBorderError:
            return None
        if (row, col) not in fired_locations and turtle.can_fire(board):
            fired_locations = ((row, col), *fired_locations)
        else:
            # Cannot fire, either location already fired at or illegal tile to fire at
            return None
    else:
        return None

    h_cost = distance(curr_row=tile.row, curr_col=tile.col, goal_row=goal_row, goal_col=goal_col)
    node = Node(path_cost=1 + parent.path_cost, heuristic_cost=h_cost, action=action, tile=tile,
                agent_dir=turtle.direction, parent=parent, fired_locations=fired_locations)

    return node


def a_star_search(board: Board) -> Union[None, Node]:
    """
    Implementation of the A-star search algorithm. Given the game board,
    search for the best path to the goal node and return that node, or
    return None if no path exists.
    """
    goal_row, goal_col = board.get_goal_loc()
    curr_tile = board[board.max_row - 1, 0]

    g_cost = 0
    h_cost = distance(curr_row=curr_tile.row, curr_col=curr_tile.col, goal_row=goal_row, goal_col=goal_col)
    start_node = Node(path_cost=g_cost, heuristic_cost=h_cost, action=None,
                      tile=curr_tile, agent_dir=Direction.RIGHT, parent=None)

    frontier = queue.PriorityQueue()
    visited = {start_node: start_node.path_cost}
    frontier.put((start_node.path_cost + start_node.heuristic_cost, start_node))

    while frontier.qsize() > 0:
        _, node = frontier.get()

        if node.tile.row == goal_row and node.tile.col == goal_col:
            return node
        else:
            for action in Action:
                child_node = create_node(node, action, board, goal_row, goal_col)
                if child_node is not None and (child_node not in visited or
                                               child_node.path_cost < visited[child_node] or
                                               child_node.action == Action.FIRE):
                    visited[child_node] = child_node.path_cost
                    frontier.put((child_node.path_cost + child_node.heuristic_cost, child_node))

    return None


def create_plan(node: Node) -> str:
    """Given a solution node, create and return a string of all actions taken to get to that node."""
    actions = []
    action = node.action

    while action is not None:
        actions.append(action)
        node = node.parent
        action = node.action

    plan = ''.join(map(lambda a: a.value, actions[::-1]))
    return plan


def main():
    """
    Reading input, creating board, running algorithm to find solution or
    determining no solution exists, and lastly print the outcome.
    """
    num_rows = 8
    rows = []

    for i in range(num_rows):
        rows.append(input())

    board = Board(tuple(rows))
    solution_node = a_star_search(board)

    if solution_node is not None:
        plan = create_plan(solution_node)
        print(plan, flush=True)
    else:
        print("no solution", flush=True)


if __name__ == '__main__':
    main()

# =============== END OF FILE ===============
