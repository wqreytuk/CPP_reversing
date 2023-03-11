大半夜睡不着觉，看会儿文章

https://www.blackhat.com/presentations/bh-dc-07/Sabanal_Yason/Paper/bh-dc-07-Sabanal_Yason-WP.pdf


文中提到关于C++的汇编代码的特征识别，其中一个就是可以看到大量的ecx寄存器的使用

[示例代码](https://github.com/wqreytuk/C-_reversing/blob/main/exmaple_code/code_1.cpp)
 
![image](https://user-images.githubusercontent.com/48377190/224508343-efcf2c10-dafc-4368-8650-724565a0ae4c.png)

可以看到，在两次test函数中间，出现了两个call指令，但是源代码中只有一个new对象的操作，关于这个地方的解释就是第一个call是new关键字发起的调用，
第二个call是对象的构造函数的调用

可以看到在第二个call调用中，ecx的值是dword ptr [ebp-338h]，正是第一次调用返回之后eax的值存储到的位置

这里的ecx其实就是this指针

另一个特征就是如果你没有看到ecx被初始化就被用上了，那么大概率这是一个类的成员函数

[示例代码](https://github.com/wqreytuk/C-_reversing/blob/main/exmaple_code/code_2.cpp)

![image](https://user-images.githubusercontent.com/48377190/224509863-48dac479-a304-4bde-b39f-0c5a6bd8ccb7.png)

可以看到ecx并没有被进行任何初始化，直接就用上了
