template <typename T>
void Set(T amount){
    amount = constrain(amount, 0, 255);
    analogWrite(pinNumber, amount);
}
