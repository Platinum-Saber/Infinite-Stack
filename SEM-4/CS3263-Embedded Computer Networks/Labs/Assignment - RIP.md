---
tags: 
Created: 2025-05-01 13:27
About: 
Reviewed: false
Completion: 0
---
**Name :** S.S.Waduge
**Index :** 220673K
## RIP – Routing Information Protocol

### What is RIP?

> [!NOTE] **RIP** is a **distance-vector routing protocol** used in **small to medium-sized IP networks**. It uses **hop count** as a routing metric and works at the **network layer (Layer 3)** of the OSI model. RIP routers periodically exchange routing tables to maintain path information.

---

### RIP Characteristics

|Feature|Description|
|---|---|
|Protocol Type|Distance Vector|
|Metric|Hop Count (Max 15, ∞ = 16)|
|Updates Interval|Every 30 seconds|
|Protocol Numbers|RIP v1 (classful), RIP v2 (classless)|
|Transport Layer|UDP Port 520|
|Algorithm|Bellman-Ford|
|Limitations|No support for >15 hops|

---

### RIP Working Process

> [!info] RIP process:
> 
> 1. **Initialization** – Each router starts with only directly connected networks in its routing table.
> 2. **Periodic Update** – Every 30 seconds, the router sends a copy of its routing table to its neighbors.
> 3. **Update on Change** – If a route changes or becomes unavailable, the metric increases, possibly to infinity.
> 4. **Route Calculation** – Bellman-Ford algorithm determines the shortest (least hop count) path.

---

> [!image] RIP Flowchart (Mermaid)
> 
> ```mermaid
> flowchart TD
>     A[Start: Router Boots Up] --> B[Initialize Routing Table]
>     B --> C{Every 30s Timer Expired?}
>     C -- Yes --> D[Send Routing Table to Neighbors]
>     D --> E[Receive Routing Tables from Neighbors]
>     E --> F["Update Routing Table (Bellman-Ford)"]
>     F --> C
>     C -- No --> G[Wait or Listen for Updates]
>     G --> C
> ```
> 

---

<br>
<br>


> [!image] RIP Network Illustration 
> 
> ```mermaid
> graph TD
>     R1[Router 1] --"10.0.0.0/24 (1 hop)"--> R2[Router 2]
>     R2 --"10.0.1.0/24 (1 hop)"--> R3[Router 3]
>     R1 ---|Routing Table| T1{{10.0.0.0/24 - 0 hops<br>10.0.1.0/24 - 2 hops}}
>     R3 ---|Routing Table| T2{{10.0.1.0/24 - 0 hops<br>10.0.0.0/24 - 2 hops}}
> ```
> 
> ---
> 

> [!example]  RIP Example (Routing Table Update)
> 
> |Destination|Next Hop|Metric|
> |---|---|---|
> |10.0.0.0|Direct|0|
> |10.0.1.0|R2|1|
> |10.0.2.0|R2|2|
> 
> If the link to 10.0.1.0 fails, RIP sets the metric to **16** (unreachable), and after 180 seconds, the route is removed.

---

### RIP Limitations

> [!warning] Limitations
> - Slow convergence (180s to timeout a route).
> - Limited scalability due to hop count = 15.
> - Susceptible to routing loops (mitigated by techniques like **Split Horizon**, **Route Poisoning**, and **Hold-Down Timers**).

---




