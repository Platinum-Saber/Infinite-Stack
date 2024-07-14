>[!FAQ]- What is an **Agent**
>An entity that can **Perceives** its'  **Environment** through **Sensors** and acts upon the environment through **Actuators**

>[!example]- Examples for Agents
>![[Pasted image 20240708102629.png]]
>![[Pasted image 20240708102646.png]]
>![[Pasted image 20240708102703.png]]

<br>
<br>

### The Agent Function
>[!FAQ]- What is an **Agent Function**
>The function of mapping the agent's ***perception sequence*** to an action.

>[!info]- **Perception Sequence**
>The complete history of everything an agent has perceived so far.

>[!info]- **Agent Program**
>The implementation of the agent function

>[!tip] The effectiveness of the agent program is measured through a **performance measure**



<br>
<br>

### Agent Program 
>[!abstract]- Agent Program Types
>- Simple Reflex agents
>- Model - based agents
>- Goal - based agents
>- Utility - based agents

<br>

>[!note]- **Simple Reflex Agent**
>- Simplest kind of agent.
>>[!warning] Actions depend only on **present percepts**. Ignores the **history**.
>- Has limited intelligence.
>- Works best in an **observable environment.**
>
>![[Pasted image 20240708105128.png]]

>[!note]- **Model-based Reflex Agent**
>>[!warning] Maintains an **internal state** that depends on the **perception history.**
>
>- Useful in a **partially observable environments**
>- Requires to store 2 kinds of knowledge to maintain the internal state
>	- `Transition model` of the world. (how the world works)
>	- `Sensor model` (how the state of the world is reflected in the agent's percepts)
>
>![[Pasted image 20240708110207.png]]

>[!note]- **Goal-based Agents**
>- Combines **prior knowledge** and **perceptions** and takes actions to **achieve a goal** 🥅 
>- More flexible than reflex agents. (Changing the goal will change the actions appropriately)
>
>![[Pasted image 20240708110747.png]]

>[!note]- **Utility-based Agents**
>>[!warning] Maps a state or sequence of states onto a real number
>
>- Describes the **degree of happiness**.
>- Is used in cases where goals are inadequate.
>	- Conflicting goals (utility function specifies a tradeoff)
>	- Choosing a best fit out of many options
>
>![[Pasted image 20240708111359.png]]

<br>

#### Learning Agents
>[!abstract]- Components  of **Learning Agents**
>>[!info]- Performance Element
>>Takes in percepts and decides on actions
>
>>[!info]- Critic
>>Evaluates how the agent is performing and gives feedback 
>
>>[!info]- Learning Element
>>Takes feedback from the *Critic* and modifies the *performance element* to do better in the future.
>
>>[!info]- Problem Generator
>>Suggests exploratory actions leading to new and informative experiences. (learn through mistakes)
>
>![[Pasted image 20240708112427.png]]


