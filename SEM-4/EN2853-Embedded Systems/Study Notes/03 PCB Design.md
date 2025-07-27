---
tags:
  - EmbeddedSystems
Created: 2025-03-31 21:01
About: 
Reviewed: true
Completion: 10
---

## Status
Reviewed : `INPUT[toggle:Reviewed]`

Progress :  
```meta-bind
INPUT[progressBar:Completion]
```





## PCB Design Flow


> [!faq] How to design a PCB
> 1. List down the requirements
> 2. Collect relevant information
> 	 - List of similar products and compare features.
> 	 - List of components of the project
> 	 - Find relevant datasheets.
> 1. PCB schematic design
> 2. PCB layout design

```mermaid
flowchart LR
Schematic(Schematic) --> Layout(Layout)
Layout --> Gerber(Gerber)
Gerber --> PCB(PCB)
```

## Schematic Design


> [!NOTE] A **Schematic** is a visual representation of a circuit.

> [!info] Purpose of a schematic
> Communicate circuit information,
> - quickly
> - clearly
> - with low chance of misunderstanding


> [!image] Schematic
> ![[Pasted image 20250331212848.png]]



### Schematic Libraries in PCB Design

Schematic libraries in PCB design are collections of electronic component symbols and their associated attributes, used to create circuit schematics. 


#### 1. Components of a Schematic Library (`*.SchLib`)

> [!tip] A schematic library typically contains:
> 1. **Symbols** – Graphical representations of electronic components (e.g., resistors, capacitors, ICs).
> 2. **Pins & Connections** – Defined electrical terminals for connectivity.
> 3. **Attributes & Parameters** – Information such as part number, voltage ratings, footprint link, and manufacturer details.
> 4. **Footprint Link** – A reference to the PCB layout footprint that corresponds to the component.
> 5. **SPICE Models** – Electrical models for simulation, if supported by the tool.
> 

---

#### 2. Importance of Schematic Libraries
- **Standardization:** Ensures that all components in the design adhere to the same standards.
- **Efficiency:** Saves time by reusing verified symbols instead of creating them from scratch.
- **Error Reduction:** Minimizes mistakes by maintaining a consistent database of validated components.
- **Interoperability:** Helps in seamless transition from schematic to PCB layout by linking symbols to footprints.
- <span style="color: rgb(0, 200, 255);">Useful to generate BOM (Bill Of Materials)</span> using the specific parametric information like manufacturing, supplier part number, component values.


> [!NOTE] **PCB footprints**, **SPICE simulations** (`*.MDL` or `*.CKT` files) and **Signal Integrity** (SI) models are linked to the schematic component



---

#### 3. Types of Schematic Libraries
##### (a) Built-in Libraries
- Provided by PCB design software (e.g., KiCad, Altium Designer, Eagle).
- Contains commonly used electronic components.

##### (b) Custom Libraries
- Created by users for proprietary or specialized components.
- Used when specific manufacturer parts are not available in default libraries.

##### (c) Manufacturer Libraries
- Provided by component manufacturers (e.g., Texas Instruments, STMicroelectronics).
- Includes accurate footprints, 3D models, and electrical specifications.

##### (d) Third-Party Libraries
- Developed by the community or third-party vendors (e.g., SnapEDA, Ultra Librarian).
- Provides a large collection of verified components.

---

### Schematic Features


> [!image] 1 - Visual and Logical Structure
>>[!warning] Convention
> > - Input should be on the left-hand side.
> > - Output should be on the right-hand side.
> > - There should be a voltage flow. (Either from top to bottom or bottom to top)

> [!info] 2 - Electrical Rule Check
>  Check all the connections using software simulations to find any errors.


> [!info] 3 - Multilevel Hierarchy
> Schematic contains expandable blocks with more detailed information.


> [!info] 4 - Import/Export
> Can import different libraries and export smart pdfs etc.

