### Project overview
---
The proyect aims to teach a **neural network** how to play **tic-tac-toe**. The modality of game considered is the one that can be played with **paper and pencil**: the game ends after a maximum of nine steps. (The other game mode, which can be played with six stones, three of each colour, is not considered.)

In order to achieve this, the set of all (not that much) possible games is first created by means of a **backtracking algorithm** that determines **optimal and suboptimal moves**. Every possible **symmetry** is detected in order to simplify the process; similarly, possitions that differ only by the **orientation** of the board are detected and **reduced** to one.

The set is then divided into a **training** sub-set and a **testing** sub-set and fed to a **neural network**. Different structures for the NN are designed and evaluated in terms of **complexity, under/overfitting, variance and bias**.

### Progress
---
Every possible board is designated by an **int 0 < board < 3^9**, which expressed in **base 3** indicates the content of each of the 9 holes: 0 means empty, 1 means first player's sign and 2 means second player's sign. For the visual representation, the signs used are '.' for empty, 'X' for the first player and 'O' for the second player. After **elimination** of invalid boards (wrong number of signs or both players have a line) and **reduction** of identical positions (up to rotation and reflexion), only 627 boards remain.

The base-3 board number encodes the position of the holes not in a linear way, but following a **magic square**:
165
840
327

The advantage of this arrangement is that every possible line (horizontal, vertical or diagonal) adds up to 12. This fact symplifies the **detection of wins**.

There are 8 **symmetry operations**, which are encoded in the following way:
- 0, identity
- 1 90º turn right
- 2 180º turn
- 3 270º turn right
- 4 vertical mirror
- 5 left diagonal mirror (equivalent to operations 4 then 3)
- 6 horizontal mirror (equivalent to operations 4 then 2)
- 5 right diagonal mirror (equivalent to operations 4 then 1)

The backtracking algorithm arranges the 627 boards, together with information of **multiplicity and optimality** of every position in that board, into **nodes in a network**.

An **output** of board numbers and optimal positions is generated, both **reduced** (only 627 boards) and **extended** (4520 boards, rotations and reflexions included).

It is the possible to **play the game**, either 0, 1 or two human players.

### Pending
---
The **neural network** is still not implemented.
