
### 1. **Flutter Frontend**

NutriMithu is built as a cross-platform mobile app using Flutter. It provides users with a smooth interface to:

- Log daily meals,
    
- Receive AI-generated dietary feedback,
    
- View real-time plate weight,
    
- Track nutrition metrics,
    
- Authenticate and sync user data with Firebase.
    

### 2. **Backend Services**

A FastAPI-based Python backend powers the business logic and data processing. It serves multiple roles:

- Handles user requests and communicates with AI models,
    
- Fetches localized food data from a PostgreSQL database,
    
- Receives real-time weight data from the smartplate,
    
- Routes user-specific data to Firebase Firestore for persistence.
    

An AI chatbot powered by NVIDIA’s `Palmyra Med-70B` is integrated into the backend to deliver expert-level nutritional advice contextualized for local food patterns. The chatbot responses will be further enhanced with a **vector database** to ensure contextual understanding of Sri Lankan dishes and ingredients.

### 3. **PostgreSQL Food Database**

A curated PostgreSQL database contains nutritional information for a wide range of Sri Lankan food items. The backend queries this database to support:

- Food logging,
    
- Calorie estimation,
    
- Macronutrient breakdown,
    
- Personalized recommendations.
    

### 4. **AI Integration with NVIDIA**

The AI assistant is accessed through NVIDIA's cloud API and is configured with a system prompt to act as a nutritional expert. Prompts from the user are sanitized, sent to the model, and streamed back to the client to ensure a responsive experience.

### 5. **Smartplate with IoT Integration**

The app connects with a **smartplate** embedded with a **weight sensor** and an **ESP32 microcontroller**. The ESP32:

- Reads live weight data from the plate,
    
- Sends it over Wi-Fi to the backend via REST or WebSocket protocols,
    
- Enables the app to estimate portion size and calorie intake in real time.