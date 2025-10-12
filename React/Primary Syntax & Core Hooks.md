
## Table of Contents
- React Basics
  - JSX
  - Components
  - Props
  - State
- Core Hooks
  - useState
  - useEffect
  - useContext
  - useReducer
  - useRef
  - useMemo / useCallback
- Additional Notes

---

## React Basics

### JSX
> [!info] What is JSX?
> **JSX** is a syntax extension to JavaScript that looks like HTML, but compiles to `React.createElement`.

```jsx
function Hello() {
  return <h1>Hello, world!</h1>;
}


* Embeds JS: `{2+2}` → 4
* Attributes use **camelCase**: `className`, `onClick`.

```


``
### Components

> [!note] Two types
>
> * **Function components** (modern, hooks-based)
> * **Class components** (legacy, rarely used now)

```jsx
function Welcome(props) {
  return <h1>Hello, {props.name}</h1>;
}
```

---

### Props

> [!tip] Props are immutable
> They are **read-only inputs** passed from parent to child.

```jsx
function Button({label}) {
  return <button>{label}</button>;
}
```

---

### State

> [!warning] State is local
> Unlike props, **state belongs to the component** and can change.

```jsx
import { useState } from "react";

function Counter() {
  const [count, setCount] = useState(0);
  return (
    <button onClick={() => setCount(count+1)}>
      {count}
    </button>
  );
}
```

---

## Core Hooks

### useState

* Adds local state to function components.
* Returns `[value, setter]`.

✔ **Benefits:** Simple, readable.
⚠ **Disadvantages:** Only local, no sharing.

---

### useEffect

> [!info] Side Effects
> `useEffect` runs after render. Used for **fetching data, subscriptions, DOM manipulations**.

```jsx
import { useState, useEffect } from "react";

function Timer() {
  const [seconds, setSeconds] = useState(0);

  useEffect(() => {
    const id = setInterval(() => setSeconds(s => s+1), 1000);
    return () => clearInterval(id); // cleanup
  }, []); // [] → run once

  return <p>Time: {seconds}</p>;
}
```

✔ Handles async tasks.
⚠ Overuse can cause performance issues.

---

### useContext

* Shares data across tree without props drilling.

```jsx
const ThemeContext = React.createContext("light");

function App() {
  return (
    <ThemeContext.Provider value="dark">
      <Toolbar />
    </ThemeContext.Provider>
  );
}

function Toolbar() {
  const theme = React.useContext(ThemeContext);
  return <div>Theme: {theme}</div>;
}
```

---

### useReducer

* Alternative to useState for complex logic.

```jsx
function reducer(state, action) {
  switch (action.type) {
    case "increment": return {count: state.count+1};
    default: return state;
  }
}
const [state, dispatch] = useReducer(reducer, {count:0});
```

---

### useRef

* Persistent mutable value, doesn’t trigger re-renders.

```jsx
const inputRef = useRef(null);
<input ref={inputRef} />
```

---

### useMemo & useCallback

* **useMemo**: memoize computed value.
* **useCallback**: memoize function.

```jsx
const memoizedValue = useMemo(() => slowFn(x), [x]);
const memoizedHandler = useCallback(() => doSomething(), []);
```

---

