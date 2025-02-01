# Pedestrian-Traffic-Light-Controller 🚦

![Image](https://github.com/user-attachments/assets/265b2a0a-3e85-4fc7-bb91-e38b3118f9c5)

This project implements a **traffic light and pedestrian crossing system** using **direct port manipulation** on an **Arduino board**. Instead of using `digitalWrite()`, it directly modifies **PORTx, DDRx, and PINx registers** for **faster execution and better performance**.

## Features
✅ Traffic light control (Red, Yellow, Green)

✅ Pedestrian crossing with blinking Green light & countdown display

✅ Push-button activated pedestrian request

✅ 7-segment display countdown timer

✅ Optimized performance using **PORTx, DDRx, PINx**

## Hardware Requirements
- **Arduino Uno/Nano/Mega**
- **LEDs** (Traffic: Red, Yellow, Green; Pedestrian: Green)
- **Push button** (for pedestrian request)
- **7-segment display** (Common cathode)
- **Resistors & jumper wires**

## Circuit Diagram
(Include a simple diagram or Fritzing image here)

## Installation & Usage
1. Clone this repository:
   ```sh
   git clone https://github.com/krishnaelectrovoltz/Pedestrian-Traffic-Light-Controller.git
   ```
2. Open the project in **Arduino IDE**.
3. Upload the sketch to your **Arduino board**.
4. Connect the components as per the circuit diagram.
5. Press the push button to simulate pedestrian crossing.

## How It Works
- By default, the **traffic light is Green**.
- When the **pedestrian button is pressed**, the sequence begins:
- An additional segment lights up to indicate the pedestrian button was pressed.
  - Traffic **Green → Yellow → Red**
  - Pedestrian **Green blinks**, countdown starts on the **7-segment display**.
  - Once the countdown ends, traffic **resumes with Green light**.

## Why Port Manipulation?
Using `PORTB`, `DDRB`, and `PINB` instead of `digitalWrite()` ensures:
- ⚡ **Faster execution**
- 🔄 **Better real-time control**
- 🛠 **Efficient hardware interaction**

## License
This project is open-source under the **MIT License**.
