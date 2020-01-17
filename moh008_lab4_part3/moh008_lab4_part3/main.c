/*
 * Lab Section: 21
 * Assignment: Lab #4 Exercise #3
 * I acknowledge all content contained herein, excluding template
	or example code, is my own original work.
 */ 

#include <avr/io.h>
enum States{Locked, prsd, rlsd, Unlocked} state;
unsigned char A = 0x00;
unsigned char tmpB = 0x00;
void Tick_SM_B();

void Tick_SM_B()
{
	switch(state)
	{
		case Locked:
		if(A == 0x04)
		{
			state = prsd;
		}
		else
		{
			state = Locked;
		}
		break;
		
		case prsd:
		if(A == 0x02)
		{
			state = Locked;
		}
		else if(A == 0x00)
		{
			state = rlsd;
		}
		else if(A == 0x04)
		{
			state = prsd;
		}
		else
		{
			state = Locked;
		}
		break;
		
		case rlsd:
		if(A == 0x02)
		{
			state = Unlocked;
		}
		else
		{
			state = Locked;
		}
		break;
		
		case Unlocked:
		if(A == 0x80)
		{
			state = Locked;
		}
		else
		{
			state = Unlocked;
		}
		break;
		
		default:
		state = Locked;
		break;
	}
	switch(state)
	{
		case Locked:
		tmpB = 0x00;
		break;
		
		case prsd:
		break;
		
		case rlsd:
		break;
		
		case Unlocked:
		tmpB = 0x01;
		break;
		
		default:
		break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	state = Locked;
	/* Replace with your application code */
	while (1)
	{
		A = PINA;
		Tick_SM_B();
		PORTB = tmpB;
	}
	return 0;
}
