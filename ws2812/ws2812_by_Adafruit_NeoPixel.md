```arduino
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// 定义 WS2812 的引脚和灯珠数量
#define LED_PIN     2     // ESP32 引脚 2 连接到 WS2812 数据线
#define LED_COUNT   16    // WS2812 灯珠的数量

// 声明 NeoPixel 对象
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// 参数 1: 灯珠的数量
// 参数 2: 连接到 WS2812 的引脚
// 参数 3: 数据线的类型，NEO_GRB + NEO_KHZ800 大部分情况适用，如果不行尝试更换

void setup() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif

  strip.begin();           // 初始化 NeoPixel 对象
  strip.show();            // 初始化所有像素为 off
  strip.setBrightness(50); // 设置亮度 (0-255)
}

void loop() {
  // 示例 1: 逐个点亮灯珠
  for (int i = 0; i < LED_COUNT; i++) {
    // setPixelColor(pixel, color) 设置特定灯珠的颜色
    // pixel 是灯珠的索引，从 0 开始
    // color 是 24-bit 颜色值 (R,G,B)
    strip.setPixelColor(i, strip.Color(0, 150, 0)); // 绿色
    strip.show();         // 发送数据到 WS2812
    delay(50);
    strip.setPixelColor(i, strip.Color(0, 0, 0)); //熄灭
    strip.show();
    delay(50);
  }

  // 示例 2: 彩虹效果
  rainbow(10); // 传入一个delay参数，决定变换速度

  delay(1000);
}

// 彩虹效果函数
void rainbow(uint8_t wait) {
  for (long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for (int i=0; i< strip.numPixels(); i++) {
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();
    delay(wait);
  }
}
```

**代码说明：**

1.  **引入库：**
    *   `#include <Adafruit_NeoPixel.h>`:  引入 Adafruit NeoPixel 库，该库提供了控制 WS2812 灯珠的便捷方法。 你需要在 Arduino IDE 中安装这个库（菜单 "项目" -> "加载库" -> "管理库"，搜索 "Adafruit NeoPixel" 并安装）。

2.  **定义引脚和灯珠数量：**
    *   `#define LED_PIN 2`:  定义连接到 WS2812 数据线的 ESP32 引脚。  你可以根据实际连接修改此值。
    *   `#define LED_COUNT 16`:  定义 WS2812 灯珠的数量。  请根据你使用的 WS2812 灯条或灯环的灯珠数量修改此值。

3.  **创建 NeoPixel 对象：**
    *   `Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);`:  创建一个 `Adafruit_NeoPixel` 类的对象 `strip`。  
        *   第一个参数是灯珠的数量。
        *   第二个参数是连接到 WS2812 的引脚。
        *   第三个参数指定 WS2812 的类型和频率。  `NEO_GRB + NEO_KHZ800`  适用于大多数 WS2812 灯珠。  如果你的灯珠工作不正常，可以尝试更换 `NEO_GRB` 为 `NEO_RGB` 或 `NEO_BRG` 等。

4.  **`setup()` 函数：**
    *   `strip.begin();`:  初始化 NeoPixel 对象。
    *   `strip.show();`:  初始化所有像素为关闭状态 (黑色)。
    *   `strip.setBrightness(50);`:  设置亮度。  范围是 0 (最暗) 到 255 (最亮)。  可以根据需要调整此值。

5.  **`loop()` 函数：**
    *   **示例 1: 逐个点亮灯珠：**  使用 `strip.setPixelColor()` 函数设置特定灯珠的颜色。
        *   `strip.setPixelColor(i, strip.Color(0, 150, 0));`:  将索引为 `i` 的灯珠设置为绿色 (R=0, G=150, B=0)。
        *   `strip.show();`:  将颜色数据发送到 WS2812 灯珠，使其显示设置的颜色。
        *   `delay(50);`:  延时一段时间，以便观察灯珠的颜色变化。
    *   **示例 2: 彩虹效果：** 调用 rainbow 函数，实现彩虹渐变的效果。
    *   彩虹效果的函数中`strip.gamma32(strip.ColorHSV(pixelHue))`可以使色彩更鲜艳

**接线：**

*   **ESP32 VCC  ->  WS2812 VCC (+5V)**
*   **ESP32 GND  ->  WS2812 GND**
*   **ESP32 D2   ->  WS2812 DIN (Data In)**

**重要提示：**

*   **供电：**  WS2812 灯珠需要 5V 电源。 确保你的 ESP32 能够提供足够的电流。  如果灯珠数量较多，建议使用外部 5V 电源供电，并将 ESP32 和 WS2812 的 GND 连接在一起。
*   **限流电阻：**  在 WS2812 数据线上串联一个 300-500 欧姆的电阻，可以保护 ESP32 和 WS2812。
*   **电容：**  在 WS2812 的电源输入端并联一个 100-1000uF 的电解电容，可以提高供电的稳定性。

**如何运行：**

1.  确保你已经安装了 Arduino IDE，并且为 ESP32 配置了开发环境 (例如，安装了 ESP32 核心)。
2.  在 Arduino IDE 中，选择你的 ESP32 开发板 ("工具" -> "开发板" -> "ESP32 Dev Module" 或类似的选项)。
3.  选择正确的端口 ("工具" -> "端口" -> 你的 ESP32 串口")。
4.  复制上面的代码到 Arduino IDE 中。
5.  点击 "上传" 按钮，将代码上传到 ESP32。

上传成功后，WS2812 灯珠应该会开始显示示例中的颜色效果。 你可以修改代码，尝试不同的颜色和动画效果。  记得根据你的实际硬件连接修改 `LED_PIN` 和 `LED_COUNT`。

