List:
	cc -c ./CommonLibs/List.c -o build/List.o
Sort:
	cc -c ./CommonLibs/sort.c -o build/Sort.o

closestzero:
	cc lab1/ClosestZero.c -o Result.out

hands:
	cc lab1/hands.c -o Result.out

symdiff: List Sort
	cc lab1/SymDiff.c build/Sort.o build/List.o -o Result.out

duoarrays: List 
	cc lab1/DuoArrays.c build/List.o -o Result.out
