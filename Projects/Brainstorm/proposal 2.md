

### **NutriMithu – AI-Powered Nutrition & Smartplate App for Sri Lankan Lifestyles**

**Overview:**

**NutriMithu** is a smart, culturally-aware nutrition app tailored for the dietary habits of Sri Lankan users. Combining AI guidance, local food tracking, and hardware integration, the app promotes healthy eating through personalized plans and real-time food monitoring. It bridges the gap between everyday meals and nutritional awareness, using modern technology to empower healthier lifestyles.

**Key Features:**

- **Localized Food Intelligence:**  A curated set of Sri Lankan meals with localized calorie and nutrient estimates are stored in a **PostgreSQL database** and served via a **Python FastAPI backend**.

-  **AI Nutrition Assistant:** Integrated with NVIDIA’s **Palmyra Med-70B** model to provide intelligent, conversational responses on diet and health.

-  **Personalized Meal Planning:** Automatically adjusts daily nutrition plans based on user profile, preferences, and health conditions.

-  **Smart-plate Integration:** Connected to a **weight sensor-equipped plate** powered by an **ESP32 microcontroller**, allowing real-time measurement of food quantity to enhance calorie tracking.

- **Secure Cloud Backend:** Built with Firebase Authentication and Firestore for real-time data storage and user management.

-  **Modern Flutter UI:** Smooth multi-step onboarding, reusable UI components, and responsive design for an engaging user experience.


```mermaid
graph TD
    subgraph User Interface
        A1[Flutter Mobile App]
    end

    subgraph Backend Services
        B1[FastAPI Server]
        B2[PostgreSQL Food Database]
        B3[NVIDIA AI Chatbot]
        B4[Firebase Authentication & Firestore]
        B5[Vector Database]
    end

    subgraph IoT Hardware
        C1[Smartplate]
        C2[ESP32 Microcontroller]
        C3[Weight Sensor]
    end

    %% Connections
    A1 -->|Send user queries| B1
    B1 -->|Fetch food data| B2
    B1 -->|Send prompt & receive response| B3
    A1 -->|User auth & data sync| B4
    B1 -->|Similarity search| B5
    A1 -->|Display real-time weight| C2
    C2 -->|Read weight data| C3
    C2 -->|Send weight data via Wi-Fi| B1

    %% Styling
    classDef hardware fill:#fef3c7,stroke:#facc15,stroke-width:2px;
    classDef backend fill:#e0f2fe,stroke:#3b82f6,stroke-width:2px;
    classDef frontend fill:#e0ffe0,stroke:#10b981,stroke-width:2px;

    class A1 frontend;
    class B1,B2,B3,B4,B5 backend;
    class C1,C2,C3 hardware;

```