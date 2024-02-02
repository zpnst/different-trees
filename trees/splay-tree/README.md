# Splay Tree

## Tree structure
It allows you to find data that has been used recently faster.

One of the most interesting data structures with the time complexity of searching for O(n) elements, in the worst case.
Every operation, whether it's insertion, deletion, or search, changes the structure of the tree.
For example, if we are looking for an element X, then after getting the result, 
by means of rotations that are used in the AVL Tree, X will become the root of the tree, as in the case of insertion.

## After insertion
After inserting an array of elements {100, 50, 150, 25, 55, 175, 125, 300, 1000} the tree will take the form:

![image](https://github.com/zpnst/different-trees/assets/105946529/bffeb1b9-1b7e-4ef2-ae4e-dae256b87a00)

It's not the best shape, but it's a tree and it's not self-balancing.

## After deleting
After deleting elements 150, 50 and 1000.

![image](https://github.com/zpnst/different-trees/assets/105946529/5bf8ad29-8baa-4f43-a55e-d52ca949e1f8)

## After searching
Let's try to find element 55.

#### Our example: 
![image](https://github.com/zpnst/different-trees/assets/105946529/c21e0ccf-894d-44ba-8db2-4e3def7d7448)

#### Terminal output:
![image](https://github.com/zpnst/different-trees/assets/105946529/7fb3cd99-27d8-4194-9c65-f7309c2deddd)

#### The structure of the tree after searching for the element 55:
![image](https://github.com/zpnst/different-trees/assets/105946529/646fb115-6423-4136-89ec-fab67d3cd6e5)
As we can see, element 55 has now become the root just because we found it, amazing!

## Links
- https://en.wikipedia.org/wiki/Splay_tree
- http://cs.indstate.edu/~rcheruku/splaytree.pdf
