mkdir -p build
mkdir -p build/src
mkdir -p build/tests

# Compile test case generator
g++ -Wall -g tests/test_case_generator.cpp -o ./build/tests/test_case_generator.o

# Compile the source
echo "> Compiling the source:"

g++ -Wall -g -c ./src/utils.cpp -o ./build/src/utils.o
echo "	Generated ./build/src/utils.o"

g++ -Wall -g -c ./main.cpp -o ./build/main.o
echo "	Generated ./build/main.o"

g++ -Wall -g -o daaaaaaaaaaa ./build/main.o ./build/src/utils.o
echo "	Generated daaaaaaaaaaa"