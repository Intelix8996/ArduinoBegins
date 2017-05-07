template <typename T>
void Set(int pinNum, T amount){
    amount = constrain(amount, 0, 255);
    analogWrite(pinNum, amount);
}
