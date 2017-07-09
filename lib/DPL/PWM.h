template <typename T>
void ANALOG_IO_SETPWMSIGNAL (T amount){
    amount = constrain(amount, 0, 255);
    analogWrite(pinNumber, amount);
}
