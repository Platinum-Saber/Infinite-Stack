---
tags: 
Reviewed: 
Created: 2024-09-04T13:41:00
About: Based on CS2033-Lecture 03 Encoding and Modulation. This chapter from "Encoding and Modulation" delves into the methods used to encode and modulate data for effective communication. It explains how digital and analog signals can represent data, the advantages and limitations of various encoding techniques, and the role of modulation in transmitting signals over different mediums.
---
Related : #Networking #Networking/03 #Encoding #Modulation 

---
# Content
1. [[#Encoding Techniques]]
2. [[#Digital Data, Digital Signal]]
3. [[#]]


# Encoding Techniques
> [!abstract]- Glossary
> - **Unipolar** : All signal elements have same sign
> - **Polar**       : One logic state represented by positive voltage the other by negative voltage.
> - **Data rate** : Rate of data transmission on bits per second.
> - 

- [[#Digital data, Digital signal]]  
- [[#Analog data, digital signal]] 
- [[#Digital data, analog signal]] ****
- [[#Analog data, analog signal]]


<br>

# Digital data, Digital signal  

> [!NOTE]- Signal Characteristics
> 
> - **Digital Signal:** Consists of discrete, discontinuous voltage pulses. Each pulse is a signal element representing binary data.
> 
> - **Unipolar Encoding:** All signal elements have the same sign (e.g., positive voltage for binary 1, zero voltage for binary 0). It’s simple but has limitations such as a DC component, which can cause synchronization issues.
> 
> - **Polar Encoding:** Utilizes both positive and negative voltages. One logic state is represented by a positive voltage, and the other by a negative voltage. Polar encoding can improve synchronization by providing clearer transitions between states.

## NRZ Encoding

> [!info]-  NRZ-L (Nonreturn to Zero-Level)
>  A type of **polar encoding** where *two different voltages represent binary 0 and 1*. 
>  The voltage **remains constant** during the bit interval, and there's **no return to zero voltage** between bits. 
>  This method is straightforward but can lead to synchronization problems due to the lack of transitions in long sequences of identical bits.

> [!info]- NRZI (Nonreturn to Zero Inverted)
> -  An enhancement of NRZ-L. 
> - **Instead of using constant voltage levels**, NRZI encodes binary *1 by transitioning the voltage at the start of the bit interval*, while binary *0 is represented by no transition*. This method improves synchronization but still has some limitations, especially in complex transmission systems.

<br>

## Differential Encoding:

- **Concept:** In differential encoding, data is represented by changes in the signal rather than the signal levels themselves. This approach is more robust because detecting a transition is generally more reliable than detecting a specific voltage level.
- **Pros:** Improved reliability in detecting transitions.
- **Cons:** Potentially complex, especially in environments with multiple signal paths where polarity could be lost.

## Multilevel Binary Encoding:

- **Bipolar-AMI (Alternate Mark Inversion):** Uses more than two voltage levels. Binary 0 is represented by no signal, while binary 1 is represented by alternating positive and negative pulses. This method avoids a DC component and is effective for error detection.
- **Pseudoternary:** Opposite to Bipolar-AMI, where binary 1 is represented by the absence of a signal and binary 0 by alternating positive and negative pulses.

**Trade-offs:**

- Multilevel encoding schemes are less efficient than NRZ because they require distinguishing between multiple signal levels, which increases the likelihood of errors. Additionally, they require more signal power to achieve the same probability of bit error compared to simpler encoding schemes.

**Biphase Encoding:**

- **Manchester Encoding:** Features a transition in the middle of each bit period, which serves as both clock and data. A low-to-high transition represents a binary 1, and a high-to-low transition represents a binary 0. This method is self-clocking, which enhances synchronization but requires more bandwidth.
- **Differential Manchester:** Similar to Manchester but with a transition at the start of the bit period representing binary 0 and no transition representing binary 1. Like Manchester, it’s self-clocking but also requires more bandwidth.

**Pros and Cons of Biphase Encoding:**

- **Pros:** Self-synchronizing, no DC component, and error detection through the presence or absence of expected transitions.
- **Cons:** Higher modulation rate and greater bandwidth requirement than NRZ schemes.