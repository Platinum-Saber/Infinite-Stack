Related : #Thermo #Thermo/1 

[Reference Lecture](file:///E:%5CAcademics%5CSEM%203%5CME1823-Fundamentals%20of%20Engineering%20Thermodynamics%20and%20Applications%5CLecture%20Video%5CLec%2001-%20Review%20of%20Ideal%20Gases%20%20Specific%20Heat%20Capacity.mp4)

<br>

---
# Content
1. [[#Ideal Gasses]]
2. [[#Specific Heat Capacity]]
3. [[#Specific Heat Capacity Relations for Ideal Gases]]

<br>

****
# Ideal Gasses
<br>

>[!abstract]- Characteristics of Ideal Gases
>- No intermolecular forces
>- Occupies no space (massless & point like particles)
>- Perform perfectly elastic collisions 
>- Has pure random motion (real gases has `Brownian` motion)

>[!warning]- Real gasses with smaller sizes demonstrate *Ideal gas* behavior at **high temperature** & **low pressure**
>>[!tip] How !
>>- At higher temperatures the intermolecular forces become negligible compared to its' total internal energy
>>- At low pressure the volume of the gas molecules become negligible compared to the gas volume. 

<br>

>[!equation]- Characteristic Equation
> $$\frac{P\ V}{T}\ =\ k$$
> P - pressure
> V - Volume
> T - Absolute temperature
> 
> For a given mass of `m` , 
>> $\ \ \ \ \ \ k\ =\ m\ R$
>> $\therefore \ P\ V\ =\ m\ R\ T$
>> Where R is `Gas Constant` 
>>
>>For universal gas constant ($R_u$) & molar mass ($M$)
>>##### $R = \frac{R_u}{M}$
>> $$\therefore \ P\ V\ =\ n\ R_u\ T$$

<br>

### Specific Heat Capacity

<br>

>[!FAQ]- What is **Specific Heat Capacity**
> The amount of energy required to raise the temperature of Unit mass of a substance by one degree.
> >[!error] Definition is **valid** only for `reversible` processes.

>[!info]- Heating at **constant volume** & **constant pressure** 
>![[Pasted image 20240714202505.png]] ![[Pasted image 20240714202532.png]]

>[!note]- **Constant Volume Heat Capacity** ($C_v$)
> Consider a fixed volume of gas is being heated *reversibly* at constant volume.
> 
>>$\Delta Q - \Delta W = \Delta U$
>> 
>>Since boundary work is Zero, $\Delta W = 0$
>>$$\therefore \ \ \Delta Q =\ \Delta U$$
> 
> > From the definition of Spec.Heat Capacity
> > $$\Delta Q\ =\ m\ C_v\ \Delta T$$
> 
> > From the two equations,
> > 
> > $m\ C_v\ dT\ =\ dU$
> > $du\ = C_v\ dT\ \ \ \ \ ;where\ u\ is\ the\ specific\ internal\ energy$
> > 
> > $\int du\ =\ \int {C_v\ dT}$
> > $u\ =\ C_v\ T\ +\ K\ \ \ \ ;where\ K\ is\ a\ constant\ of\ integration$
> > 
> > For ideal gases when `T=0` , `u=0`  $\ \ \ \therefore$ `k=0`
> > ### $$\therefore \ \ u\ =\ C_v\ T$$
> This is a **property function** .
> Hence it can be used regardless if the process is *reversible* or *irreversible*

>[!note]- **Constant Pressure Specific Heat Capacity ** ($C_p$)
>Consider a fixed volume of gas being heated at constant pressure
>>Since the process is *irreversible*, the only work is the moving boundary work.
>> $$\Delta Q - \Delta W = \Delta U$$
>
>>From the definition of Spec.Heat Capacity
>>$$\Delta Q = m\ C_p \Delta T$$
>
>>From the two equations
>>
>> $m\ C_p\ dT\ -\ P\ dV\ =\ dU$
>> $P\ dV\ +\ dU\ =\ dH\ \ \ \ \ ;$ From the enthalpy definition
>> $m\ C_p\ dT\ =\ dH$ 
>> $C_p\ dT\ =\ dh$
>> $\int dh\ = \int {C_p\ dT}$
>> $h\ =\ C_p\ T\ +\ k$
>> For ideal gases when T=0 , u=0 $\therefore k=0$
>> ### $$\therefore h\ =\ C_p\ T$$
>> 
>> **This is a property function**
>> Hence it can be used regardless if the process is _reversible_ or _irreversible_

<br>
<br>

### Specific Heat Capacity Relations for Ideal Gases

<br>

>[!note]- Relation between $C_p$ and $C_v$
>> For ideal gases
>> $P\ \nu =\ R\ T$ (R is the gas constant)
>
>>From the definition of enthalpy 
>> $h\ =\ u\ +\ P\ \nu$
>
>>By substitution
>>$C_p\ T\ =\ C_v\ T\ +\ R\ T$
>>### $$C_p\ =\ C_v\ +\ R$$

>[!note]- Specific Heat Capacity Ratio
>#### $$\gamma =\ \frac {C_p}{C_v}$$
>Usually $\gamma = 1.4$ for most *diatomic* gases.

<br>
<br>

**Up Next** : [[Basic Concepts of Thermodynamics]]