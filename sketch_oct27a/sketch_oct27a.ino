void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
if (Serial.available() >0){
  char mensagem = Serial.read();
  Serial.print(mensagem);
  }
}