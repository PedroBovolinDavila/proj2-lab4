# Sensor Calibration System Documentation

This documentation describes the operation of the C code responsible for reading, calibrating, and calculating statistics for a set of up to 10 sensors. The system allows manual data entry for sensors, performs measurement corrections based on gain and offset, and displays the average before and after calibration, as well as the sensor with the highest recorded measurement.

## Data Structures and Constants

```c
#define MAX_SENSORES 10
```
Defines the maximum limit of sensors that the program can process simultaneously.

### `struct Sensor`
Structure used to store data for each sensor individually. It contains the following fields:
* **`canal`** (int): The sensor channel (0 or 1).
* **`ganho`** (double): The gain applied during calibration (must be between 10V and 10.4V).
* **`offset`** (double): The compensation value (between -1 and 1).
* **`medida`** (double): The current measurement recorded by the sensor (raw or calibrated).

## Functions

### `void calibrar_sensor(struct Sensor* sensor)`
**Description:** Calibrates the measurement of a specific sensor.

The function uses the mathematical formula:  
`corrected_measurement = (gain * measurement) + offset`  
to update the measurement value directly at the memory address of the passed sensor.

**Parameters:**
* `sensor` (`struct Sensor*`) - Pointer to the sensor that will have its measurement calibrated.

**Return:** `void` (No value returned, modification is done by reference).

---

### `void mostrar_sensor(const struct Sensor sensor, int numero_sensor)`
**Description:** Displays the details of a sensor in the console.

The function receives a copy of a sensor and its identification number, displaying its properties (channel, gain, offset, and measurement) in a standardized and readable format.

**Parameters:**
* `sensor` (`const struct Sensor`) - Sensor structure to be displayed on the screen.
* `numero_sensor` (`int`) - Identification/order number of the sensor for display purposes.

**Return:** `void` (Prints the data to the console).

---

### `double calcular_media(const struct Sensor* sensores, int qtd_sensores)`
**Description:** Calculates the arithmetic mean of the sensor measurements.

The function iterates over the provided sensor array, accumulating the sum of all measurements in a temporary variable. Finally, it divides this sum by the quantity of sensors to obtain the average.

**Parameters:**
* `sensores` (`const struct Sensor*`) - Array containing the evaluated sensors.
* `qtd_sensores` (`int`) - Quantity of valid elements in the sensor array.

**Return:** `double` - The numeric value corresponding to the arithmetic mean of the measurements.

---

### `int indice_maior(const struct Sensor* sensores, int qtd_sensores)`
**Description:** Returns the index of the sensor with the highest recorded measurement.

The function iterates over the sensor array and sequentially compares the measurements. It stores the index of the sensor that has the highest measurement value found during the loop.

**Parameters:**
* `sensores` (`const struct Sensor*`) - Array containing the sensors to be evaluated.
* `qtd_sensores` (`int`) - Quantity of valid elements in the sensor array.

**Return:** `int` - The numeric index (0-based) of the element in the array that has the highest measurement.
