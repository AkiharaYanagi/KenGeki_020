//=================================================================================================
//
//	EfClang ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "EfClang.h"
#include "../../GameMain/G_Ftg.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	EfClang::EfClang ()
	{
		m_impact = std::make_shared < GrpEf > ();
		AddpTask ( m_impact );
//		SDRLST_INSERT ( m_impact );

		m_circle = std::make_shared < GrpEf > ();
		AddpTask ( m_circle );
//		SDRLST_INSERT ( m_circle );

		m_thunder0 = std::make_shared < GrpEf > ();
		AddpTask ( m_thunder0 );
//		SDRLST_INSERT ( m_thunder0 );

		m_thunder1 = std::make_shared < GrpEf > ();
		AddpTask ( m_thunder1 );
//		SDRLST_INSERT ( m_thunder1 );


		VEC2 base { -400, -400 };
		m_impact->SetBase ( base );
		m_circle->SetBase ( base );
		m_thunder0->SetBase ( base );
		m_thunder1->SetBase ( base );

#if 0
		m_impact->SetValid ( T );
		m_circle->SetValid ( T );
		m_thunder0->SetValid ( T );
		m_thunder1->SetValid ( T );

		VEC2 pos { 1000, 1000 };
		m_impact->SetPos ( pos );
		m_circle->SetPos ( pos );
		m_thunder0->SetPos ( pos );
		m_thunder1->SetPos ( pos );
#endif // 0

		VEC2 rtt_cnt { 400, 400 };
		m_impact->SetRotationCenter ( rtt_cnt );
		m_circle->SetRotationCenter ( rtt_cnt );
		m_thunder0->SetRotationCenter ( rtt_cnt );
		m_thunder1->SetRotationCenter ( rtt_cnt );


		VEC2 scl_cnt { 400, 400 };
		const VEC2 scl { 12.f, 2.f };
		SetScale ( m_impact, scl );
		SetScale ( m_circle, scl );
		SetScale ( m_thunder0, scl );
		SetScale ( m_thunder1, scl );

//		m_test = std::make_shared < GameGraphic > ();
		m_test = std::make_shared < GrpEf > ();
		AddpTask ( m_test );
//		SDRLST_INSERT ( m_test );
//		GRPLST_INSERT ( m_test );

		m_test->SetPos ( VEC2 ( 0, 0 ) );
//		m_test->SetBase ( VEC2 ( 400, 400 ) );
		m_test->SetRotationCenter ( VEC2 ( 200, 200 ) );
		m_test->SetValid ( T );

	}

	EfClang::~EfClang ()
	{
	}



	void EfClang::Load ()
	{
		m_impact->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Impact\\Ef_impact_00.png" );
		m_impact->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Impact\\Ef_impact_01.png" );
		m_impact->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Impact\\Ef_impact_02.png" );
		m_impact->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Impact\\Ef_impact_03.png" );
		m_impact->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Impact\\Ef_impact_04.png" );
		m_impact->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Impact\\Ef_impact_05.png" );
		m_impact->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Impact\\Ef_impact_06.png" );
		m_impact->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Impact\\Ef_impact_07.png" );
		m_impact->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Impact\\Ef_impact_08.png" );
		m_impact->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Impact\\Ef_impact_09.png" );
		m_impact->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Impact\\Ef_impact_10.png" );
		m_impact->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Impact\\Ef_impact_11.png" );
		m_impact->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Impact\\Ef_impact_12.png" );
		m_impact->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Impact\\Ef_impact_13.png" );
		m_impact->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Impact\\Ef_impact_14.png" );
		m_impact->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Impact\\Ef_impact_15.png" );
		m_impact->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Impact\\Ef_impact_16.png" );
		m_impact->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Impact\\Ef_impact_17.png" );
		m_impact->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Impact\\Ef_impact_18.png" );
		m_impact->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Impact\\Ef_impact_19.png" );
		m_impact->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Impact\\Ef_impact_20.png" );
		m_impact->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Impact\\Ef_impact_21.png" );
		m_impact->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Impact\\Ef_impact_22.png" );
		m_impact->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Impact\\Ef_impact_23.png" );
		m_impact->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Impact\\Ef_impact_24.png" );

		m_circle->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Circle\\Ef_circle_00.png" );
		m_circle->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Circle\\Ef_Circle_01.png" );
		m_circle->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Circle\\Ef_Circle_02.png" );
		m_circle->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Circle\\Ef_Circle_03.png" );
		m_circle->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Circle\\Ef_Circle_04.png" );
		m_circle->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Circle\\Ef_Circle_05.png" );
		m_circle->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Circle\\Ef_Circle_06.png" );
		m_circle->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Circle\\Ef_Circle_07.png" );
		m_circle->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Circle\\Ef_Circle_08.png" );
		m_circle->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Circle\\Ef_Circle_09.png" );
		m_circle->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Circle\\Ef_Circle_10.png" );
		m_circle->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Circle\\Ef_Circle_11.png" );
		m_circle->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Circle\\Ef_Circle_12.png" );
		m_circle->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Circle\\Ef_Circle_13.png" );
		m_circle->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Circle\\Ef_Circle_14.png" );
		m_circle->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Circle\\Ef_Circle_15.png" );
		m_circle->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Circle\\Ef_Circle_16.png" );
		m_circle->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Circle\\Ef_Circle_17.png" );
		m_circle->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Circle\\Ef_Circle_18.png" );
		m_circle->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Circle\\Ef_Circle_19.png" );
		m_circle->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Circle\\Ef_circle_20.png" );
		m_circle->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Circle\\Ef_Circle_21.png" );
		m_circle->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Circle\\Ef_Circle_22.png" );
		m_circle->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Circle\\Ef_Circle_23.png" );
		m_circle->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Circle\\Ef_Circle_24.png" );

		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_00.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_01.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_02.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_03.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_04.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_05.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_06.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_07.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_08.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_09.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_10.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_11.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_12.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_13.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_14.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_15.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_16.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_17.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_18.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_19.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_20.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_21.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_22.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_23.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_24.png" );

		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_Thunder1_00.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_Thunder1_01.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_Thunder1_02.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_Thunder1_03.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_Thunder1_04.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_Thunder1_05.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_Thunder1_06.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_Thunder1_07.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_Thunder1_08.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_Thunder1_09.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_Thunder1_10.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_Thunder1_11.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_Thunder1_12.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_Thunder1_13.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_Thunder1_14.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_Thunder1_15.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_Thunder1_16.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_Thunder1_17.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_Thunder1_18.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_Thunder1_19.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_Thunder1_20.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_Thunder1_21.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_Thunder1_22.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_Thunder1_23.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_Thunder1_24.png" );



		m_test->AddTexture_FromArchive ( U"Ef_Test.png" );


		TASK_VEC::Load ();

		m_test->SetValid ( T );
	}



	void EfClang::Move ()
	{
		m_impact->SetDispBase ( G_BASE_POS () );
		m_circle->SetDispBase ( G_BASE_POS () );
		m_thunder0->SetDispBase ( G_BASE_POS () );
		m_thunder1->SetDispBase ( G_BASE_POS () );

		m_impact->Advance ();
		m_circle->Advance ();
		m_thunder0->Advance ();
		m_thunder1->Advance ();

#if 0
		m_impact->SetValid ( T );
		m_circle->SetValid ( T );
		m_thunder0->SetValid ( T );
		m_thunder1->SetValid ( T );
#endif // 0

#if 0

		double r = s3d::Random ( 0.f, D3DX_PI_TWICE );
		m_thunder1->SetRadian ( (float)r );


//		m_test->SetDispBase ( G_BASE_POS () );
//		m_thunder1->Advance ();

		m_r += 0.1;
		m_test->SetRadian ( (float)m_r );

		m_test->Move();

#endif // 0


		TASK_VEC::Move ();

#if 0
		VEC2 pos { 0, 0 };
		m_impact->SetPos ( pos );
		m_circle->SetPos ( pos );
		m_thunder0->SetPos ( pos );
		m_thunder1->SetPos ( pos );
#endif // 0
	}

	void EfClang::On ( VEC2 center )
	{
		m_r = s3d::Random ( 0.f, D3DX_PI_TWICE );
		m_impact->SetRadian ( (float)m_r );
		m_circle->SetRadian ( (float)m_r );
		m_thunder0->SetRadian ( (float)m_r );
		m_thunder1->SetRadian ( (float)m_r );



		m_impact->SetRevised ( center );
		m_impact->On ();

		m_circle->SetRevised ( center );
		m_circle->On ();

		m_thunder0->SetRevised ( center );
		m_thunder0->On ();

		m_thunder1->SetRevised ( center );
		m_thunder1->On ();

#if 0
#endif // 0

//		m_test->SetRevised ( center );
//		m_thunder1->On ();
	}

	void EfClang::SetScale ( P_Grp pGrp, const VEC2 & v )
	{
		PAP_Ob papOb = pGrp->Getpap_ob ();
		for ( P_Ob pOb : * papOb )
		{
			pOb->SetScaling ( v );
		}
	}


}
