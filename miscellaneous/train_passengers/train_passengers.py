"""
train_passengers.py
----------------

Description:
* Train Passengers (https://open.kattis.com/problems/trainpassengers)
  Given information about a train, such as capacity, the number of people 
  entering and leaving it at every station, and the number of people waiting
  after its departure in a station, determine whether these numbers are realistic.

Solution:
  For each station, check that the number of people enetering and leaving, the 
  train capacity, the number of people waiting and the number of occupied places
  are all within ranges.  
  
"""

from typing import List, Tuple


def is_valid(capacity: int, n_stations: int, stations: List[Tuple[int, int, int]]) -> bool:
    """Given information about a train, determine whether it is valid input."""
    n_occupied = 0

    for i in range(n_stations - 1):
        n_left, n_entered, n_waited = stations[i]
        n_empty_places = capacity - n_occupied + n_left
        
        if ((n_left > n_occupied) or
                (n_entered > n_empty_places) or
                ((n_entered < n_empty_places) and n_waited > 0) or
                (n_occupied > capacity) or
                (n_occupied < 0)):
            return False
        n_occupied += (n_entered - n_left)

    last_n_left, last_n_entered, last_n_waited = stations[n_stations - 1]

    if ((last_n_left != n_occupied) or
            (n_occupied > capacity) or
            (n_occupied < 0) or
            (last_n_entered > 0) or
            (last_n_waited > 0)):
        return False

    return True


def main():
    """Read input, solve and print out solution."""
    first_line = input().split()
    capacity, n_stations = [int(el) for el in first_line]
    stations = [tuple(map(lambda t: int(t), input().split(' '))) for _ in range(n_stations)]
    
    valid_solution = is_valid(capacity, n_stations, stations)
    print('possible') if valid_solution else print('impossible')


if __name__ == '__main__':
    main()

# =============== END OF FILE ===============
