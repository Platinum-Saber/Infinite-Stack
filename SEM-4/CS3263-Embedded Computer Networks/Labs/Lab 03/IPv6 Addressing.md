---
tags: 
Created: 2025-03-16 18:55
About: 
Reviewed: false
Completion: 0
---
**Name** : Waduge.S.S
**Index** : 220673K


> [!image] Network Addresses
> ![[Pasted image 20250316190346.png]]


> [!image] IPv6 Addresses
> ![[Pasted image 20250316192145.png]]


> [!image] IPv6 Default Gateway
> ![[Pasted image 20250316192514.png]]

---

<div style="page-break-after: always;"></div>





### **IPv6 Address Analysis According to RFC 2373**

#### **1. Loopback Address (`::1/128`)**

- **Address:** `::1/128`
- **Scope:** Host
- **Interface:** `lo` (Loopback interface)
- **Meaning:**
    - This is the IPv6 **loopback address**, equivalent to `127.0.0.1` in IPv4.
    - It is used by the local system to communicate with itself.
    - Packets sent to this address never leave the host.

---

#### **2. Link-Local Address (`fe80::408f:e6c4:6503:821c/64`)**

- **Address:** `fe80::408f:e6c4:6503:821c/64`
- **Scope:** Link
- **Interface:** `wlo1` (Wireless interface)
- **Meaning:**
    - This is a **link-local address**, automatically assigned to the interface.
    - It allows communication between devices **within the same local network segment**.
    - All link-local addresses start with `fe80::/10` and are not routable beyond the local network.

---

<div style="page-break-after: always;"></div>

#### **3. Global Unicast Address (`2401:dd00:10:20:6b4f:8c2c:8d82:5b8c/64`)**

- **Address:** `2401:dd00:10:20:6b4f:8c2c:8d82:5b8c/64`
- **Scope:** Global
- **Interface:** `wlo1` (Wireless interface)
- **Meaning:**
    - This is a **global unicast address**, which means it is **publicly routable** on the internet.
    - The prefix `2401:dd00::/32` suggests that this is assigned by an **ISP or network provider** in the APNIC region (Asia-Pacific).
    - The `temporary` flag indicates that it is a **temporary address used for privacy** (RFC 4941), meaning it is **randomized** to prevent tracking.

---


#### **4. Global Unicast Address (`2401:dd00:10:20:5dbf:e3fe:818d:71a7/64`)**

- **Address:** `2401:dd00:10:20:5dbf:e3fe:818d:71a7/64`
- **Scope:** Global
- **Interface:** `wlo1` (Wireless interface)
- **Meaning:**
    - Similar to the previous global address, but this one is likely the **main address assigned by DHCPv6** or SLAAC (Stateless Address Auto-Configuration).
    - The `mngtmpaddr` flag indicates that this is a **managed temporary address**, likely generated using **IPv6 Privacy Extensions**.
    - The `noprefixroute` flag suggests that **manual prefix routing is disabled** for this address.

---
#### 5. **IPv6 Default Gateway**

```
default via fe80::7269:5aff:fee4:a141 dev wlo1 proto ra metric 600 pref medium
```

- **Gateway: `fe80::7269:5aff:fee4:a141`** 
	-  This is the **IPv6 router’s link-local address**.
- **`dev wlo1`** : Traffic is routed through the **Wi-Fi interface (`wlo1`)**.
- **`proto ra`** : The gateway was obtained via **Router Advertisement (RA)** (part of IPv6 Neighbor Discovery Protocol).
- **Metric `600`** : Lower metric values indicate higher priority.
- **Preference: `medium`** - Default preference for this gateway.
<div style="page-break-after: always;"></div>

### **Conclusion**

| IPv6 Address                             | Type                       | Scope  | Purpose                                                   |
| ---------------------------------------- | -------------------------- | ------ | --------------------------------------------------------- |
| `::1/128`                                | Loopback                   | Host   | Self-communication within the device                      |
| `fe80::408f:e6c4:6503:821c/64`           | Link-Local                 | Link   | Used for local communication (non-routable)               |
| `2401:dd00:10:20:6b4f:8c2c:8d82:5b8c/64` | Global Unicast (Temporary) | Global | Randomized for privacy (internet-reachable)               |
| `2401:dd00:10:20:5dbf:e3fe:818d:71a7/64` | Global Unicast (Managed)   | Global | Main assigned IPv6 address (internet-reachable)           |
| fe80::7269:5aff:fee4:a141                | Default Gateway            | Link   | Forwards packets from the local network to other networks |



