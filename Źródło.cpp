#include <iostream>

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

float MinMax(float value, float a, float b)
{
    if (value > b)
    {
        value = b;
    }
    else if (value < a)
    {
        value = a;
    }

    return value;
}

float PIDcontroller(
    float Kp, //Propotional coefficient 
    float Ki, //Integral coefficient 
    float Kd, //Derivative coefficient
    float& pastError, //Last-iteration error
    float desiredValue, //Set-point
    float realValue, //Real-world filtered data
    float& pastErrorSum) //Sum of the errors
{
    float P, I, D;
    float current_error = realValue - desiredValue;

    //Propotional Part
    P = Kp * (-current_error);
    //Integral Part
    I = Ki * (-pastErrorSum);
    I = MinMax(I, -70, 70);
    //Derivative Part
    D = Kd * (pastError - current_error);


    float potential_return = P + I + D;

    float real_return;
    real_return = MinMax(potential_return, -100, 100);

    pastError = current_error;
    pastErrorSum = pastErrorSum + (current_error / 4);
    pastErrorSum = MinMax(pastErrorSum, -100 / Ki, 100 / Ki);

    return real_return;
}


int main()
{
    float past_error = -120, errorSum = 0, the_value = -60;
    float velocity = 0;
    for (int i = 0; i < 500; i++) {
        /*velocity += -5;
        velocity += 0.1 * PIDcontroller(1.5, 0.5, 2, past_error, 60, the_value, errorSum);
        the_value += velocity;*/
    }
    for (int i = 0; i < 198; i++) {

        std::cout << the_value << std::endl;

        velocity += -7;
        velocity += 0.3 * PIDcontroller(1.1, 0.5, 4, past_error, 60, the_value, errorSum);

        the_value += velocity;

    }

    return 0;
}
