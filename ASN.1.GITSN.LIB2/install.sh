#!/bin/bash

if [ -z $1 ]; then
	echo "$0 <install_path>"
	exit 1
fi

DEST=$1
echo "destination = $DEST"

ROOT=.
LIB_PATH=$ROOT/lib
LIBS=`ls $LIB_PATH/*-lib -d`

echo $LIBS
if [ -z "$LIBS" ]; then
	echo "build first as you wish"
	exit 1
fi

if [ -d $DEST ]; then
	echo "$DEST is exist"
else
	echo "create $DEST"
	mkdir $DEST
fi

if ! [ -d $DEST/include ]; then
	echo "create $DEST/include"
	mkdir $DEST/include
fi

if ! [ -d $DEST/lib ]; then
	echo "create $DEST/lib"
	mkdir $DEST/lib
fi

for ccc in $LIBS; do
	echo "copy $ccc to $DEST/lib"
	cp -r $ccc $DEST/lib
done

HEADERS='BER IO MEM OS PER TOOL TYPE XER'
for ccc in $HEADERS; do
	if ! [ -d $DEST/include/$ccc ]; then
		echo "create $DEST/include/$ccc"
		mkdir -p $DEST/include/$ccc
	fi
	cp $ROOT/SupportLib/$ccc/*.h $DEST/include/$ccc
done

