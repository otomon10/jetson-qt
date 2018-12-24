# create libsub.so
g++ -shared -o libsub.so sub.cpp

# build
g++ main.cpp libsub.so 
