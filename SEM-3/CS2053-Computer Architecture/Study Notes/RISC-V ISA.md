# Instructions
[[#1. `lui` Instruction]]
[[#2. `addi` Instruction]]
[[#3. `lw` Instruction (Load Word)]]
[[#4. `sw` Instruction (Store Word)]]




### 1. `lui` Instruction
-  **Opcode** : `0110111`
- **Immediate** : The 20 bit immediate value is placed directly in bits 31-12 of the instruction.
- **Register** : The destination register `rd` is specified in bits 11-7.


> [!image] Binary encoding
> ![[Pasted image 20240830155341.png]]

### 2. `addi` Instruction
- **Opcode** : `0010011`
- **Immediate** : A 12 bit immediate value is sign-extended and added to the value in the source register.
- **Registers** : The source register (`rs1`) and destination register (`rd`) are specified.

#### Instruction 
- **Bits 31-20**: Immediate value (lower 12 bits of the address)
- **Bits 19-15**: Source register (`rs1`, 5 bits)
- **Bits 14-12**: Function code (`funct3`, 3 bits `000` for `addi`)
- **Bits 11-7**: Destination register (`rd`, 5 bits)
- **Bits 6-0**: Opcode (`0010011` for `addi`, 7 bits)

> [!image] Binary encoding
> ![[Pasted image 20240830144952.png]]

> [!code] Example code
```assembly
 .section .data
   my_data: .word 0x12345678   # Define a data word at a specific memory location
 
 .section .text
   .globl _start
 
 _start:
   lui t0, %hi(my_data)        # Load the upper 20 bits of the address of my_data into t0
   addi t0, t0, %lo(my_data)   # Add the lower 12 bits to t0 to get the full address
 
   # The address of my_data is now directly addressed in register t0
 ```

<br>

### 3. `lw` Instruction (Load Word)
- **Opcode** : `0000011`.
- **Immediate** : The 12-bit immediate value is sign-extended and added to the value in the source register (`rs1`) to compute the effective address.
- **Registers** : The source register (`rs1`) contains the base address, and the destination register (`rd`) receives the loaded data.

#### Instruction
- **Bits 31-20**: Immediate value (offset, 12 bits)
- **Bits 19-15**: Source register (`rs1`, 5 bits)
- **Bits 14-12**: Function code (`funct3`, 3 bits, `010` for `lw`)
- **Bits 11-7**: Destination register (`rd`, 5 bits)
- **Bits 6-0**: Opcode (`0000011` for `lw`)


> [!code] Example code
>
```assembly
lw x5, 4(x10)  # Load the word at the address x10 + 4 into x5 (Register indirect  addressing)

# binary encoding of the instruction : 000001100100 00010 010 00101 0000011
# In hexadecimal : 0x06452003
```

> [!image] Binary encoding
> 
> ![[Pasted image 20240830150848.png]]



### 4. `sw` Instruction (Store Word)
- **Opcode**: The `sw` instruction uses the opcode `0100011`.
- **Immediate**: The 12-bit immediate value is split across two fields in the instruction (upper 7 bits and lower 5 bits).
- **Registers**: The source register (`rs2`) contains the data to be stored, and the base register (`rs1`) provides the address.

#### Instruction
- **Bits 31-25**: Immediate value (upper 7 bits)
- **Bits 24-20**: Source register (`rs2`, 5 bits)
- **Bits 19-15**: Base register (`rs1`, 5 bits)
- **Bits 14-12**: Function code (`funct3`, 3 bits, `010` for `sw`)
- **Bits 11-7**: Immediate value (lower 5 bits)
- **Bits 6-0**: Opcode (`0100011` for `sw`)


> [!code] Example code
> 
```assembly
sw x5, 4(x10)  # Store the word in x5 to the address x10 + 4 (Register indirect  addressing)


# binary encoding of the instruction : 0000011 00101 01010 010 00100 0100011
# In hexadecimal : 0x006552223

```

> [!image] Binary encoding
> ![[Pasted image 20240830155106.png]]
