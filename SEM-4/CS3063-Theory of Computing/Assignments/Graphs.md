---
tags: 
Created: 2025-05-05 19:19
About: 
Reviewed: false
Completion: 0
---
```mermaid
stateDiagram-v2
    [*] --> q0
    q0 --> q1 : a
    q0 --> q2 : b
    q1 --> q0 : b
    q1 --> q3 : a
    q2 --> q0 : a
    q2 --> q3 : b
    q3 --> q3 : a,b

    state q0 <<accept>>
```




