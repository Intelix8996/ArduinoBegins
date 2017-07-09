template <typename T>
void SERIAL_IO_SENDDATA(T str, int mode)
{
    Serial.print(String(str));
    if (mode == NEW_LINE)
        Serial.println("");
}

template <typename T>
void SERIAL_IO_SENDDATA(T str)
{
    Serial.print(String(str));
}

void SERIAL_IO_SENDDATA(DPL_RGB::RGB LED_OBJ){
    SERIAL_IO_SENDDATA("R: " + S(LED_OBJ.color.R) + " on Pin " + S(LED_OBJ.PIN_R) + "\t\tG: " + S(LED_OBJ.color.G) + " on Pin " + S(LED_OBJ.PIN_G) + "\t\tB: " + S(LED_OBJ.color.B) + " on Pin " + S(LED_OBJ.PIN_B));
}

void SERIAL_IO_SENDDATA(DPL_RGB::RGB LED_OBJ, int mode){
    SERIAL_IO_SENDDATA("R: " + S(LED_OBJ.color.R) + " on Pin " + S(LED_OBJ.PIN_R) + "\t\tG: " + S(LED_OBJ.color.G) + " on Pin " + S(LED_OBJ.PIN_G) + "\t\tB: " + S(LED_OBJ.color.B) + " on Pin " + S(LED_OBJ.PIN_B));
    if (mode == DPL_SerialPort::NEW_LINE)
        Serial.println("");
}

void SERIAL_IO_SENDDATA(String NAME, DPL_RGB::RGB LED_OBJ, int mode){
    SERIAL_IO_SENDDATA(NAME + ": " + "R: " + S(LED_OBJ.color.R) + " on Pin " + S(LED_OBJ.PIN_R) + "\t\tG: " + S(LED_OBJ.color.G) + " on Pin " + S(LED_OBJ.PIN_G) + "\t\tB: " + S(LED_OBJ.color.B) + " on Pin " + S(LED_OBJ.PIN_B));
    if (mode == DPL_SerialPort::NEW_LINE)
        Serial.println("");
}

int SERIAL_IO_READNUMBER ();

float SERIAL_IO_READNUMBER (String arg);
