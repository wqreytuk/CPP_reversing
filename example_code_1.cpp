#include <Windows.h>
#include <comdef.h>
#include <stdio.h>
#include <vector>
using namespace std;

#define CHUNK_SIZE 0x190
#define ALLOC_COUNT 10

class SomeObject {
public:
    void function1() {};
    virtual void virtual_function1() {};
};
void test() {
    printf("\n");
}
int main(int args, char** argv) {
    test();
    SomeObject* objsect = new SomeObject();
    test();
    int i;
    BSTR bstr;
    HANDLE hChunk;
    void* allocations[ALLOC_COUNT];
    BSTR bStrings[5];
    SomeObject* object = new SomeObject();
    HANDLE defaultHeap = GetProcessHeap();
    HANDLE pre_chunk_addr = 0;
    for (i = 0; i < ALLOC_COUNT; i++) {
        // 比实际要分配的内存多了10个字节，要分配的是190h
        // 但是实际分配出来的chunk之间的偏移量是1a0h
        // 在调试器里面跑的时候可能更大，实际跑的时候是1a0h
        hChunk = HeapAlloc(defaultHeap, 0, CHUNK_SIZE);
        memset(hChunk, 'A', CHUNK_SIZE);
        allocations[i] = hChunk;
        printf("[%d] Heap chunk in backend : 0x%016x\n", i, hChunk);
        printf("%s\n", hChunk);
        printf("%p\n", hChunk);
        printf("%x\n", (LONG)hChunk - (LONG)pre_chunk_addr);
        pre_chunk_addr = hChunk;
    }
    test();
    // 释放掉中间一块内存
    HeapFree(defaultHeap, HEAP_NO_SERIALIZE, allocations[3]);

    test();
    for (i = 0; i < 5; i++) {
        // 再次要求分配124字节的内存7ch
        bstr = SysAllocString(L"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
        bStrings[i] = bstr;
        printf("[%d] BSTR string : 0x%08x\n", i, bstr);
    }
    test();
    // 再释放中间一块内存
    HeapFree(defaultHeap, HEAP_NO_SERIALIZE, allocations[4]);
    test();
    // 给一个类申请一块内存，指针抓换成int值了
    long long objRef = (long long)object;
    printf("SomeObject address for Chunk 3 : 0x%016x\n", objRef);
    // 这是什么用法，哦哦哦，就是搞了一堆数组，值是40和object地址
    // 搞了10个，上面说错了，这个是使用array来初始化vector，具体意思就是
    // 给一个array的起始地址和终止地址，去初始化vector
    // 哦哦，分配40字节，值是objref，但是地址在哪？怎么看
    // 不管了，直接还从heap[1]开始看
    vector<long long> array1(40, objRef);
    vector<long long> array2(40, objRef);
    vector<long long> array3(40, objRef);
    vector<long long> array4(40, objRef);
    vector<long long> array5(40, objRef);
    vector<long long> array6(40, objRef);
    vector<long long> array7(40, objRef);
    vector<long long> array8(40, objRef);
    vector<long long> array9(40, objRef);
    vector<long long> array10(40, objRef);

    test();
    system("PAUSE");
    return 0;
}
