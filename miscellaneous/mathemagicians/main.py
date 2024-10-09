"""
main.py
-------

Description:
* Mathemagicians (https://open.kattis.com/problems/mathemagicians)
    Given a binary string, a rule and a target binary string, determine whether
    it is possible to reach the target string from the original string in a finite
    number of steps if the rule is applied over and over.


Solution:
    This is a circular version of an elementary Cellular Automata, and the given 
    rule can be translated to exactly two rules among the 256 rules available.
    The idea is to divide a pattern into contiguous subfields of same bit value,
    and count the number of such fields for both the original and the target string.
    A target pattern cannot be reached if it has more subfields than the original,
    because a subfield can only be moved/removed, but new ones cannot be created,
    therefore it is impossible to go from 2 subfields to 4, etc.
    Another observation is that the number of subfields is {1, 2, 4, 6, ..} etc.
    There is one special case, namely even if the number of subfields are equal between
    original and target, but they are both alternating and opposite, then it is not
    possible to reach one another. Ex '1010' and '0101'.
  
"""

import sys


def is_alternating(configuration: str) -> bool:
    """Determine whether a configuration is alternating."""
    for i in range(1, len(configuration)-1):
        if configuration[i-1] == configuration[i+1] and configuration[i] != configuration[i+1]:
            continue
        else:
            return False
    return True


def count_fields(configuration: str) -> int:
    """Count and return the number of contiguous subfields in a configuration."""
    if len(set(configuration)) == 1:
        return 1
    
    n_fields = 1
    curr_bit_value = configuration[0]
    
    for i in range(1, len(configuration)): 
        if configuration[i] == curr_bit_value:
            continue
        else:
            n_fields += 1
            curr_bit_value = configuration[i]

    if configuration[0] == configuration[-1]:
        n_fields -= 1
    
    return n_fields


def is_possible(n_bits: int, original: str, target: str) -> bool:
    """
    Given an original configuration and a target configuration, 
    determine whether it is possible to reach target from original.
    """
    original_n_fields = count_fields(original)
    target_n_fields = count_fields(target)

    if original_n_fields == 1:
        return False
    elif n_bits % 2 == 0 and \
        target_n_fields == original_n_fields and \
        is_alternating(original) and \
        is_alternating(target) and \
        original[0] != target[0]:
        return False
    elif target_n_fields > original_n_fields:
        return False
    else:
        return True

       
def main():
    """Read all input, split them into cases of three lines, solve each case."""
    all_lines = sys.stdin.read().splitlines()
    
    for i in range(0, len(all_lines), 3):
        n_persons = int(all_lines[i])
        original = all_lines[i+1]
        target = all_lines[i+2]
        
        possible = is_possible(n_persons, original, target)
        print("yes") if possible else print("no")
        

if __name__ == "__main__":
    main()

# =============== END OF FILE ===============
