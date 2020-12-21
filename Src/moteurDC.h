void moteurDC_Init(void);// Configurer PWM
void moteurDC_SetSpeed(int speed);//Changer Duty cycle
int moteurDC_GetDirection(void);
int moteurDC_SetDirection(int direction); //Changer l'etat de Interrupter qui controle le sens