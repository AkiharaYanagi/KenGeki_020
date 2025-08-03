//=================================================================================================
//
// ExeEffect ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "ExeEffect.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//特定エフェクト処理
	void ExeEffect::PreMove_Special()
	{
		//月日星
		if ( m_pEffect->IsName( U"OD0" ) )
		{
			if (m_pScript->GetFrame() == 0)
			{
				//拡大
//				m_pScript->m_prmStaging.Scaling = VEC2 ( 2.f, 2.f );
			}
		}

		//Enemy_0
		if ( m_pEffect->IsName ( U"Laser_m" ) )
		{
			static float w = 1.f;
			m_dispEffect->SetW ( w += 1.f );
			m_pScript->m_prmStaging.Rotate_center = VEC2 ( 0, 128 );
			if ( m_pEffect->IsEndScript ( m_frame ) )
			{
				m_dispEffect->SetW ( w = 0 );
			}
		}
	}

	void ExeEffect::PostMove_Special()
	{
		//----------------------------------
		//	Ef個別指定
		//----------------------------------
		if ( m_pEffect->GetName () == U"空中竜巻_鞘" )
		{
			if ( m_ptEffect.y >= (float)GROUND_Y )
			{
				m_ptEffect.y = GROUND_Y;
				m_vel.x = 0;
				m_vel.y = 0;
				m_acc.x = 0;
				m_acc.y = 0;
			}
		}


	}

}	//namespace GAME

