## 1. Introduction to Images

### Definition of an Image

- **Visible Impression**: Obtained by devices like cameras, telescopes, or microscopes, or displayed on screens.
- **Optical Appearance**: Formed by light reflection (mirrors) or refraction (lenses).
- **Representation**: A 2D construct of elements representing light intensity in small areas, perceived by the human brain.
- **Mathematical Representation**: A 2D discrete function $I(x, y)$, where $( x )$ and $( y )$ are pixel coordinates, and the value represents light intensity.

> [!info] Key Concept  
> Images are not just visual data but constructs interpreted by the brain, carrying vast amounts of information.  
> **Further Reading**: [Image Formation and Representation](https://www.geeksforgeeks.org/digital-logic/fundamentals-of-image-formation/)

### Human Visual System (HVS)

- **Photoreceptor Cells**: The human eye has ~13 million cells sensitive to light, some for color and others for brightness.
- **Signal Processing**: Light triggers electrochemical signals sent to the brain’s visual cortex for processing.
- **Focus Capability**: The eye can focus from very near objects to infinity.
- **Depth of Field** : The range of depth the eye can focus and see at a time

> [!tip] Importance of HVS  
> The human eye’s ability to perceive images relies on a complex neural network, making image processing a bridge between technology and human perception.  
> **Further Reading**: [Human Visual System](https://www.ncbi.nlm.nih.gov/books/NBK11538/)

## 2. Image Processing Stages

### Acquire

- **Process**: Converting input into physical or logical representations using devices.
- **Sources**:
    - Visible light: Cameras, scanners, frame grabbers.
    - Non-visible light: X-Ray, UV, IR.
    - Other sources: Sonar, MRI, RADAR.

> [!warning] Acquisition Challenges  
> Acquisition devices may introduce artifacts that need correction during processing.  
> **Further Reading**: [Image Acquisition Techniques](https://www.sciencedirect.com/topics/engineering/image-acquisition)

### Enhance

- **Purpose**: Correct defects or artifacts introduced during acquisition.
- **Corrections**:
    - Brightness adjustments.
    - Contrast (dynamic range limitation).
    - Color consistency.
    - Geometrical defect correction.
      

> [!image] Enhancement Example
> ![[Pasted image 20250723104943.png]]  ![[Pasted image 20250723105004.png]]

> [!tip] Enhancement Benefits  
> Enhancement ensures images are optimized for further processing or display, improving quality and usability.  
> **Further Reading**: [Image Enhancement Techniques](https://www.tutorialspoint.com/dip/image_enhancement.htm)

### Store or Transmit

- **Formats**: Digital (analog/digital conversion) or physical/optical (e.g., printing).
- **Challenges**:
    - Data corruption or errors during transmission.
    - Losses due to encoding/compression.
    - Physical degradation (e.g., color fading, scratches).

> [!info] Storage Considerations  
> Compression and transmission can degrade image quality, requiring careful management to preserve data.  
> **Further Reading**: [image compression Basics](https://www.geeksforgeeks.org/search/?gq=image+compression)

### Restore/Recover

- **Goal**: Return the image to its original state by removing artifacts.
- **Tasks**:
    - Correct brightness and color consistency.
    - Enhance contrast.
    - Remove defects (e.g., scratches, data errors).
    - Correct geometric distortions.

> [!note] Restoration Importance  
> Restoration is critical for recovering degraded images, especially in archival or forensic applications.  
> **Further Reading**: [Image Restoration Techniques](https://www.mathworks.com/help/images/image-restoration.html)

### Re-Produce

- **Process**: Creating optical images from data using devices like printers, projectors, or LED/LCD screens.
- **Challenges**: Output quality depends on the device’s ability to reproduce light accurately, often requiring device-specific corrections.

> [!info] Reproduction Challenges  
> Device limitations can affect reproduction fidelity, necessitating tailored transformations.  
> **Further Reading**: [Image Reproduction Technologies](https://www.britannica.com/technology/image-processing)

## 3. Image Compression

- **Need**: Large data volumes in imaging require compression for storage and transmission.
- **Examples**:
    - A4 page at 600 dpi: >100 MB.
    - Digital camera color image: 10-30 MB.
    - Digital cinema (4K): 48 MB/frame or 70 GB/min.

> [!tip] Compression Significance  
> Compression is an enabling technology for modern imaging and multimedia, balancing quality and storage needs.  
> **Further Reading**: [Image Compression Techniques](https://www.tutorialspoint.com/dip/image_compression.htm)

## 4. Perceived Brightness

- **Key Concept**: Perceived brightness is not solely a function of light intensity but also depends on background intensity.
- **HVS Sensitivity**: The human eye is more sensitive to edges, causing perceived brightness to overshoot or undershoot at transitions.

> [!warning] Brightness Perception  
> Understanding perceived brightness is crucial for designing effective image processing algorithms, as human perception varies with context.  
> **Further Reading**: [Brightness Perception](https://www.vision-research.com/perception-of-brightness)

## 5. Contrast Stretching and Histogram Equalization

- **Contrast Stretching**: Enhances low-contrast images by stretching the intensity range.
- **Histogram Equalization**: Redistributes pixel intensities to improve contrast, often used in image enhancement.

> [!info] Enhancement Techniques  
> These techniques significantly improve image visibility and are foundational in image processing workflows.  
> **Further Reading**: [Contrast Stretching and Histogram Equalization](https://www.geeksforgeeks.org/histogram-equalization-in-digital-image-processing/)

## 6. Historical Context

- **Evolution**: Image processing predates computers, initially in the analog domain.
- **Digital Shift**: Enabled by increased processing power, memory, and widespread imaging devices.

> [!note] Historical Significance  
> The transition to digital image processing has democratized its applications, making it accessible to all.  
> **Further Reading**: [History of Image Processing](https://www.sciencedirect.com/topics/engineering/digital-image-processing)

---

**Source**: Department of Computer Science and Engineering, University of Moratuwa  
**Additional Resources**:

- [Digital Image Processing by Gonzalez and Woods](https://www.imageprocessingbook.com/)
- [OpenCV Documentation](https://docs.opencv.org/master/)