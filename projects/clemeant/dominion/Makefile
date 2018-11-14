CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

testIsGameOver: unittest1.c dominion.o rngs.o
	gcc -o testIsGameOver -g unittest1.c dominion.o rngs.o $(CFLAGS)

testGainCard: unittest2.c dominion.o rngs.o
	gcc -o testGainCard -g unittest2.c dominion.o rngs.o $(CFLAGS)

testDiscardCard: unittest3.c dominion.o rngs.o
	gcc -o testDiscardCard -g unittest3.c dominion.o rngs.o $(CFLAGS)

testFullDeckCount: unittest4.c dominion.o rngs.o
	gcc -o testFullDeckCount -g unittest4.c dominion.o rngs.o $(CFLAGS)

testSmithyCard: cardtest1.c dominion.o rngs.o
	gcc -o testSmithyCard -g cardtest1.c dominion.o rngs.o $(CFLAGS)

testAdventurerCard: cardtest2.c dominion.o rngs.o
	gcc -o testAdventurerCard -g cardtest2.c dominion.o rngs.o $(CFLAGS)

testTreasureMapCard: cardtest3.c dominion.o rngs.o
	gcc -o testTreasureMapCard -g cardtest3.c dominion.o rngs.o $(CFLAGS)

testSalvagerCard: cardtest4.c dominion.o rngs.o
	gcc -o testSalvagerCard -g cardtest4.c dominion.o rngs.o $(CFLAGS)

randomTestAdventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomTestAdventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomTestCard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomTestCard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomTestCard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomTestCard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)

tests: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o 
	gcc -o testIsGameOver -g unittest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o testGainCard -g unittest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o testDiscardCard -g unittest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o testFullDeckCount -g unittest4.c dominion.o rngs.o $(CFLAGS)
	gcc -o testSmithyCard -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o testAdventurerCard -g cardtest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o testTreasureMapCard -g cardtest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o testSalvagerCard -g cardtest4.c dominion.o rngs.o $(CFLAGS)

randomtests: randomtestadventurer.c randomtestcard1.c randomtestcard2.c dominion.o rngs.o 
	gcc -o randomTestAdventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	gcc -o randomTestCard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	gcc -o randomTestCard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)

unittestresults: testIsGameOver testGainCard testDiscardCard testFullDeckCount testSmithyCard testAdventurerCard testTreasureMapCard testSalvagerCard 
	./testIsGameOver &> unittestresult.out
	./testGainCard >> unittestresult.out
	./testDiscardCard >> unittestresult.out
	./testFullDeckCount >> unittestresult.out
	./testSmithyCard >> unittestresult.out
	./testAdventurerCard >> unittestresult.out
	./testTreasureMapCard >> unittestresult.out
	./testSalvagerCard >> unittestresult.out
	gcov -b dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

randomtestresults: randomTestAdventurer randomTestCard1 randomTestCard2 
	./randomTestAdventurer &> randomtestadventurer.out
	./randomTestCard1 &> randomtestcard1.out
	./randomTestCard2 &> randomtestcard2.out
	gcov -b dominion.c >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard2.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
