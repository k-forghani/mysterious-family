g++ -c libs/*.cpp -ljsoncpp
g++ -o $1.out $1.cpp *.o -ljsoncpp
./$1.out
