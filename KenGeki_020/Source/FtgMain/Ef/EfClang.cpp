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
		m_impact->SetShader ( T );
		m_impact->Off ();
		m_impact->SetbCenterOfTx ( T );
		AddpTask ( m_impact );
		GRPLST_INSERT ( m_impact );

		m_circle = std::make_shared < GrpEf > ();
		m_circle->SetShader ( T );
		m_circle->Off ();
		m_circle->SetbCenterOfTx ( T );
		AddpTask ( m_circle );
		GRPLST_INSERT ( m_circle );


		//雷エフェクト
		m_thunder0 = std::make_shared < GrpEf > ();
//		m_thunder0->AddTexture_FromArchive ( U"Ef_Test.png" );

//		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_06.png" );
		m_thunder0->SetShader ( T );

		//オブジェクトを追加
		m_thunder0->AddObject ();
		P_Ob pOb = m_thunder0->Getpap_ob ()->at ( 1 );

		m_thunder0->SetbCenterOfTx ( F );

		//m_thunder0->SetBase ( VEC2 ( 0, 0 ) );
		m_thunder0->SetBase ( VEC2 ( 600, 600 ) );
		m_thunder0->SetRevised ( VEC2 ( -800, -800 ) );		//Scalingで2倍したテクスチャの中心位置

		m_thunder0->Getpap_ob ()->at ( 0 )->SetbScalingCntrOfTx ( F );
		pOb->SetbRotationCntrOfTx ( F );
		m_thunder0->SetScaling ( VEC2 ( 2.f, 2.f ) );
		pOb->SetScaling ( VEC2 ( 2.f, 2.f ) );

		m_thunder0->Getpap_ob ()->at ( 0 )->SetbRotationCntrOfTx ( F );
		pOb->SetbRotationCntrOfTx ( F );
//		m_thunder0->SetRotationCenter ( VEC2 ( 400, 400 ) );
//		m_thunder0->SetRotationCenter ( VEC2 ( 600, 600 ) );
		m_thunder0->SetRotationCenter ( VEC2 ( 800, 800 ) );
		pOb->SetRotationCenter ( VEC2 ( 800, 800 ) );

//		m_thunder0->On ();
		AddpTask ( m_thunder0 );
		GRPLST_INSERT ( m_thunder0 );


		//-------------------------------
		//test
		m_test = std::make_shared < GrpEf > ();
		m_test->AddTexture_FromArchive ( U"Ef_Test.png" );
//		m_test->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_06.png" );
		m_test->SetShader ( T );
		m_test->SetbCenterOfTx ( T );

//		m_test->SetPos ( VEC2 ( 100, 100 ) );
		m_test->SetBase ( VEC2 ( 600, 600 ) );
//		m_test->SetBase ( VEC2 ( 400, 400 ) );
//		m_test->SetBase ( VEC2 ( 0, 0 ) );

//		m_test->SetScaling ( VEC2 ( 2.f, 2.f ) );
//		m_test->SetRotationCenter ( VEC2 ( 800, 800) );

//		m_test->On ();
		m_test->Off ();
		AddpTask ( m_test );
//		GRPLST_INSERT ( m_test );



#if 0
		m_thunder1 = std::make_shared < GrpEf > ();
//		m_thunder1->SetShader ( T );
		AddpTask ( m_thunder1 );
//		GRPLST_INSERT ( m_thunder1 );
#endif // 0


		m_impact->Off ();
		m_circle->Off ();
		m_thunder0->Off ();


#if 0
		VEC2 base { -400, -400 };
		m_impact->SetBase ( base );
		m_circle->SetBase ( base );
		m_thunder0->SetBase ( base );
		m_thunder1->SetBase ( base );

		VEC2 rtt_cnt { 400, 400 };
		m_impact->SetRotationCenter ( rtt_cnt );
		m_circle->SetRotationCenter ( rtt_cnt );
		m_thunder0->SetRotationCenter ( rtt_cnt );
		m_thunder1->SetRotationCenter ( rtt_cnt );
#endif // 0

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


		VEC2 scl_cnt { 400, 400 };
		const VEC2 scl { 12.f, 2.f };
		SetScale ( m_impact, scl );
		SetScale ( m_circle, scl );
		SetScale ( m_thunder0, scl );
		SetScale ( m_thunder1, scl );

#endif // 0


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



#if 1

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

#endif // 0

#if 0
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
#endif // 0



//		m_test->AddTexture_FromArchive ( U"Ef_Test.png" );


		TASK_VEC::Load ();

//		m_test->SetValid ( T );
	}



	void EfClang::Move ()
	{
#if 0
		static float rad = 0.1f;
		rad += 0.1f;

		m_r = s3d::Random ( 0.f, D3DX_PI_TWICE );

		m_thunder0->SetRadian ( m_r );

		float rnd_rad = s3d::Random ( 0.f, D3DX_PI_TWICE );
		P_Ob pOb = m_thunder0->Getpap_ob ()->at ( 1 );
		pOb->SetRadian ( rnd_rad );

		//		m_test->SetRadian ( rad );
#endif // 0


		m_impact->SetDispBase ( G_BASE_POS () );
		m_circle->SetDispBase ( G_BASE_POS () );
		m_thunder0->SetDispBase ( G_BASE_POS () );
//		m_thunder1->SetDispBase ( G_BASE_POS () );

		m_impact->Advance ();
		m_circle->Advance ();
		m_thunder0->Advance ();
//		m_thunder1->Advance ();

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


#endif // 0


		TASK_VEC::Move ();

#if 0
		VEC2 pos { 0, 0 };
		m_impact->SetPos ( pos );
		m_circle->SetPos ( pos );
		m_thunder0->SetPos ( pos );
		m_thunder1->SetPos ( pos );
#endif // 0



//		m_test->SetValid ( T );
//		m_test->SetDispBase ( G_BASE_POS () );

//		m_thunder0->Draw ();
//		m_test->Draw();
	}

	void EfClang::On ( VEC2 center )
	{
		m_r = s3d::Random ( 0.f, D3DX_PI_TWICE );

		//m_impact->SetRadian ( (float)m_r );
		//m_circle->SetRadian ( (float)m_r );

		m_thunder0->SetRadian ( (float)m_r );

		float rnd_rad = s3d::Random ( 0.f, D3DX_PI_TWICE );
		P_Ob pOb = m_thunder0->Getpap_ob ()->at ( 1 );
		pOb->SetRadian ( rnd_rad );

		//m_thunder1->SetRadian ( (float)m_r );


#if 0
		m_impact->SetRevised ( center );
		m_circle->SetRevised ( center );
		m_thunder0->SetRevised ( center );
		m_thunder1->SetRevised ( center );
#endif // 0
		m_impact->SetBase ( center );
		m_circle->SetBase ( center );
		m_thunder0->SetBase ( center );
		//		m_thunder1->SetBase ( center );


		m_impact->On ();
		m_circle->On ();
		m_thunder0->On ();
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
