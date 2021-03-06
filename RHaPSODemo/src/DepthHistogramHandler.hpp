/*============================================================================*/
/*                  Copyright (c) 2014 RWTH Aachen University                 */
/*============================================================================*/
/*                                  License                                   */
/*                                                                            */
/*  This program is free software: you can redistribute it and/or modify      */
/*  it under the terms of the GNU Lesser General Public License as published  */
/*  by the Free Software Foundation, either version 3 of the License, or      */
/*  (at your option) any later version.                                       */
/*                                                                            */
/*  This program is distributed in the hope that it will be useful,           */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/*  GNU Lesser General Public License for more details.                       */
/*                                                                            */
/*  You should have received a copy of the GNU Lesser General Public License  */
/*  along with this program.  If not, see <http://www.gnu.org/licenses/>.     */
/*============================================================================*/
/*                                Contributors                                */
/*                                                                            */
/*============================================================================*/
// $Id: $

#ifndef _RHAPSODIES_DEPTHFRAMEHANDLER
#define _RHAPSODIES_DEPTHFRAMEHANDLER

// @todo forward declare the data series, mon!
//#include <Vfl2DDiagrams/Data/V2dDataSeriesTypes.h>

class V2dDiagramDefault;
class V2dDiagramTextureVista;

namespace rhapsodies {
	class ImagePBOOpenGLDraw;
	class HistogramUpdater;

	class DepthHistogramHandler {
		bool m_bEnabled;

		ImagePBOOpenGLDraw *m_pDraw;

		// V2dDiagramDefault *m_pDiagram;
		// V2dDiagramTextureVista *m_pDiagramTexture;
		// V2dDataSeriesIntContinuousOverString *m_pDataSeries;

		int m_iHistNumBins;
		int m_iHistDrawCounter;
		int m_iHistDrawInterval;
		HistogramUpdater *m_pHistUpdater;
		
	public:
		DepthHistogramHandler(ImagePBOOpenGLDraw *pDraw);
		virtual ~DepthHistogramHandler();

//		V2dDiagramTextureVista *GetDiagramTexture();
		HistogramUpdater       *GetHistogramUpdater();
		ImagePBOOpenGLDraw     *GetPBODraw();

		bool Enable(bool bEnable);
		bool isEnabled();

		void ProcessFrame(const unsigned short *pFrame);
	};
}

#endif // _RHAPSODIES_DEPTHFRAMEHANDLER
