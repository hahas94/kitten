"""
babel_fish.py
-------------

Description:
* Babel Fish (https://open.kattis.com/problems/babelfish)
  The task is to translate a message from one language to another, by using
  a dictionary of words.

Solution:
  Map each word in the foreign language to English using the dicttionary.  
  
"""

import sys

def main():
    dictionary = {}
    message = []

    all_data = sys.stdin.read().splitlines()
    dict_done = False

    for line in all_data:
        if line == "":
            dict_done = True
            continue
        
        if dict_done:
            message.append(line)
        else:
            english, foreign = line.split(" ")
            dictionary[foreign] = english
    
    message = list(map(lambda w: (dictionary[w] if w in dictionary else "eh"), message))
    
    print("\n".join(message))


if __name__ == "__main__":
    main()

# =============== END OF FILE ===============
