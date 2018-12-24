# create libsub.so
g++ -shared -o libsub.so sub.cpp

# build
-ldlオプションをmain.cppより前に付けると正しく動作しない

g++ main.cpp -ldl -rdynamic
