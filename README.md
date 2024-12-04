# Input Shaping and Signal Processing 🛠️📊

A project to fine-tune **input shaping parameters** for 3D printers.

---

## 📂 Repository Overview

### `input_shaping.ino`  
**Purpose**: Reads motion data from an **MPU6050** sensor.  

**Hardware**:  
- MPU6050 sensor (I2C interface).  
- Microcontroller (e.g., Teensy).  
- Status LED connected to pin 13.  

---

### `main.ipynb`  
**Purpose**: Processes and visualizes sensor data for parameter analysis.  

**Features**:  
- Signal processing (FFT, filtering).  
- Vibration analysis and visualization.  
- Serial communication with Teensy.

**Dependencies**:  
Install with:  
```bash
pip install numpy matplotlib scipy pyserial
```
---

### `shaker/`  
**Purpose**: Generates controlled vibrations to test the system by driving a stepper motor at a specified frequency.  

**Features**:  
- Simple Teensy sketch to control a stepper motor.  
- Generates vibrations at adjustable frequencies to simulate real-world conditions.

**Hardware**:  
- Stepper motor and driver.  
- Microcontroller.

---

## 🚀 How to Use

1. **Set Up the Hardware**:  
   - Connect MPU6050.  
   - Upload the `input_shaping.ino` sketche to the microcontroller.

2. **Run the Python Notebook**:  
   - Execute `main.ipynb` to collect, process, and visualize vibration data.  
   - Automatically generate G-Code for your 3D printer.  
   - Apply the G-Code to fine-tune input shaping parameters on your printer.
---

## 💡 Contributing
We welcome your ideas! Feel free to submit pull requests or report issues.

