大半夜睡不着觉，看会儿文章

https://www.blackhat.com/presentations/bh-dc-07/Sabanal_Yason/Paper/bh-dc-07-Sabanal_Yason-WP.pdf


文中提到关于C++的汇编代码的特征识别，其中一个就是可以看到大量的ecx寄存器的使用

[示例代码](https://github.com/wqreytuk/C-_reversing/blob/main/exmaple_code/code_1.cpp)
 
![image](https://user-images.githubusercontent.com/48377190/224508343-efcf2c10-dafc-4368-8650-724565a0ae4c.png)

可以看到，在两次test函数中间，出现了两个call指令，但是源代码中只有一个new对象的操作，关于这个地方的解释就是第一个call是new关键字发起的调用，
第二个call是对象的构造函数的调用

可以看到在第二个call调用中，ecx的值是dword ptr [ebp-338h]，正是第一次调用返回之后eax的值存储到的位置

这里的ecx其实就是this指针

# C++类的内存布局

包含有虚函数的类的内存布局

[示例代码](https://github.com/wqreytuk/C-_reversing/blob/main/exmaple_code/code_2.cpp)


`00f65e30`为new操作返回的地址值，就是ex2类在内存中的地址

```
0:000> dc eax
00f65e30  00ac7b34 00000000 fdfdfdfd abababab  4{..............
00f65e40  abababab feeefeee 00000000 00000000  ................
00f65e50  2ff15af0 0000e109 00f65c60 00f6bfb8  .Z./....`\......
00f65e60  feeefeee feeefeee feeefeee feeefeee  ................
00f65e70  feeefeee feeefeee feeefeee feeefeee  ................
00f65e80  feeefeee feeefeee feeefeee feeefeee  ................
00f65e90  feeefeee feeefeee feeefeee feeefeee  ................
00f65ea0  feeefeee feeefeee 3ff25ae3 1800e10b  .........Z.?....
```

`00ac7b34`是vftable的地址，`00000000`是成员变量var1

```
0:000> dc poi(eax)
00ac7b34  00ac12d0 00ac1046 00000000 74736574  ....F.......test
00ac7b44  0000000a 00ac8b24 00ac1447 00000000  ....$...G.......
00ac7b54  00ac8b7c 00ac13c5 00ac1127 00000000  |.......'.......
00ac7b64  6e6b6e55 206e776f 65637865 6f697470  Unknown exceptio
00ac7b74  0000006e 00000000 00ac8bd4 00ac10ff  n...............
00ac7b84  00ac1127 00000000 20646162 6f6c6c61  '.......bad allo
00ac7b94  69746163 00006e6f 00000000 00ac8c30  cation......0...
00ac7ba4  00ac10a0 00ac1127 00000000 20646162  ....'.......bad 
```

`00ac12d0`和`00ac1046`是ex2类的两个虚函数的地址

```
0:000> uf poi(poi(eax))
client!ex2::get_sum [C:\Users\x\source\repos\udp\client\client.cpp @ 22]:
   22 00ac1900 55              push    ebp
   22 00ac1901 8bec            mov     ebp,esp
   22 00ac1903 81eccc000000    sub     esp,0CCh
   22 00ac1909 53              push    ebx
   22 00ac190a 56              push    esi
   22 00ac190b 57              push    edi
   22 00ac190c 51              push    ecx
   22 00ac190d 8d7df4          lea     edi,[ebp-0Ch]
   22 00ac1910 b903000000      mov     ecx,3
   22 00ac1915 b8cccccccc      mov     eax,0CCCCCCCCh
   22 00ac191a f3ab            rep stos dword ptr es:[edi]
   22 00ac191c 59              pop     ecx
   22 00ac191d 894df8          mov     dword ptr [ebp-8],ecx
15732480 00ac1920 b908c0ac00      mov     ecx,offset client!_NULL_IMPORT_DESCRIPTOR <PERF> (client+0x1c008) (00acc008)
15732480 00ac1925 e882faffff      call    client!ILT+935(__CheckForDebuggerJustMyCode (00ac13ac)
   23 00ac192a 8b4508          mov     eax,dword ptr [ebp+8]
   23 00ac192d 03450c          add     eax,dword ptr [ebp+0Ch]
   24 00ac1930 5f              pop     edi
   24 00ac1931 5e              pop     esi
   24 00ac1932 5b              pop     ebx
   24 00ac1933 81c4cc000000    add     esp,0CCh
   24 00ac1939 3bec            cmp     ebp,esp
   24 00ac193b e86df9ffff      call    client!ILT+680(__RTC_CheckEsp) (00ac12ad)
   24 00ac1940 8be5            mov     esp,ebp
   24 00ac1942 5d              pop     ebp
   24 00ac1943 c20800          ret     8

client!ILT+715(?get_sumex2UAEHHHZ):
00ac12d0 e92b060000      jmp     client!ex2::get_sum (00ac1900)  Branch
```

```
0:000> uf poi(poi(eax)+4)
client!ex2::reset_value [C:\Users\x\source\repos\udp\client\client.cpp @ 26]:
   26 00ac19c0 55              push    ebp
   26 00ac19c1 8bec            mov     ebp,esp
   26 00ac19c3 81eccc000000    sub     esp,0CCh
   26 00ac19c9 53              push    ebx
   26 00ac19ca 56              push    esi
   26 00ac19cb 57              push    edi
   26 00ac19cc 51              push    ecx
   26 00ac19cd 8d7df4          lea     edi,[ebp-0Ch]
   26 00ac19d0 b903000000      mov     ecx,3
   26 00ac19d5 b8cccccccc      mov     eax,0CCCCCCCCh
   26 00ac19da f3ab            rep stos dword ptr es:[edi]
   26 00ac19dc 59              pop     ecx
   26 00ac19dd 894df8          mov     dword ptr [ebp-8],ecx
15732480 00ac19e0 b908c0ac00      mov     ecx,offset client!_NULL_IMPORT_DESCRIPTOR <PERF> (client+0x1c008) (00acc008)
15732480 00ac19e5 e8c2f9ffff      call    client!ILT+935(__CheckForDebuggerJustMyCode (00ac13ac)
   27 00ac19ea 8b45f8          mov     eax,dword ptr [ebp-8]
   27 00ac19ed c74004d2040000  mov     dword ptr [eax+4],4D2h
   28 00ac19f4 5f              pop     edi
   28 00ac19f5 5e              pop     esi
   28 00ac19f6 5b              pop     ebx
   28 00ac19f7 81c4cc000000    add     esp,0CCh
   28 00ac19fd 3bec            cmp     ebp,esp
   28 00ac19ff e8a9f8ffff      call    client!ILT+680(__RTC_CheckEsp) (00ac12ad)
   28 00ac1a04 8be5            mov     esp,ebp
   28 00ac1a06 5d              pop     ebp
   28 00ac1a07 c3              ret

client!ILT+65(?reset_valueex2UAEXXZ):
00ac1046 e975090000      jmp     client!ex2::reset_value (00ac19c0)  Branch
```

所以我们可以看到ex2类在内存中的布局如下：

```
class ex2:
+-----------------+
| vftable_address |
+-----------------+
| member_var      |
+-----------------+

vftable：
+----------------------+
| virtuable_func1_addr |
+----------------------+
| virtuable_func2_addr |
+----------------------+
```

而对于没有虚函数的类而言，其内存布局就是一堆成员变量按照声明的顺序进行排列，并根最长的据数据类型进行padding，看不到成员函数，从windbg的调试结果来看，成员函数的地址和类的地址并没有什么关系

## 继承类的内存布局

比如下面的继承关系：

```c++
class ex2 {
	int var1;
public:
	virtual int get_sum(int x, int y);
	virtual void reset_value();
};

class ex3 :public ex2 {
	int var1;
public:
	int get_value();
};
```

ex3在内存中的布局如下：


```
class ex3:
+-----------------------------+
| vftable_address_of_ex2      |
+-----------------------------+
| member_var_of_ex2           |
+-----------------------------+
| member_var_of_ex3           |
+-----------------------------+

vftable：
+-----------------------------+
| virtuable_func1_addr_of_ex2 |
+-----------------------------+
| virtuable_func2_addr_of_ex2 |
+-----------------------------+
```
可以看到，只是将ex3中的成员变量拼到下面而已

### 多继承

考虑下面这种情况

```c++
class ex4 {
	int var1;
	int var2;
public:
	virtual int ex4_func1();
	virtual void ex4_func2();
};

int ex4::ex4_func1() {
	return var1;
}

void ex4::ex4_func2() {
	printf("1234");
}

class ex5 :public ex2, ex4 {
	int var1;
public:
	void ex5_func1();
	virtual void ex5_func2();
};

void ex5::ex5_func1() {
	printf("1234");
}

void ex5::ex5_func2() {
	printf("7890");
}
```

那么ex5的内存布局应该是什么样子的呢？

[原始分析数据](https://github.com/wqreytuk/CPP_reversing/blob/main/raw_analyse/1)

内存布局：

```
class ex5:
+-------------------------------+
| vftable_address_of_ex2&5      |
+-------------------------------+
| member_var_of_ex2             |
+-------------------------------+
| vftable_address_of_ex4        | 
+-------------------------------+
| member_var_of_ex4             | 
+-------------------------------+
| member_var_of_ex4             | 
+-------------------------------+ 
| member_var_of_ex5             |
+-------------------------------+

vftable_of_2&5：
+-----------------------------+
| ex2::get_sum                |
+-----------------------------+
| ex2::reset_value            |
+-----------------------------+
| ex5::ex5_func2              |
+-----------------------------+


vftable_of_4：
+-----------------------------+
| ex2::get_sum                |
+-----------------------------+
| ex4::ex4_fun1               |
+-----------------------------+
| ex4::ex4_fun2               |
+-----------------------------+
```

可以看到ex5并没有自己专属的vftable，而是和ex2合并到一起了，我做了以下测试，发现在声明ex5的时候，`class ex5 :public ex2, ex4`，哪个基类在前面，ex5的虚函数就会合并到哪个基类的vftable中

# 识别class

## 识别构造函数和析构函数

需要注意的是，如果是默认构造函数和析构函数，在汇编代码中是看不到的，只有自己实现的构造函数和析构函数才能在汇编代码中看到显式的调用


### 全局声明的对象

对于这种情况，类的构造函数会在main函数被调用之前就被调用

[示例代码](https://github.com/wqreytuk/C-_reversing/blob/main/exmaple_code/code_3.cpp)

![image](https://user-images.githubusercontent.com/48377190/224530296-7dfa52a4-b2fa-4352-8306-d776b43b8b15.png)

可以看到调用栈中并没有出现main函数

在windbg中我看不到相关的汇编代码，用ida试一下

在.data可以看到我们的全局对象

```
.data:0041B144 ; global_object go
.data:0041B144 ?go@@3Vglobal_object@@A global_object <0>
.data:0041B144                                         ; DATA XREF: _dynamic_initializer_for__go__+23↑o
```

查看该对象的交叉引用，即可定位到构造函数

```assembly
.text:004117F1                 push    7Bh ; '{'       ; a
.text:004117F3                 mov     ecx, offset ?go@@3Vglobal_object@@A ; this
.text:004117F8                 call    j_??0global_object@@QAE@H@Z ; global_object::global_object(int)
```

可以看到构造函数的调用特点，this指针用ecx寄存器，其他的参数用栈来传递

### 局部对象

[示例代码](https://github.com/wqreytuk/C-_reversing/blob/main/exmaple_code/code_4.cpp)

![image](https://user-images.githubusercontent.com/48377190/224531476-c6dd8a84-ec9e-438d-a8b0-ccf118d0f663.png)

ecx作为this指针，分别被构造函数和析构函数所调用，而且注意ecx的值ebp-14h是一个没有初始化的栈地址


### 对动态声明的对象

构造函数的识别关键就是一个对new的调用后面紧跟一个对constructer的调用，这个上面我们已经说明过了

## 通过C++的RTTI特性识别多态类

RTTI是Run-Time Type Infomation的简称，该特性能够在**运行时**判断一个对象究竟是什么类型

[示例代码](https://github.com/wqreytuk/CPP_reversing/blob/main/exmaple_code/code_5.cpp)

启用RTII：

![image](https://user-images.githubusercontent.com/48377190/224550660-1e4357e0-5fc5-4c41-a629-a3b91ddc92dc.png)

禁用RTTI：

![image](https://user-images.githubusercontent.com/48377190/224550676-35650e31-49bb-40ee-a386-cc14ea74137e.png)

VS有一个编译选项（flag）叫做`-d1reportAllClassLayout`，启用之后会输出所有类在内存中的布局

![image](https://user-images.githubusercontent.com/48377190/224550688-b7714520-fc91-4e6d-80a6-2da2bd898842.png)

为了实现RTTI，编译器在编译出来的二进制文件中存储了一些数据结构

### RTTICompleteObjectLocator

该结构包含两个指针，一个指向描述class信息的结构体，另一个指向描述class的继承关系的结构体

![image](https://user-images.githubusercontent.com/48377190/224550702-dd171e29-3c7c-48c6-bb52-da2b3ca60386.png)

使用IDA打开启用了RTII编译生成的exe

![image](https://user-images.githubusercontent.com/48377190/224550712-b3b413d2-08e8-41ac-aa1b-fa2ae9e574d3.png)

![image](https://user-images.githubusercontent.com/48377190/224550720-78d922af-1c55-4e8b-b0c3-05391429faf3.png)

可以看到我们上面提到过的结构体

typeDescriptor：

![image](https://user-images.githubusercontent.com/48377190/224550742-412f8bd3-f599-42ac-acae-d31d2ccb8cc4.png)

```
.data:0041C138 ??_R0?AVAnimal@@@8 dd offset ??_7type_info@@6B@
.data:0041C138                                         ; DATA XREF: .rdata:0041AAD8↑o
.data:0041C138                                         ; .rdata:Animal::`RTTI Base Class Descriptor at (0,-1,0,64)'↑o
.data:0041C138                                         ; reference to RTTI's vftable
.data:0041C13C                 dd 0                    ; internal runtime reference
.data:0041C140 aAvanimal       db '.?AVAnimal@@',0     ; type descriptor name
```

HierachyDescriptor:

![image](https://user-images.githubusercontent.com/48377190/224550763-ca0da9eb-f32b-4423-be56-1969360745c4.png)

```
.rdata:0041AAE4 ; Animal::`RTTI Class Hierarchy Descriptor'
.rdata:0041AAE4 ??_R3Animal@@8  dd 0                    ; DATA XREF: .rdata:0041AADC↑o
.rdata:0041AAE4                                         ; .rdata:0041AB18↓o
.rdata:0041AAE4                                         ; signature
.rdata:0041AAE8                 dd 0                    ; attributes
.rdata:0041AAEC                 dd 1                    ; # of items in the array of base classes
.rdata:0041AAF0                 dd offset ??_R2Animal@@8 ; reference to the array of base classes
```






