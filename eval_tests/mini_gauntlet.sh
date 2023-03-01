#!/bin/bash
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
NC='\033[0m'
RUN_TEST () {
				echo -n "Testing on $1: "
				RES=$(../lem-in < $1)
				EXPECT=$(cat $1 | grep -m 1 'lines required' | awk 'NF>1{print $NF}')
				OUT=$(echo "$RES" | grep '^L' | wc -l)
				DIFF=$(echo "$OUT - $EXPECT" | bc)
				if [ $DIFF -lt 0 ]
				then
					echo -e "${GREEN}[OK] IMPRESSIVE, LESS THAN REQUIRED!! ${NC}"
				elif [ $DIFF -eq 0 ]
				then
					echo -e "${GREEN}[OK] Full points!!${NC}"
				elif [ $DIFF -le 2 ]
				then
					echo -e "${YELLOW}Almost perfect, 4 points!${NC}"
				else
					echo -e "${RED}:( Printed $DIFF lines above${NC}"
				fi
}

echo "Welcome to the ACCURACY GAUNTLET"
RUN_TEST cases/augment_0.map
RUN_TEST cases/augment_1.map
RUN_TEST cases/augment_2.map
RUN_TEST cases/augment_3.map
RUN_TEST cases/augment_4.map
RUN_TEST cases/augment_5.map
RUN_TEST cases/augment_6.map
RUN_TEST cases/augment_7.map
RUN_TEST cases/augment_8.map
RUN_TEST cases/augment_9.map

for f in $1
do
	RUN_TEST $f
done