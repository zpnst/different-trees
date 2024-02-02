# Red Black Tree

## Properties of a red-black tree
- Each tree node is colored either red or black.
- The root node of the tree is always black.
- Every path from the root to any of the leaf nodes must have the same number of black nodes.
- No two red nodes can be adjacent, i.e., a red node cannot be the parent or the child of another red node.

## After insertion
After inserting an array of elements {100, 50, 150, 25, 55, 175, 125, 300, 1000} the tree will take the form:

![image](https://github.com/zpnst/different-trees/assets/105946529/93c7861c-9e68-44a0-9e2f-6881c057c709)

It is important to say that null lists are considered black.
In this example, the black height is 2, i.e, every path from the root to any of the leaf nodes have 2 black nodes.

## After deleting
After deleting elements 150, 50 and 1000, the tree did not lose its red-black properties.

![image](https://github.com/zpnst/different-trees/assets/105946529/44ab4680-43aa-4490-9157-6bb892640f27)

The black height remained also equal to 2.

If you are still here, I advise you to familiarize yourself with one of the most interesting data structures - [Splay tree](../splay-tree/).
