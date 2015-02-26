#ifndef _RHAPSODIES_HANDRENDERDRAW
#define _RHAPSODIES_HANDRENDERDRAW

#include <VistaKernel/GraphicsManager/VistaOpenGLDraw.h>

namespace rhapsodies {
	class ShaderRegistry;
	class HandModel;
	class HandRenderer;
	
	class HandRenderDraw : public IVistaOpenGLDraw {
	public:
		HandRenderDraw(HandModel *pModelLeft,
					   HandModel *pModelRight,
					   HandModelRep *pModelRep,
					   ShaderRegistry *pReg);

		~HandRenderDraw();
		
		virtual bool Do();
		virtual bool GetBoundingBox(VistaBoundingBox &bb);

	private:
		HandModel *m_pModelLeft;
		HandModel *m_pModelRight;

		HandModelRep *m_pModelRep;

		HandRenderer *m_pRenderer;
	};
}

#endif // _RHAPSODIES_HANDRENDERDRAW