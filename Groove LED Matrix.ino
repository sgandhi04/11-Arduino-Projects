#include "Grove_LED_Matrix_Driver_HT16K33.h"
#include <Wire.h>
 
//put your own design hex group here.
const uint64_t Emoji[] = 
{
  0x66361e3e66663e00,
  0x3c66666666663c00,
  0x3c66603c06663c00,
  0x3c18181818183c00, 
};
 
Matrix_8x8 matrix;
 
 
void setup() {
    Wire.begin();
    matrix.init();
    matrix.setBrightness(0);
    matrix.setBlinkRate(BLINK_OFF);
    /*************************************************************
    * Description
    *    Setting the blink rate of matrix
    * Parameter
    *    blink_type: BLINK_OFF, BLINK_2HZ, BLINK_1HZ
    * Return
    *    Null.
    *************************************************************/
}
 
void loop() {
  for (int i = 0;i < 4;i++)
    {
        matrix.writeOnePicture(Emoji[i]);
        /*************************************************************
        * Description
        *    Write a picture in display buffer.
        *    Call display() to show display buffer.
        * Parameter
        *    pic: A uint64_t type 8x8 matrix picture, you can make it at
        *         https://xantorohara.github.io/led-matrix-editor/#
        * Return
        *    Null.
        *************************************************************/
        matrix.display();
        /*************************************************************
        * Description
        *    Clear the display buffer.
        *    This function will display nothing on 8x8 Matrix after call display().
        * Parameter
        *    Null.
        * Return
        *    Null.
        *************************************************************/
        delay(500);
    }
}
