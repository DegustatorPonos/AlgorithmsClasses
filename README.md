# AlgorithmsClasses
A repo for algo classes

# FOR ALL C PURISTS
**I DON'T KNOW HOW TO WRITE IN C.** I have written some basic semi-safe stuff but it's like my firs time touching it.
Some things have to be clarified here:
- I assume the input is correct.
- I assume there is no one who is trying to break into my PC.
- The constructive critique is welcome

# BUILDING
This project uses make as a build tool. You can specify what task you are building in the lab*id* dir.
The list of possible builds is as follows:
 ID | Name | Command | Task description | Test run command |
----|------|---------|------------------|------------------|
1.1 | Closest zero |```make closestzero```|[Description](tasks/lab1/ClosestZero)| ``` bash ./test.sh ./tests/lab1/ClosestZero/ ./inputs/lab1/ClosestZero ``` |
1.2 | Hands |``` make hands ```|[Description](tasks/lab1/Hands)| ``` bash ./test.sh ./tests/lab1/Hands/ ./inputs/lab1/Hands ``` |
1.3 | Symmetric diff |``` make symdiff ```|[Description](tasks/lab1/SymDiff)| |
1.4 | Duo arrays |``` make duoarrays ```|[Description](tasks/lab1/DuoLists)| |
1.5 | Long sum |``` make longsum ```|[Description](tasks/lab1/LongSum)| |

# TESTS
**How to run tests**
- Build teh correct app
- Run test.sh with 2 arguments. The first argument is a folder with test. The second is a file the program reads from.

**How to write tests**
- Make a *testname*.in file with a desired input
- Make a *testname*.res with  desired result
