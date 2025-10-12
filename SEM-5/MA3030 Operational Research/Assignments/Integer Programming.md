
# 3) Factory & warehouse selection (Maliban)

Let

* $F_J, F_B \in \{0,1\}$ = build factory in Jaffna / Batticaloa,
* $W_J, W_B \in \{0,1\}$ = build warehouse in Jaffna / Batticaloa.

Capex (million \$): $6F_J+5W_J+3F_B+2W_B\le 10$.
Warehouses only where a factory is built: $W_J\le F_J,\; W_B\le F_B$.
At most one warehouse: $W_J+W_B\le 1$.

Maximize total NPV (million \$):

$$
\max\; (9F_J+6W_J+5F_B+4W_B).
$$

All variables are binary.&#x20;

---

# 4) Project portfolio with logical constraints

Let a binary decision variable for each project:
$\{x_{\text{CP1}},\dots,x_{\text{CP6}},x_{\text{KP7}},\dots,x_{\text{KP10}}\}\in\{0,1\}$.

Objective (maximize total 3-year return, \$ million):

$$
\max\;\; 8x_{\text{CP1}}+9.5x_{\text{CP2}}+8.5x_{\text{CP3}}+7.5x_{\text{CP4}}+9.5x_{\text{CP5}}+10x_{\text{CP6}}+9x_{\text{KP7}}+8x_{\text{KP8}}+10x_{\text{KP9}}+9x_{\text{KP10}}.
$$

Budget:

$$
5x_{\text{CP1}}+6x_{\text{CP2}}+5.5x_{\text{CP3}}+7x_{\text{CP4}}+8x_{\text{CP5}}+6.5x_{\text{CP6}}+7.5x_{\text{KP7}}+5x_{\text{KP8}}+8.5x_{\text{KP9}}+8x_{\text{KP10}}\le 60.
$$

Cardinality constraints:

$$
\begin{aligned}
&\text{CP count: } x_{\text{CP1}}+\cdots+x_{\text{CP6}}\in[2,5],\\
&\text{KP count: } x_{\text{KP7}}+\cdots+x_{\text{KP10}}\in[2,3],\\
&\text{Total projects: } \sum x \in[5,9].
\end{aligned}
$$

Logic constraints:

$$
\begin{aligned}
&\text{Exactly one of CP2 or CP5: } x_{\text{CP2}}+x_{\text{CP5}}=1,\\
&\text{KP9 and KP10 not together: } x_{\text{KP9}}+x_{\text{KP10}}\le 1,\\
&\text{If CP3 then KP7: } x_{\text{KP7}}\ge x_{\text{CP3}},\\
&\text{If CP3 and CP4 then KP6: } x_{\text{KP6}}\ge x_{\text{CP3}}+x_{\text{CP4}}-1,\\
&\text{If CP4 then (KP6 or KP7): } x_{\text{KP6}}+x_{\text{KP7}}\ge x_{\text{CP4}},\\
&\text{If CP3 then (CP4 and KP8): } x_{\text{CP4}}\ge x_{\text{CP3}},\;\;x_{\text{KP8}}\ge x_{\text{CP3}},\\
&\text{If CP6 then KP10 (one-way implication): } x_{\text{KP10}}\ge x_{\text{CP6}}.
\end{aligned}
$$

All $x$ are binary.&#x20;

---

# 7) Product & plant choice with capacity and at-most-two products

Products $j\in\{1,2,3\}$. Plants $p\in\{1,2\}$.
Let $y_j\in\{0,1\}$ (choose product $j$), $q_j\ge 0$ (units/week, integer if required).
Let $z_p\in\{0,1\}$ (choose plant $p$), with exactly one plant:

$$
z_1+z_2=1.
$$

At most two products:

$$
y_1+y_2+y_3\le 2.
$$

Sales potential: $0\le q_1\le 7y_1,\;0\le q_2\le 5y_2,\;0\le q_3\le 9y_3$.

Capacities (hours/week; coefficients are hours/unit from the table):

$$
\begin{aligned}
&\text{Plant 1: } 3q_1+4q_2+2q_3 \le 30\,z_1,\\
&\text{Plant 2: } 4q_1+6q_2+2q_3 \le 40\,z_2.
\end{aligned}
$$

Profit (thousand \$ per unit): $(5,7,3)$. Maximize:

$$
\max\; 5q_1+7q_2+3q_3.
$$

Binary/continuous (or integer) variable domains as above.&#x20;

---

# 10) Crew pairing (set covering with exactly 3 sequences)

Let sequences $k=1,\dots,12$ with costs $c_k$ (in \$ thousands) and indicator $z_k\in\{0,1\}$.
Let $F$ be the set of flights; define $a_{fk}=1$ if sequence $k$ includes flight $f$ (per the table), else 0.

Choose exactly three sequences:

$$
\sum_{k=1}^{12} z_k = 3.
$$

Cover every flight at least once:

$$
\sum_{k=1}^{12} a_{fk}\, z_k \ge 1,\quad \forall f\in F.
$$

Minimize total cost:

$$
\min \sum_{k=1}^{12} c_k z_k.
$$

(Use the given incidence table and the bottom-row costs.)&#x20;

---

# 12) Cutting 17-ft boards to meet demand with minimum waste

**Demands:** $d_3=25$ (3-ft), $d_5=20$ (5-ft), $d_9=15$ (9-ft).
Each board length $=17$ ft. Minimizing waste $\iff$ minimizing number of boards $N$ because total required length is $310$ ft and waste $=17N-310$. Lower bound: $\lceil 310/17\rceil=19$ boards.

## Integer program (pattern model)

Let $x_p\in\mathbb{Z}_{\ge 0}$ be the number of boards cut according to pattern $p$.
A pattern $p$ is any nonnegative triple $(u_3,u_5,u_9)$ with $3u_3+5u_5+9u_9\le 17$.

$$
\begin{aligned}
\min\quad & \sum_{p} x_p\\
\text{s.t.}\quad
& \sum_{p} u_3^{(p)} x_p \;\;\ge d_3,\\
& \sum_{p} u_5^{(p)} x_p \;\;\ge d_5,\\
& \sum_{p} u_9^{(p)} x_p \;\;\ge d_9,\\
& x_p\in\mathbb{Z}_{\ge 0}.
\end{aligned}
$$

**Useful patterns** (examples):
A: $(1,1,1)$ → $9+5+3=17$
B: $(2,0,1)$ → $3+3+9=15$
C: $(2,2,0)$ → $3+3+5+5=16$
D: $(4,1,0)$ → $3+3+3+3+5=17$
E: $(0,3,0)$ → $5+5+5=15$
F: $(0,2,0)$ → $5+5=10$ (allowed; leaves waste)

## One optimal cutting plan (achieves the lower bound of 19 boards)

Use:

* 13 boards of pattern **A** $(1,1,1)$ → adds 13 of each,
* 2 boards of **B** $(2,0,1)$ → adds 4×3-ft and 2×9-ft,
* 2 boards of **C** $(2,2,0)$ → adds 4×3-ft and 4×5-ft,
* 1 board of **D** $(4,1,0)$ → adds 4×3-ft and 1×5-ft,
* 1 board of **F** $(0,2,0)$ → adds 2×5-ft.

Totals delivered:

* 3-ft: $13+4+4+4=25$,
* 5-ft: $13+4+1+2=20$,
* 9-ft: $13+2=15$.

Board count $=13+2+2+1+1=19\Rightarrow$ waste $=19\cdot17-310=13$ ft (provably minimal by the lower bound).&#x20;

---

