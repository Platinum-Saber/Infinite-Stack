---
tags:
  - CA
  - "#CA/05"
  - ComputerArchitecture
  - "#MemoryHierarchy"
Reviewed: false
Created: 2024-09-01T01:08:00
About: Based on CS2053-Lecture 05 Memory Hierarchy part 1
---
Related : #CA #CA/05 #ComputerArchitecture #MemoryHierarchy 

Reference Note : [Memory Hierarchy 1](file:///E:%5CAcademics%5CSEM%203%5CCS2053-Computer%20Architecture%5CLecture%20note%5C05%20-%20Memory%20Hierarchy%20I.pdf) ,[[GPT_Memory Hierarchy note ]]

---
# Content
1. [[#Accessing Memory]]
2. [[#Reading From & Writing to Memory]]
3. [[#Connecting Memory & CPU]]
4. [[#Addressing Modes]]

<br>

## Accessing Memory
- The **address bus** activates a memory cell at a particular location. This prepares the memory cell for read or write operation that will occur.
- The **control bus** specifies the action done on the particular activated memory location. Typically whether read or write action is performed.
- **Data bus** carries the relevant data to or from the memory cell depending on the control signal.

> [!tip]- Address bus & Control bus are unidirectional. The data bus can carry signals both ways but only in one direction at a time.

![[Pasted image 20240901012947.png]]
<br>

### Reading From & Writing to Memory
> [!info] Reading From Memory
> - **Address** of memory location to read is placed on *Address Bus*.
> - **Read Signal** (RD) in *Control Bus* is activated.
> - **Data** Is fetched (read) from *Data Bus*.

> [!info] Writing to Memory
> - **Address** of the memory location to write is placed on *Address Bus*.
> - **Data** is placed on *Data Bus.*
> - **Write Signal** (WR) in *Control Bus* is activated.

<br>

### Connecting Memory & CPU
- Details of handling different memory modules & memory hierarchy is *off load* to **memory controller**.

![[Pasted image 20240901015138.png]]
<br>

### Addressing Modes

#### 1. PC-relative Addressing

- **Instructions**: `auipc`, `jal`, and branch instructions (`beq`, `bne`, `blt`, `bge`, etc.)
- The effective address is calculated relative to the current value of the Program Counter (PC).


> [!code] Example code
```assembly
auipc x5, 20  # x5 = PC + 20; here rd is X5

jal x1, 20  # x1 = PC + 20; jump to PC + 20

beq x5, x6, label  # If x5 == x6, jump to the address at label
```

<br>

> [!image]- `auipc` diagram
> ![[Pasted image 20240830170542.png]]

<br>
<br>

> [!image]- `jal` diagram
> ![[Pasted image 20240830225137.png]]

<br>
<br>

#### 2. Register-offset (Base + Offset) Addressing

- **Instructions**: `jalr`, `addi`, and all memory instructions (`lw`, `sw`, `lb`, `sb`, etc.).
- The effective address is computed by adding a constant offset (an immediate value) to the contents of a base register.


> [!code] Example code
```assembly
jalr x1, x2, 0  # x1 = PC + 4; jump to address in x2 + 0

lw x5, 4(x10)  # Load word from memory address (x10 + 4) into x5
```

<br>

> [!image]- `jalr` diagram
> ![[Pasted image 20240830173547.png]]

<br>

> [!image]- `lw` diagram
> ![[Pasted image 20240830230821.png]]

<br>
<br>

#### 3. Absolute Addressing

- **Instruction**: `lui`
- The `lui` instruction loads a 20-bit immediate value into the upper 20 bits of a register, effectively setting up a large constant or address.
- Directly addresses the register.

> [!code] Example code
```assembly
lui x5, 0x12345  # x5 = 0x12345000
addi x5, x5, 0x678  # x5 = 0x12345678 ; addi is used to complete the full address.
```

<br>

> [!image]- `lui` diagram
> ![[Pasted image 20240830174616.png]]

For more info on instructions: [[RISC-V ISA]]

## Memory Hierarchy
- Organizing memory in a way that the slowness of larger memory doesn't reduce the overall performance of the system.
- Faster memory is expensive hence a small amount is used (*Registers, static RAM*). Slow memory isn't expensive hence can be used in large amounts(*Dynamic RAM*).

**Main objective of a memory system**,
- Have sufficient speed
- Have sufficient capacity
- Be as cheap as possible.

> [!image]- Memory hierarchy diagram
> ![[Pasted image 20240906105711.png]]

<br>

### Principal of Locality
- Refers to the tendency of a program to access the same data or 

