
### 📚 Key Papers & Reviews

#### 1. **“Multi‑Robot System for Cooperative Exploration in Unknown Environments: A Survey”**

A state‑of‑the‑art survey (arXiv, March 2025, revised May 2025) covering cooperative exploration by multi‑robot systems, including modules for mapping, localization, map merging, task allocation, and communication limitations. Discusses use cases like the DARPA SubT Challenge. ([Reddit](https://www.reddit.com/r/robotics/comments/qqxsnb?utm_source=chatgpt.com "What is the current state of the art in term of collaborative robotics between *robots only*"), [arXiv](https://arxiv.org/abs/2503.07278?utm_source=chatgpt.com "[2503.07278] Multi-Robot System for Cooperative Exploration in Unknown Environments: A Survey"))  


#### 2. **“Towards Collaborative Simultaneous Localization and Mapping: a Survey of the Current Research Landscape”**

Comprehensive review (Aug 2021) of collaborative SLAM (C‑SLAM), covering decentralized vs centralized architectures, communication challenges, scalability, and open research directions. Great conceptual foundation. ([arXiv](https://arxiv.org/abs/2108.08325?utm_source=chatgpt.com "Towards Collaborative Simultaneous Localization and Mapping: a Survey of the Current Research Landscape"))  


#### 3. **“Swarm‑SLAM: Sparse Decentralized Collaborative SLAM Framework for Multi‑Robot Systems”**

A practical and scalable decentralized SLAM system (Jan 2023), supporting lidar, stereo, RGB‑D sensors, with inter‑robot loop closure prioritization to reduce communication load. ROS‑2 implementation and open‑source code shared. ([arXiv](https://arxiv.org/abs/2301.06230?utm_source=chatgpt.com "Swarm-SLAM : Sparse Decentralized Collaborative Simultaneous Localization and Mapping Framework for Multi-Robot Systems"))  


#### 4. **“Collaborative Robot Mapping using Spectral Graph Analysis”**

Proposes a graph‑spectral method (Mar 2022) to align onboard pose graphs with a central server’s global map, mitigating drift and inconsistencies. Demonstrated up to 90% improvement in real multi‑robot deployments. ([arXiv](https://arxiv.org/abs/2503.07278?utm_source=chatgpt.com "[2503.07278] Multi-Robot System for Cooperative Exploration in Unknown Environments: A Survey"), [arXiv](https://arxiv.org/abs/2203.00308?utm_source=chatgpt.com "Collaborative Robot Mapping using Spectral Graph Analysis"))  


#### 5. **“Multi‑Robot Mapping Based on 3D Maps Integration”**

A 2022 book chapter describing feature‑based alignment and integration of local 3D occupancy maps produced independently by multiple robots. Doesn’t require an initial transformation guess. Valuable for large‑scale rough terrain mapping. ([IntechOpen](https://www.intechopen.com/chapters/84082?utm_source=chatgpt.com "Multi-Robot Mapping Based on 3D Maps Integration | IntechOpen"))  


#### 6. **“Distributed Cooperative Outdoor Multi‑robot Localization and Mapping”**

A classic (2004) paper using distributed Extended Kalman Filtering for cooperative localization and terrain elevation mapping by robot teams. Demonstrates early multi‑robot mapping outdoors. ([IntechOpen](https://www.intechopen.com/chapters/84082?utm_source=chatgpt.com "Multi-Robot Mapping Based on 3D Maps Integration | IntechOpen"), [SpringerLink](https://link.springer.com/article/10.1023/B%3AAURO.0000032936.24187.41?utm_source=chatgpt.com "Distributed Cooperative Outdoor Multirobot Localization and Mapping | Autonomous Robots"))  


#### 7. **“Aerial and Ground Robot Collaboration for Autonomous Mapping in Search and Rescue Missions”**

Presents an integrated UAV + mobile ground robot system (year 2024) for collaborative terrain mapping in rescue scenarios. Highlights stereo disparity, 3D reconstruction, and cooperation protocols. ([MDPI](https://www.mdpi.com/2504-446X/4/4/79?utm_source=chatgpt.com "Aerial and Ground Robot Collaboration for Autonomous Mapping in Search and Rescue Missions"))  


#### 8. **“Collaborative Mobile Robotics for Semantic Mapping: A Survey”**

An overview (2022) of multi‑robot collaboration specifically for _semantic mapping_, blending geometry with semantic labels. Covers data‑fusion, coordination architectures, challenges in multi‑robot semantic integration. ([MDPI](https://www.mdpi.com/2076-3417/12/20/10316?utm_source=chatgpt.com "Collaborative Mobile Robotics for Semantic Mapping: A Survey"))  


---

### 🧠 Summary Table

|Paper / Survey|Focus|Why It’s Useful|
|---|---|---|
|_Survey 2025: Cooperative Exploration_|Map merging, communication, coordination|Latest trends in collaborative systems ([arXiv](https://arxiv.org/abs/2503.07278?utm_source=chatgpt.com "[2503.07278] Multi-Robot System for Cooperative Exploration in Unknown Environments: A Survey"))|
|_C-SLAM Landscape Survey_|Core challenges and architectures|Solid theoretical grounding|
|_Swarm-SLAM_|Open-source decentralized SLAM|Real-world ROS‑2 implementation|
|_Spectral Graph Analysis_|Global-map alignment via graph spectral features|Efficient drift mitigation|
|_3D Map Integration_|Feature-based map merging across agents|Useful for terrain beyond the visible spectrum|
|_Distributed EKF Mapping (2004)_|Early cooperative terrain mapping setup|Classical method in outdoor terrain mapping|
|_UAV + Ground Collaboration_|Heterogeneous platform 3D mapping|Relevant to mixed systems and UAV support|
|_Semantic Collaborative Mapping_|Multi-robot semantic data fusion|Adds context understanding to terrain mapping|

---

### ✅ How to Use These in Your Research

- **For theory and structure**: Start with the surveys (_Survey 2025_ and _C‑SLAM Survey_) to grasp terminology, architecture types, and core challenges.
    
- **For implementation strategies**: Dive into _Swarm‑SLAM_ and the spectral graph approach—both report real-world results.
    
- **For multi-model or heterogeneous systems**: Use the UAV/ground robot paper and the semantic mapping survey to understand coordination across platforms and map layers.
    
- **For historical perspective**: The 2004 distributed EKF paper offers insight into foundational distributed terrain mapping methods.
    
