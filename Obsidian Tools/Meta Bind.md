
### **1. Text Input Field**

The `text` input field allows you to input and edit single-line text values.

**Syntax:**

 `INPUT[text:propertyName]`

**Example:**

`INPUT[text:projectName]`

This creates a text input bound to the `projectName` property in your frontmatter.

---

### **2. Number Input Field**

The `number` input field is designed for numerical values.

**Syntax:**


`INPUT[number:propertyName]`


**Example:**


`INPUT[number:projectDuration]`


This sets up a number input linked to the `projectDuration` property.

---

### **3. Toggle Input Field**

The `toggle` input field provides a switch for boolean values.

**Syntax:**


`INPUT[toggle:propertyName]`


**Example:**


`INPUT[toggle:isCompleted]`


This adds a toggle switch associated with the `isCompleted` property.

---

### **4. Select Input Field**

The `select` input field offers a dropdown menu for selecting a single option from predefined choices.

**Syntax:**


`INPUT[select:propertyName|Option1,Option2,Option3]`


**Example:**


`INPUT[select:priority|Low,Medium,High]`


This creates a dropdown linked to the `priority` property with options "Low," "Medium," and "High."

---

### **5. Multi-Select Input Field**

The `multi-select` input field allows selection of multiple options from a list.

**Syntax:**


`INPUT[multi-select:propertyName|Option1,Option2,Option3]`


**Example:**


`INPUT[multi-select:tags|Work,Personal,Important]`


This sets up a multi-select field bound to the `tags` property with specified options.

---

### **6. Date Picker Input Field**

The `date-picker` input field enables date selection via a calendar interface.

**Syntax:**


`INPUT[date-picker:propertyName]`


**Example:**


`INPUT[date-picker:dueDate]`


This adds a date picker linked to the `dueDate` property.

---

### **7. Slider Input Field**

The `slider` input field allows selection of a numerical value within a specified range using a slider.

**Syntax:**


`INPUT[slider:propertyName|min,max,step]`


**Example:**


`INPUT[slider:progress|0,100,5]`


This creates a slider bound to the `progress` property, ranging from 0 to 100 in steps of 5.

---

### **8. Progress Bar Input Field**

The `progress-bar` input field visually represents progress as a bar.

**Syntax:**


`INPUT[progress-bar:propertyName]`


**Example:**


`INPUT[progress-bar:taskCompletion]`


This displays a progress bar linked to the `taskCompletion` property.

---

### **9. Text Area Input Field**

The `text-area` input field is suitable for multi-line text input.

**Syntax:**


`INPUT[text-area:propertyName]`


**Example:**


`INPUT[text-area:notes]`


This sets up a text area bound to the `notes` property.

---

### **10. Time Picker Input Field**

The `time-picker` input field allows selection of a time value.

**Syntax:**


`INPUT[time-picker:propertyName]`


**Example:**


`INPUT[time-picker:meetingTime]`


This adds a time picker linked to the `meetingTime` property.

---



For more detailed information and advanced configurations, refer to the [Meta Bind Documentation](https://www.moritzjung.dev/obsidian-meta-bind-plugin-docs/).

---

