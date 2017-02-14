#include "glexp.h"

PFNGLMULTITEXCOORD1FPROC				glMultiTexCoord1f			= NULL;
PFNGLMULTITEXCOORD2FPROC				glMultiTexCoord2f			= NULL;
PFNGLMULTITEXCOORD2FVPROC				glMultiTexCoord2fv			= NULL;
PFNGLMULTITEXCOORD3FPROC				glMultiTexCoord3f			= NULL;
PFNGLMULTITEXCOORD4FPROC				glMultiTexCoord4f			= NULL;
PFNGLACTIVETEXTUREPROC				    glActiveTexture				= NULL;
PFNGLCLIENTACTIVETEXTUREPROC			glClientActiveTexture		= NULL;
PFNGLUSEPROGRAMPROC						glUseProgram				= NULL;
PFNGLCREATEPROGRAMPROC					glCreateProgram				= NULL;
PFNGLDELETEPROGRAMPROC					glDeleteProgram				= NULL;
PFNGLCREATESHADERPROC					glCreateShader				= NULL;
PFNGLDELETESHADERPROC					glDeleteShader				= NULL;
PFNGLSHADERSOURCEPROC					glShaderSource				= NULL;
PFNGLATTACHSHADERPROC					glAttachShader				= NULL;
PFNGLLINKPROGRAMPROC				    glLinkProgram				= NULL;
PFNGLCOMPILESHADERPROC					glCompileShader				= NULL;
PFNGLGENQUERIESPROC						glGenQueries				= NULL;
PFNGLDELETEQUERIESPROC					glDeleteQueries				= NULL;
PFNGLISQUERYPROC						glIsQuery					= NULL;
PFNGLBEGINQUERYPROC						glBeginQuery				= NULL;
PFNGLENDQUERYPROC						glEndQuery					= NULL;
PFNGLGETQUERYOBJECTIVPROC				glGetQueryObjectiv			= NULL;
PFNGLBEGINCONDITIONALRENDERPROC			glBeginConditionalRender	= NULL;
PFNGLENDCONDITIONALRENDERPROC			glEndConditionalRender		= NULL;
PFNGLPOINTPARAMETERFPROC				glPointParameterf			= NULL;
PFNGLPOINTPARAMETERFVPROC				glPointParameterfv			= NULL;
PFNWGLSWAPINTERVALEXTPROC				wglSwapIntervalEXT			= NULL;
PFNGLGETUNIFORMLOCATIONPROC				glGetUniformLocation		= NULL;
PFNGLGETSHADERSOURCEPROC				glGetShaderSource			= NULL;
PFNGLUNIFORM1FPROC						glUniform1f					= NULL;
PFNGLUNIFORM2FPROC						glUniform2f					= NULL;
PFNGLUNIFORM3FPROC						glUniform3f					= NULL;
PFNGLUNIFORM4FPROC						glUniform4f					= NULL;
PFNGLUNIFORM1IPROC						glUniform1i					= NULL;
PFNGLUNIFORM2IPROC						glUniform2i					= NULL;
PFNGLUNIFORM3IPROC						glUniform3i					= NULL;
PFNGLUNIFORM4IPROC						glUniform4i					= NULL;
PFNGLUNIFORM2FVPROC						glUniform2fv				= NULL;
PFNGLUNIFORM3FVPROC						glUniform3fv				= NULL;
PFNGLUNIFORM4FVPROC						glUniform4fv				= NULL;
PFNGLUNIFORMMATRIX2FVPROC				glUniformMatrix2fv			= NULL;
PFNGLUNIFORMMATRIX3FVPROC				glUniformMatrix3fv			= NULL;
PFNGLUNIFORMMATRIX4FVPROC				glUniformMatrix4fv			= NULL;
PFNGLISPROGRAMPROC						glIsProgram					= NULL;
PFNGLBLENDFUNCSEPARATEPROC				glBlendFuncSeparate			= NULL;
PFNGLFOGCOORDFPROC						glFogCoordf					= NULL;
PFNGLFOGCOORDFVPROC						glFogCoordfv				= NULL;
PFNGLFOGCOORDDPROC						glFogCoordd					= NULL;
PFNGLFOGCOORDDVPROC						glFogCoordddv				= NULL;
PFNGLGENBUFFERSPROC						glGenBuffers				= NULL;
PFNGLBINDBUFFERPROC						glBindBuffer				= NULL;
PFNGLBUFFERDATAPROC						glBufferData				= NULL;
PFNGLMAPBUFFERPROC						glMapBuffer					= NULL;
PFNGLUNMAPBUFFERPROC					glUnmapBuffer				= NULL;
PFNGLBUFFERSUBDATAPROC					glBufferSubData				= NULL;
PFNGLDELETEBUFFERSPROC					glDeleteBuffers				= NULL;
PFNGLRENDERBUFFERSTORAGEPROC					glRenderbufferStorage					= NULL;
PFNGLGETRENDERBUFFERPARAMETERIVPROC				glGetRenderbufferParameteriv			= NULL;
PFNGLISFRAMEBUFFERPROC							glIsFrameBuffer							= NULL;
PFNGLBINDFRAMEBUFFERPROC						glBindFramebuffer 						= NULL;
PFNGLDELETEFRAMEBUFFERSPROC						glDeleteFramebuffers					= NULL;
PFNGLGENFRAMEBUFFERSPROC						glGenFramebuffers						= NULL;
PFNGLCHECKFRAMEBUFFERSTATUSPROC					glCheckFramebufferStatus				= NULL;
PFNGLFRAMEBUFFERTEXTURE1DPROC					glFramebufferTexture1D 					= NULL;
PFNGLFRAMEBUFFERTEXTURE2DPROC					glFramebufferTexture2D					= NULL;
PFNGLFRAMEBUFFERTEXTURE3DPROC					glFramebufferTexture3D					= NULL;
PFNGLFRAMEBUFFERRENDERBUFFERPROC				glFramebufferRenderbuffer 				= NULL;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC	glGetFramebufferAttachmentParameteriv 	= NULL;
PFNGLGENERATEMIPMAPPROC							glGenerateMipmap 						= NULL;
PFNGLGENRENDERBUFFERSPROC						glGenRenderbuffers						= NULL;
PFNGLDELETERENDERBUFFERSPROC					glDeleteRenderbuffers					= NULL;
PFNGLBINDRENDERBUFFERPROC						glBindRenderbuffer						= NULL;
PFNGLISRENDERBUFFERPROC							glIsRenderbuffer							= NULL;
PFNGLCLAMPCOLORARBPROC							glClampColorARB								= NULL;
PFNWGLCREATECONTEXTATTRIBSARBPROC				wglCreateContextAttribsARB					= NULL;
PFNWGLCHOOSEPIXELFORMATARBPROC					wglChoosePixelFormatARB						= NULL;
PFNGLCOMPRESSEDTEXIMAGE2DPROC					glCompressedTexImage2D						= NULL;
PFNGLCOMPRESSEDTEXIMAGE3DPROC					glCompressedTexImage3D						= NULL;
PFNGLTEXIMAGE3DPROC								glTexImage3D								= NULL;
PFNGLVERTEXATTRIB3FPROC							glVertexAttrib3f							= NULL;
PFNGLVERTEXATTRIB3FVPROC						glVertexAttrib3fv							= NULL;
PFNGLVERTEXATTRIB2FVPROC						glVertexAttrib2fv							= NULL;
PFNGLVERTEXATTRIB2FPROC							glVertexAttrib2f							= NULL;
PFNGLGETATTRIBLOCATIONPROC						glGetAttribLocation							= NULL;
PFNGLVERTEXATTRIBPOINTERPROC				    glVertexAttribPointer						= NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC				glEnableVertexAttribArray					= NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC				glDisableVertexAttribArray					= NULL;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC		glRenderbufferStorageMultisampleEXT			= NULL;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC		glRenderbufferStorageMultisampleCoverageNV			= NULL;
PFNGLBLENDEQUATIONEXTPROC						glBlendEquationEXT							= NULL;
PFNGLDRAWBUFFERSPROC							glDrawBuffers								= NULL;
PFNGLBLITFRAMEBUFFEREXTPROC						glBlitFramebufferEXT						= NULL;
PFNWGLGETEXTENSIONSSTRINGARBPROC				wglGetExtensionsStringARB					= NULL;
PFNGLBINDATTRIBLOCATIONPROC						glBindAttribLocation						= NULL;
PFNGLBINDMULTITEXTUREEXTPROC					glBindMultiTextureEXT						= NULL;
PFNGLPROGRAMPARAMETERIEXTPROC					glProgramParameteriEXT						= NULL;
PFNGLFRAMEBUFFERTEXTUREEXTPROC					glFramebufferTextureEXT						= NULL;
PFNGLFRAMEBUFFERTEXTURELAYEREXTPROC				glFramebufferTextureLayerEXT				= NULL;
PFNGLFRAMEBUFFERTEXTUREFACEEXTPROC				glFramebufferTextureFaceEXT					= NULL;
PFNGLMULTIDRAWELEMENTSPROC						glMultiDrawElements							= NULL;
PFNGLISBUFFERPROC								glIsBuffer									= NULL;

/*
=========================================
     GetOpenGLVersion
=========================================
*/
char* GetOpenGLVersion( void ) {
	return ( char* )glGetString( GL_VERSION );
}

/*
=========================================
     GetOpenGLVersion
=========================================
*/
unsigned char LoadOpenGLCore_2_0( void ) {
	
	glActiveTexture				= ( PFNGLACTIVETEXTUREPROC )   wglGetProcAddress( "glActiveTexture" );
    glMultiTexCoord2f			= ( PFNGLMULTITEXCOORD2FPROC ) wglGetProcAddress( "glMultiTexCoord2f" );
	glMultiTexCoord2fv			= ( PFNGLMULTITEXCOORD2FVPROC )wglGetProcAddress( "glMultiTexCoord2fv" );
	glMultiTexCoord3f			= ( PFNGLMULTITEXCOORD3FPROC ) wglGetProcAddress( "glMultiTexCoord3f" );
	glUseProgram				= ( PFNGLUSEPROGRAMPROC )		 wglGetProcAddress( "glUseProgram" );
	glCreateProgram				= ( PFNGLCREATEPROGRAMPROC )   wglGetProcAddress( "glCreateProgram" );
	glDeleteProgram				= ( PFNGLDELETEPROGRAMPROC )   wglGetProcAddress( "glDeleteProgram" );
	glCreateShader				= ( PFNGLCREATESHADERPROC )	 wglGetProcAddress( "glCreateShader" );
	glDeleteShader				= ( PFNGLDELETESHADERPROC )	 wglGetProcAddress( "glDeleteShader" );
	glShaderSource				= ( PFNGLSHADERSOURCEPROC )    wglGetProcAddress( "glShaderSource" );
	glAttachShader				= ( PFNGLATTACHSHADERPROC )	 wglGetProcAddress( "glAttachShader" );
	glLinkProgram				= ( PFNGLLINKPROGRAMPROC )	 wglGetProcAddress( "glLinkProgram" );
	glCompileShader				= ( PFNGLCOMPILESHADERPROC )	 wglGetProcAddress( "glCompileShader" );
	glGenQueries				= ( PFNGLGENQUERIESPROC )      wglGetProcAddress( "glGenQueries" );
	glDeleteQueries				= ( PFNGLDELETEQUERIESPROC )   wglGetProcAddress( "glDeleteQueries" );
	glIsQuery					= ( PFNGLISQUERYPROC )		 wglGetProcAddress( "glIsQuery" );
	glBeginQuery				= ( PFNGLBEGINQUERYPROC )		 wglGetProcAddress( "glBeginQuery" );
	glEndQuery					= ( PFNGLENDQUERYPROC )		 wglGetProcAddress( "glEndQuery" );
	glGetQueryObjectiv			= ( PFNGLGETQUERYOBJECTIVPROC )wglGetProcAddress( "glGetQueryObjectiv" );
	glPointParameterf			= ( PFNGLPOINTPARAMETERFPROC ) wglGetProcAddress( "glPointParameterf" );
	glPointParameterfv			= ( PFNGLPOINTPARAMETERFVPROC )wglGetProcAddress( "glPointParameterfv" );
	glGetUniformLocation		= ( PFNGLGETUNIFORMLOCATIONPROC )	 wglGetProcAddress( "glGetUniformLocation" );
	glGetShaderSource		= ( PFNGLGETSHADERSOURCEPROC )	 wglGetProcAddress( "glGetShaderSource" );
	glUniform1f					= ( PFNGLUNIFORM1FPROC )	     wglGetProcAddress( "glUniform1f" );
	glUniform2f					= ( PFNGLUNIFORM2FPROC )	     wglGetProcAddress( "glUniform2f" );
	glUniform3f					= ( PFNGLUNIFORM3FPROC )	     wglGetProcAddress( "glUniform3f" );
	glUniform4f					= ( PFNGLUNIFORM4FPROC )	     wglGetProcAddress( "glUniform4f" );
	glUniform1i					= ( PFNGLUNIFORM1IPROC )	     wglGetProcAddress( "glUniform1i" );
	glUniform2i					= ( PFNGLUNIFORM2IPROC )	     wglGetProcAddress( "glUniform2i" );
	glUniform3i					= ( PFNGLUNIFORM3IPROC )	     wglGetProcAddress( "glUniform3i" );
	glUniform4i					= ( PFNGLUNIFORM4IPROC )	     wglGetProcAddress( "glUniform4i" );
	glUniform2fv				= ( PFNGLUNIFORM2FVPROC )		 wglGetProcAddress( "glUniform2fv" );
	glUniform3fv				= ( PFNGLUNIFORM3FVPROC )		 wglGetProcAddress( "glUniform3fv" );
	glUniform4fv				= ( PFNGLUNIFORM4FVPROC )		 wglGetProcAddress( "glUniform4fv" );
	glUniformMatrix2fv			= ( PFNGLUNIFORMMATRIX2FVPROC )					wglGetProcAddress( "glUniformMatrix2fv" );
	glUniformMatrix3fv			= ( PFNGLUNIFORMMATRIX3FVPROC )					wglGetProcAddress( "glUniformMatrix3fv" );
	glUniformMatrix4fv			= ( PFNGLUNIFORMMATRIX4FVPROC )					wglGetProcAddress( "glUniformMatrix4fv" );
	glBlendFuncSeparate			= ( PFNGLBLENDFUNCSEPARATEPROC )				wglGetProcAddress( "glBlendFuncSeparate" );
	glFogCoordf					= ( PFNGLFOGCOORDFPROC )		 				wglGetProcAddress( "glFogCoordf" );
	glFogCoordfv				= ( PFNGLFOGCOORDFVPROC )		 				wglGetProcAddress( "glFogCoordfv" );
	glFogCoordd					= ( PFNGLFOGCOORDDPROC )						wglGetProcAddress( "glFogCoordd" );
	glFogCoordddv				= ( PFNGLFOGCOORDDVPROC )						wglGetProcAddress( "glFogCoorddv" );
	glClientActiveTexture		= ( PFNGLCLIENTACTIVETEXTUREPROC ) 				wglGetProcAddress( "glClientActiveTexture" );
	glGenBuffers				= ( PFNGLGENBUFFERSPROC )	 	 				wglGetProcAddress( "glGenBuffersARB" );
	glBindBuffer				= ( PFNGLBINDBUFFERPROC )	 	 				wglGetProcAddress( "glBindBuffer" );
	glBufferData				= ( PFNGLBUFFERDATAPROC )		 				wglGetProcAddress( "glBufferData" );
	glMapBuffer					= ( PFNGLMAPBUFFERPROC )						wglGetProcAddress( "glMapBuffer" );
	glUnmapBuffer				= ( PFNGLUNMAPBUFFERPROC )						wglGetProcAddress( "glUnmapBuffer" );
	glBufferSubData				= ( PFNGLBUFFERSUBDATAPROC )					wglGetProcAddress( "glBufferSubData" );
	glDeleteBuffers				= ( PFNGLDELETEBUFFERSPROC )					wglGetProcAddress( "glDeleteBuffers" );
	glCompressedTexImage2D		= ( PFNGLCOMPRESSEDTEXIMAGE2DPROC )				wglGetProcAddress( "glCompressedTexImage2D" );
	glCompressedTexImage3D		= ( PFNGLCOMPRESSEDTEXIMAGE3DPROC )				wglGetProcAddress( "glCompressedTexImage3D" );
	glTexImage3D				= ( PFNGLTEXIMAGE3DPROC )						wglGetProcAddress( "glTexImage3D" );
	glDrawBuffers				= ( PFNGLDRAWBUFFERSPROC )						wglGetProcAddress( "glDrawBuffers" );
	glVertexAttrib3f			= ( PFNGLVERTEXATTRIB3FPROC )					wglGetProcAddress( "glVertexAttrib3f" );
	glVertexAttrib3fv			= ( PFNGLVERTEXATTRIB3FVPROC )					wglGetProcAddress( "glVertexAttrib3fv" );
	glVertexAttrib2f			= ( PFNGLVERTEXATTRIB2FPROC )					wglGetProcAddress( "glVertexAttrib2f" );
	glVertexAttrib2fv			= ( PFNGLVERTEXATTRIB2FVPROC )					wglGetProcAddress( "glVertexAttrib2fv" );
	glGetAttribLocation			= ( PFNGLGETATTRIBLOCATIONPROC )				wglGetProcAddress( "glGetAttribLocation" );
	glVertexAttribPointer		= ( PFNGLVERTEXATTRIBPOINTERPROC )				wglGetProcAddress( "glVertexAttribPointer" );
	glEnableVertexAttribArray	= ( PFNGLENABLEVERTEXATTRIBARRAYPROC )			wglGetProcAddress( "glEnableVertexAttribArray" );
	glDisableVertexAttribArray	= ( PFNGLDISABLEVERTEXATTRIBARRAYPROC )			wglGetProcAddress( "glDisableVertexAttribArray" );
	glBindAttribLocation		= ( PFNGLBINDATTRIBLOCATIONPROC )				wglGetProcAddress( "glBindAttribLocation" );
	glMultiDrawElements			= ( PFNGLMULTIDRAWELEMENTSPROC )				wglGetProcAddress( "glMultiDrawElements" );
	glIsBuffer					= ( PFNGLISBUFFERPROC )							wglGetProcAddress( "glIsBuffer" );
	glIsProgram					= ( PFNGLISPROGRAMPROC )						wglGetProcAddress( "glIsProgram" );
	glBeginConditionalRender	= ( PFNGLBEGINCONDITIONALRENDERPROC )			wglGetProcAddress( "glBeginConditionalRender" );
	glEndConditionalRender		= ( PFNGLENDCONDITIONALRENDERPROC )				wglGetProcAddress( "glEndConditionalRender" );
	
	return 1;
}

/*
=========================================
     3.0 not implemented yet
=========================================
*/
unsigned char LoadOpenGLCore_3_0( void ) {
	LoadOpenGLCore_2_0();
	if ( !( wglCreateContextAttribsARB = ( PFNWGLCREATECONTEXTATTRIBSARBPROC ) wglGetProcAddress( "wglCreateContextAttribsARB" ) ) )
		return 0;
	return 1;
}

/*
=========================================
     3.2 not implemented yet
=========================================
*/
unsigned char LoadOpenGLCore_3_2( void ) {
	LoadOpenGLCore_3_0();
	return 1;
}

/*
=========================================
     4.0 not implemented yet
=========================================
*/
unsigned char LoadOpenGLCore_4_0( void ) {
	LoadOpenGLCore_3_2();
	return 1;
}

/*
=========================================
     4.2 not implemented yet
=========================================
*/
unsigned char LoadOpenGLCore_4_2( void ) {
	LoadOpenGLCore_4_0();
	return 1;
}

/*
=========================================
     IsGLExtensionSupported
=========================================
*/
unsigned char IsGLExtensionSupported( char* extname ) {
	char* extList = ( char* )glGetString( GL_EXTENSIONS );

	if ( strstr( extList, extname ) ) return 1;
	else return 0;
}

/*
=========================================
     IsWGLExtensionSupported
=========================================
*/
unsigned char IsWGLExtensionSupported( char* extname ) {
	char* extList;

	LoadEXT_WGL_ARB_extensions_string();
	extList = ( char* )wglGetExtensionsStringARB( wglGetCurrentDC() );

	if ( strstr( extList, extname ) ) return 1;
	else return 0;
}

/*
=========================================
     LoadEXT_WGL_ARB_extensions_string
=========================================
*/
unsigned char LoadEXT_WGL_ARB_extensions_string( void ) {
	wglGetExtensionsStringARB = ( PFNWGLGETEXTENSIONSSTRINGARBPROC ) wglGetProcAddress( "wglGetExtensionsStringARB" );
	return 1;
}

/*
=========================================
     LoadEXT_WGL_EXT_swap_control
=========================================
*/
unsigned char LoadEXT_WGL_EXT_swap_control( void ) {
	if ( !IsWGLExtensionSupported( "WGL_EXT_swap_control" ) ) return 0;
	wglSwapIntervalEXT			= ( PFNWGLSWAPINTERVALEXTPROC )wglGetProcAddress( "wglSwapIntervalEXT" );
	return 1;
}

/*
=========================================
     LoadEXT_WGL_ARB_pixel_format
=========================================
*/
unsigned char LoadEXT_WGL_ARB_pixel_format( void ) {
	if ( !IsWGLExtensionSupported( "WGL_ARB_pixel_format" ) ) return 0;
	wglChoosePixelFormatARB = ( PFNWGLCHOOSEPIXELFORMATARBPROC ) wglGetProcAddress( "wglChoosePixelFormatARB" );
	return 1;
}

/*
=========================================
     LoadEXT_GL_EXT_blend_minmax
=========================================
*/
unsigned char LoadEXT_GL_EXT_blend_minmax( void ) {
	if ( !IsGLExtensionSupported( "GL_EXT_blend_minmax" ) ) return 0;
	glBlendEquationEXT	= ( PFNGLBLENDEQUATIONEXTPROC )wglGetProcAddress( "glBlendEquationEXT" );
	return 1;
}

/*
=========================================
     LoadEXT_GL_EXT_framebuffer_multisample
=========================================
*/
unsigned char LoadEXT_GL_EXT_framebuffer_multisample( void ) {
	if ( !IsGLExtensionSupported( "GL_EXT_framebuffer_multisample" ) ) return 0;
	glRenderbufferStorageMultisampleEXT = ( PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC ) wglGetProcAddress( "glRenderbufferStorageMultisampleEXT" );
	return 1;
}

/*
=========================================
     LoadEXT_GL_NV_framebuffer_multisample_coverage
=========================================
*/
unsigned char LoadEXT_GL_NV_framebuffer_multisample_coverage( void ) {
	if ( !IsGLExtensionSupported( "GL_NV_framebuffer_multisample_coverage" ) ) return 0;
	glRenderbufferStorageMultisampleCoverageNV = ( PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC ) wglGetProcAddress( "glRenderbufferStorageMultisampleCoverageNV" );
	return 1;
}

/*
=========================================
     LoadEXT_GL_EXT_framebuffer_object
=========================================
*/
unsigned char LoadEXT_GL_EXT_framebuffer_object( void ) {
	if ( !IsGLExtensionSupported( "GL_EXT_framebuffer_object" ) ) return 0;
	glIsRenderbuffer			= ( PFNGLISRENDERBUFFERPROC )		wglGetProcAddress( "glIsRenderbuffer" );
	glBindRenderbuffer		= ( PFNGLBINDRENDERBUFFERPROC )	wglGetProcAddress( "glBindRenderbuffer" );
	glDeleteRenderbuffers		= ( PFNGLDELETERENDERBUFFERSPROC )wglGetProcAddress( "glDeleteRenderbuffers" );
	glGenRenderbuffers			= ( PFNGLGENRENDERBUFFERSPROC )	wglGetProcAddress( "glGenRenderbuffers" );
	glRenderbufferStorage		= ( PFNGLRENDERBUFFERSTORAGEPROC )		wglGetProcAddress( "glRenderbufferStorage" );
	glGetRenderbufferParameteriv	= ( PFNGLGETRENDERBUFFERPARAMETERIVPROC )	wglGetProcAddress( "glGetRenderbufferParameteriv" );
	glBindFramebuffer			= ( PFNGLBINDFRAMEBUFFERPROC )			wglGetProcAddress( "glBindFramebuffer" );
	glIsFrameBuffer			= ( PFNGLISFRAMEBUFFERPROC )					wglGetProcAddress( "glIsFrameBuffer" );
	glDeleteFramebuffers		= ( PFNGLDELETEFRAMEBUFFERSPROC )				wglGetProcAddress( "glDeleteFramebuffers" );
	glGenFramebuffers			= ( PFNGLGENFRAMEBUFFERSPROC )			wglGetProcAddress( "glGenFramebuffers" );
	glCheckFramebufferStatus	= ( PFNGLCHECKFRAMEBUFFERSTATUSPROC )			wglGetProcAddress( "glCheckFramebufferStatus" );
	glFramebufferTexture1D			= ( PFNGLFRAMEBUFFERTEXTURE1DPROC )	wglGetProcAddress( "glFramebufferTexture1D" );
	glFramebufferTexture2D			= ( PFNGLFRAMEBUFFERTEXTURE2DPROC )	wglGetProcAddress( "glFramebufferTexture2D" );
	glFramebufferTexture3D			= ( PFNGLFRAMEBUFFERTEXTURE3DPROC )	wglGetProcAddress( "glFramebufferTexture3D" );
	glFramebufferRenderbuffer	= ( PFNGLFRAMEBUFFERRENDERBUFFERPROC )	wglGetProcAddress( "glFramebufferRenderbuffer" );
	glGetFramebufferAttachmentParameteriv = ( PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC ) wglGetProcAddress( "glGetFramebufferAttachmentParameteriv" );
	return 1;
}

/*
=========================================
     LoadEXT_GL_EXT_framebuffer_blit
=========================================
*/
unsigned char LoadEXT_GL_EXT_framebuffer_blit( void ) {
	if ( !IsGLExtensionSupported( "GL_EXT_framebuffer_blit" ) ) return 0;
	glBlitFramebufferEXT		= ( PFNGLBLITFRAMEBUFFEREXTPROC )				wglGetProcAddress( "glBlitFramebufferEXT" );
	return 1;
}

/*
=========================================
     LoadEXT_GL_EXT_geometry_shader4
=========================================
*/
unsigned char LoadEXT_GL_EXT_geometry_shader4( void ) {
	if ( !IsGLExtensionSupported( "GL_EXT_geometry_shader4" ) ) return 0;
	glProgramParameteriEXT		= ( PFNGLPROGRAMPARAMETERIEXTPROC )		wglGetProcAddress( "glProgramParameteriEXT" );
	glFramebufferTextureEXT		= ( PFNGLFRAMEBUFFERTEXTUREEXTPROC )		wglGetProcAddress( "glFramebufferTextureEXT" );
    glFramebufferTextureLayerEXT= ( PFNGLFRAMEBUFFERTEXTURELAYEREXTPROC ) wglGetProcAddress( "glFramebufferTextureLayerEXT" );
    glFramebufferTextureFaceEXT = ( PFNGLFRAMEBUFFERTEXTUREFACEEXTPROC )  wglGetProcAddress( "glFramebufferTextureFaceEXT" );
	return 1;
}

/*
=========================================
     LoadEXT_GL_EXT_direct_state_access
=========================================
*/
unsigned char LoadEXT_GL_EXT_direct_state_access( void ) {
	if ( !IsGLExtensionSupported( "GL_EXT_direct_state_access" ) ) return 0;
	glBindMultiTextureEXT = ( PFNGLBINDMULTITEXTUREEXTPROC ) wglGetProcAddress( "glBindMultiTextureEXT" );
	return 1;
}