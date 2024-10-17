//=================================================================================================
//
//	EfSouha ヘッダファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "EfSouha.h"
#include "../../GameMain/G_Ftg.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	EfSouha::EfSouha ()
	{
		AddTexture_FromArchive ( U"Souha.png" );

		//シェーダ利用
		SetShader ( T );

		//表示をテクスチャの中心にする
		SetbCenterOfTx ( T );

		//拡大縮小をテクスチャの中心にする
		Getpap_ob()->at(0)->SetbScalingCntrOfTx( T );
		Getpap_ob()->at(0)->SetScalingCenter ( VEC2 ( 400, 400 ) );


		m_scalingStart = VEC2 ( 0.01f, 0.01f );
		m_vStart = VEC2 ( 0.03f, 0.03f );
		m_a = VEC2 ( 0.03f, 0.03f );

		m_timer.SetTargetTime ( 20 );
		m_scaling = m_scalingStart;


		//test
		//On ( VEC2 ( 400, 400 ) );
		Init ();
	}

	EfSouha::~EfSouha ()
	{
	}

	void EfSouha::Init ()
	{
		m_scaling = m_scalingStart;
		m_v = m_vStart;
		GrpEf::Init ();
	}

	void EfSouha::Move ()
	{
		if ( m_valid )
		{
			m_v += m_a;
			m_scaling += m_v;

			if ( m_scaling.x > 1.2f )
			{
				m_scaling = VEC2 ( 1.2f, 1.2f );
			}
			SetScaling ( m_scaling );

			SetDispBase ( G_BASE_POS () );
		}

		m_timer.Move ();
		if ( m_timer.IsLast () )
		{
			Off ();
			Init ();
		}


		GrpEf::Move ();
	}

	void EfSouha::On ( VEC2 center )
	{
		SetBase ( center );
		m_timer.Start ();

		GrpEf::On ();
	}

}
