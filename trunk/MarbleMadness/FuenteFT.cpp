#include "FuenteFT.h"

namespace freetype {


//primer potencia de 2 >= a
inline int next_p2 (int a )
{
	int rval=1;
	// (rval<<=1) == (rval*=2) 
	while(rval<a) rval<<=1;
	return rval;
}

FuenteFT::FuenteFT(const char* fname, unsigned int h)
{
	// Allocate Some Memory To Store The Texture Ids.
	texturas = new GLuint[128];

	this->h=h;

	// Create And Initilize A FreeType Font Library.
	FT_Library library;
	if (FT_Init_FreeType( &library )) 
		throw std::runtime_error("FT_Init_FreeType failed");

	// The Object In Which FreeType Holds Information On A Given
	// Font Is Called A "face".
	FT_Face face;

	// This Is Where We Load In The Font Information From The File.
	// Of All The Places Where The Code Might Die, This Is The Most Likely,
	// As FT_New_Face Will Fail If The Font File Does Not Exist Or Is Somehow Broken.
	if (FT_New_Face( library, fname, 0, &face )) 
		throw std::runtime_error("FT_New_Face failed (there is probably a problem with your font file)");

	// For Some Twisted Reason, FreeType Measures Font Size
	// In Terms Of 1/64ths Of Pixels.  Thus, To Make A Font
	// h Pixels High, We Need To Request A Size Of h*64.
	// (h << 6 Is Just A Prettier Way Of Writing h*64)
	FT_Set_Char_Size( face, h << 6, h << 6, 96, 96);

	// Here We Ask OpenGL To Allocate Resources For
	// All The Textures And Display Lists Which We
	// Are About To Create.  
	baseLista=glGenLists(128);
	glGenTextures( 128, texturas );

	// This Is Where We Actually Create Each Of The Fonts Display Lists.
	for(unsigned char i=0;i<128;i++)
		crearDllist(face,i,baseLista,texturas);

	// We Don't Need The Face Information Now That The Display
	// Lists Have Been Created, So We Free The Assosiated Resources.
	FT_Done_Face(face);

	// Ditto For The Font Library.
	FT_Done_FreeType(library);


}

void FuenteFT::limpiar() {
	glDeleteLists(baseLista,128);
	glDeleteTextures(128,texturas);
	delete [] texturas;
}

void FuenteFT::imprimir(const FuenteFT &fuente, float x, float y, const char* text, ...) {

}

void FuenteFT::crearDllist(FT_Face face, char ch, GLuint listaBase, GLuint * texturaBase) {
	// The First Thing We Do Is Get FreeType To Render Our Character
	// Into A Bitmap.  This Actually Requires A Couple Of FreeType Commands:

	// Load The Glyph For Our Character.
	if(FT_Load_Glyph( face, FT_Get_Char_Index( face, ch ), FT_LOAD_DEFAULT ))
		throw std::runtime_error("FT_Load_Glyph failed");

	// Move The Face's Glyph Into A Glyph Object.
	FT_Glyph glyph;
	if(FT_Get_Glyph( face->glyph, &glyph ))
		throw std::runtime_error("FT_Get_Glyph failed");

	// Convert The Glyph To A Bitmap.
	FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
	FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

	// This Reference Will Make Accessing The Bitmap Easier.
	FT_Bitmap& bitmap=bitmap_glyph->bitmap;

	// Use Our Helper Function To Get The Widths Of
	// The Bitmap Data That We Will Need In Order To Create
	// Our Texture.
	int width = next_p2( bitmap.width );
	int height = next_p2( bitmap.rows );

	// Allocate Memory For The Texture Data.
	GLubyte* expanded_data = new GLubyte[ 2 * width * height];

	// Here We Fill In The Data For The Expanded Bitmap.
	// Notice That We Are Using A Two Channel Bitmap (One For
	// Channel Luminosity And One For Alpha), But We Assign
	// Both Luminosity And Alpha To The Value That We
	// Find In The FreeType Bitmap. 
	// We Use The ?: Operator To Say That Value Which We Use
	// Will Be 0 If We Are In The Padding Zone, And Whatever
	// Is The FreeType Bitmap Otherwise.
	for(int j=0; j <height;j++) {
		for(int i=0; i < width; i++){
			expanded_data[2*(i+j*width)]= expanded_data[2*(i+j*width)+1] = 
				(i>=bitmap.width || j>=bitmap.rows) ?
				0 : bitmap.buffer[i + bitmap.width*j];
		}
	}

	// Now We Just Setup Some Texture Parameters.
	
	glBindTexture( GL_TEXTURE_2D, texturaBase[ch]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	// Here We Actually Create The Texture Itself, Notice
	// That We Are Using GL_LUMINANCE_ALPHA To Indicate That
	// We Are Using 2 Channel Data.
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
		GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expanded_data );

	// With The Texture Created, We Don't Need The Expanded Data Anymore.
	delete [] expanded_data;
	// Now We Create The Display List
	glNewList(listaBase+ch,GL_COMPILE);

	glBindTexture(GL_TEXTURE_2D,texturaBase[ch]);

	glPushMatrix();

	// First We Need To Move Over A Little So That
	// The Character Has The Right Amount Of Space
	// Between It And The One Before It.
	glTranslatef(bitmap_glyph->left,0,0);

	// Now We Move Down A Little In The Case That The
	// Bitmap Extends Past The Bottom Of The Line 
	// This Is Only True For Characters Like 'g' Or 'y'.
	glTranslatef(0,bitmap_glyph->top-bitmap.rows,0);

	// Now We Need To Account For The Fact That Many Of
	// Our Textures Are Filled With Empty Padding Space.
	// We Figure What Portion Of The Texture Is Used By 
	// The Actual Character And Store That Information In
	// The x And y Variables, Then When We Draw The
	// Quad, We Will Only Reference The Parts Of The Texture
	// That Contains The Character Itself.
	float   x=(float)bitmap.width / (float)width,
	y=(float)bitmap.rows / (float)height;

	// Here We Draw The Texturemapped Quads.
	// The Bitmap That We Got From FreeType Was Not 
	// Oriented Quite Like We Would Like It To Be,
	// But We Link The Texture To The Quad
	// In Such A Way That The Result Will Be Properly Aligned.
	glBegin(GL_QUADS);
	glTexCoord2d(0,0); glVertex2f(0,bitmap.rows);
	glTexCoord2d(0,y); glVertex2f(0,0);
	glTexCoord2d(x,y); glVertex2f(bitmap.width,0);
	glTexCoord2d(x,0); glVertex2f(bitmap.width,bitmap.rows);
	glEnd();
	glPopMatrix();
	glTranslatef(face->glyph->advance.x >> 6 ,0,0);

	// Increment The Raster Position As If We Were A Bitmap Font.
	// (Only Needed If You Want To Calculate Text Length)
	// glBitmap(0,0,0,0,face->glyph->advance.x >> 6,0,NULL);

	// Finish The Display List
	glEndList();

}


FuenteFT::~FuenteFT(void)
{
}



}
