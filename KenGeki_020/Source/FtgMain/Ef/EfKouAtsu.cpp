//=================================================================================================
//
//	EfKouAtsu ヘッダファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "EfKouAtsu.h"
#include "../../GameMain/G_Ftg.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	EfKouAtsu::EfKouAtsu ()
	{
		AddTexture_FromArchive ( U"KouAtsu0.png" );
		AddTexture_FromArchive ( U"KouAtsu1.png" );
		AddTexture_FromArchive ( U"KouAtsu2.png" );
		AddTexture_FromArchive ( U"KouAtsu3.png" );
		AddTexture_FromArchive ( U"KouAtsu4.png" );

		//シェーダ利用
//		SetShader ( T );

		//表示をテクスチャの中心にする
		SetbCenterOfTx ( T );

		//拡大縮小をテクスチャの中心にする
		Getpap_ob()->at(0)->SetbScalingCntrOfTx( T );

		SetZ ( Z_EFF );	//Z位置手前エフェクト

		SetIndexTexture ( 0 );

		m_pchTimer.SetTargetTime ( 3 );

#if 0

		m_scalingStart = VEC2 ( 0.01f, 0.01f );
		m_vStart = VEC2 ( 0.03f, 0.03f );
		m_a = VEC2 ( 0.03f, 0.03f );

		m_timer.SetTargetTime ( 20 );
		m_scaling = m_scalingStart;

#endif // 0


		//test
//		On ( VEC2 ( 400, 400 ) );
		Init ();
	}

	EfKouAtsu::~EfKouAtsu ()
	{
	}

	void EfKouAtsu::Init ()
	{
#if 0

		m_scaling = m_scalingStart;
		m_v = m_vStart;

#endif // 0
		m_pchTimer.Init ();
		GrpEf::Init ();
	}

	void EfKouAtsu::Move ()
	{
#if 0
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
#endif // 0

		SetDispBase ( G_BASE_POS () );

		if ( m_pchTimer.IsLast () )
		{
			GrpEf::Advance ();
//			GrpEf::Advance_Loop ();
			m_pchTimer.Start ();
		}
		m_pchTimer.Move ();


#if 0
		GrpEf::Advance_Loop ();
#endif // 0

		GrpEf::Move ();
	}

	void EfKouAtsu::On ( const BtlParam & btlPrm )
	{
		//向きと位置補正
		float dx = 0;
		if ( btlPrm.GetDirRight () )
		{
			SetScaling ( 1.f, 1.f );
			dx = 100;
		}
		else
		{
			SetScaling ( -1.f, 1.f );
			dx = -100;
		}

		VEC2 pos = btlPrm.GetPos();
		SetBase ( VEC2 ( pos.x + dx, pos.y - 220 ) );

		m_pchTimer.Start ();

		GrpEf::On ();
	}

}
