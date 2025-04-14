# XENSIV™ 3D Magnetic Sensor TLx493D ESP-IDF Library

ESP-IDF Library of Infineon's [XENSIV™ 3D Magnetic Sensor TLx493D](https://www.infineon.com/cms/en/product/sensor/magnetic-sensors/magnetic-position-sensors/3d-magnetics/)family.

### Supported Sensor Platforms

- [TLV493D-A1B6](https://www.infineon.com/cms/en/product/sensor/magnetic-sensors/magnetic-position-sensors/3d-magnetics/tlv493d-a1b6/)
- [TLV493D-A2BW](https://www.infineon.com/cms/en/product/sensor/magnetic-sensors/magnetic-position-sensors/3d-magnetics/tlv493d-a2bw/)

- [TLI493D-A2B6](https://www.infineon.com/cms/en/product/sensor/magnetic-sensors/magnetic-position-sensors/3d-magnetics/tli493d-a2b6/)
- [TLI493D-W2BW](https://www.infineon.com/cms/en/product/sensor/magnetic-sensors/magnetic-position-sensors/3d-magnetics/tli493d-w2bw-a0/)

- [TLE493D-A2B6](https://www.infineon.com/cms/en/product/sensor/magnetic-sensors/magnetic-position-sensors/3d-magnetics/tle493d-a2b6/)
- [TLE493D-W2B6](https://www.infineon.com/cms/en/product/sensor/magnetic-sensors/magnetic-position-sensors/3d-magnetics/tle493d-w2b6-a0/)
- [TLE493D-P2B6](https://www.infineon.com/cms/en/product/sensor/magnetic-sensors/magnetic-position-sensors/3d-magnetics/tle493d-p2b6-a0/)
- [TLE493D-P3I8](https://www.infineon.com/cms/en/product/sensor/magnetic-sensors/magnetic-position-sensors/3d-magnetics/tle493d-p3i8/)

## Add component to your project

Please add the following line to your `idf_component.yml`:

```yaml
dependencies:
  esp-idf-tlx493d:
    git: https://github.com/davidli218/esp-idf-xensiv-tlx493d.git
    version: "*"
```

## Basic Usage

```c
#include "esp_tlx493d.h"

TLx493D_t dut;
const TLx493D_SupportedSensorType_t sensorType = TLx493D_A1B6_e;

void app_main(void) {
    /* ... Initialize I2C master bus ... */

    tlx493d_init(&dut, sensorType);
    tlx493d_init_com_iic(&dut, i2c_bus_handle, TLx493D_IIC_ADDR_A0_e);
    tlx493d_setDefaultConfig(&dut);

    double x, y, z, t;
    tlx493d_getMagneticFieldAndTemperature(&dut, &x, &y, &z, &t);

    ESP_LOGI("TLx493D", "Magnetic Field: x=%f, y=%f, z=%f, Temperature=%f", x, y, z, t);
}
```

