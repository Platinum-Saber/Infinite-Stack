
# Addressing Modes

<br>

### 1. PC-relative Addressing

- **Instructions**: `auipc`, `jal`, and branch instructions (`beq`, `bne`, `blt`, `bge`, etc.)
- The effective address is calculated relative to the current value of the Program Counter (PC).


> [!code] Example code
```assembly
auipc x5, 20  # x5 = PC + 20; here rd is X5

jal x1, 20  # x1 = PC + 20; jump to PC + 20

beq x5, x6, label  # If x5 == x6, jump to the address at label
```

<br>

> [!image] `auipc` diagram
> ![[Pasted image 20240830170542.png]]



<br>
<br>
<br>
<br>
<br>
<br>
<br>

### 2. Register-offset (Base + Offset) Addressing

- **Instructions**: `jalr`, `addi`, and all memory instructions (`lw`, `sw`, `lb`, `sb`, etc.).
- The effective address is computed by adding a constant offset (an immediate value) to the contents of a base register.


> [!code] Example code
```assembly
jalr x1, x2, 0  # x1 = PC + 4; jump to address in x2 + 0

lw x5, 4(x10)  # Load word from memory address (x10 + 4) into x5
```

<br>

> [!image] `jarl` diagram
> ![[Pasted image 20240830173547.png]]

<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>

### 3. Absolute Addressing

- **Instruction**: `lui`
- The `lui` instruction loads a 20-bit immediate value into the upper 20 bits of a register, effectively setting up a large constant or address.
- Directly addresses the register

> [!code] Example code
```assembly
lui x5, 0x12345  # x5 = 0x12345000
addi x5, x5, 0x678  # x5 = 0x12345678 ; addi is used to complete the full address.
```

<br>

> [!image] `lui` diagram
> ![[Pasted image 20240830174616.png]]

