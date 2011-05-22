#pragma once
#ifndef FUENTE_FT_H
#define FUENTE_FT_H

#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

#include <SDL.h>
#include <SDL_opengl.h>
#include <gl\GL.h>
#include <gl\GLU.h>

// Some STL Headers
#include <vector>
#include <string>

// Using The STL Exception Library Increases The
// Chances That Someone Else Using Our Code Will Correctly
// Catch Any Exceptions That We Throw.
#include <stdexcept>

namespace freetype {

using std::vector;
using std::string;


	class FuenteFT
	{
	private:
		float h;
		GLuint* texturas;
		GLuint baseLista;

		void crearDllist(FT_Face face, char ch, GLuint listaBase, GLuint * texturaBase);

	public:
		FuenteFT(const char* fname, unsigned int h);
		void limpiar();	
		void imprimir(float x, float y, const char* fmt, ...);


		~FuenteFT(void);
	};

}

#endif FUENTE_FT_H;
