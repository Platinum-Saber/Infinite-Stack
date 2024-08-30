# Addressing Modes
1. [[#Direct Addressing]]
2. [[#Register Indirect Addressing]]
3. [[#Displacement Addressing]]

## Direct Addressing
- The **immediate value** of the instruction specifies the **memory address** that will be referenced. Only 1 memory access is required to access the memory location.
### 

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