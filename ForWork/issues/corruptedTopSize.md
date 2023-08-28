# Memory error: malloc(): corrupted top size

Program exits with "malloc(): corrupted top size" error. According to this information, we can tell that it is related to
memory allocation, but no more specific information can be acquired.
With gdb, we still cannot figure out the exact location to cause this error.
With Valgrind, the exact location can be determined:
```
root@ucm-imx8m-plus:~# /root/bin/valgrind --leak-check=yes --track-origins=yes ./vStream
...
==15817== Conditional jump or move depends on uninitialised value(s)    // --> 15817是进程号
==15817==    at 0x4D1AEC: calloc (in /home/root/vStream)    // --> 此calloc引起问题
==15817==    by 0x401E27: vStreamAllocBuffer() (vStream.cpp:180)    // --> 在此函数里面
==15817==    by 0x40291F: vStreamCapture() (vStream.cpp:368)    // --> 调用栈回溯
==15817==    by 0x402CCF: main (main.cpp:5)
==15817==  Uninitialised value was created
==15817==    at 0x4E3CFC: brk (in /home/root/vStream)
==15817==    by 0x4E3DA3: sbrk (in /home/root/vStream)
==15817==    by 0x4A48E7: __libc_setup_tls (in /home/root/vStream)
==15817==    by 0x4A456B: (below main) (in /home/root/vStream)
...
```
虽然给出的信息仍然不是十分明确，但藉此提示去查看代码：
```
...
    buffers = (struct Buffer*)calloc(req.count, sizeof(buffers));
...
```
发现buffers是指针变量，只分配了4bytes内存，而需要分配的内存则实际是结构struct Buffer，问题在此。





==656== 32 bytes in 1 blocks are definitely lost in loss record 109 of 284

==656==    at 0x484D8B8: operator new(unsigned long) (in /usr/lib/valgrind/vgpreload_memcheck-arm64-linux.so)

==656==    by 0x49910B: v4l2Init(_CustomData*) (v4l2Stream.cpp:41)

==656==    by 0x499E07: streamWithAppsrcV4l2(int, char**) (gstPipeline.cpp:247)

==656==    by 0x49A8BB: main (main.cpp:12)