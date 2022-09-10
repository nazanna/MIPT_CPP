#include <iostream>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;

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

bool is_lower(int* a, int* b, void* env = nullptr) {
    return *a < *b;
}

struct Heap{
    int* start;
    void* env;
    Heap() {
        // cout << "im default constructor\n";
        start = new int[1000];
        for (int i = 0; i < 1000; ++i) start[i] = 0;
    }
    int n=0;
};

bool is_empty(Heap* heap){
    return (*heap).n==0;
}

void swap(int *a, int *b) {
    auto temp = *b;
    *b = *a;
    *a = temp;
}

void sift_up(Heap* heap, const int& u){
    int v = u;
    while (v!=0){
        if ((*heap).start[v]<(*heap).start[(v-1)/2]){
            swap(&(heap->start)[v], &(heap->start)[(v-1)/2]);
            v = (v-1)/2;
        }
        else break;
    }
}

void sift_down(Heap* heap, const int& num){
    int v = num;
    // for (int i = 0; i < heap->n; ++i) cout << heap->start[i] << ' '; cout << '\n';

    while (2*v+1<=(*heap).n-1){
        int u = 2*v+1;
        if (u+1 <= (*heap).n - 1 && (*heap).start[u] > (*heap).start[u+1]){
            u++;
        }
        if ((*heap).start[u]<(*heap).start[v]){
            swap((*heap).start+u, (*heap).start+v);
            v = u;
        }
        else break;
    }
}

int get_min(Heap* heap){
    return *(*heap).start;
}

void insert(Heap* heap, int x){
    if (is_empty(heap)){*(*heap).start = x; (*heap).n++;}
    else{
        (*heap).n++;
        (*heap).start[(*heap).n-1] = x;
        sift_up(heap, (*heap).n-1);
    }
}

void delete_min(Heap* heap){
    if (is_empty(heap)) cout<<"can't delete min";
    else{
        (*heap).start[0] = (*heap).start[(*heap).n - 1];
        (*heap).n--;
        // cout << (*heap).start[0];
        sift_down(heap, 0);
        // cout << (*heap).start[0];
    }
}

// void construct(Heap* h) {
//     h->start = new int[1000];

//     for (int i = 0; i < 1000; ++i) {
//         h->start[i] = 0;
//     }
// }

int main(){
    int a = 3;
    int* p = &a;
    // cout << "1\n";
    // Heap h;
    // cout << "2\n";
    // // construct(&h);
    // insert(&h, 4);
    // cout << get_min(&h) << endl;
    // insert(&h, 2);
    // cout << get_min(&h) << endl;
    // insert(&h, 5);
    // cout << get_min(&h) << endl;
    // insert(&h, 1);
    // cout << get_min(&h) << endl;
    // // dbg
    // delete_min(&h);
    // // dbg
    // cout << get_min(&h) << endl;
    // return 0;
}