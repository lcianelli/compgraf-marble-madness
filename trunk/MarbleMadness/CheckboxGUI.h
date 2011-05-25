#pragma once
#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "ObjetoGUI.h"
#include "Vector.h"

namespace mmgui {
class CheckboxGUI : public ObjetoGUI
{
private:
	int idTextura;
	int idTexturaChecked;
	bool checked;

public:
	CheckboxGUI(bool checked);
	CheckboxGUI(int x, int y, int w, int h, bool checked);
	
	//le da el id de la textura a usar como imagen
	inline void setImagenUnchecked(int idTex) { this->idTextura = idTex;}
	inline void setImagenChecked(int idTex) { this->idTexturaChecked = idTex;}
	inline void setChecked(bool checked) { this->checked = checked;}
	inline bool isChecked() { return this->checked;}

	inline void onClick() { this->checked = !this->checked;}

	void dibujar();
	virtual ~CheckboxGUI(void);
};

}
#endif CHECKBOX_H;