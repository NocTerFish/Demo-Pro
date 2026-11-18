#pragma once
#include<glad/glad.h>

//‰÷»æ◊¥Ã¨
struct RenderState
{
	//√ÊÃﬁ≥˝
	bool enableCullFace;
	GLenum cullMode;		// GL_BACK / GL_FRONT / GL_FRONT_AND_BACK
	GLenum frontFace;		// GL_CCW / GL_CW

	//…Ó∂»≤‚ ‘
	bool enableDepthTest;
	GLenum depthFunc;		// GL_LESS / GL_LEQUAL ...


	RenderState()
		: enableCullFace(false)
		, cullMode(GL_BACK)
		, frontFace(GL_CCW)
		, enableDepthTest(false)
		, depthFunc(GL_LESS)
	{
	}

	//”¶”√◊¥Ã¨
	void apply() const
	{
		if (enableCullFace)
			glEnable(GL_CULL_FACE);
		else
			glDisable(GL_CULL_FACE);

		glCullFace(cullMode);
		glFrontFace(frontFace);

		if (enableDepthTest)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);

		glDepthFunc(depthFunc);
	}

	//2d‰÷»æ‘§…Ë
	static RenderState Default2D()
	{
		RenderState s;
		s.enableCullFace = false;
		s.enableDepthTest = false;
		return s;
	}

	//3d‰÷»æ‘§…Ë
	static RenderState Default3D()
	{
		RenderState s;
		s.enableCullFace = true;
		s.cullMode = GL_BACK;
		s.frontFace = GL_CCW;
		s.enableDepthTest = true;
		return s;
	}
};