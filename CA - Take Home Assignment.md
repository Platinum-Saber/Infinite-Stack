# Addressing Modes
1. [[#Direct Addressing]]
	- [[#1. `lui` Instruction]]
	- [[#2. `addi` Instruction]]
2. [[#Register Indirect Addressing]]
3. [[#Displacement Addressing]]

## Direct Addressing
- The **immediate value** of the instruction specifies the **memory address** that will be referenced. 
- Only 1 memory access is required to access the memory location.
### 1. `lui` Instruction
-  **Opcode** : `0110111`
- **Immediate** : The 20 bit immediate value is placed directly in bits 31-12 of the instruction.
- **Register** : The destination register `rd` is specified in bits 11-7.

![[Drawing 2024-08-22 13.38.19.excalidraw.png]]

### 2. `addi` Instruction
- **Opcode** : `0010011`
- **Immediate** : A 12 bit immediate value is sign-extended and added to the value in the source register.
- **Registers** : The source register `rs1` and destination register `rd` are specified.

#### Instruction 
- **Bits 31-20**: Immediate value (lower 12 bits of the address)
- **Bits 19-15**: Source register (`rs1`)
- **Bits 14-12**: Function code (`000` for `addi`)
- **Bits 11-7**: Destination register (`rd`)
- **Bits 6-0**: Opcode (`0010011` for `addi`)

![[Pasted image 20240830144952.png]]

> [!code] Example code
> ```assembly
> .section .data
>   my_data: .word 0x12345678   # Define a data word at a specific memory location
> 
> .section .text
>   .globl _start
> 
> _start:
>   lui t0, %hi(my_data)        # Load the upper 20 bits of the address of my_data into t0
>   addi t0, t0, %lo(my_data)   # Add the lower 12 bits to t0 to get the full address
> 
>   lw t1, 0(t0)                # Load the data at the address stored in t0 into t1
> 
>   # The address of my_data is now directly addressed in register t0
>   # The value 0x12345678 is loaded into register t1
> 
> ```

<br>

## Register Indirect Addressing

