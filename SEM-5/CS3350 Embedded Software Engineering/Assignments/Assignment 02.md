<center>
<h1> Assignment 02</h1>
Name : Waduge S.S. <br>
Index : 220673K
</center>

## (a) Identification of Unsafe Situations

For the safe operation of the elevator, the following unsafe situations are identified:

1. **Stopped Away from a Floor**

   * **Condition**: The motor is switched **off** (cage stopped), but the floor sensor indicates **invalid floor** (`motor = off ∧ validf = no`).
   * **Hazard**: The cage stops between floors, creating a fall risk if the door opens.

2. **Door Open While Moving**

   * **Condition**: The motor is switched **on** (cage moving), and the door is **open**. (`door = open ∧ motor = on`)
   * **Hazard**: Passengers are exposed to the moving shaft.

3. **Door Open Away from a Floor**

   * **Condition**: The door is **open**, but the sensor indicates **invalid floor** (`door = open ∧ validf = no`).
   * **Hazard**: Passengers could step into an empty shaft.

4. **Stopped but Motor Still On** (control logic violation)

   * **Condition**: The cage is reported as **stopped**, but the motor is still **on**. (`moving = no ∧ motor = on`)
   * **Hazard**: Inconsistent state may lead to unsafe door operations.

---


###  Rule S1: Stopping Implies Valid Floor

**Predicate:**  $\mathcal{(moving = no) \Rightarrow (validf = yes)}$  
- _If the elevator is stopped, it must be at a valid floor._

|moving|validf|S1 holds?|Status|
|---|---|---|---|
|yes|no|T|Safe|
|yes|yes|T|Safe|
|**no**|**no**|**F**|**Unsafe (stopped away from floor)**|
|no|yes|T|Safe|

---

<div style="page-break-before: always;"></div>

### Rule S2: Door Open Implies No Movement 

**Predicate:**  $\mathcal{(door = open) \Rightarrow (moving = no)}$  
- _If the door is open, the elevator must not be moving._

|door|moving|S2 holds?|Status|
|---|---|---|---|
|close|yes|T|Safe|
|close|no|T|Safe|
|**open**|**yes**|**F**|**Unsafe (door open while moving)**|
|open|no|T|Safe|

---

### Rule S3: Door Open Implies Valid Floor

**Predicate:**  $\mathcal{(door = open) \Rightarrow (validf = yes)}$  
- _If the door is open, the elevator must be aligned with a valid floor._

|door|validf|S3 holds?|Status|
|---|---|---|---|
|close|no|T|Safe|
|close|yes|T|Safe|
|**open**|**no**|**F**|**Unsafe (door open away from floor)**|
|open|yes|T|Safe|

---

### Rule S4 : No Movement Implies Motor Is Off

**Predicate:**  $\mathcal{(moving = no) \Rightarrow (motor = off)}$  
- _If the elevator is not moving, the motor must be off._

|moving|motor|S4 holds?|Status|
|---|---|---|---|
|yes|on|T|Safe|
|yes|off|T|Safe|
|**no**|**on**|**F**|**Unsafe (stopped but motor still on)**|
|no|off|T|Safe|

---

<div style="page-break-before: always;"></div>


## (c) Formal Specification in Z

$$
\begin{aligned}
&DOOR ::= close \mid open \\
&MOTOR ::= off \mid on \\
&MOVING ::= yes \mid no \\
&VALID\_FLOOR ::= yes \mid no \\ \\
&\textbf{ElevatorSafety} \\
&\hline \\
&door : DOOR \\
&motor : MOTOR \\
&moving : MOVING \\
&validf : VALID\_FLOOR \\
&\hline \\
&\forall \; \mathcal{door,\ motor,\ moving,\ validf}  \;\bullet\;  \\ \\
&(moving = no) \Rightarrow (validf = yes) \;\land \\
&(door = open) \Rightarrow (moving = no) \;\land \\
&(door = open) \Rightarrow (validf = yes) \;\land \\
&(moving = no) \Rightarrow (motor = off)
\end{aligned}
$$

### Declarations
```zed
DOOR ::= close | open
MOTOR ::= off | on
MOVING ::= yes | no
VALID_FLOOR ::= yes | no
```


### Safety Schema

```zed
ElevatorSafety
==============
door   : DOOR
motor  : MOTOR
moving : MOVING
validf : VALID_FLOOR
--------------------------------
-- S1: If stopped then at a valid floor
(moving = no) ⇒ (validf = yes)

-- S2: Door may open only if not moving
(door = open) ⇒ (moving = no)

-- S3: If door is open, then must be at a valid floor
(door = open) ⇒ (validf = yes)

-- S4: If not moving, then motor must be off
(moving = no) ⇒ (motor = off)

∀ door, motor, moving, validf ∙
(moving = no ⇒ validf = yes)  ∧ (door = open ⇒ moving = no)  ∧ 
(door = open ⇒ validf = yes)   ∧ (moving = no ⇒ motor = off)    
```

