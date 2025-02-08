# Memory Hierarchy and Cache
## 1. Memory Hierarchy Overview

### Memory Access Basics
- Memory is accessed through:
  - Address Bus: Carries memory location addresses
  - Data Bus: Carries data being read/written
  - Control Bus: Carries control signals (RD/WR)

### The Memory Problem
- Growing gap between processor and memory speed (50% per year)
- Solution: Hierarchical memory system
  - Fast but expensive memory (small capacity)
  - Slow but cheap memory (large capacity)

### Principle of Locality
1. **Temporal Locality**
   - Recently referenced items likely to be referenced again
   - Example: Variables in loops

2. **Spatial Locality**
   - Items with nearby addresses tend to be referenced together
   - Example: Array elements, sequential instructions

## 2. Cache Memory

### Basic Concepts
- Small, fast memory between CPU and main memory
- Built using SRAM (Static RAM)
- Size ranges from KB to MB
- Multiple levels:
  - L1 Cache: Fastest, within CPU
  - L2 Cache: Larger, slightly slower
  - L3 Cache: Even larger, present in modern processors

### Cache Organization
1. **Cache Block (Line)**
   - Minimum unit of data transfer
   - Contains multiple words
   - Tagged with memory address

2. **Cache Entry Components**
   - Valid bit
   - Tag (upper portion of address)
   - Data
   - Index = (Memory block address) modulo #Cache blocks

### Cache Associativity Types
1. **Direct Mapped**
   - Each memory block maps to exactly one cache location
   - Simple but can lead to conflicts

2. **Fully Associative**
   - Memory block can go anywhere in cache
   - Requires parallel search of all tags
   - Expensive hardware, used for small caches

3. **Set Associative**
   - Compromise between direct mapped and fully associative
   - n-way set associative: n blocks per set
   - Memory block can go to any block within its assigned set

### Cache Performance Metrics
1. **Hit/Miss**
   - Hit: Data found in cache
   - Miss: Data not found in cache
   - Hit ratio: Fraction of accesses found in cache
   - Miss ratio: Fraction of accesses not found in cache

2. **Types of Cache Misses**
   - Compulsory: First access to a block
   - Capacity: Cache too small to hold all needed blocks
   - Conflict: Multiple blocks competing for same location

3. **Access Time Calculation**
   - Average Memory Access Time = Hit time + (Miss rate × Miss penalty)

### Cache Replacement Policies
When cache is full, existing blocks must be removed:
1. Random: Simple to implement
2. Least Recently Used (LRU): Removes least recently accessed block
3. Least Frequently Used (LFU): Removes least frequently accessed block
4. First In First Out (FIFO): Removes oldest block

### Cache Write Policies
1. **Write-through**
   - Write to both cache and memory
   - Uses write buffer to improve performance
   
2. **Write-back**
   - Write only to cache
   - Memory updated when block is replaced
   - Better performance but more complex

### Performance Improvement Techniques
1. Increasing cache capacity
2. Multiple levels of cache
3. Prefetching: Loading data before it's needed
4. Using fully associative caches where practical