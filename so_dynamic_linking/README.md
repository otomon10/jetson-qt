# create libsub.so
g++ -shared -o libsub.so sub.cpp

# build
g++ main.cpp libsub.so 

or

g++ main.cpp -lsub -L./
