template <typename T>
void Out(T str, int mode)
{
    Serial.print(String(str));
    if (mode == NEW_LINE)
        Serial.println("");
}

template <typename T>
void Out(T str)
{
    Serial.print(String(str));
}

void Out(DPL_RGB::RGB LED_OBJ){
    Out("R: " + S(LED_OBJ.color.R) + " on Pin " + S(LED_OBJ.PIN_R) + "\t\tG: " + S(LED_OBJ.color.G) + " on Pin " + S(LED_OBJ.PIN_G) + "\t\tB: " + S(LED_OBJ.color.B) + " on Pin " + S(LED_OBJ.PIN_B));
}

void Out(DPL_RGB::RGB LED_OBJ, int mode){
    Out("R: " + S(LED_OBJ.color.R) + " on Pin " + S(LED_OBJ.PIN_R) + "\t\tG: " + S(LED_OBJ.color.G) + " on Pin " + S(LED_OBJ.PIN_G) + "\t\tB: " + S(LED_OBJ.color.B) + " on Pin " + S(LED_OBJ.PIN_B));
    if (mode == DPL_SerialPort::NEW_LINE)
        Serial.println("");
}

void Out(String NAME, DPL_RGB::RGB LED_OBJ, int mode){
    Out(NAME + ": " + "R: " + S(LED_OBJ.color.R) + " on Pin " + S(LED_OBJ.PIN_R) + "\t\tG: " + S(LED_OBJ.color.G) + " on Pin " + S(LED_OBJ.PIN_G) + "\t\tB: " + S(LED_OBJ.color.B) + " on Pin " + S(LED_OBJ.PIN_B));
    if (mode == DPL_SerialPort::NEW_LINE)
        Serial.println("");
}

int In ();

float In (String arg);
