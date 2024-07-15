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

### Performance Measures
>[!FAQ]- What is a **Performance Measure**
>It's the criteria used to evaluate the agent's success/effectiveness in achieving its goals or completing its tasks.
>- `Consequentialism`  : Evaluating an agent's behavior by it's consequences.

>[!tip] Design the performance measure according to **What we want in the environment** and not *how we think the agent should behave*

<br>
<br>

### Rational Agent
>[!note]- Definition
>For each possible percept sequence, a rational agent should select an action that is expected to maximize its performance measure, given the evidence provided by the percept sequence and whatever built in knowledge an agent has. 

>[!note]- Perfect Rationality
>- Assumes the agent knows everything.
>- Will always take the action that *maximizes its utility*

>[!note]- Bounded Rationality
>- Proposed by Herbert Simon in 1958.
>- Limited by the information it has
>- Uses **approximate** methods to handle many tasks 
>- Similar to how the human mind works

>[!info]- **Rational Action**
>The action that maximizes the expected value of the performance measure given the percept sequence to date.

>[!tip] A rational agent always does the *right thing*

<br>
<br>

### Omniscience, Learning, and Autonomy
>[!info]- Omniscience
>The agent who knows about the ACTUAL outcome of its actions and acts accordingly.

>[!note]- Rationality
>- The agent who maximizes the EXPECTED outcome
>- Doesn't have to be omniscient
>- The rational choice depends only on the percept sequence to date
>  
>  >[!tip] This requires a rational agent to gather information and learn from perceptions.

>[!tip] If an agent's actions depend more on its own experience it's **More autonomous**

>[!tip] If an agents actions depend more on knowledge of the environment that has been built in by the designer is **Less autonomous **

<br>
<br>

### Task Environment
>[!FAQ]- What is a **Task Environment**
>It defines the problems to which the rational agents attempt to provide solutions.

>[!abstract]- **PEAS** of a Task Environment
>- Performance Measure
>- Environment
>- Actuators
>- Sensors
>
>>[!example]- Example (Automated Taxi Driver)
>>![[Pasted image 20240714234830.png]]

>[!tip] The first step of designing an agent must always be to specify the task environment as fully as possible.

<br>

#### Properties of Task Environments
1. >[!note]- Single Agent 🆚 Multi Agent
>- `Single-agent` :   If a task is done solely by one agent. (ex:- an agent solving a crossword puzzle)
>- `Multi-agent` :  If a task is handled by more than one agent. (automated taxi driving)
>	- **Multi-agent Environments**
>		- *Competitive* (one agent trying to maximize its performance measure causes to minimize another agent)
>		- *Cooperative* (one agent trying to maximize its performance also causes to maximize another)

2. >[!note]- Deterministic 🆚 Nondeterministic 🆚 Stochastic
>- Whether the next state of the environment is completely determined by the current state and the actions executed by the agents or not.
>- *Stochastic* :  When the environment explicitly deals with probabilities.

3. >[!note]- Episodic 🆚 Sequential
>- `Episodic environment`
>	- Agent's experience is divided into atomic episodes.
>	- Each episode consists of the agent perceiving and performing a single action.
>	- Episodic actions are simpler because the agent doesn't **think ahead**
>	>[!warning] Next episode doesn't depend on the actions taken in the previous.
>	
>- `Sequential environment` 
>	- The current decision could affect all future decisions.
>	- ex :- chess, taxi driving

4. >[!note]- Dynamic 🆚 Static
>- Whether the environment can change while the agent's deliberating or not.
>- Dynamic --> Taxi driving
>- Static --> Crossword puzzle

5. >[!note]- Discrete 🆚 Continuous
>- Apply to the state of the environment, the way time is handled, and the percepts and actions of the agent



<br>
<br>

# The Structure of Agents
>[!FAQ]- What is an **Agent Program**
>The mapping of the percepts to action.

>[!FAQ]- What is **Agent Architecture**
>The computing device with physical sensors and actuators on which the agent program runs.

>[!tip] Agent = Architecture + Program

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

#### How does the components of an **agent program** work
>[!info]- The representation in the order of increasing complexity and expressive power are *atomic < factored < structured*
>![[Pasted image 20240715154311.png]]

>[!abstract]- Atomic representation
>- A state is a black box with no internal structure
>- Algorithms
>	- Standard searching algorithm
>	- Hidden Markov Models
>	- Markov Decision processes.
>
> ![[Pasted image 20240715154653.png]]


