# create libsub.so
g++ -shared -o libsub.so sub.cpp

# build
-ldlオプションをmain.cppより前に付けると正しく動作しない

g++ main.cpp -ldl -rdynamic

# extern "C"
C++ではシンボル名称が自動生成されるので"add"で名前解決のためにはextern "C"が必要
