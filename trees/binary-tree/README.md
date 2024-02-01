# Binary Tree

## The simplest binary tree with only two rules behind it:
- Larger or equal elements to the right
- Smaller elements to the left

After inserting an array of elements {100, 50, 150, 25, 55, 175, 125, 300, 1000} the tree will take the form:

![image](https://github.com/zpnst/different-trees/assets/105946529/b5a1bcc6-fd4d-458a-ba1e-1f97d0fb6e45)

As we can see, the tree outweighs to the right, which has a bad effect on the speed of searching for elements, since if you insert elements in order (1, 2, 3, 4, 5, ... , n), then the tree will turn into a simple linked list with the time complexity of searching for the element O(n)

After deleting elements 150, 50 and 1000, the problem does not go away

![image](https://github.com/zpnst/different-trees/assets/105946529/e8ab8d25-6ee6-4a02-b471-4920a76da49c)

In order to avoid mixing the tree in one direction or another, special balance factors and rotations of the subtrees were invented, which includes the AVL Binary tree
