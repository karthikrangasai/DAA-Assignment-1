if [ ! -d build ]; then
	mkdir build
	cd build/
	if [ ! -d src ]; then
		mkdir src
	fi
	cd ../
fi

echo "> Compiling the source:"

g++ -Wall -g -c ./src/utils.cpp -o ./build/src/utils.o
echo "	Generated ./build/src/utils.o"