使用ledcAttach：设置 LEDC 引脚的给定频率和分辨率。LEDC 通道将自动选择。
bool ledcAttach(uint8_t pin, uint32_t freq, uint8_t resolution);
 
/*
·pin选择 LEDC 引脚。
 
·freq选择 pwm 的频率。
 
·resolution选择LEDC通道的分辨率。范围是 1-14 位（ESP32 为 1-20 位）。
 
·true如果配置成功，此函数将返回。如果false返回，则发生错误，LEDC 通道未配置。
*/


使用ledcWrite：设置 LEDC 引脚的占空比

bool ledcWrite(uint8_t pin, uint32_t duty);
 
/*
·pin选择 LEDC 引脚。
 
·duty选择要为选定的 LEDC 引脚设置的占空比。
 
·true如果设置占空比成功，此函数将返回。如果false返回，则发生错误，并且未设置占空比。

————————————————

                            版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。
                        
原文链接：https://blog.csdn.net/weixin_73690807/article/details/143751376
