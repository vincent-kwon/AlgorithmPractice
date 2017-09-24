/*
 * =====================================================================================
 *
 *       Filename:  LinuxStudy.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 09월 22일 13시 24분 15초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

uname -a : kernel info
intel_idle: regardless of bios, work in c-state mode follows this
kernel compile info: cat /boot/config-`uname -r` | more
dmidecode -t system | processor | memory: returns BIOS info
cat /proc/cpuinfo: shows similar info
lscpu: shows well
dmidecode -t memory | grep -i size: shows memory slot
lspci | grep -i ether: ethernet info
ethtool eth0: performance, current performance, network status
ethtool -g eth0 | -G eth0 rx 255: network info. -G for setting
ethtool -k: other options
ethrool -i: kernel drivers
vm.overcommit_memory: virtual memory limit on/off
[free] buffers/cache: buffers & cached removed, free excluding buffer/cache is larger than free (what is it?)
[free] swap: size of swap <== use some area of hard disk to be used for memory (what about speed?)
[free] buffers cache: store meta data of file system 
[free] page cache: store page data of file system
[free] how memory change:
 - [    available       ][ used ]
 - [ available ][ cach ][used   ]
 - [av][cach][   used           ]

  when no memory available, then use swap area. 

[proc/meminfo] swapCached: return from swap 
               swap area is not returned after memory used but stay for later use

[proc/meminfo] active(anon): excluding page cache, mostly process used memory
               inactive(anon): relatively old enough to return to swap
               active(file): kernel use for improve io (page cache
               inactive(file): similar
               dirty: write is done so it should be back to disk write
               
               after malloc, even though rest 10 min, it does not make inactive state
               kernel only makes inactive when lack of memory.
               lack of memory determined by  vm.min_free_kbytes kernel config parameter

               sysctl -w vm.min_free_kbytes=6553500
               vm.min_free_kbytes = 6553500
 
               after setting like this, if memory is less than above, kswapd is running to
               reclaim memory (move from active to inactive)

               Slab: kernel use it internally . Kernel is also process . it has area it uses
                     dentry cache, inode cache are in this area
               SReclaimable: reusable slab area. all cache purpose included. If memory sparse, can be 
                             used
               SUnreclaimed: Slab area can't be used in other purpose

               slaptop -o: shows slab info

               slab use caches for inode, dentry, network socket memory, device driver memory
               kernel's buddy use 4kb page unit memory. but it can cause fragmentation.
 
               slab received 4kb by buddy and divide into 4 slab area for dentry, inode, x cache

               slabtop -o | grep dentry

               slab memory can be leaked also. check slab memory usage 

               in case study, dentry cache 26G (abnormal)

               can drop cache: echo 2 > /proc/sys/vm/drop_cached : echo 2, echo 3 has different cache flushing (2 dentry, 3 include
               page cache)

               lsof | grep DIR | wc -l

               some bug in nss-softokn of curl library can increase dentry cache much more increased

               lesson: small bug can ruin system

[swap] swap area is reserved in case process requires more memory
       
       /proc/<pid>/smaps or /status: shows memory info

               Swap shows swap memory

       smem -t : per process PSS, RSS <== shows swap memory
       
[swap] buddy system: 1, 2, 4, 8, ..... 
       cat /proc/buddyinfo : show buddy memory

       kernel moves inactive memory to swap area

       dd if=/dev/zero of=./file_1 bs=1024 count=1000000 // 1GB file creation

       when memory dd requested, cache is first released.

       use vmstat to see memory usage in time change

       vm.swappiness: how often swap memory move. default 60 // if this value bigger, no cache throw but move inactive to swap
      
       sysctl -w vm.swappiness=100

       free's cached is page cache

       vm.vfs_cache_pressure: when cache realloc, pageCache or directory/inode cache more 
                              default is 100 
                              if 0, no dentry and cache return (can cause system memory lack)

[memory leak]  ps aux | grep -i malloc | grep -iv grep

       pmap pid

       shows memory usage by malloc (per) 

       (gdb) dump memory /root/memory_dump 0x7fe148f88000 .....
              
       strings ./memory_dump

       vm.vfs_cache_pressure:  

[NUMA] UMA (early) <---> NUMA
       UMA: all cpu use shared bus so if 0 cpu is accessing memory, 1 cpu can't access memory
       NUMA: socket for cpus has own memory. 
       Local access: memory0 accessed by socket #0 is NUMA architecture
       numactl -H: shows numa info (how many, node distance - access time - from node (socket) 1 to node 2 time
       numastat -cm: can show memory unbalance between processes <= too much memory usage can cause swap
       cat /proc/pid/numa_maps <== in my pc, no numa (may UMA???) 
       numastat 7564: shows heap, stack info of per node info
       taskset -pc 1 7564: from which memory to allocate is defined here after this command
       if process 7564 was using cpu 0 but now assigned to cpu 1 then the memory allocated by cpu 0 is now 
       remote access (more time to access) <== Linux scheduler tends to stick to current Node amap 
       membind_Bindpolicy: membind (stick to original - not recommended), 
                   In membind policy, if memory is insufficient, use swap (instead of cpu 1) and crash <== terrible
                   numastat `pidof malloc_test`; free -m
       cpunodebind_BindPolicy: it allow only one CPU is being used and then if insufficient, use other cpu memory
       It uses other cpu's memory, but it only uses cpu 0 so not good for multi-thread
       physcpubind_BindPolicy: similar to cpu but ???? (later)
       numactl --preferred=1 ./malloc_test: as much as possible to cpu 1
       numactl --interleave=all ./malloc_test: assign evenly to cpus (used when more than 1 cpu for sure)
       numad: no direct control using numactl but enhance locality of memory
              help one process memory from one memory node. relatively good but can a process of numad can dominate one node
              eventually process 0 using node 0 and 1 interleaved will face memory inconsistency
       vm.zone_reclaim_mode kernel_param: not as important as numad but it can be used also
               cat /proc/buddyinfo will show how memory node is being used (my notepc 1 node of 0(dma), 1(normal), 2(highmem))
       DMA: before old hardware only work with DMA but not now.
       Normal: general purpose kernel, process's memory. received from Normal memory area
       vm.zone_reclain_mode allows in one memory area is lack of memory, allow other other mem to allow to use for others
              0 is disable (use cache for more page cache like file server which can take more advantage with page cache than
              many I/O), 1 is enable and good for the case of memory local access is important (not much file I/O)
       
      single thread no single over: bind would be better to stick to one cpu socket
                                    vm.zone_reclaim_mode = 1 fine because one node has all attention improve local access
                                    
      multi-thread  no single over: cpudnodebind => assign a process to many cores vm.zone_recelaim_mode 1 (not exceeding)
   
      single thread single over: cpunodebind, vm.zone_reclaim_mode 0 since requires more than one node of memry, rather than
             reclaim memory but rather assigned from multi-node
      multi-thread single over: may interleaved and vm.zone_reclaim_mode 0
              
       
       
              

        
               


