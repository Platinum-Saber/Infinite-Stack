Creating a React frontend for your Node.js backend with an SQL database is a great choice. Here's a step-by-step approach to get you started:

1. Set up a new React project:
   Use Create React App (CRA) or Vite to bootstrap your React project. For example, with CRA:

   ```
   npx create-react-app my-frontend
   cd my-frontend
   ```

2. Install necessary dependencies:
   You'll need a few additional packages to communicate with your backend:

   ```
   npm install axios react-router-dom
   ```

3. Set up API communication:
   Create a service to handle API calls to your backend. You can use Axios for this:

   ```javascript
   import axios from 'axios';

   const API_BASE_URL = 'http://your-backend-url:port';

   export const apiService = {
     get: (endpoint) => axios.get(`${API_BASE_URL}${endpoint}`),
     post: (endpoint, data) => axios.post(`${API_BASE_URL}${endpoint}`, data),
     // Add other methods as needed
   };
   ```

4. Create React components:
   Design and implement your UI components based on the data and functionality your backend provides.

5. Implement state management:
   For simple applications, you can use React's built-in useState and useContext hooks. For more complex state management, consider using Redux or MobX.

6. Set up routing:
   Use react-router-dom to handle navigation between different views in your application.

7. Connect to your backend:
   Use the apiService you created to fetch and send data to your backend from your React components.

8. Handle authentication:
   If your application requires user authentication, implement a login system and store tokens (e.g., JWT) for authenticated requests.

9. Implement error handling and loading states:
   Add proper error handling for API requests and show loading indicators when fetching data.

10. Style your components:
    Use CSS, CSS-in-JS solutions, or a UI library like Material-UI or Ant Design to style your components.

Would you like me to provide a more detailed example of any of these steps? For instance, I could show you how to create a basic component that fetches and displays data from your backend.