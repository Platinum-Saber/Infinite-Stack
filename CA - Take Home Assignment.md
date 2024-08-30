
# Addressing Modes

### 1. PC-relative Addressing

- **Instructions**: `auipc`, `jal`, and branch instructions (`beq`, `bne`, `blt`, `bge`, etc.)
- The effective address is calculated relative to the current value of the Program Counter (PC).


> [!code] Example code
> 
```assembly
auipc x5, 1000  # x5 = PC + (1000 << 12)

jal x1, 20  # x1 = PC + 4; jump to PC + 20

beq x5, x6, label  # If x5 == x6, jump to the address at label
```

### 2. Register-offset (Base + Offset) Addressing

- **Instructions**: `jalr`, `addi`, and all memory instructions (`lw`, `sw`, `lb`, `sb`, etc.).
- The effective address is computed by adding a constant offset (an immediate value) to the contents of a base register.

### 3. Absolute Addressing

- **Instruction**: `lui`
- The `lui` instruction loads a 20-bit immediate value into the upper 20 bits of a register, effectively setting up a large constant or address.