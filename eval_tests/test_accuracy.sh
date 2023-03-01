#!/bin/bash

LEM="../lem-in"

GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
YELLOW='\033[0;33m'
NC='\033[0m'
TIME='0.2'

TEST_ONE () {
	echo "Result: " > result/flow-one.txt
	COUNT=1
	REF=0
	LINES=0
	TOTAL=0
	while (( $COUNT < 50 ))
	do
		RES=$(./generator --flow-one | $LEM -l | grep "#Lines")
		REF=$(printf "$RES" | grep -m 1 "required" | cut -d " " -f 3)
		LINES=$(printf "$RES" | grep -m 1 "printed" | cut -d " " -f 3)
		DIFF=$(($LINES - $REF))
		TOTAL=$(($TOTAL + $DIFF))
		printf "Required: $REF printed: $LINES DIFF $DIFF\n" >> result/flow-one.txt
		COUNT=$(( $COUNT + 1 ))
	done
	AVG=$(bc <<< "scale=2;$TOTAL/50")
	printf "\nAVERAGE $AVG\n" && printf "AVERAGE $AVG\n" >> result/flow-one.txt
	printf "${GREEN}Flow-one test done${NC}\n\n"
}

TEST_TEN () {
	echo "Result: " > result/flow-ten.txt
	COUNT=1
	REF=0
	LINES=0
	TOTAL=0
	while (( $COUNT < 50 ))
	do
		RES=$(./generator --flow-ten | ../lem-in -l | grep "#Lines")
		REF=$(printf "$RES" | grep -m 1 "required" | cut -d " " -f 3)
		LINES=$(printf "$RES" | grep -m 1 "printed" | cut -d " " -f 3)
		DIFF=$(($LINES - $REF))
		TOTAL=$(($TOTAL + $DIFF))
		printf "Required: $REF printed: $LINES DIFF $DIFF\n" >> result/flow-ten.txt
		COUNT=$(( $COUNT + 1 ))
	done
	AVG=$(bc <<< "scale=2;$TOTAL/50")
	#printf "TOTAL $TOTAL\n"
	printf "AVERAGE $AVG\n" && printf "AVERAGE $AVG\n" >> result/flow-ten.txt
	printf "${GREEN}Flow-ten test done${NC}\n\n"
}

TEST_THOUSAND () {
	echo "Result: " > result/flow-thousand.txt
	COUNT=1
	REF=0
	LINES=0
	TOTAL=0
	while (( $COUNT < 50 ))
	do
		RES=$(./generator --flow-thousand | ../lem-in -l | grep "#Lines")
		REF=$(printf "$RES" | grep -m 1 "required" | cut -d " " -f 3)
		LINES=$(printf "$RES" | grep -m 1 "printed" | cut -d " " -f 3)
		DIFF=$(($LINES - $REF))
		TOTAL=$(($TOTAL + $DIFF))
		printf "Required: $REF printed: $LINES DIFF $DIFF\n" >> result/flow-thousand.txt
		COUNT=$(( $COUNT + 1 ))
	done
	AVG=$(bc <<< "scale=2;$TOTAL/50")
	#printf "TOTAL $TOTAL\n"
	printf "AVERAGE $AVG\n" && printf "AVERAGE $AVG\n" >> result/flow-thousand.txt
	printf "${GREEN}Flow-thousand test done${NC}\n\n"
}

TEST_BIG () {
	echo "Result: " > result/big.txt
	COUNT=1
	REF=0
	LINES=0
	TOTAL=0
	while (( $COUNT < 50 ))
	do
		RES=$(./generator --big | ../lem-in -l | grep "#Lines")
		REF=$(printf "$RES" | grep -m 1 "required" | cut -d " " -f 3)
		LINES=$(printf "$RES" | grep -m 1 "printed" | cut -d " " -f 3)
		DIFF=$(($LINES - $REF))
		TOTAL=$(($TOTAL + $DIFF))
		printf "Required: $REF printed: $LINES DIFF $DIFF\n" >> result/big.txt
		COUNT=$(( $COUNT + 1 ))
		echo -n "."
	done
	AVG=$(bc <<< "scale=2;$TOTAL/50")
	#printf "TOTAL $TOTAL\n"
	printf "\nAVERAGE $AVG\n" && printf "AVERAGE $AVG\n" >> result/big.txt
	printf "${GREEN}Big test done${NC}\n\n"
}

TEST_BIG_SUP () {
	echo "Result: " > result/big_sup.txt
	COUNT=1
	REF=0
	LINES=0
	TOTAL=0
	while (( $COUNT < 50 ))
	do
		RES=$(./generator --big-superposition | ../lem-in -l | grep "#Lines")
		REF=$(printf "$RES" | grep -m 1 "required" | cut -d " " -f 3)
		LINES=$(printf "$RES" | grep -m 1 "printed" | cut -d " " -f 3)
		DIFF=$(($LINES - $REF))
		TOTAL=$(($TOTAL + $DIFF))
		printf "Required: $REF printed: $LINES DIFF $DIFF\n" >> result/big_sup.txt
		COUNT=$(( $COUNT + 1 ))
		echo -n "."
	done
	AVG=$(bc <<< "scale=2;$TOTAL/50")
	#printf "TOTAL $TOTAL\n"
	printf "\nAVERAGE $AVG\n" && printf "AVERAGE $AVG\n" >> result/big_sup.txt
	printf "${GREEN}Big-superposition test done${NC}\n\n"
}


if test -f "../lem-in";
then
	printf "Testing lem-in accuracy"
else
	printf "${RED}No lem-in executable found${NC}"
	exit 1
fi
#if !test -f "./result/";
#then
#	mkdir result
#	printf "Testing lem-in accuracy"
#fi

TEST_ONE
TEST_TEN
TEST_THOUSAND
TEST_BIG
TEST_BIG_SUP
printf "${GREEN}>>> All tests completed${NC}\n"
