int *g;
int *h;
void setup() {
  // put your setup code here, to run once:

  //All of these will output all of the same thing set before the prints.

  
  int x = 12;
  int a = 11;
  int b = 13;
  Serial.begin(115200);
  int *y = &x;
  Serial.println(x);
  Serial.println(*y);
  Serial.println();
  x = 33;
  Serial.println(x);
  Serial.println(*y);
  Serial.println();
  *y = 10;
  Serial.println(x);
  Serial.println(*y);
  Serial.println();
  foo(&x);
  Serial.println(x);
  Serial.println(*y);
  Serial.println(*g);
  Serial.println();
  *g = 2;
  Serial.println(x);
  Serial.println(*y);
  Serial.println(*g);
  Serial.println();
  x = 4;
  Serial.println(x);
  Serial.println(*y);
  Serial.println(*g);
  Serial.println();
  bar(y);
  *h = 3;
  Serial.println(x);
  Serial.println(*y);
  Serial.println(*g);
  Serial.println(*h);
  Serial.println();
  *g = 5;
  Serial.println(x);
  Serial.println(*y);
  Serial.println(*g);
  Serial.println(*h);
  Serial.println();

  *y = a;
  Serial.println(x);
  Serial.println(*y);
  Serial.println(*g);
  Serial.println(*h);
  Serial.println();

  b = *y;
  Serial.println(x);
  Serial.println(*y);
  Serial.println(*g);
  Serial.println(*h);
  Serial.println(b);
  Serial.println();

  b = 15;
  Serial.println(x); //prints 11
  Serial.println(*y);
  Serial.println(*g);
  Serial.println(*h);
  Serial.println(b); // prints 15
  Serial.println();

  if(*h = 5) {
    Serial.println("Prints");
  }
  
}


void foo(int *z) {
  g = z;
}

void bar(int *v) {
  h = v;
}

void loop() {
  // put your main code here, to run repeatedly:

}
