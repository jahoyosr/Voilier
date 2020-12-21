#ifndef servomoteur_H
#define servomoteur_H

void servomoteur_Init(void);//Configurer PWM, Timers.
void servomoteur_SetPos(int angle);//Cambiar posicion del servo (relacion Duty cycle/Posicion)
uint32_t servomoteur_GetPos(void);
void roulis_critique(void); //Accion de control cuando Roulis mayor a 45deg

#endif