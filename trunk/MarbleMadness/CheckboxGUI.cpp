#include "CheckboxGUI.h"

namespace mmgui {

CheckboxGUI::CheckboxGUI(bool checked) {
	this->h = this->w = this->x = this->y = 0;
	this->idTextura = -1;
	this->idTexturaChecked  = -1;
	this->checked = checked;
}
	
CheckboxGUI::CheckboxGUI(int x, int y, int w, int h, bool checked) {
	setLimites(x, y, w, h);
	this->idTextura = -1;
	this->idTexturaChecked = -1;
	this->checked = checked;
}

CheckboxGUI::~CheckboxGUI(void)
{
}

void CheckboxGUI::dibujar() {

	/*if (this->idTextura >= 0) {
		glBindTexture(GL_TEXTURE_2D, this->idTextura);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);	
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);	
		
	}*/
	if (this->checked) {
		float wdiezporc = this->w*0.1f;
		float hdiezporc = this->h*0.1f;
		//glTexCoord2f(1.0f, 0.0f);
		glColor3f(color.X(), color.Y(), color.Z());
		glBegin(GL_QUADS);

		glVertex3f(this->w-wdiezporc, 0+hdiezporc, 0);
		//glTexCoord2f(1.0f, 1.0f); 
		glVertex3f(this->w-wdiezporc, this->h-wdiezporc, 0);
		//glTexCoord2f(0.0f, 1.0f); 
		glVertex3f(0+wdiezporc, this->h-wdiezporc, 0);
		//glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(0+wdiezporc, 0+hdiezporc, 0);	
		glEnd();
	}



	//glTexCoord2f(1.0f, 0.0f);
	glBegin(GL_QUADS);
	glColor3f(1.f, 1.f, 1.f);
	glVertex3f(this->w, 0, 0);
	//glTexCoord2f(1.0f, 1.0f); 
	glVertex3f(this->w, this->h, 0);
	//glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(0, this->h, 0);
	//glTexCoord2f(0.0f, 0.0f); 
	glVertex3f(0, 0, 0);	
	glEnd();

	vector<ObjetoGUI*>::iterator it;
	for (it = this->hijos.begin(); it != this->hijos.end(); it++) {
		glPushMatrix();
		ObjetoGUI* hijo = (*it);
		glTranslatef(hijo->X(), hijo->Y(), 0.f);	
		hijo->dibujar();
		glPopMatrix();	
	}

	


}

}