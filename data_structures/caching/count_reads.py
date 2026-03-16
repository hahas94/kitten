"""
This file can be used to both generate random test cases as well as
computing answers for a test case using brute-force.
"""

import random
import sys

def count_reads(cache_size, n_items, n_accesses, items):
    """Count number of items read into system using brute-force."""
    count = 0
    cache = set()
    if n_accesses == 0:
        return 0
    i = 0
    while len(cache) < cache_size and i < len(items):
        cache.add(items[i])
        i += 1

    count += len(cache)

    while i < n_accesses:
        elem = items[i]
        if elem not in cache:
            # find elem to discard
            item_pos_dict = {}
            for item in cache:
                item_pos = 1000_000
                for j in range(i+1, n_accesses):
                    if items[j] == item:
                        item_pos = j
                        break
                item_pos_dict[item] = item_pos

            sorted_cached_tuples = sorted(item_pos_dict.items(), key=lambda k: k[1])
            least_accessed_elem = sorted_cached_tuples[-1][0]

            cache.discard(least_accessed_elem)
            cache.add(elem)
            count += 1
        i += 1
    return count


def test_inputs():
    """Read from sys and run tests."""
    all_data = sys.stdin.read().splitlines()
    n_test_case = 0
    line_nr = 0

    while line_nr < len(all_data):
        case = all_data[line_nr].split(" ")
        # print(line_nr, ": " ,case)
        n_test_case += 1
        c, n, a = [int(el) for el in case]
        items = []
        for i in range(line_nr + 1, line_nr + 1 + a):
            items.append(int(all_data[i]))
        line_nr += a + 1

        count = count_reads(c, n, a, items)
        print(count, flush=True)


def generate_test_cases():
    """Generate random test cases."""
    """Generate random numbers in range."""
    c, n, a = 7, 10, 30
    for _ in range(20):
        rng = range(n)
        numbers = random.choices(rng, k=a)
        print(f"{c} {n} {a}")
        print("\n".join([str(n) for n in numbers]))


if __name__ == '__main__':
	test_inputs()
