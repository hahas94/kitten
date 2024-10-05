"""
main.py
-------

Description:
* Closest Sum (https://open.kattis.com/problems/closestsum)
    Given a set of distinct integers, and a target number, find
    two integers in the set whose sum is closest to the target.


Solution:
    Aftor sorting the list, we can use two pointers to traverse it
    using a single loop, each time moving one pointer depending on 
    the relation between the target and last computed sum. This is 
    repeated until the best sum is found.
  
"""

import sys
from typing import List


def closest_sum(q: int, integers: List[int]) -> int:
    """Find and return the sum of two different elements in `integers` that are closest to `q`."""
    integers.sort()
    a, b = 0, len(integers) - 1
    closest_sum = integers[a] + integers[b]
    curr_sum = closest_sum
    distance = abs(q - closest_sum)

    while a < b-1:
        if q > curr_sum:
            a += 1
            curr_sum = integers[a] + integers[b]
            d = abs(q - curr_sum)
            if d < distance:
                distance = d
                closest_sum = curr_sum
        elif q < curr_sum:
            b -= 1
            curr_sum = integers[a] + integers[b]
            d = abs(q - curr_sum)
            if d < distance:
                distance = d
                closest_sum = curr_sum
        else:
            break

    return closest_sum
       

def main():
    """Read all input, then divide into cases and serve each query in the case."""
    all_data = sys.stdin.read().splitlines()
    n_test_case = 0
    line_nr = 0

    while line_nr < len(all_data):
        n_integers = int(all_data[line_nr])
        n_test_case += 1
        integers = [int(all_data[i]) for i in range(line_nr+1, line_nr+n_integers+1)]
        line_nr += 1 + n_integers
        n_queries = int(all_data[line_nr])
        queries = [int(all_data[i]) for i in range(line_nr+1, line_nr+n_queries+1)]
        line_nr += 1 + n_queries

        print(f"Case {n_test_case}:")

        for q in queries:
            print(f"Closest sum to {q} is {closest_sum(q, integers)}.")
        

if __name__ == "__main__":
    main()

# =============== END OF FILE ===============
