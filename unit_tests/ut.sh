#!/bin/bash

RED="\033[31m"
GREEN="\033[32m"
RESET="\033[0m"

function step_zero()
{
	make re -C .. || return 1
	cp ../corewar . || return 1
	return 0
}

if [ "$1" == "--normal" ]
then
	level="1"
elif [ "$1" == "--double-diff" ]
then
	level="2"	
elif [ "$1" == "--valgrind" ]
then
	level="3"
else
	echo -e $RED"ERROR : Missing argument.$RESET"
	exit 1
fi

shift

echo -n "- Check presence corewar binary file."
ls corewar 2> /dev/null > /dev/null || { echo -e $RED [ERROR] $RESET; exit 1; } && echo -e "$GREEN" [OK] "$RESET"


if [ "$level" == "1" ]
then
	rm vm_tests/out 2> /dev/null > /dev/null
	echo -n "- Execute :" $*
	./corewar $* > vm_tests/out || { echo -e $RED [ERROR] $RESET; exit 1; } && echo -e "$GREEN" [OK] "$RESET"
fi

if [ "$level" == "2" ]
then
	rm vm_tests/out 2> /dev/null > /dev/null
	rm vm_tests/out 2> /dev/null > /dev/null
	echo -n "- Execute :" $*
	./corewar $* > vm_tests/out || { echo -e $RED [ERROR] $RESET; exit 1; } && echo -e "$GREEN" [OK] "$RESET"
	echo -n "- Second Execute :" $*
	./corewar $* > vm_tests/out2 || { echo -e $RED [ERROR] $RESET; exit 1; } && echo -e "$GREEN" [OK] "$RESET"
	echo -n "- Diff"
	diff vm_tests/out vm_tests/out2 >/dev/null 2> /dev/null || { echo -e $RED [ERROR] $RESET; exit 1; } && echo -e "$GREEN" [OK] "$RESET"
fi

if [ "$level" == "3" ]
then
	rm vm_tests/out 2> /dev/null > /dev/null
	rm vm_tests/valgrind_dump 2> /dev/null > /dev/null
	echo -n "- Valgrind Execute :" $*
	valgrind ./corewar $* > vm_tests/out 2> vm_tests/valgrind_dump || { echo -e $RED [ERROR] $RESET; exit 1; } && echo -e "$GREEN" [OK] "$RESET"
	ERRORS=`cat vm_tests/valgrind_dump | tail -n 1 | cut -d ":" -f 2 | cut -d " " -f 2`
	if [ $ERRORS != "0" ]
	then
		echo -e $RED $ERRORS [VALGRIND ERRORS] $RESET
		exit 1
	fi
fi

