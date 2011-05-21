#include "HUD.h"


HUD::HUD(void)
{
}

void HUD::dibujarHud()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();

		SDL_Surface* s = SDL_GetVideoSurface();
		glOrtho(0.f, s->w, 0.f, s->h, -1.f, 1.f);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glViewport(0, 0, (GLsizei) s->w, (GLsizei) s->h);
			glBegin(GL_QUADS);
			
			glEnd();
		glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

}

HUD::~HUD(void)
{
}
