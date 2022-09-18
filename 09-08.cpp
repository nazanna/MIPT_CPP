#include <iostream>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::string;

//быстрая сортировка
/*generic_qsort(void* begin, size_t element_byte_size, bool (*cmp)(*void const*, void const*, void const*), void* end, void const*){
}*/

//очередь с приоритетом
/*struct PriorityQueue{
    cmp(a, b, env)
    env;
    memory;
    size_t element_byte_size;
};

void push(PriorityQueue* q, void const*){}
void poll(PriorityQueue* q){/*убирает макс}
void const* peek(PriorityQueue* q){/*возвращает макс}
bool is_empty(PriorityQueue* q){}*/

bool is_lower(void* a, void* b, void* env = nullptr) {
    auto ia = *(int*)(a);
    auto ib = *(int*)(b);
    return ia < ib;
}

void swap(void *a, void *b, size_t element_byte_size) {
    void* temp = malloc(element_byte_size);
    memcpy(temp, a, element_byte_size);
    memcpy(a, b, element_byte_size);
    memcpy(b, temp, element_byte_size);
    free(temp);
}


struct Heap{
    void* memory;
    void* env;
    Heap(bool (*cmp)(void*, void*, void*), void* memory, void* env, size_t element_byte_size): 
    cmp(cmp), memory(memory), env(env), element_byte_size(element_byte_size) {}
    bool (*cmp)(void*, void*, void*);
    int n=0;
    size_t element_byte_size;

    void sift_up(const int& u) {
        int v = u;
        while (v!=0){
            if (cmp(memory + v * element_byte_size, memory + (v-1)/2 * element_byte_size, env)){
                swap((memory + v * element_byte_size), (memory + (v-1)/2 * element_byte_size), element_byte_size);
                v = (v-1)/2;
            }
            else break;
        }
    }

    bool is_empty() {
        return n==0;
    }

    void sift_down(const int& num){
        int v = num;

        while (2*v+1<=n-1){
            int u = 2*v+1;
            if (u+1 <= n - 1 && cmp(memory+(u+1)*element_byte_size, memory+u*element_byte_size, env)){
                u++;
            }
            if (cmp(memory+u*element_byte_size, memory+v*element_byte_size, env)) {
                swap(memory+u*element_byte_size, memory+v*element_byte_size, element_byte_size);
                v = u;
            }
            else break;
        }
    }

    void* get_min() {
        return memory;
    }

    void insert(void* x){
        memcpy(memory+n*element_byte_size, x, element_byte_size);
        n++;
        sift_up(n-1);
        
    }

    void delete_min(){
        if (is_empty()) cout<<"can't delete min";
        else{
            memcpy(memory, memory+element_byte_size*(n - 1), element_byte_size);
            n--;
            sift_down(0);
        }
    }

};



bool TestHeap1() {
    int* start = new int[1000];
    int* a = new int(4);
    Heap h(&is_lower, start, nullptr, 32);
    h.insert(a);
    if (*(int*)h.get_min() != 4) {
        delete[] start;
        return false;
    }
    *a = 5;
    h.insert(a);
    if (*(int*)h.get_min() != 4) {
        delete[] start;
        return false;
    }
    *a = 3;
    h.insert(a);
    if (*(int*)h.get_min() != 3) {
        delete[] start;
        return false;
    }    
    *a = 2;
    h.insert(a);
    if (*(int*)h.get_min() != 2) {
        delete[] start;
        return false;
    }    
    h.delete_min();
    if (*(int*)h.get_min() != 3) {
        delete[] start;
        return false;
    }
    delete[] start;
    return true;
}

bool is_lower_double(void* a, void* b, void* env) {
    auto ia = *(double*)(a);
    auto ib = *(double*)(b);
    return ia < ib;
}

bool TestHeap2() {
    double* start = new double[1000];
    double* a = new double(1.2);
    Heap h(&is_lower_double, start, nullptr, 8 * (sizeof *a));
    h.insert(a);
    if (*(double*)h.get_min() != 1.2) {
        delete[] start;
        return false;
    }
    *a = 5.09;
    h.insert(a);
    if (*(double*)h.get_min() != 1.2) {
        delete[] start;
        return false;
    }
    *a = 0.76;
    h.insert(a);
    if (*(double*)h.get_min() != 0.76) {
        delete[] start;
        return false;
    }    
    *a = 2.0;
    h.insert(a);
    if (*(double*)h.get_min() != 0.76) {
        delete[] start;
        return false;
    }    
    h.delete_min();
    if (*(double*)h.get_min() != 1.2) {
        delete[] start;
        return false;
    }
    delete[] start;
    return true;
}


int main(){
    if (TestHeap2()) cout << "ok\n";
    else cout<< "error\n";
}