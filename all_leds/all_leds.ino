void setup()
{
pinMode( 3 , OUTPUT);
pinMode( 13 , OUTPUT);
}

void loop()
{
digitalWrite( 13 , HIGH );
analogWrite(3 , 32);
delay( 100 );
digitalWrite( 13 , LOW );
analogWrite(3 , 0);
delay( 1000 );
}


