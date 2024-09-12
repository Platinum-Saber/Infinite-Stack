Related : #nodejs #nodemon #hotreload #package #backend 

# Adding Nodemon for Hot Reloading

Nodemon is a utility that monitors for any changes in your source and automatically restarts your server, making the development process much smoother.

### Step 1: Install Nodemon

You can install Nodemon as a development dependency:

```
npm install --save-dev nodemon
```

<br>

### Step 2: Configure Nodemon

Add a new script in your `package.json` file:

```json
{
  "scripts": {
    "start": "node app.js",
    "dev": "nodemon app.js"
  }
}
```

<br>

### Step 3: Run your application with Nodemon

Now you can start your application in development mode using:

```
npm run dev
```

This will start your server with Nodemon, which will watch for file changes and restart the server automatically when changes are detected.

<br>

### Step 4 (Optional): Configure Nodemon

If you want to customize Nodemon's behavior, you can create a `nodemon.json` file in your project root:

```json
{
  "watch": ["app.js", "routes/", "models/"],
  "ext": "js,json",
  "ignore": ["node_modules/", "public/"],
  "exec": "node app.js"
}
```

This configuration tells Nodemon to:
- Watch the `app.js` file and the `routes/` and `models/` directories
- Watch for changes to files with .js and .json extensions
- Ignore the `node_modules/` and `public/` directories
- Execute `node app.js` when restarting the server

<br>

### Benefits of using Nodemon

1. Automatic server restarts: You don't need to manually stop and start your server after making changes.
2. Improved productivity: Allows you to focus on coding without the need for manual restarts.
3. Customizable: You can configure which files to watch, ignore, and what commands to run.

Remember, Nodemon is a development tool and should not be used in production environments. For production, you should use process managers like PM2 or Docker containers for managing your Node.js application.

