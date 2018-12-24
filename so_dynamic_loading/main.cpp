#include <iostream>
#include <dlfcn.h>
#include <stdio.h>

int main()
{
    // open library
    void *handle = dlopen("./libsub.so", RTLD_LAZY);
    if(handle == NULL){
        std::cout << "cannot open library" << std::endl;
        return 1;
    }

    // load the symbol
    typedef int (*add_t)(int ,int);

    // reset error
    dlerror();
    add_t add = (add_t)dlsym(handle, "add");
    const char *dlsym_error = dlerror();
    if(dlsym_error){
        std::cout << "dlsym error" << std::endl;
        dlclose(handle);
        return 1;
    }

    // use it
    std::cout << add(1,2) << std::endl;
}
