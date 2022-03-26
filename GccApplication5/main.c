/*
 * GccApplication5.c
 *
 * Created: 6/4/2021 10:42:51 AM
 * Author : Billy
 */ 

#include <avr/io.h>
#include "avr.h"
#include "lcd.h"
#include <stdio.h>
#include <math.h>
#include "music.h"
#include <time.h>
#include <stdlib.h>



enum keyLabel{None, KeyStar, Key0, KeyHash, KeyD, Key1, Key2, Key3, KeyA, Key4, Key5, Key6, KeyB, Key7, Key8, Key9, KeyC};

enum musicState{State_Stop, State_Pause, State_Play, State_Defeat, State_Ready, State_Setup};

int is_pressed(int x, int y)
{
	DDRC = 0xF0;
	PORTC = ~(1 << (y + 4));
	return !(PINC & (1 << x));
}

int get_key()
{
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			if (is_pressed(i,j))
			{
				return i + (j*4) + 1;
			}
		}
	}
	return 0;
}

void gameTick()
{
	
}

void playNote(int frequency, int durationMsec)
{
	float f_calibration = 1.6;
	float d_calibration = 0.6325;
	float duration = durationMsec / 1000.0;
	int periodNsec;
	int loopLimit;
	
	if (frequency == 0)
	{
		loopLimit = (400 * f_calibration) * duration * d_calibration;
		periodNsec = 250 / f_calibration;
	}
	else
	{
		loopLimit = (frequency * f_calibration)  * duration * d_calibration;
		periodNsec = 100000.0 / (frequency * f_calibration);
	}

	for(long j=0; j<loopLimit; j++)
	{
		if(frequency == REST)
		{
			CLR_BIT(PORTB,3);
		}
		else
		{
			SET_BIT(PORTB,3);
		}
		avr_wait_2(periodNsec/2);
		CLR_BIT(PORTB,3);
		avr_wait_2(periodNsec/2);
	}
}

struct Note
{
	int frequency;
	float duration;
};

struct Song
{
	struct Note notes[32];
	int noteLength;
	int bpm;
	char name[17];
};

struct DefeatSong
{
	struct Note notes[16];
	int noteLength;
	int bpm;
	char name[17];
};

struct ReadySong
{
	struct Note notes[16];
	int noteLength;
	int bpm;
	char name[17];
};

void playMarioSong(struct Song* song, int noteNumber, int bpm, float pitch)
{
	//playNote(FREQ_C5,1000); //C4
	//playNote(659,1000); //E4
	int f = song->notes[noteNumber].frequency;
	double d = song->notes[noteNumber].duration;
	
	//int f = FREQ_G5;
	//double d = 1;
	
	int freq = f * pitch;
	double ratio = 60.0 / bpm;
	double dur = ratio * 4000.0 * d;
	
	playNote(freq,dur);
}

void playDefeatSong(struct DefeatSong* song, int noteNumber, int bpm, float pitch)
{
	//playNote(FREQ_C5,1000); //C4
	//playNote(659,1000); //E4
	int f = song->notes[noteNumber].frequency;
	double d = song->notes[noteNumber].duration;
	
	//int f = FREQ_G5;
	//double d = 1;
	
	int freq = f * pitch;
	double ratio = 60.0 / bpm;
	double dur = ratio * 4000.0 * d;
	
	playNote(freq,dur);
}

void playReadySong(struct ReadySong* song, int noteNumber, int bpm, float pitch)
{
	//playNote(FREQ_C5,1000); //C4
	//playNote(659,1000); //E4
	int f = song->notes[noteNumber].frequency;
	double d = song->notes[noteNumber].duration;
	
	//int f = FREQ_G5;
	//double d = 1;
	
	int freq = f * pitch;
	double ratio = 60.0 / bpm;
	double dur = ratio * 4000.0 * d;
	
	playNote(freq,dur);
}

void writeSong_Mario(struct Song* song)
{
	int n = 0;
	int mark = 0;
	int loopLength = 0;
	/*
	//Intro
	song->notes[n].frequency = FREQ_E5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_E5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_E5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_C5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_E5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
		
	song->notes[n].frequency = FREQ_G5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_G4; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	*/
	//Part 1
	song->notes[n].frequency = FREQ_C5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_G4; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_E4; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_A4; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_B4; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_A4S; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_A4; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	
	song->notes[n].frequency = FREQ_G4; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_E5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_G5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_A5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_F5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_G5; song->notes[n].duration = 1.0/8; n++;
	
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_E5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_C5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_D5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_B4; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	/*
	//Part1 Repeat
	mark = n;
	loopLength = 32;
	for(int i=0; i<loopLength; i++)
	{
		song->notes[mark+i].frequency = song->notes[mark+i-loopLength].frequency;
		song->notes[mark+i].duration = song->notes[mark+i-loopLength].duration;
		n++;
	}
	
	//Part2
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_G5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_F5S; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_F5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_D5S; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_E5; song->notes[n].duration = 1.0/8; n++;
	
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_G4S; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_A4; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_C5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_A4; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_C5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_D5; song->notes[n].duration = 1.0/8; n++;
	
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_G5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_F5S; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_F5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_D5S; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_E5; song->notes[n].duration = 1.0/8; n++;
	
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_C6; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_C6; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_C6; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_G5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_F5S; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_F5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_D5S; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_E5; song->notes[n].duration = 1.0/8; n++;
	
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_G4S; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_A4; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_C5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_A4; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_C5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_D5; song->notes[n].duration = 1.0/8; n++;
	
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_D5S; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_D5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	
	song->notes[n].frequency = FREQ_C5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	
	//Part2 Repeat
	mark = n;
	loopLength = 64;
	for(int i=0; i<loopLength; i++)
	{
		song->notes[mark+i].frequency = song->notes[mark+i-loopLength].frequency;
		song->notes[mark+i].duration = song->notes[mark+i-loopLength].duration;
		n++;
	}
	
	//Part 3
	song->notes[n].frequency = FREQ_C5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_C5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_C5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_C5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_D5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	
	song->notes[n].frequency = FREQ_E5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_C5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_A4; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_G4; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	
	song->notes[n].frequency = FREQ_C5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_C5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_C5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_C5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_D5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_E5; song->notes[n].duration = 1.0/8; n++;
	
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	
	song->notes[n].frequency = FREQ_C5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_C5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_C5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_C5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_D5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	
	song->notes[n].frequency = FREQ_E5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_C5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_A4; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_G4; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	*/
	song->noteLength = n;
	song->bpm = 180;
	sprintf(song->name,"MARIO");
}

void writeSong_MarioDefeat(struct DefeatSong* song)
{
	int n = 0;
	//Part2
	song->notes[n].frequency = FREQ_B4; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_F5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_F5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_F5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_E5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_D5; song->notes[n].duration = 1.0/8; n++;
		
	song->notes[n].frequency = FREQ_C5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_E4; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_E4; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_C4; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	
	song->noteLength = n;
	song->bpm = 180;
	sprintf(song->name,"DEFEAT");
}

void writeSong_MarioReady(struct ReadySong* song)
{
	int n = 0;
	//Part2
	song->notes[n].frequency = FREQ_C5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_C5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_C5; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	
	song->notes[n].frequency = FREQ_G4; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_G4; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = FREQ_G4; song->notes[n].duration = 1.0/8; n++;
	song->notes[n].frequency = REST   ; song->notes[n].duration = 1.0/8; n++;
	
	song->noteLength = n;
	song->bpm = 180;
	sprintf(song->name,"READY");
}

int getRandom(int rndMin, int rndMax)
{
	return rndMin + (rand() % (rndMax-rndMin+1));      // Returns a pseudo-random integer between 0 and RAND_MAX.
}

void resetString(char *str, int length)
{
	for(int i=0; i<length; i++)
	{
		str[i] = ' ';
	}
}


int main(void)
{
	srand(time(NULL));   // Initialization, should only be called once.
	
	
	lcd_init();
	//playNote(523,1000); //C5
	
	//Music setup
	struct Song marioMusic;
	struct DefeatSong defeatMusic;
	struct ReadySong readyMusic;
	writeSong_Mario(&marioMusic);
	writeSong_MarioDefeat(&defeatMusic);
	writeSong_MarioReady(&readyMusic);
	int notePointer = 0;
	int bpm = 60;
	double pitch = 1;
	int bpm_modifier = 0;
	double pitch_modifier = 0;
	
	//Speaker setup
	SET_BIT(DDRB,3); //PORTB3 Output Mode
	
	//Device Setup
	int myState = State_Setup;
	int isPressing = None;
	int setupLoop = 10;
	int hiScore = 0;
	
	//Game Setup
	int advanceTimer = 0;
	int advanceCounter = 0;
	int playerJumpCounter = 0;
	int playerJumpValue = 4;
	int score = 0;
	int obstacleCounter = 0;
	int obstacleFrequency = 1; //difficulty
	int spaceCounter = 0;
	int spaceFrequency = 6;
	int difficultyUpInterval = 50;
	int buffCounter = 0;
	int buffValue = 20;
	
	char line1[17] = "                ";
	char line2[17] = "                ";
	char line0[17] = "1234567890123456";
	char scoreTxt[6];
	char hiScoreTxt[6];
	
	char playerChar = 'O';
	char playerNormalChar = 'O';
	char playerBuffChar = '>';
	char playerInvulChar = '?';
	char playerDefeatChar = 'X';
	char obstacleChar = '#';
	char itemBuffChar = 'o';
	
	
	lcd_clr();
	lcd_pos(0,0);
	lcd_puts("STANDBY",7);
	avr_wait(100);
	
	int n = None;
    while (1) 
    {
		
		//=======================================================
		//===                  BUTTON UPDATE                  ===
		//=======================================================
		if(setupLoop>0)
		{
			setupLoop--;
		}
		else
		{
			n = get_key();
		}
		
		if(isPressing == None && n != None) //button trigger OnPress
		{
			switch(n)
			{
				case KeyStar:
					//Restart Button
					if(myState != State_Ready)
					{
						notePointer = 0;
					}
					myState = State_Ready;
					break;
				
				case Key0:
					//Pause Button
					if(myState == State_Play)
					{
						myState = State_Pause;
					}
					break;
				
				case KeyHash:
					//Play Button
					switch(myState)
					{
						case State_Pause:
							myState = State_Play;
							break;
						case State_Ready:
							lcd_clr();
							resetString(line2,16);
							
							//=======
							// SETUP
							//=======
							notePointer = 0;
							
							advanceTimer = 0;
							advanceCounter = 0;
							playerJumpCounter = 0;
							playerJumpValue = 4;
							score = 0;
							obstacleCounter = 0;
							obstacleFrequency = 1; //difficulty
							spaceCounter = 0;
							spaceFrequency = 6;
							difficultyUpInterval = 50;
							buffCounter = 0;
							buffValue = 20;
								
							myState = State_Play;
					}
					break;
				
				case KeyA:
					playerChar = playerNormalChar;
					break;
					
				case KeyB:
					playerChar = playerInvulChar;
					break;
					
				case KeyC:
					if(myState == State_Ready)
					{
						hiScore = 0;
					}
					break;
					
				case KeyD:
					break;
				
				case Key2:
					//Jump Button
					if(myState == State_Play && playerJumpCounter == 0)
					{
						playerJumpCounter = playerJumpValue;
					}
					break;
				
				case Key8:
					break;
					
				case Key4:
					break;
				
				case Key6:
					break;
					
				case Key5:
					break;
					
			}
		}
		isPressing = n;
		
		
		
		
		switch(myState)
		{
			case State_Setup:
				lcd_clr();
				lcd_pos(0,0);
				lcd_puts("SETUP",5);
				if(setupLoop<=0)
				{
					notePointer = 0;
					myState = State_Ready;
				}
				break;
			case State_Ready:
				lcd_clr();
				lcd_pos(0,0);
				lcd_puts("READY",5);
				
				sprintf(scoreTxt,"%5d",hiScore);
				lcd_pos(0,11);
				lcd_puts(scoreTxt,5);
				lcd_pos(1,0);
				lcd_put(playerChar);
				
				lcd_pos(1,4);
				lcd_put(obstacleChar);
				
				lcd_pos(1,6);
				lcd_put(itemBuffChar);
				
				bpm = readyMusic.bpm + bpm_modifier;
				pitch = 1 + pitch_modifier/100.0;
				playReadySong(&readyMusic,notePointer,bpm,pitch);
				notePointer++;
				if (notePointer == readyMusic.noteLength)
				{
					notePointer = 0;
				}
				
				break;
				
			case State_Play:
				
				
				//=======================================================
				//===                    GAME UPDATE                  ===
				//=======================================================
				advanceCounter++;
				if(playerChar != playerInvulChar)
				{
					score += obstacleFrequency;
				}
				
				//===================
				// DIFFICULTY UPDATE
				//===================
				if(advanceCounter % difficultyUpInterval == 0 && obstacleFrequency<10)
				{
					obstacleFrequency++;
				}
				if(advanceCounter % difficultyUpInterval == 0 && spaceFrequency>0)
				{
					spaceFrequency--;
					if(spaceFrequency == 1) spaceFrequency = 0;
				}
				
				//=============
				// BUFF UPDATE
				//=============
				
				if(buffCounter>0)
				{
					buffCounter--;
					if(buffCounter == 0)
					{
						playerChar = playerNormalChar;
					}
				}
				
				//===============
				// PLAYER UPDATE
				//===============
				if(playerJumpCounter>0) playerJumpCounter--;
				if (playerJumpCounter>0)
				{
					lcd_pos(0,0);
					lcd_put(playerChar);
					line2[0] = ' ';
					
				}
				else
				{
					
					lcd_pos(0,0);
					lcd_put(' ');
					line2[0] = playerChar;
				}
				
				//===============
				// STAGE ADVANCE
				//===============
				for(int i=0; i<15; i++)
				{
					//==================
					// DEFEAT CONDITION
					//==================
					if(i==0)
					{
						
						if(line2[0] == playerChar)
						{
							if(line2[0] == playerNormalChar && line2[1] == obstacleChar)
							{
								line2[0] = playerDefeatChar;
							}
							else
							{
								if(line2[0] != playerInvulChar && line2[1] == itemBuffChar)
								{
									//ACTIVATE BUFF
									playerChar = playerBuffChar;
									buffCounter = buffValue;
								}
								line2[0] = playerChar;
							}
						}
						else
						{
							line2[0] = line2[1];
						}
					}
					else
					{
						line2[i] = line2[i+1];
					}
				}
				
				//=====================
				// OBSTACLE / ITEM SET
				//=====================
				if(obstacleCounter < playerJumpValue-1 && spaceCounter >= spaceFrequency)
				{
					int r = getRandom(1,10);
					int s = getRandom(1,60);
					if(s <= 1)
					{
						obstacleCounter = 0;
						spaceCounter++;
						line2[15] = itemBuffChar;
					}
					else if(r <= obstacleFrequency)
					{
						obstacleCounter++;
						spaceCounter = 0;
						line2[15] = obstacleChar;
					}
					else
					{
						obstacleCounter = 0;
						spaceCounter++;
						line2[15] = ' ';
					}
				}
				else
				{
					obstacleCounter = 0;
					spaceCounter++;
					line2[15] = ' ';
				}
				
				//=======================================================
				//===                   SCREEN UPDATE                 ===
				//=======================================================
				//update buff
				if(playerChar == playerBuffChar)
				{
					sprintf(scoreTxt,"%2d",buffCounter);
					lcd_pos(0,2);
					lcd_puts(scoreTxt,2);
				}
				else
				{
					lcd_pos(0,2);
					lcd_puts("  ",2);
				}
				
				//update score
				sprintf(scoreTxt,"%5d",score);
				lcd_pos(0,11);
				lcd_puts(scoreTxt,5);
				
				//update stage
				lcd_pos(1,0);
				lcd_puts(line2,16);
				
				//=======================================================
				//===                       DEFEAT                    ===
				//=======================================================
				if(line2[0] == playerDefeatChar)
				{
					notePointer = 0;
					sprintf(scoreTxt,"%5d",hiScore);
					lcd_pos(0,2);
					lcd_puts(scoreTxt,5);
					
					if(hiScore<score)
					{
						lcd_pos(0,8);
						lcd_puts("HI",2);
						hiScore = score;
					}
					
					myState = State_Defeat;
					break;
				}
				
				//=======================================================
				//===           MUSIC UPDATE - TIMER DELAY            ===
				//=======================================================
				
				bpm = marioMusic.bpm + bpm_modifier;
				pitch = 1 + pitch_modifier/100.0;
				playMarioSong(&marioMusic,notePointer,bpm,pitch);
				notePointer++;
				if (notePointer == marioMusic.noteLength)
				{
					notePointer = 0;
				}
				//lcd_clr();
			
			
				break;
				
				
				
			case State_Defeat:
				if (notePointer < defeatMusic.noteLength)
				{
					bpm = defeatMusic.bpm + bpm_modifier;
					pitch = 1 + pitch_modifier/100.0;
					playDefeatSong(&defeatMusic,notePointer,bpm,pitch);
					notePointer++;
				}
				else
				{
					avr_wait(100);
				}
				
				break;
			case State_Pause:
				bpm = marioMusic.bpm + bpm_modifier;
				pitch = 1 + pitch_modifier/100.0;
				playMarioSong(&marioMusic,notePointer,bpm,pitch);
				notePointer++;
				if (notePointer == marioMusic.noteLength)
				{
					notePointer = 0;
				}
				break;
				
		}
		
    }
}

