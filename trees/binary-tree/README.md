# Binary Tree

## The simplest binary tree with only two rules behind it:
- Larger or equal elements to the right(>=).
- Smaller elements to the left(<).
  
## After insertion
After inserting an array of elements {100, 50, 150, 25, 55, 175, 125, 300, 1000} the tree will take the form:

![image](https://github.com/zpnst/different-trees/assets/105946529/ffaae670-bfc0-4ae2-8be4-11ee88eefe5c)

As we can see, the tree outweighs to the right, which has a bad effect on the speed of searching for elements, since if you insert elements in order (1, 2, 3, 4, 5, ... , n), then the tree will turn into a simple linked list with the time complexity of searching for the element O(n).

## After deleting
After deleting elements 150, 50 and 1000, the problem does not go away.

![image](https://github.com/zpnst/different-trees/assets/105946529/bdab68b3-0094-40ce-b101-9fa64948e5c2)

To return the logarithmic complexity, special rotations and balance factors were invented, which [AVL Binary Tree](../avl-binary-tree) contains.

## Links
- https://en.wikipedia.org/wiki/Binary_search_tree
- https://www.geeksforgeeks.org/binary-search-tree-data-structure
