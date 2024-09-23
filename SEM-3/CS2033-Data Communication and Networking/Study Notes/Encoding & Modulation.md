---
tags: 
Reviewed: 
Created: 2024-09-04T13:41:00
About: Based on CS2033-Lecture 03 Encoding and Modulation. This chapter from "Encoding and Modulation" delves into the methods used to encode and modulate data for effective communication. It explains how digital and analog signals can represent data, the advantages and limitations of various encoding techniques, and the role of modulation in transmitting signals over different mediums.
---
Related : #Networking #Networking/03 #Encoding #Modulation 

Reference Note : 

---
# Content
- [[#Encoding Techniques]]
- [[#1. Digital data, Digital signal]]
	1. [[#NRZ Encoding]]
	2. [[#Differential Encoding]]
	3. [[#Multilevel Binary Encoding]]
	4. [[#Biphase Encoding]]
- [[#2. Digital Data, Analog Signal]]
	1. [[#Modulation Techniques]]
	2. [[#Advanced Modulation]]
	3. [[#Performance Considerations]]
- [[#3. Analog Data, Digital Signal]]
	1. [[#Digitization Process]]
	2. [[#Delta Modulation]]
- [[#4. Analog Data, Analog Signal]]
	1. [[#Modulation Types]]
- [[#5. Scrambling Techniques]]
	1. [[#Purpose of Scrambling]]
	2. [[#Techniques]]
	3. [[#Advantages]]

---

# Encoding Techniques
> [!abstract]- Glossary
> - **Unipolar** : All signal elements have same sign
> - **Polar**       : One logic state represented by positive voltage the other by negative voltage.
> - **Data rate** : Rate of data transmission on bits per second.


- [[#1. Digital data, Digital signal]]  
- [[#2. Digital Data, Analog Signal]] 
- [[#3. Analog Data, Digital Signal]] 
- [[#4. Analog Data, Analog Signal]]


<br>

# 1. Digital data, Digital signal  

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

<br>

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

<br>

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

<br>
<br>

# 2. Digital Data, Analog Signal

- **Public Telephone System:**
	- *Bandwidth* :  Limited to 300Hz to 3400Hz, requiring modulation techniques to transmit digital data over this analog system.

<br>

## Modulation Techniques

> [!info]- Amplitude Shift Keying **(ASK)**
> - Represents binary values by varying the **amplitude** of the carrier signal. 
> - Typically, one amplitude is zero, which makes the system vulnerable to gain changes and noise, limiting its efficiency and data rate (up to 1200bps on voice-grade lines).
> > [!image]- ASK diagram
> > ![[Pasted image 20240904151109.png]]

> [!info]- Frequency Shift Keying **(FSK)**
> - Represents binary values using different frequencies near the **carrier frequency**. 
> - It’s *less susceptible to* **errors** than ASK and is commonly used in radio and LAN communications.
> 
> > [!image]- FSK diagram
> > ![[Pasted image 20240904151142.png]]
> 
> > [!image]- Full-Duplex FSK Transmission on a Voice-Grade Line
> > ![[Pasted image 20240904151607.png]]

> [!info]- Phase Shift Keying **(PSK)**
> - Represents data by **shifting** the phase of the **carrier** signal. 
> - PSK is more **resistant to noise** than ASK and FSK and provides **better bandwidth efficiency**.
> 
> > [!note]- Binary **PSK**
> > 2 phases represents 2 binary digits.
> > > [!image]- Binary PSK
> > > ![[Pasted image 20240904152012.png]]
> 
> > [!note]- Differential **PSK**
> > Phase shifted relative to previous transmission rather than some reference signal
> > > [!image]- Differential PSK diagram
> > > ![[Pasted image 20240904152322.png]]

> [!image]- Modulation techniques diagram 
> ![[Pasted image 20240905204016.png]]

<br>

## Advanced Modulation

> [!info]- Quadrature PSK **(QPSK)** 
> - Improves efficiency by representing multiple bits with each signal element. 
> - It uses shifts of 90° in **phase (π/2)** to represent data. 
> - Higher-order PSK schemes can use even more phase angles and multiple amplitudes to transmit data more efficiently.

> [!info]- Quadrature Amplitude Modulation **(QAM)**
> -  Combines ASK and PSK, using two carrier signals 90° out of phase with each other. 
> - Each carrier is independently ASK modulated, allowing for two different signals to be transmitted simultaneously over the same medium. 
> - QAM is used in applications like ADSL and some wireless systems, offering high data rates and efficient use of bandwidth.

<br>

## Performance Considerations

- **Bandwidth:**
	-  The bandwidth required for ASK and PSK is directly related to the bit rate, while FSK’s bandwidth depends on the data rate at lower frequencies and the offset from the carrier at higher frequencies.
- **Bit Error Rate:** 
	- In noisy environments, PSK and QPSK offer better bit error rates (about 3dB better) than ASK and FSK.

<br>
<br>

# 3. Analog Data, Digital Signal

## Digitization Process

> [!note]- Pulse Code Modulation (PCM)
> - Converts `analog` data into `digital` by **sampling** the signal at regular intervals. 
> - According to the **Nyquist Theorem**, the sampling rate must be at least **twice the highest frequency** of the analog signal to retain all the information.
> 
> > [!image]- Digitalization diagram
> > ![[Pasted image 20240905193156.png]]

> [!image]- PCM example diagram
> ![[Pasted image 20240905193947.png]]
> ![[Pasted image 20240905194009.png]]



> [!info]- Sampling
> - For voice data, which is limited to 4000Hz, the sampling rate is typically 8000 samples per second. 
> - Each sample is then **quantized** and **encoded** into a digital value.

> [!info]- Quantization
> - The process of mapping the **continuous** **amplitude** of the analog signal to discrete digital levels. 
> - For instance, an 8-bit PCM system provides 256 quantization levels, which allows for a quality of transmission comparable to the original analog signal.

> [!note]- Nonlinear Encoding
> - Quantization levels are **not evenly spaced**.
> - Reduces overall signal distortion.
> - Can also be done by **companding** (Compressing & Expanding).
> 
> > [!image]- Nonlinear Encoding diagram
> > ![[Pasted image 20240905194558.png]]

<br>

## Delta Modulation:

> [!info]- Concept 
> - Instead of encoding each sample's amplitude, Delta Modulation encodes the difference between successive samples, effectively creating a **staircase approximation** of the original analog signal. 
> - This approach can reduce the amount of data needed to represent the signal, but it may introduce quantization noise.
> 
> > [!image]- Delta modulation example diagram
> > ![[Pasted image 20240905195252.png]]
> 
> > [!image]- Delta modulation operation diagram
> > ![[Pasted image 20240905195336.png]]

> [!info]- Performance
>  Delta modulation provides good voice reproduction, with further compression techniques like **interframe coding** improving efficiency for applications like video.

<br>
<br>

# 4. Analog Data, Analog Signal

> [!faq]- Why Modulate Analog Signals
> - Modulating analog signals to higher frequencies allows for more **efficient** transmission and supports **frequency division multiplexing**, enabling multiple signals to be transmitted simultaneously over the same medium.

### Modulation Types

> [!info]- Amplitude Modulation (AM)
>  - The carrier signal’s amplitude is varied according to the information in the message signal. 
>  - AM is **simple** but **less efficient** than other modulation types because it’s more susceptible to noise and requires more bandwidth.
>
>> [!image]- Amplitude modulation diagram
>> ![[Pasted image 20240905202123.png]]
>> ![[Pasted image 20240905202136.png]]

> [!info]- Frequency Modulation (FM)
> - The carrier signal’s frequency is varied in accordance with the message signal. 
> - FM is more resistant to noise and provides better sound quality than AM.

> [!info]- Phase Modulation (PM)
> - The carrier signal’s phase is varied to encode the message. PM is closely related to FM but differs in how the carrier's phase is directly proportional to the modulating signal.

> [!image]- Phase and Frequency modulation method
> ![[Pasted image 20240905202353.png]]

> [!image]- Modulation types diagram
> ![[Pasted image 20240905202501.png]]

<br>
<br>

# 5. Scrambling Techniques

### Purpose of Scrambling

- Scrambling is used to **avoid long sequences** of **constant voltage** in digital signals, which can cause synchronization problems. 
- It ensures that there are enough **transitions** in the signal to maintain **synchronization** without reducing the data rate.
- The `filling sequence` has the **same length** as the original.

<br>

### Techniques

- **B8ZS (Bipolar with 8-Zero Substitution):** 
	- Substitutes sequences of **eight consecutive zeros** with a pattern that includes deliberate violations of the bipolar-AMI code. This pattern is unlikely to occur naturally and is easily detected and interpreted by the receiver.
- **HDB3 (High-Density Bipolar 3 Zeros):** 
	- Similar to B8ZS, but it replaces sequences of **four zeros** with a pattern that includes one or two pulses, depending on the number of previous pulses.
	- Based on `Bipolar-AMI`

> [!image]- `B8ZS` and `HDB3` diagrams
> ![[Pasted image 20240905204439.png]]

<br>

### Advantages

- Both `B8ZS` and `HDB3` maintain synchronization by ensuring there are enough transitions in the signal, avoid DC components, and offer error detection capabilities without reducing the overall data rate.

<br>

# Questions


> [!faq]- Explain the key differences between unipolar, polar, and bipolar encoding. Provide examples of when each might be used.
> - Unipolar encoding uses a single voltage level (e.g., 0 for binary 0, positive voltage for binary 1). 
> - It’s simple but has synchronization issues due to the presence of a DC component. 
> - Polar encoding uses both positive and negative voltages, improving synchronization by providing clearer transitions.
> - Bipolar encoding alternates between positive and negative voltages for binary 1s, with 0s represented by no voltage, effectively eliminating the DC component and allowing for better error detection.

> [!faq]- Describe how Manchester and Differential Manchester encoding work. What are the advantages of these encoding schemes
> - Manchester encoding uses a transition in the middle of the bit period to represent data, with a low-to-high transition indicating binary 1 and a high-to-low transition indicating binary 0. 
> - Differential Manchester also uses a mid-bit transition for clocking, but the start-of-bit transition represents binary 0, and no transition represents binary 1. Both methods are self-synchronizing and eliminate DC components, making them robust for data transmission.

> [!faq]- How does Quadrature Amplitude Modulation (QAM) achieve higher data rates than simple ASK or PSK?
> - QAM combines ASK and PSK by modulating two carrier signals that are 90° out of phase with each other. 
> - Each carrier is independently ASK modulated, allowing for the simultaneous transmission of two different signals over the same frequency, effectively doubling the data rate compared to ASK or PSK alone.

> [!faq]- Why is the Nyquist Theorem critical in the process of digitizing analog signals? How does it affect the choice of sampling rate
> - The Nyquist Theorem states that to accurately digitize an analog signal, the sampling rate must be at least twice the highest frequency present in the signal. 
> - This ensures that the sampled signal retains all the information of the original analog signal. If the sampling rate is too low (below the Nyquist rate), aliasing can occur, resulting in the loss of information and distortion.

> [!faq]- Compare B8ZS and HDB3 scrambling techniques. How do they help maintain synchronization in digital transmission
> - B8ZS and HDB3 both replace sequences of zeros with patterns that include intentional violations of the encoding rules, which are unlikely to occur naturally. 
> - These patterns introduce transitions in the signal, which help maintain synchronization. B8ZS replaces sequences of eight zeros, while HDB3 focuses on sequences of four zeros. Both methods avoid the loss of synchronization and reduce the likelihood of error due to long sequences without transitions.

<br>

---
Up Next : [[Data Transmission]]
