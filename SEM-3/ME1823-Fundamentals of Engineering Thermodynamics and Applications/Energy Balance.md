Related : #Thermo #Thermo/3 #Thermo/3/energy

[Reference Lecture](file:///E:%5CAcademics%5CSEM%203%5CME1823-Fundamentals%20of%20Engineering%20Thermodynamics%20and%20Applications%5CLecture%20Video%5CLec%2004%20-%20Laws%20of%20Thermodynamics%20-%20Episode%201.mp4)

<br>

****
# Energy Balance for Closed Systems
- There is **no** *mass transfer*
- There is **energy transfer** in the form of *heat* or *work*.
- Can be expressed through the *Non - flow energy equation*

>[!note]- Specific Equation
>${Net\ energy\ transferred\ to\ or\ from\ the\ system\ as\ heat\ and\ work\ }\ =\  {\ Net\ increase\ or\ decrease\ in\ the\ total\ energy\ of\ the\ system\ }$
>$Q\ -\ W\ =\ \Delta E$
>$Q\ -\ W\ =\ \Delta U\ +\ \Delta KE\ +\ \Delta PE$

<br>
<br>

****
# Energy Balance for Open Systems
- Has both *mass transfer* & *Energy transfer*
- **CV** : *Control Volume*

<br>

>[!abstract]- How to calculate the total specific energy of a flow system
>![[Pasted image 20240815115511.png]]
>> Work done to enable mass flow $=\ F\ *\ L$
>
>> Flow work,
>>  $W_{flow}\ =\ P\ *\ A\ *\ L$
>> $W_{flow}\ =\ P\ *\ V$
>> 
>> Specific flow work, 
>> $W_{flow}\ =\ P\ *\ \nu$
>
>>Total specific energy of a flow system ($\theta$)
>>$\theta =\ e\ +\ W_{flow}$
>>$\theta =\ u\ +\ 1/2\ C^2\ +\ g\ z\ +\ P \nu$
>>$h\ =\ u\ +\ P\ \nu$
>
>>#### $$\therefore \ \ \ \ \ \ \theta =\ h\ +\ 1/2\ C^2\ +\ g\ z$$


>[!note]- Specific Equation
>$$Total\ Energy\ crossing\ CV\ boundary\ as\ heat\ and\ work\ +\ Total\ Energy\ of\ the\ mass\ entering\ the\ CV\ -\ Total\ energy\ of\ the\ mass\ leaving\ the\ CV\ =\ Net\ Change\ in\ energy\ of\ the\ CV$$
>
>>#### $$Q\ -\ W\ +\ \sum {m_i\ \theta_i}\ -\ \sum {m_e\ \theta_e}\ =\ \Delta E_{CV}$$

>[!info]- Transient State vs Steady State
**Transient state** : properties change with time
**Steady state** : properties **don't** change with time.
>![[Pasted image 20240815123056.png]]

<br>

## Steady State Flow Process
- Properties at the *boundaries* **don't** change with time.
- *Heat* and *work* interaction between the *system* and the *surroundings* **don't** change with time.

>[!note]- **Definition**
>Fluid properties **may change** *from one point to another* within the control volume, but *at any fixed point* they **remain the same** during the entire process.

>[!warning]-  Energy balance equation for open systems at steady state
>- *Net change* in *energy* of the *control volume* becomes **0**.
> $$Q\ -\ W\ =\ \sum {m_e\ \theta_e}\ -\ \sum {m_i\ \theta_i}$$
> 
> By differentiating once with respect to time
> ![[Pasted image 20240815125000.png]]
> 
> In most cases there is only an identical single inlet and single outlet.
> Hence,
>  ![[Pasted image 20240815125406.png]]
> 
>> For specific conditions (per kilogram),
>>#### $$q\ -\ w\ =\ (\ h_e\ -\ h_i\ +\ \frac {{C_e}^2\ -\ {C_i}^2}{2}\ +\ g\ (\ Z_e\ -\ Z_i\ )\ )\ \ \ kJ/kg$$
>>This equation is known as the *Steady flow energy equation* (SFEE)

<br>

****
Up Next : [[3. The Second Law of Thermodynamics]]




