# Implementation of various trees in C++
![image](https://github.com/zpnst/different-trees/assets/105946529/69fb44f1-a6a6-47ef-b55c-91d26c05cceb)
## The following trees are implemented in this repository:
  1. [Binary Tree](trees/binary-tree)
  2. [AVL Binary Tree](trees/avl-binary-tree)
  3. [Red Black Tree](trees/red-black-tree)
  4. [Splay Tree](trees/splay-tree)

Each tree has its own characteristics, which I will not describe in detail, since countless Internet resources have done it for me.

## How to draw a tree based on the output in the terminal

You need to use the level_order_print() function.
But do not confuse it with the order_print() function, it outputs the elements of the tree in order(from smaller to larger).

![image](https://github.com/zpnst/different-trees/assets/105946529/b7fc1008-f798-4d2b-a74f-46fef8fd53cf)

Next, simply restore the tree according to the simplest rules of a binary tree(>= - to the right, < - to the left), abstracting from the type of tree.

## Our example
In our example, we insert an array of numbers {100, 50, 150, 25, 55, 175, 125, 300, 1000}, and then we delete the values 150, 50 and 1000.

What will happen to a simple search tree after all the above actions:
![image](https://github.com/zpnst/different-trees/assets/105946529/74358117-3ad8-493b-8c10-3bb6422c4b5d)

## Navigation

To learn more about the implementation of each of the trees and their brief description, follow these paths (<u>I recommend in this order</u>):

```
trees/binary-tree
trees/avl-binary-tree
trees/red-black-tree
trees/splay-tree
```

Each folder will show the trees before and after deleting the items and briefly describe their properties

## Assembling

From the root folder "different-trees" type the following commands:

```
cmake -S . -B build
make --build build
cd build/
./comparison
```

If you did everything right, then you will get this result:

![image](https://github.com/zpnst/different-trees/assets/105946529/c68e952b-28ed-47f8-b58d-e2716e4bde29)

