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
[free] cache: store page data of file system
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

               


