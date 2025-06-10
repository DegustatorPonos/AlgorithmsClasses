List:
	cc -c ./CommonLibs/List.c -o build/List.o
LinkedList:
	cc -c ./CommonLibs/LinkedList.c -o build/LinkedList.o
Sort:
	cc -c ./CommonLibs/sort.c -o build/Sort.o
Longop:
	cc -c ./CommonLibs/longop.c -o build/Longop.o
Bits:
	cc -c ./CommonLibs/BitUtils.c -o build/Bits.o
Files:
	cc -c ./CommonLibs/FileUtils.c -o build/Files.o
Deck:
	cc -c ./CommonLibs/deck.c -o build/Deck.o

# TESTS 

ListTest: List
	cc CommonLibs/ListTest.c build/List.o -o Result.out

#LAB 1 

closestzero:
	cc lab1/ClosestZero.c -o Result.out

hands:
	cc lab1/hands.c -o Result.out

symdiff: List Sort
	cc lab1/SymDiff.c build/Sort.o build/List.o -o Result.out

duoarrays: List 
	cc lab1/DuoArrays.c build/List.o -o Result.out

longsum: Longop List
	cc lab1/LongSum.c build/Longop.o build/List.o -o Result.out

polynom: 
	cc lab1/polynom.c -o Result.out

twoheaps:
	cc lab1/TwoHeaps.c -o Result.out

magajarah:
	cc lab1/magajarah.c -o Result.out

trees: 
	cc lab1/Trees.c -o Result.out

rope: Files Bits
	cc lab1/ropepulling.c build/Files.o build/Bits.o -o Result.out

# LAB 2

brokenarray: List Files
	cc lab2/BrokenArray.c build/List.o build/Files.o -o Result.out
eqs: Files
	cc lab2/eqs.c build/Files.o -o Result.out

# LAB 3

deck: Files List
	cc lab3/deck.c build/List.o build/Files.o -o Result.out
