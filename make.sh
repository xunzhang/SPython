#! /bin/sh
g++ -c ./object/*.C -I./include
g++ -o main ./python/driver.C *.o -I./include
