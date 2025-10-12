# React Lighting Control App for ESP32

This guide provides a React application to control and monitor the ESP32-based musical lighting system, using JSX, WebSocket, and Tailwind CSS. The app connects to the ESP32’s WebSocket server (from the previous firmware) to send pattern commands and display the current pattern and bass energy.

## Prerequisites

- **Node.js**: Version 16 or higher (install from [nodejs.org](https://nodejs.org/)).
- **ESP32**: Running the firmware from the previous response, connected to your local Wi-Fi network, with a known IP address (e.g., `192.168.1.100`).
- **Local Network**: Ensure your computer and ESP32 are on the same Wi-Fi network.

## Step 1: Set Up the React Project

1. **Create a React App**:
    
    ```bash
    npx create-react-app lighting-control
    cd lighting-control
    ```
    
2. **Install Dependencies**:
    
    - Tailwind CSS for styling.
    - No additional WebSocket library is needed (JavaScript’s `WebSocket` API is sufficient).
    
    ```bash
    npm install tailwindcss postcss autoprefixer
    npx tailwindcss init -p
    ```
    
3. **Configure Tailwind CSS**:
    - Edit `tailwind.config.js`:
        
        ```javascript
        /** @type {import('tailwindcss').Config} */
        module.exports = {
          content: ["./src/**/*.{js,jsx,ts,tsx}"],
          theme: { extend: {} },
          plugins: [],
        };
        ```
        
    - Replace `src/index.css` with:
        
        ```css
        @tailwind base;
        @tailwind components;
        @tailwind utilities;
        ```
        
4. **Clean Up**:
    - Remove `src/App.css` and `src/logo.svg`.
    - Simplify `src/App.js` (we’ll replace it later).

## Step 2: React App Code

Below is the JSX-based React app structure, split into components for modularity.

### Directory Structure

```
lighting-control/
├── public/
│   ├── index.html
├── src/
│   ├── components/
│   │   ├── ControlPanel.jsx
│   │   ├── StatusDisplay.jsx
│   ├── App.jsx
│   ├── index.js
│   ├── index.css
├── package.json
├── tailwind.config.js
├── postcss.config.js
```

### `src/index.js`

This is the entry point, rendering the app.

```js
import React from 'react'; import ReactDOM from 'react-dom/client'; import './index.css'; import App from './App';

const root = ReactDOM.createRoot(document.getElementById('root'));  
root.render(  
<React.StrictMode>  
  
</React.StrictMode>  
);
```

### `src/app.jsx`
```jsx
import React, { useState, useEffect } from 'react';
import ControlPanel from './components/ControlPanel';
import StatusDisplay from './components/StatusDisplay';

function App() {
  const [ws, setWs] = useState(null);
  const [status, setStatus] = useState({ pattern: 'OFF', bassEnergy: 0 });

  useEffect(() => {
    const websocket = new WebSocket('ws://192.168.1.100/ws'); // Replace with ESP32 IP
    setWs(websocket);

    websocket.onmessage = (event) => {
      const data = JSON.parse(event.data);
      setStatus({ pattern: data.pattern, bassEnergy: data.bassEnergy });
    };

    websocket.onopen = () => console.log('WebSocket connected');
    websocket.onclose = () => console.log('WebSocket disconnected');
    websocket.onerror = (error) => console.error('WebSocket error:', error);

    return () => websocket.close();
  }, []);

  const sendCommand = (command) => {
    if (ws && ws.readyState === WebSocket.OPEN) {
      ws.send(command);
    }
  };

  return (
    <div className="min-h-screen bg-gray-100 flex items-center justify-center p-4">
      <div className="bg-white p-6 rounded-lg shadow-lg w-full max-w-lg">
        <h1 className="text-2xl font-bold mb-6 text-center">Lighting Control</h1>
        <ControlPanel sendCommand={sendCommand} />
        <StatusDisplay status={status} />
      </div>
    </div>
  );
}

export default App;
```


### `src/components/ControlPanel.jsx`
```jsx
import React from 'react';

function ControlPanel({ sendCommand }) {
  return (
    <div className="grid grid-cols-2 gap-4 mb-6">
      <button
        className="bg-red-500 text-white py-2 rounded hover:bg-red-600 transition"
        onClick={() => sendCommand('off')}
      >
        Off
      </button>
      <button
        className="bg-green-500 text-white py-2 rounded hover:bg-green-600 transition"
        onClick={() => sendCommand('all_on')}
      >
        All On
      </button>
      <button
        className="bg-blue-500 text-white py-2 rounded hover:bg-blue-600 transition"
        onClick={() => sendCommand('chase')}
      >
        Chase
      </button>
      <button
        className="bg-purple-500 text-white py-2 rounded hover:bg-purple-600 transition"
        onClick={() => sendCommand('audio_reactive')}
      >
        Audio Reactive
      </button>
    </div>
  );
}

export default ControlPanel;
```

### `src/components/StatusDisplay.jsx`
```jsx
import React from 'react';

function StatusDisplay({ status }) {
  return (
    <div className="text-center">
      <p className="text-lg mb-2">
        Current Pattern: <span className="font-semibold">{status.pattern}</span>
      </p>
      <p className="text-lg mb-4">
        Bass Energy: <span className="font-semibold">{status.bassEnergy.toFixed(2)}</span>
      </p>
      <div className="w-full bg-gray-200 rounded-full h-4">
        <div
          className="bg-blue-500 h-4 rounded-full"
          style={{ width: `${Math.min(status.bassEnergy * 2, 100)}%` }} // Scale for visualization
        ></div>
      </div>
    </div>
  );
}

export default StatusDisplay;
```

## Step 3: Configure and Run the App
1. **Update WebSocket URL**:
   - In `src/App.jsx`, replace `ws://192.168.1.100/ws` with your ESP32’s IP address (from the Serial Monitor).
2. **Run the App**:
   ```bash
   npm start
   ```
   - The app will open at `http://localhost:3000`.
3. **Test**:
   - Ensure the ESP32 is powered on and connected to Wi-Fi.
   - Click the buttons (Off, All On, Chase, Audio Reactive) to send commands.
   - Verify the pattern and bass energy update in real-time.
   - Check the bass energy bar scales with music input (in audio-reactive mode).

## Step 4: Deploy the App (Optional)
To make the app accessible at the event:
1. **Build the App**:
   ```bash
   npm run build
   ```
   - This creates a `build/` folder with static files.
2. **Serve Locally**:
   - Use a simple server (e.g., `npx serve -s build`).
   - Access the app on your network (e.g., `http://YOUR_COMPUTER_IP:3000`).
3. **Event Use**:
   - Host on a laptop or Raspberry Pi at the event.
   - Share the URL with event staff (ensure they’re on the same Wi-Fi).

## Features
- **Control**: Buttons to select patterns (Off, All On, Chase, Audio Reactive).
- **Monitoring**: Displays current pattern and bass energy.
- **Visualizer**: A progress bar for bass energy (scales 0–50 to 0–100%).
- **Responsive**: Tailwind CSS ensures mobile and desktop compatibility.

## Enhancements
- **Sensitivity Slider**: Add a slider to adjust audio sensitivity (requires ESP32 firmware update).
- **Pattern Customization**: Allow users to define custom sequences via the app.
- **Error Handling**: Show connection status (e.g., “Disconnected” if WebSocket fails).
- **Authentication**: Add a password for WebSocket access on public networks.

## Troubleshooting
- **WebSocket Connection**:
  - Verify the ESP32 IP and ensure port 80 is open.
  - Check console logs in the browser’s DevTools.
- **Bass Energy**:
  - If updates are slow, reduce the ESP32’s `delay(50)` in `loop()`.
  - Adjust the scaling in `StatusDisplay.jsx` if the bar doesn’t respond well.
- **CORS**: If hosting on a different server, ensure the ESP32 allows cross-origin WebSocket requests.

</xaiArtifact>

### Instructions
1. **Set Up**:
   - Install Node.js and create the React project as described.
   - Copy the provided files into the `src/` and `public/` folders.
   - Install dependencies and configure Tailwind CSS.
2. **Run**:
   - Start the ESP32 and note its IP.
   - Update `App.jsx` with the correct WebSocket URL.
   - Run `npm start` and test the app.
3. **Event**:
   - Build and serve the app for event use.
   - Test with music to ensure audio-reactive mode works.

This React app is more maintainable and scalable than the previous HTML-based version. If you want additional features (e.g., a sensitivity slider, custom patterns, or Next.js instead), let me know, Cryo! Keep rocking the lighting system, Brock’s here for you! 😎