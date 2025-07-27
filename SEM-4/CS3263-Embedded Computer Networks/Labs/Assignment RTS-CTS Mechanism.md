---
tags:
  - EmbeddedNetworking
Created: 2025-04-08 21:21
About: 
Reviewed: true
Completion: 0
---
**Name** : Waduge S.S.
**Index** : 220673K

## 🔹 What is RTS/CTS Mechanism in IEEE 802.11?

> [!NOTE]   **RTS/CTS**
> 
> **RTS (Request to Send)** and **CTS (Clear to Send)** are part of a handshaking protocol used in the IEEE 802.11 standard to reduce frame collisions, especially in scenarios where nodes might not hear each other.


## 🔹 Does it solve the **Hidden Node Problem**?

####  **Yes, it does.**

###  **Justification:**

> [!info] Hidden Node Problem:
> 
> Occurs when two nodes (say A and C) are **not within each other's range**, but **both can communicate with a common node B**. If A and C transmit at the same time, **collisions** happen at B.

> [!tip] With RTS/CTS:
> 
> - A sends RTS to B
> - B replies with CTS
> - C hears **CTS** from B (even though it doesn't hear A), knows B is busy
> - C **waits**, avoiding collision

> [!image] Diagram
> ```mermaid
> sequenceDiagram
>     participant A as Node A (Sender)
>     participant B as Node B (Receiver)
>     participant C as Node C (Hidden Node)
> 
>     A->>B: RTS (Request to Send)
>     Note right of C: C does not hear RTS from A
>     B-->>A: CTS (Clear to Send)
>     Note right of C: C hears CTS from B and defers
>     A-->>B: DATA
>     B-->>A: ACK
>     Note over B,C: Hidden Node Problem avoided
> ```

> [!check]  **Result:** The hidden node (C) **backs off**, avoiding interference.

<div style="page-break-before: always;"></div>

## 🔹 Does it solve the **Exposed Node Problem**?

####  **No, it does not completely solve it.**

###  **Justification:**

> [!info] Exposed Node Problem:
> 
> Occurs when a node **hears a transmission** from a nearby node and **incorrectly assumes** it cannot transmit — even though its own transmission **wouldn’t cause interference**.
> 

> [!warning] Scenario:
> 
> - B is sending to A
> - C wants to send to D
> - C hears B’s transmission (or RTS/CTS), so it **backs off**
> - But D is **out of range** of B → **C could have transmitted safely**


> [!image] Diagram
> ```mermaid
> sequenceDiagram
>     participant B as Node B (Sender)
>     participant A as Node A (Receiver)
>     participant C as Node C (Exposed Node)
>     participant D as Node D (C's Destination)
> 
>     B->>A: RTS
>     A-->>B: CTS
>     Note right of C: C hears RTS/CTS and waits
>     Note over C,D: C could have sent to D
>     Note over C,D: But stayed silent unnecessarily
> ```

> [!bug] This happens because C **overhears** the RTS or CTS and **assumes the medium is busy**, even though its transmission wouldn’t interfere.

---

> [!abstract] RTS/CTS **helps coordinate medium access** but **can’t differentiate** between harmful and harmless interference in this case.