List:
	cc -c ./CommonLibs/List.c -o build/List.o
Sort:
	cc -c ./CommonLibs/sort.c -o build/Sort.o
Longop:
	cc -c ./CommonLibs/longop.c -o build/Longop.o

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
	cc lab1/magajarah.c  -o Result.out
