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

> [!abstract]- Encoding Schemes
> - Nonreturn to Zero-Level (NRZ-L) 
> - Nonreturn to Zero Inverted (NRZI) 
> - Bipolar -AMI 
> - Pseudoternary 
> - Manchester 
> - Differential Manchester 
> - B8ZS 
> - HDB3


## NRZ Encoding

> [!info]-  NRZ-L (Nonreturn to Zero-Level)
> -  A type of **polar encoding** where *two different voltages represent binary 0 and 1*. 
> - The voltage **remains constant** during the bit interval, and there's **no return to zero voltage** between bits. 
> - This method is straightforward but can lead to synchronization problems due to the lack of transitions in long sequences of identical bits.
> > [!image]- NRZ-L Diagram 
> > ![[Pasted image 20240904144052.png]]


> [!info]- NRZI (Nonreturn to Zero Inverted)
> -  An enhancement of NRZ-L. 
> - **Instead of using constant voltage levels**, NRZI encodes binary *1 by transitioning the voltage at the start of the bit interval*, while binary *0 is represented by no transition*. 
> - This method improves synchronization but still has some limitations, especially in complex transmission systems.

> [!image]- Comparison diagram
> ![[Pasted image 20240904144205.png]]


<br>

## Differential Encoding

> [!info] Concept
> - In differential encoding, data is represented by changes in the signal rather than the signal levels themselves. 
> - This approach is more robust because detecting a transition is generally more reliable than detecting a specific voltage level.

> [!success]- Pros
> -  Improved reliability in detecting transitions.

> [!fail]- Cons
> - Potentially complex, especially in environments with multiple signal paths where polarity could be lost.

<br>

## Multilevel Binary Encoding

> [!info]- Bipolar-AMI (Alternate Mark Inversion)
>  - Uses **more than two voltage levels**. Binary 0 is represented by no signal, while binary 1 is represented by alternating positive and negative pulses. 
> - This method **avoids a DC component** and is *effective for error detection*.

> [!info]- Pseudoternary
> - Opposite to Bipolar-AMI.
> - Binary *1 is represented by the* **absence of a signal** and *binary 0 by* **alternating positive and negative pulses**.

> [!image]- Comparison diagram
> ![[Pasted image 20240904144325.png]]


> [!error]- Trade-offs:
> - Multilevel encoding schemes are less efficient than NRZ because they require distinguishing between multiple signal levels, which increases the likelihood of errors.
> - Additionally, they require more signal power to achieve the same probability of bit error compared to simpler encoding schemes.

## Biphase Encoding

> [!info]- Manchester Encoding
> - Features a **transition** in the *middle of each bit period*, which serves as **both clock and data**. 
> - A *low-to-high transition* represents a **binary 1**, and a *high-to-low transition* represents a **binary 0**. 
> - This method is **self-clocking**, which enhances synchronization but **requires more bandwidth.**
> > [!image]- Manchester encoding diagram
> > ![[Pasted image 20240904144657.png]]

> [!info]- Differential Manchester
> - Similar to Manchester but with a **transition** at the **start of the bit period** representing *binary 0* and **no transition** representing *binary 1.*
> - Like Manchester, it’s **self-clocking** but also **requires more bandwidth.**
> > [!image]- Differential Manchester diagram
> > ![[Pasted image 20240904144802.png]]

> [!check]- Pros
> - Self-synchronizing
> - No DC component 
> - error detection through the presence or absence of expected transitions.

> [!fail]- Cons
> - Higher modulation rate.
> - Greater bandwidth requirement than NRZ schemes.


# Digital Data, Analog Signal

- **Public Telephone System:**
	- *Bandwidth* :  Limited to 300Hz to 3400Hz, requiring modulation techniques to transmit digital data over this analog system.

## Modulation Techniques

> [!info]- Amplitude Shift Keying **(ASK)**
> - Represents binary values by varying the **amplitude** of the carrier signal. 
> - Typically, one amplitude is zero, which makes the system vulnerable to gain changes and noise, limiting its efficiency and data rate (up to 1200bps on voice-grade lines).

> [!info]- Frequency Shift Keying **(FSK)**
> - Represents binary values using different frequencies near the **carrier frequency**. 
> - It’s *less susceptible to* **errors** than ASK and is commonly used in radio and LAN communications.

> [!info]- Phase Shift Keying **(PSK)**
> - Represents data by **shifting** the phase of the **carrier** signal. 
> - PSK is more **resistant to noise** than ASK and FSK and provides **better bandwidth efficiency**.

## Advanced Modulation

> [!info]- Quadrature PSK **(QPSK)** 
> - Improves efficiency by representing multiple bits with each signal element. 
> - It uses shifts of 90° in **phase (π/2)** to represent data. 
> - Higher-order PSK schemes can use even more phase angles and multiple amplitudes to transmit data more efficiently.

> [!info]- Quadrature Amplitude Modulation **(QAM)**
> -  Combines ASK and PSK, using two carrier signals 90° out of phase with each other. 
> - Each carrier is independently ASK modulated, allowing for two different signals to be transmitted simultaneously over the same medium. 
> - QAM is used in applications like ADSL and some wireless systems, offering high data rates and efficient use of bandwidth.

## Performance Considerations

- **Bandwidth:** The bandwidth required for ASK and PSK is directly related to the bit rate, while FSK’s bandwidth depends on the data rate at lower frequencies and the offset from the carrier at higher frequencies.
- **Bit Error Rate:** In noisy environments, PSK and QPSK offer better bit error rates (about 3dB better) than ASK and FSK.