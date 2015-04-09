#include "HandModelRep.hpp"

namespace rhapsodies {
	
	HandModelRep::HandModelRep() :
		m_vecExtents(19) {

		m_vecExtents[T_MC] = 37;
		m_vecExtents[T_PP] = 44;
		m_vecExtents[T_DP] = 37;

		m_vecExtents[I_MC] = 93;
		m_vecExtents[I_PP] = 55;
		m_vecExtents[I_MP] = 35;
		m_vecExtents[I_DP] = 30;

		m_vecExtents[M_MC] = 84;
		m_vecExtents[M_PP] = 65;
		m_vecExtents[M_MP] = 43;
		m_vecExtents[M_DP] = 32;

		m_vecExtents[R_MC] = 76;
		m_vecExtents[R_PP] = 60;
		m_vecExtents[R_MP] = 37;
		m_vecExtents[R_DP] = 30;

		m_vecExtents[L_MC] = 67;
		m_vecExtents[L_PP] = 47;
		m_vecExtents[L_MP] = 28;
		m_vecExtents[L_DP] = 27;
	}

	float HandModelRep::GetExtent(size_t eExt) {
		return m_vecExtents[eExt];
	}

	void HandModelRep::SetExtent(size_t eExt,
								 float fLengthMm) {
		m_vecExtents[eExt] = fLengthMm;
	}
}
