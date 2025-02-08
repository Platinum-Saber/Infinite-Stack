## Initialize the react project

### 1. Run command
```shell
npm create vite@latest packet-sender -- --template react
```

- You will get something like this
> [!image] Shell
> ![[Pasted image 20241215135226.png]]
> 
> next use arrow keys to select "React"
> ![[Pasted image 20241215135423.png]]
>  
>  use arrow keys to select "JavaScript" 
>  ![[Pasted image 20241215135609.png]]

### 2. Run Command
```shell
cd packet-sender 
npm install
```

> [!image] Shell
> ![[Pasted image 20241215135952.png]]

### 3. Run Command

#### Add Tailwind CSS to your project:
```shell
npm install -D tailwindcss postcss autoprefixer
npx tailwindcss init -p
```

> [!image] VS Code
> ![[Pasted image 20241215140158.png]]
> ![[Pasted image 20241215140238.png]]

#### Now configure Tailwind. Update `tailwind.config.js` like this:
```js
/** @type {import('tailwindcss').Config} */
export default {
  content: [
    "./index.html",
    "./src/**/*.{js,ts,jsx,tsx}",
  ],
  theme: {
    extend: {},
  },
  plugins: [],
}
```

#### Add Tailwind directives to your CSS file  `src/index.css`
```css
@tailwind base;
@tailwind components;
@tailwind utilities;
```

> [!image] VS Code
> ![[Pasted image 20241215141217.png]]



## Create the UI

#### Replace the content of `App.jsx` with the following:
```jsx
import { useState } from "react";

function App() {
  const [file, setFile] = useState(null);
  const [inputFileType, setInputFileType] = useState("");
  const [outputFileType, setOutputFileType] = useState("");
  const [sendMethod, setSendMethod] = useState("");
  const [output, setOutput] = useState("");

  const fileTypes = ["video", "audio", "text", "image"];

  const handleSubmit = (e) => {
    e.preventDefault();

    if (!file || !inputFileType || !outputFileType || !sendMethod) {
      setOutput("Please fill in all fields");
      return;
    }

    setOutput(
      `✅ File "${file.name}" (${inputFileType}) sent successfully via ${sendMethod}.\nOutput file type: ${outputFileType}`
    );
  };

  return (
    <div className="min-h-screen bg-gray-50 flex items-center justify-center">
      <div className="bg-white shadow-lg rounded-lg p-8 w-full max-w-2xl">
        {/* Header */}
        <h1 className="text-3xl font-bold mb-6 text-center text-gray-800">
          Packet Sender
        </h1>

        {/* Form */}
        <form onSubmit={handleSubmit} className="space-y-6">
          {/* File Upload */}
          <div>
            <label htmlFor="file" className="block text-lg font-semibold mb-2 text-gray-700">
              Select File
            </label>
            <input
              id="file"
              type="file"
              onChange={(e) => setFile(e.target.files[0] || null)}
              className="w-full border rounded-md p-3 text-gray-700"
            />
          </div>

          {/* Input File Type */}
          <div>
            <label htmlFor="inputFileType" className="block text-lg font-semibold mb-2 text-gray-700">
              Input File Type
            </label>
            <select
              id="inputFileType"
              onChange={(e) => setInputFileType(e.target.value)}
              className="w-full border rounded-md p-3 text-gray-700 bg-white"
              defaultValue=""
            >
              <option value="" disabled>
                Select input file type
              </option>
              {fileTypes.map((type) => (
                <option key={type} value={type}>
                  {type.charAt(0).toUpperCase() + type.slice(1)}
                </option>
              ))}
            </select>
          </div>

          {/* Output File Type */}
          <div>
            <label htmlFor="outputFileType" className="block text-lg font-semibold mb-2 text-gray-700">
              Output File Type
            </label>
            <select
              id="outputFileType"
              onChange={(e) => setOutputFileType(e.target.value)}
              className="w-full border rounded-md p-3 text-gray-700 bg-white"
              defaultValue=""
            >
              <option value="" disabled>
                Select output file type
              </option>
              {fileTypes.map((type) => (
                <option key={type} value={type}>
                  {type.charAt(0).toUpperCase() + type.slice(1)}
                </option>
              ))}
            </select>
          </div>

          {/* Send Method */}
          <div>
            <label className="block text-lg font-semibold mb-2 text-gray-700">Send Method</label>
            <div className="flex items-center space-x-8">
              <label className="flex items-center space-x-2 text-gray-700">
                <input
                  type="radio"
                  value="Blade RF"
                  name="sendMethod"
                  onChange={(e) => setSendMethod(e.target.value)}
                  className="w-5 h-5 accent-blue-600"
                />
                <span>Blade RF</span>
              </label>
              <label className="flex items-center space-x-2 text-gray-700">
                <input
                  type="radio"
                  value="Virtual Sink"
                  name="sendMethod"
                  onChange={(e) => setSendMethod(e.target.value)}
                  className="w-5 h-5 accent-blue-600"
                />
                <span>Virtual Sink</span>
              </label>
            </div>
          </div>

          {/* Submit Button */}
          <button
            type="submit"
            className="w-full bg-blue-600 text-white font-bold py-3 rounded-lg hover:bg-blue-700 transition"
          >
            Send Packet
          </button>
        </form>

        {/* Output Display */}
        <div className="mt-8">
          <h2 className="text-lg font-bold mb-2 text-gray-700">Output</h2>
          <div className="w-full min-h-[80px] border rounded-md p-4 bg-gray-100 text-gray-800">
            {output || "Output will be displayed here..."}
          </div>
        </div>
      </div>
    </div>
  );
}

export default App;
```

## Run 

```shell
npm run dev
```

> [!image] VS Code
> ![[Pasted image 20241215141016.png]]

- Click on the link http://localhost:5173/

> [!image] Browser
> ![[Pasted image 20241215141420.png]]

