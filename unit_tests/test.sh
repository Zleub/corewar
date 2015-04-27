#!/bin/sh

RED="\033[31m"
GREEN="\033[32m"
RESET="\033[0m"

re='^[0-9]+$'

function usage()
{
	echo "Usage: 	$0 --champions <n> --limit <cycles> --test <test number> [--all-cycles] [--no-recompile]"
	echo "	--champions : number of champions to test."
	echo "	--limit : limit in cycles."
	echo "	--test : 1=normal ; 2=double diff ; 3=valgrind"
	echo "	--all-cylces : test all cycles range (increment -d by CYCLE_DELTA until --limit)"
	echo "	--no-recompile : Compile only if necessary."
	exit 1
}

champions=""
limit=""
numtest=""
allcycles=""
norecompile="0"


while [ "$#" != "0" ]
do
	if [ "$1" == "--champions" ]
	then
		shift
		champions=$1
	elif [ "$1" == "--limit" ]
	then
		shift
		limit=$1
	elif [ "$1" == "--test" ]
	then
		shift
		numtest=$1
	elif [ "$1" == "--all-cycles" ]
	then
		allcycles=1
	elif [ "$1" == "--no-recompile" ]
	then
		norecompile=1
	else
		echo $RED"Error: Bad Argument $1"$RESET
		usage
	fi
	shift
done

if ! [[ $champions =~ $re ]] ; then
	echo $RED"Error: Unable --champions value."$RESET
	usage
fi

if ! [[ $limit =~ $re ]] ; then
	echo $RED"Error: Unable --limit value."$RESET
	usage
fi

if [ "$numtest" == "1" ] ; then
	numtest="--normal"
elif [ "$numtest" == "2" ] ; then
	numtest="--double-diff"
elif [ "$numtest" == "3" ] ; then
	numtest="--valgrind"
else
	echo $RED"Error: Unable --test value."$RESET
	usage
fi

if ! [ -f corewar ] || [ "$norecompile" == "0" ] ; then
	echo Compilation...
	make re -C .. 2> /dev/null > /dev/null || { echo $RED [ERROR] $RESET; exit 1; } && echo "$GREEN" [OK] "$RESET"
	cp ../corewar .
	make fclean -C .. 2> /dev/null > /dev/null
fi

lol=`ruby combination.rb $champions`
i=0

cmd=""

for elem in $lol
do
	if [ $i == $(($champions * 2)) ]
	then
		i=0

		./ut.sh $numtest -d $limit $cmd -v 3
		echo

		cmd=""
	fi
	cmd="$cmd $elem"
	let i++
done

