# Binary Tree

## The simplest binary tree with only two rules behind it:
- Larger or equal elements to the right
- Smaller elements to the left

After inserting an array of elements {100, 50, 150, 25, 55, 175, 125, 300, 1000} the tree will take the form:

<img src="https://github.com/zpnst/different-trees/assets/105946529/94fd00ad-2a72-47dc-b8c5-db2a4a737118" width="620" height="340">

As we can see, the tree outweighs to the right, which has a bad effect on the speed of searching for elements, since if you insert elements in order (1, 2, 3, 4, 5, ... , n), then the tree will turn into a simple linked list with the time complexity of searching for the element O(n)

After deleting elements 150, 50 and 1000, the problem does not go away

<img src="https://github.com/zpnst/different-trees/assets/105946529/6183d771-7ab7-4546-81f1-de63a3915877" width="620" height="340">

To return the logarithmic complexity, special rotations and balance factors were invented, which [AVL Binary tree](../avl-binary-tree) contains
