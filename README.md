# Philosophers_1337


==77072== HEAP SUMMARY:
==77072==     in use at exit: 1,024 bytes in 10 blocks
==77072==   total heap usage: 11 allocs, 1 frees, 2,048 bytes allocated
==77072== 
==77072== 544 bytes in 2 blocks are possibly lost in loss record 7 of 7
==77072==    at 0x4848A13: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==77072==    by 0x4012CE9: calloc (rtld-malloc.h:44)
==77072==    by 0x4012CE9: allocate_dtv (dl-tls.c:375)
==77072==    by 0x4012CE9: _dl_allocate_tls (dl-tls.c:634)
==77072==    by 0x48F8259: allocate_stack (allocatestack.c:423)
==77072==    by 0x48F8259: pthread_create@@GLIBC_2.34 (pthread_create.c:652)
==77072==    by 0x109373: philosopher_life (in /home/smarsi/Desktop/Philosophers_1337/philo)
==77072==    by 0x10944B: main (in /home/smarsi/Desktop/Philosophers_1337/philo)
==77072== 
==77072== LEAK SUMMARY:
==77072==    definitely lost: 0 bytes in 0 blocks
==77072==    indirectly lost: 0 bytes in 0 blocks
==77072==      possibly lost: 544 bytes in 2 blocks
==77072==    still reachable: 480 bytes in 8 blocks
==77072==         suppressed: 0 bytes in 0 blocks
==77072== Reachable blocks (those to which a pointer was found) are not shown.
==77072== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==77072== 
==77072== For lists of detected and suppressed errors, rerun with: -s
==77072== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
