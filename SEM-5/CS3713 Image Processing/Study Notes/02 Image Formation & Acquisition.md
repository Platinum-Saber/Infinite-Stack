
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

> [!image] Image Sensor Types
> - CCD and CMOS
>  ![[Pasted image 20250723113854.png|300]] ![[Pasted image 20250723114557.png|330]]

> [!video] CCD
> <iframe width="650" height="340" src="https://www.youtube-nocookie.com/embed/_djfA0ermCM?si=4m_2OSRB33YzoVbB" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

> [!video] CMOS
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

## 4. Spatial Resolution and Quantization

- **Spatial Resolution**: Determined by the size of the image sensor (e.g., number of pixels).
- **Quantization**: Determined by the resolution of the analog-to-digital converter, affecting the precision of pixel intensity values.
- **Example**: A 192x1024 pixel image (true HD) has fewer than 2 million pixels, requiring efficient storage mechanisms.

> [!tip] Efficient Storage  
> Using a color table with pointers to store only used colors can significantly reduce storage needs for high-resolution images.  
> **Further Reading**: [Spatial Resolution in Imaging](https://www.radiologyinfo.org/en/info.cfm?pg=article-digital-imaging)

## 5. Loss of Information and Aliasing

- **Loss of Information**: Occurs when the sampling region is large, especially with images containing fine details, leading to the checkerboard effect.
- **Aliasing**: Happens when the sampling interval differs slightly from signal frequencies, causing distortions.

> [!warning] Impact of Sampling Issues  
> Improper sampling can lead to significant data loss and visual artifacts, critical in high-detail imaging tasks.  
> **Further Reading**: [Aliasing in Digital Images](https://www.cambridgeincolour.com/tutorials/image-interpolation.htm)

## 6. Color Representation

### Emission-Based

- **Definition**: Based on the type of light emitted to produce a color.
- **Characteristics**:
    - Absence of light results in black.
    - Presence of all color components results in white.

> [!info] Emission-Based Systems  
> Common in digital displays (e.g., monitors, TVs) where light emission directly controls color output.  
> **Further Reading**: [Additive Color Models](https://www.xrite.com/blog/additive-subtractive-color)

### Absorption-Based

- **Definition**: Based on the ink applied to a substrate, which absorbs certain wavelengths to produce a color.
- **Mechanism**: Ink subtracts colors from white light to create the desired image.

> [!info] Absorption-Based Systems  
> Used in printing (e.g., CMYK), where ink absorption determines the reflected color.  
> **Further Reading**: [Subtractive Color Models](https://www.xrite.com/blog/additive-subtractive-color)

### RGB and CMYK Relationship

- **RGB**: Additive color model used for digital displays (emission-based).
- **CMYK**: Subtractive color model used for printing (absorption-based).
- **Conversion**: RGB to CMYK conversion is complex due to different color spaces and gamuts.

> [!tip] Color Model Conversion  
> Understanding RGB to CMYK conversion is essential for accurate color reproduction across digital and print media.  
> **Further Reading**: [RGB to CMYK Conversion](https://www.color-management-guide.com/rgb-to-cmyk.html)

---

**Source**: Department of Computer Science and Engineering, University of Moratuwa  
**Additional Resources**:

- [Digital Image Processing by Gonzalez and Woods](https://www.imageprocessingbook.com/)
- [OpenCV Documentation](https://docs.opencv.org/master/)