    #include <cstdlib>
    #include<stdlib.h>
    #include<iostream>
    using handle_t = FILE*;
    handle_t kNullHandle = NULL;
    void raw_write(handle_t handle, const std::string& content) {
    fprintf(handle,"%s",content.c_str());
    }
    void raw_close(handle_t handle) {
    fclose(handle);
    }
   
class IOWrapper {
private:
    handle_t _descriptor;
public:
    void Write(const std::string& content) const {
        raw_write(_descriptor, content);
    }

    IOWrapper() = delete;
    IOWrapper(handle_t descriptor): _descriptor(descriptor) {}
    IOWrapper(const IOWrapper&) = delete;
    IOWrapper& operator=(const IOWrapper&) = delete;

   
    IOWrapper(IOWrapper&& other): _descriptor(other._descriptor) {
        other._descriptor = kNullHandle;
    }

    IOWrapper& operator=(IOWrapper&& other) {
        IOWrapper cmp(std::move(other));
        std::swap(this->_descriptor, cmp._descriptor);
        return *this;
    }
    ~IOWrapper(){
        if (_descriptor!=kNullHandle)
        raw_close(_descriptor);
    }


};
    int main() {
    {
    IOWrapper wrapper(fopen("./data.txt","w"));
    wrapper.Write("Hello");
    }
    {
    IOWrapper wrapper(fopen("./data.txt","a"));
    wrapper.Write(" ");
    }
    {
    IOWrapper wrapper(fopen("./data.txt","a"));
    wrapper.Write("World!");
    }
    return 0;
    }

