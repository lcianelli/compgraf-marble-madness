#pragma once
#ifndef ESTADO_VISUAL_H
#define ESTADO_VISUAL_H

class state {
public:
	int refreshFreq; 
	static const int FPS_30 = 30;
	static const int FPS_60 = 60;

protected:
	bool loop;
	virtual void processEvents() = 0;
	virtual void drawScreen() = 0;
public:
	virtual void run() = 0;
	virtual ~state(void);
};

#endif
