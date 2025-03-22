---
tags: 
Created: 2025-02-24 11:27
About: 
Reviewed: true
Completion: 30
---

## Status
Reviewed : `INPUT[toggle:Reviewed]`

Progress :  
```meta-bind
INPUT[progressBar:Completion]
```


## Topics Covered

- Functional and Non-functional Requirements
- The Software Requirements Document
- Requirements Specification
- Requirements Engineering Processes
- Requirements Elicitation and Analysis
- Requirements Validation
- Requirements Management

---

## **1. Introduction to Requirements Engineering**

### **What is Requirements Engineering?**

- The process of determining the services a system should provide and the constraints it must adhere to.
- Requirements include descriptions of system services and operational constraints.

### **Definition of a Requirement**

- Can be a high-level abstract statement or a detailed functional specification.
- May serve different functions:
    - Basis for a bid for contract (open to interpretation).
    - Basis for the contract itself (needs to be detailed).

---

## **2. Types of Requirements**

### **User vs. System Requirements**

|Type|Description|
|---|---|
|User Requirements|High-level statements, written in natural language for customers.|
|System Requirements|Detailed descriptions of system functions, used for contracts.|

### **Functional vs. Non-functional Requirements**

|Type|Description|
|---|---|
|Functional Requirements|Define what the system should do (e.g., user authentication).|
|Non-functional Requirements|Define constraints like performance, security, and usability.|
|Domain Requirements|Constraints from the application domain (e.g., legal regulations).|

### **Examples of Functional Requirements**

- A user should be able to search appointment lists.
- The system should generate daily reports for clinics.

### **Examples of Non-functional Requirements**

|Category|Example|
|---|---|
|Performance|System response time should be under 2 seconds.|
|Security|Users must authenticate using biometric login.|
|Availability|System downtime should not exceed 5 minutes per day.|

---

## **3. Requirements Engineering Processes**

### **Key Activities in RE**

1. **Requirements Elicitation** – Gathering requirements from stakeholders.
2. **Requirements Analysis** – Understanding and refining requirements.
3. **Requirements Validation** – Ensuring requirements are correct and complete.
4. **Requirements Management** – Managing requirement changes over time.

### **Elicitation Challenges**

- Stakeholders may not fully know what they need.
- Conflicting requirements from different stakeholders.
- Business and technology changes require continuous updates.

---

## **4. The Software Requirements Document**

### **Purpose**

- Official statement of system requirements.
- Not a design document – focuses on _what_ the system should do.

### **Standard Structure of a Requirements Document**

|Section|Description|
|---|---|
|Preface|Explains purpose, intended audience, and version history.|
|Introduction|Describes system purpose, objectives, and business context.|
|User Requirements|High-level description of user needs.|
|System Architecture|Overview of system components.|
|System Requirements|Detailed functional and non-functional requirements.|
|System Models|Diagrams like use-case models and data-flow diagrams.|
|System Evolution|Assumptions about future changes.|
|Appendices|Detailed information such as hardware and database requirements.|

### **Agile Methods and Requirements**

- Agile methods use _user stories_ instead of large requirement documents.
- Works well for business applications but not for highly regulated systems.

---

## **5. Writing Effective Requirements**

### **Best Practices**

- Use a standard format for consistency.
- Clearly distinguish between _mandatory_ and _desirable_ requirements.
- Avoid ambiguous language (e.g., instead of "fast response time," specify "response time < 2s").
- Justify the need for each requirement to avoid unnecessary features.

### **Examples of Well-Written Requirements**

|ID|Requirement|
|---|---|
|FR1|The system shall authenticate users using a unique 8-digit ID.|
|NFR1|The system shall handle up to 10,000 concurrent users.|

---

## **6. Requirements Validation**

### **Validation Methods**

|Method|Description|
|---|---|
|Requirements Reviews|Manual checking of requirements.|
|Prototyping|Creating mock-ups for user validation.|
|Test-Case Generation|Designing tests to verify requirements implementation.|

### **Common Validation Issues**

- **Ambiguity:** Requirements are open to multiple interpretations.
- **Inconsistency:** Conflicts between different requirements.
- **Unrealistic Expectations:** Requirements that cannot be practically implemented.

---

## **7. Requirements Management**

### **Why Manage Requirements?**

- Business and technical environments change after deployment.
- Requirements evolve due to regulatory changes, user needs, and technology upgrades.
- Ensures traceability between requirements and implementation.

### **Change Management Process**

1. **Problem Analysis** – Assess the impact of the requested change.
2. **Change Analysis & Costing** – Evaluate the feasibility of the change.
3. **Change Implementation** – Modify requirements and update the system accordingly.

### **Requirements Traceability**

- Links each requirement to design, implementation, and testing.
- Essential for maintaining system integrity during changes.

---

## **8. Requirements Elicitation Techniques**

### **Interviews**

- **Closed Interviews:** Predefined questions.
- **Open Interviews:** Exploratory discussions with stakeholders.

### **Scenarios & Use Cases**

- Provide real-life examples of system interactions.
- Example: _A doctor updates a patient's prescription after a consultation._

### **Observation & Ethnography**

- Watching users perform their tasks to gather implicit requirements.
- Helps in understanding real-world workflows and inefficiencies.

### **Prototyping**

- Creating early versions of the system to clarify requirements.
- Useful for gathering user feedback before full development.

---

## **9. Key Takeaways**

- **Requirements Engineering is critical** in defining system behavior and constraints.
- **Functional requirements specify what the system should do**, while **non-functional requirements define system properties.**
- **Requirements Engineering is an iterative process** involving elicitation, analysis, validation, and management.
- **Effective requirement documentation ensures clarity and prevents costly changes.**
- **Traceability and change management are essential** to maintain system integrity over time.

---

This study note provides a structured overview of Requirements Engineering. Let me know if you need any modifications or additional details!