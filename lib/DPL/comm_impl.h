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
