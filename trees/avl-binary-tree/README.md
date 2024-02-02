# AVL Binary Tree

The rules of the binary tree remain in the AVL tree, but node heights and balance factors are added, 
which are calculated as the height difference of the right subtree and the left subtree.

## After insertion
After inserting an array of elements {100, 50, 150, 25, 55, 175, 125, 300, 1000} the tree will take the form:

![image](https://github.com/zpnst/different-trees/assets/105946529/04e6011a-4ba5-49d5-b7e9-c713629c8e1a)

As we can see, the tree has taken on a more orderly appearance, without overweights.
This is due to the right and left rotations.

## After deleting
After deleting elements 150, 50 and 1000.

![image](https://github.com/zpnst/different-trees/assets/105946529/677cf4e8-b9ed-4bd4-8dde-abc258d94274)

After deletion, the tree has not lost its balanced appearance, 
since the check for imbalance is checked both after insertion and after deletion.

However, since the AVL tree spends a lot of resources on maintaining balancing, the [Red Black Tree](../red-black-tree/) was invented.

## Links
- https://en.wikipedia.org/wiki/AVL_tree
- https://www.geeksforgeeks.org/introduction-to-avl-tree
