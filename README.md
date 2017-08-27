# Buddy-Memory-Allocator

In our buddy-system memory allocator, memory block sizes are a power of two, starting at the
basic_block_size. For example, if 9kB of memory are requested, the allocator returns 16kB, and
7kB goes wasted – this is called fragmentation. This restriction on allowable block sizes makes
the management of free memory blocks very easy: The allocator keeps an array of free lists, one
for each allowable block size. Every request is rounded up to the next allowable size, and the
corresponding free list is checked. If there is an entry in the free list, this entry is simply used and
deleted from the free list.
If the free list is empty (i.e. there are no free memory blocks of this size,) a larger block is selected
(using the free list of some larger block size) and split. Whenever a free memory block is split in
two, one block gets either used or further split, and the other – its buddy – is added to its
corresponding free list.

Example: In the example above, there is no 16kB block available (i.e. the free list for 16kB is
empty). The same holds for 32kB blocks. The next-size available block is of size 64kB. The
allocator therefore selects a block, say B, of size 64kB (after deleting it from the free list). It then
splits B into two blocks, BL and BR of size 32kB each. Block BR is added to the 32kB free list. Block
BL is further split into BLL and BLR of size 16 kB each. Block BLL is returned by the request, while
BLR is added to the 16kB free list.
In this example, the blocks BL and BR are buddies, as are BLL and BLR . Whenever a memory block
is freed, it may be coalesced with its buddy: If the buddy is free as well, the two buddies can be
combined to form a single memory block of twice the size of each buddy.

Example: Assume that BLL and BLR are free, and that we are just freeing BLR . In this case, BLL and
BLR can be coalesced into the single block BL. We therefore delete BLL from its free list and proceed
to insert the newly formed BL into its free list. Before we do that, we check with its buddy BR. In
this example, BR is free, which allows for BL and BR to be coalesced in turn, to form the 64kB block
B. In this process, Block BR is removed from its free list and the newly-formed block B is added
to the 64kB free list.
