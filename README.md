# Let's beat STL

The problem asks to implement my map class based on an AVL tree and compare its performance with the C++ std::map of STL as the number of elements n changes. In addition to comparing the single operations, consider also a random sequence of m operations with m chosen always larger (e.g. m = 10, 100, 1000, …).
  
### Performance Test
  
As we know that std::map in standard template library (STL) is based on red–black tree (**RB trees**) and both RB Trees and AVL Trees support insertion, deletion and look-up in guaranteed O(log N) time. However, AVL Trees are more rigidly balanced, it means that AVL Trees need more rotations in insertion and deletion, but provide faster look-up. So you are strongly recommended to use AVL Trees for **look-up** intensive tasks, otherwise RB Trees are more convenient. 

| Task | Amount | Container | Time Elapsed (ms) |
| --- | :--- | :---: | :---: |
| `insertion` | 1.000.000 | AVL Tree<br>std::map | 249<br>**248** |
| `insertion` | 10.000.000 | AVL Tree<br>std::map | 2410<br>**2138** |
| `deletion` | 1.000.000 | AVL Tree<br>std::map | **55**<br>58 |
| `deletion` | 10.000.000 | AVL Tree<br>std::map | **232**<br>259 |
| `look-up` | 1.000.000 | AVL Tree<br>std::map | **55**<br>58 |
| `look-up` | 10.000.000 | AVL Tree<br>std::map | **232**<br>259 |
