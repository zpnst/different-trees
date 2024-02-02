# Implementation of various trees in C++
![image](https://github.com/zpnst/different-trees/assets/105946529/69fb44f1-a6a6-47ef-b55c-91d26c05cceb)
## The following trees are implemented in this repository:
  1. [Binary tree](trees/binary-tree)
  2. [AVL Binary tree](trees/avl-binary-tree)
  3. [Splay tree](trees/splay-tree)
  4. [Red Black tree](trees/red-black-tree)

Each tree has its own characteristics, which I will not describe in detail, since countless Internet resources have done it for me.

## How to draw a tree

You need to use the level_order_print() function.

![image](https://github.com/zpnst/different-trees/assets/105946529/b7fc1008-f798-4d2b-a74f-46fef8fd53cf)

Next, simply restore the tree according to the simplest rules of a binary tree(>= - to the right, < - to the left), abstracting from the type of tree.

## Our example
In our example, we insert an array of numbers {100, 50, 150, 25, 55, 175, 125, 300, 1000}, and then we delete the values 150, 50 and 1000.

What will happen to a simple search tree after all the above actions:
![image](https://github.com/zpnst/different-trees/assets/105946529/bdab68b3-0094-40ce-b101-9fa64948e5c2)

## Navigation

To learn more about the implementation of each of the trees and their brief description, follow these paths (I recommend in this order):

```
trees/binary-tree
trees/avl-binary-tree
trees/splay-tree
trees/red-black-tree
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

