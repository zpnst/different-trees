# Implementation of various trees in C++
![image](https://github.com/zpnst/different-trees/assets/105946529/69fb44f1-a6a6-47ef-b55c-91d26c05cceb)
## The following trees are implemented in this repository:
  1. [Binary tree](trees/binary-tree)
  2. [AVL Binary tree](trees/avl-binary-tree)
  3. [Splay tree](trees/splay-tree)
  4. [Red Black tree](trees/red-black-tree)

Each tree has its own characteristics, which I will not describe in detail, since countless Internet resources have done it for me.

## Our example
In our example, we insert an array of numbers {100, 50, 150, 25, 55, 175, 125, 300, 1000}, and then we delete the values 150, 50 and 1000.

What will happen to a simple search tree after all the above actions:
<img src="https://github.com/zpnst/different-trees/assets/105946529/6183d771-7ab7-4546-81f1-de63a3915877" width="620" height="340">

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

<img src="https://github.com/zpnst/different-trees/assets/105946529/3cee1e15-f021-4b26-b477-5c0adcc6d032" width="620" height="340">
