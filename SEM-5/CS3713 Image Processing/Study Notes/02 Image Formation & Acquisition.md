
## 1. Optical Image Formation


### Definition
-  An optical image forms when multiple light rays from a single point converge at another point, creating contrast against the background.

> [!info]- Glossary
> - **Light Source**: Objects either emit light or reflect incident light from another source.
> - **Lens Role**: The light energy at the image depends on the extent of light reflected by the object and the lens surface area.
> - **Lens Structure**: Typically a cut-out section from a spherical surface, designed to focus light.
> - **Metering**: Measuring and controlling light
> 

> [!image] Image formation
> - Eye
> ![[Pasted image 20250723112222.png]]
> - Camera
> ![[Pasted image 20250723113005.png]]

> [!info] Importance of Optical Systems  
> Understanding light convergence is crucial for designing imaging systems like cameras and microscopes.  
> **Further Reading**: [Optical Image Formation](https://www.britannica.com/technology/optics/Image-formation)

## 2. Image Sensors

### Photo-Sensor Functionality

- **Operation**: Photo-sensors produce a weak electrical signal proportional to incident light intensity.
- **Types**:
    - **CCD (Charge-Coupled Device)**: Produces an integrating response.
    - **CMOS (Complementary Metal-Oxide-Semiconductor)**: Produces a dynamic response.
- **CMOS** require direct on sensor reading through a complex multiplexing arrangement.
- **CCD** acts like a memory and the charge can retain even after the light is removed. (can be transferred to a holding memory and read on the background)
> [!image] Image Sensor Types
> - CCD 
>  ![[Pasted image 20250723113854.png|300]] 
> - CMOS
>  ![[Pasted image 20250904200257.png|300]] ![[Pasted image 20250723114557.png|330]]

> [!video]- CCD
> <iframe width="650" height="340" src="https://www.youtube-nocookie.com/embed/_djfA0ermCM?si=4m_2OSRB33YzoVbB" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

> [!video]- CMOS
> <iframe width="650" height="340" src="https://www.youtube.com/embed/6JJXD63aTKg" title="CMOS Image Sensor Layers at a Glance" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

- **Signal Processing**:
    - Signals are weak (a few microvolts), analog, and often noisy.
    - Conditioned for DC bias (offset) and noise, then amplified using a gain-controlled amplifier.
    - Amplified signals are converted to digital format via a fast analog-to-digital converter (ADC).

> [!tip] Sensor Signal Challenges  
> Noise and weak signals necessitate careful conditioning and amplification to ensure accurate digital conversion.  
> **Further Reading**: [Image Sensors: CCD vs. CMOS](https://www.teledynedalsa.com/en/learn/knowledge-center/ccd-vs-cmos/)

## 3. Color Data Acquisition

### Beam Splitting

- **Process**: A dichroic prism splits incoming light into primary colors (e.g., red, green, blue).
- **Mechanism**: Separate image sensors capture each color beam.
- **Requirements**: The structure must be rigid and properly aligned.
- **Advantage**: Provides equal resolution for both color and illumination.

> [!image]- Beam Splitting
> ![[Pasted image 20250723115830.png|500]]

> [!info] Beam Splitting Advantage  
> Equal resolution for color and illumination makes beam splitting ideal for high-quality imaging applications.  
> **Further Reading**: [Dichroic Prisms in Imaging](https://www.edmundoptics.com/knowledge-center/application-notes/optics/dichroic-mirrors/)

### Color Filter Array (CFA)

- **Process**: An optical filter allows each sensing element to capture only one color.
- **Estimation**: Other color components are estimated using data from nearby sensors (e.g., via demosaicing).
- **Limitation**: Lower color resolution compared to illumination resolution.

> [!warning] CFA Limitation  
> The trade-off for CFA is reduced color resolution, which can impact image quality in color-critical applications.  
> **Further Reading**: [Color Filter Arrays and Demosaicing](https://www.image-engineering.de/library/technical-papers/750-color-filter-array)


## 4. Sensitivity & SNR

- **Sensitivity**: Measures how well a sensor converts incident light into an electrical signal (quantum efficiency). High sensitivity is critical for low-light performance.
- **Signal-to-Noise Ratio (SNR)**: Ratio of signal to noise, expressed in `dB`. Higher SNR means better image quality.
    - **Low SNR**: Occurs in low light with high-gain amplification, resulting in noisy images.
    - **Best SNR**: Achieved at optimum sensitivity with moderate light levels.

- **Incident Light**: Controlled by **aperture** (lens opening, f-stops) and **exposure time** (shutter speed).


> [!image]- Sensor Functionality
> ![[Pasted image 20250730104304.png|460]]
> 
> - **Sensor Output**:
>     - **Non-Sensitive**: Weak signal in low light, requires high-gain amplification, lowers SNR.
>     - **Optimum Sensitivity**: Strong signal, best SNR, high-quality images.
>     - **Saturated**: In bright light, sensor reaches full capacity, loses detail, insensitive to light variations.


**Exposure Control in CCD Sensors**:
- Uses **integrating effect** to accumulate charge over exposure time.
- Longer exposure increases signal but risks noise or blur; shorter exposure prevents saturation but may reduce detail.

> [!tip]- **Practical Notes**:
>    - Aperture: Larger (e.g., f/2.8) increases light, improves low-light sensitivity; smaller increases depth of field.
>    - Balancing aperture, exposure time, and gain optimizes sensitivity and SNR.

## 5. Depth of Field

> [!info] **Definition**:
> Depth of field (DoF) is the range within which objects appear in focus in an image.

- **Lens Equation**: Only one plane in the object region can be at proper focus according to the lens equation.
- **Circle of Confusion**:
    - Objects slightly out of the focus plane form a **circle of confusion** on the sensor.
    - No difference in output is perceived until the circle of confusion exceeds one sensor element.
- **DoF Creation**: The apparent focus across a depth range arises when the circle of confusion remains smaller than a sensor element.

> [!NOTE] Illustration:
> ![[Pasted image 20250904204912.png|260]] ![[Pasted image 20250904205006.png|340]]
> - Small circle of confusion: Objects near focus appear sharp.
> - Larger circle of confusion: Objects further out of focus blur, reducing detail (e.g., grid patterns transitioning to circles).
> - Sensor output depends on total light, not precise focus, until blur exceeds element size.

## 4. Spatial Resolution (Pixilation) and Quantization

- **Spatial Resolution**: Determined by the size of the image sensor (e.g., number of pixels).
- **Quantization**: Determined by the resolution of the analog-to-digital converter, affecting the precision of pixel intensity values.
- **Example**: A 1920x1024 pixel image (true HD) has fewer than 2 million pixels, requiring efficient storage mechanisms.

> [!NOTE] **Resolution** : Number of samples per unit length

> [!NOTE] **Gray Level Depth** : Number of discrete intensity levels.


> [!warning] **Checkerboard Effect** -> Insufficient spatial resolution

> [!warning] **False Contouring** -> Insufficient gray-level depth


> [!image] Pixelation and Quantizations
> ![[Pasted image 20250904212226.png]]

> [!image] Effect of Quantization
> ![[Pasted image 20250904213219.png]]

> [!math] Down Sampling
> $$I_{DS}(r,c) = \frac{1}{\Delta^2} \sum_{\rho=r\Delta}^{(r+1)\Delta-1} \sum_{\chi=c\Delta}^{(c+1)\Delta-1} I(\rho, \chi); \quad I_P = I_{DS} \uparrow \Delta$$


> [!tip] Efficient Storage  
> Using a color table with pointers to store only used colors can significantly reduce storage needs for high-resolution images.  
> **Further Reading**: [Spatial Resolution in Imaging](https://www.radiologyinfo.org/en/info.cfm?pg=article-digital-imaging)

## 5. Loss of Information and Aliasing

- **Loss of Information**: Occurs when the sampling region is large, especially with images containing fine details, leading to the checkerboard effect.
- **Aliasing**: Happens when the sampling interval differs slightly from signal frequencies, causing distortions.

> [!image] Aliasing
> - Original
> ![[Pasted image 20250904213636.png| 300]]
> - Aliased
> ![[Pasted image 20250904213721.png|300]]
> - Anti-Aliased
> - ![[Pasted image 20250904213822.png|300]]

> [!warning] Impact of Sampling Issues  
> Improper sampling can lead to significant data loss and visual artifacts, critical in high-detail imaging tasks.  
> **Further Reading**: [Aliasing in Digital Images](https://www.cambridgeincolour.com/tutorials/image-interpolation.htm)


> [!info] Image Dithering
> ![[Pasted image 20250904214317.png]]
> - Used in 2 color systems to create an impression of different gray levels.


## 6. Color Representation

### Emission-Based

- **Definition**: Based on the type of light emitted to produce a color.
- **Characteristics**:
    - Absence of light results in black.
    - Presence of all color components results in white.

> [!info] Emission-Based Systems  
> ![[Pasted image 20250904214529.png|120]] ![[Pasted image 20250904214613.png|530]]
> Common in digital displays (e.g., monitors, TVs) where light emission directly controls color output.  
> **Further Reading**: [Additive Color Models](https://www.xrite.com/blog/additive-subtractive-color)

### Absorption-Based

- **Definition**: Based on the ink applied to a substrate, which absorbs certain wavelengths to produce a color.
- **Mechanism**: Ink subtracts colors from white light to create the desired image.

> [!info] Absorption-Based Systems 
> ![[Pasted image 20250904215601.png|120]] 
> Used in printing (e.g., CMYK), where ink absorption determines the reflected color.  
> **Further Reading**: [Subtractive Color Models](https://www.xrite.com/blog/additive-subtractive-color)

### Pallet Based
- ![[Pasted image 20250904221541.png]]


> [!check] Advantage
> Native RGB formats reserve space even for colors that are never used. Hence storage is inefficient. 
> Creating a table of actually used colors and then storing pointers to them can reduce the required storage space.

### RGB and CMYK Relationship

- **RGB**: Additive color model used for digital displays (emission-based).
- **CMYK**: Subtractive color model used for printing (absorption-based).
- **Conversion**: RGB to CMYK conversion is complex due to different color spaces and gamuts.

> [!tip] Color Model Conversion  
> ![[Pasted image 20250904221320.png|400]]
> Understanding RGB to CMYK conversion is essential for accurate color reproduction across digital and print media.  
> **Further Reading**: [RGB to CMYK Conversion](https://www.color-management-guide.com/rgb-to-cmyk.html)

### Color in Video

- Attempt to separate **luminance** and the **chrominance** in the video signal.
- Has inherent compression capabilities. 
- **Luminance :**  $Y=f(R+G+B)$ 
- **Chrominance :**  $Cr= f(Y-R)$ , $Cb = f(Y-B)$ 
- Monochrome image can be constructed easily by discarding the $CrCb$ components.
- Human vision system is more sensitive to luminance than color. Thus storage bits are often allocated in $4:2:2$ ratio for $YCrCb$ components.

---
**Additional Resources**:

- [Digital Image Processing by Gonzalez and Woods](https://www.imageprocessingbook.com/)
- [OpenCV Documentation](https://docs.opencv.org/master/)