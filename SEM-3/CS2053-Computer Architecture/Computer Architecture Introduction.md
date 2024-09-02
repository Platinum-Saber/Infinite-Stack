Related : #ComputerArchitecture #CA #CA/01

Reference Note : [Introduction](file:///E:%5CAcademics%5CSEM%203%5CCS2053-Computer%20Architecture%5CLecture%20note%5C01%20-%20Introduction-RVFinal.pdf)
Reference Lecture : [Computer Architecture By Onur Mutlu](https://youtu.be/zLP_X4wyHbY?si=l7nz2NZAdhaxfqBv)

<br>

# Computer Architecture

<br>

>[!abstract]- Classes Of Computers
>- Desktop 🖥 
>- Personal 🖥 
>- Servers
>- Embedded 🖥 
>- Cloud 🖥 

>[!abstract]- Performance Metrics
>- Reliability
>- Capacity
>- Speed
>- Cost
>- Energy
>- Size

>[!FAQ]- What is **Computer Architecture**
>A blueprint that's visible to the programmer which contains key functional units, their interconnections, and instructions to program the `instruction set architecture`.
>- Ex :- x86, ARM

>[!FAQ]- What is **Computer Organization**
>The internal details of operational units, their interconnections, & control view of a computer designer.
>- Ex :- Intel & AMD both support x86 with different organizations

>[!FAQ]- What is **Computer Design**
>- It maps a given organization to a logic design, logic design to a silicon layout & chip packaging.
>- This is the view of the hardware designer.
>- Design decisions are based on constraints like circuit level delays, silicon real estate, heat generation & cost.

>[!info]- $\ 3^{rd}$ Level view of a computer
>![[Pasted image 20240705090046.png]]

<br>
<br>

## Registers
>[!note]- Functionality of a register
>It's a type of memory located inside the CPU
>It can hold a single piece of data (useful in both data processing & control functionalities)

>[!example]- Examples for **Special Purpose Registers**
>- Program counter
>- Instruction register
>- Accumulator or working register
>- Flag/Status register

>[!abstract]- **Special Purpose Registers**
>![[Pasted image 20240705091030.png]]
>![[Pasted image 20240705091103.png]]

> [!tip]- Building Design Solutions to Computational Problems
> ```mermaid
> classDiagram
> 	class Problem_Statement{
> 	- Algorithms, RTL
> 	- Flowcharts
> 	- State transition diagrams
> 	}
> 	
> 	class Behavioral_Description{
> 	- Logic equations
> 	- Circuit schematics
> 	}
> 	
> 	class Boolean_Logic_and_State{
> 	- TTL Gates
> 	- Programmable Logic
> 	- Custom ASICs
> 	- FPGAs
> 	- MCs, DSPs
> 	}
> 	
> 	class Hardware_Implementation{
> 	- Verilog or VHDL code
> 	- Assembler
> 	- C, C++
> 	}
> 	Problem_Statement --> Behavioral_Description
> 	Behavioral_Description --> Boolean_Logic_and_State
> 	Boolean_Logic_and_State --> Hardware_Implementation
> ```

<br>

## Architectural Differences
>[!abstract]- Commonly identifiable differences
>- Length of microprocessors' data word (4, 8,16, 32, 64,128 bit)
>- Speed of instruction execution (clock rate determines processor speed)
>- Instruction set ( `x86, ARM, SPARC, PIC, RISCV`)
>- CPU architecture (`RISC 🆚 CISC`)
>- Size of direct addressable memory
>- Number and types of registers
>- Support Circuit performance
>- Comparability with existing software and hardware

>[!abstract]- Microprocessor 🆚 Microcontroller
>> [!info]- Microprocessor
>> CPU & various IO functions are packed as separate ICs
>
>>[!info]- Microcontroller
>>Most IO functions are integrated into the same package with CPU

<br>

## Processor Design to Program
>[!info]- **Programming Hierarchies**
>![[Pasted image 20240705095649.png]]

>[!warning]- Shortcomings of a **nano-processor**
>>[!error]- Lack of stages of instructions
>>Nano processor is single cycled not multi cycled
>
>>[!error] No **Pipelining**
>
>>[!error]- Missing Peripherals
>>- Memory : RAM
>>- Input Output methods (Memory mapped inputs/outputs)
>
>>[!error]- No way to program it
>
>>[!error]- Not Efficient/ Power

<br>

****

<br>

Up Next : [[Instruction Set Architecture-RV]]
