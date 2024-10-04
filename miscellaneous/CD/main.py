"""
main.py
-------

Description:
* CD (https://open.kattis.com/problems/cd)
    Given the collection of CD's owned by two persons, determine how
    many identical CD's they both own.

Solution:
    The intersection of their CD's determine that number.
  
"""

import sys

def main():
    while True:
        line = input().split(' ')
        N, M = [int(line[0]), int(line[1])]

        if N + M == 0:
            break

        all_cd = set()
        for _ in range(N + M):
            all_cd.add(int(input()))

        n_identical_cd = N + M - len(all_cd)

        print(n_identical_cd)

if __name__ == "__main__":
    main()

# =============== END OF FILE ===============
