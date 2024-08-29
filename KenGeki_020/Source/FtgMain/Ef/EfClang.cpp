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
		SDRLST_INSERT ( m_impact );

		m_circle = std::make_shared < GrpEf > ();
		AddpTask ( m_circle );
		SDRLST_INSERT ( m_circle );

		m_thunder0 = std::make_shared < GrpEf > ();
		AddpTask ( m_thunder0 );
		SDRLST_INSERT ( m_thunder0 );

		m_thunder1 = std::make_shared < GrpEf > ();
		AddpTask ( m_thunder1 );
		SDRLST_INSERT ( m_thunder1 );


		m_test = std::make_shared < GrpEf > ();
		AddpTask ( m_test );
		SDRLST_INSERT ( m_test );
//		GRPLST_INSERT ( m_test );


		VEC2 base { -800, -800 };
		m_impact->SetBase ( base );
		m_circle->SetBase ( base );
		m_thunder0->SetBase ( base );
		m_thunder1->SetBase ( base );

		m_test->SetBase ( VEC2 ( 400, 400 ) );

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



		m_test->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_10.png" );


		TASK_VEC::Load ();

		m_test->SetValid ( T );
	}



	void EfClang::Move ()
	{
		m_impact->SetDispBase ( G_BASE_POS () );
		m_impact->Advance ();

		m_circle->SetDispBase ( G_BASE_POS () );
		m_circle->Advance ();

		m_thunder0->SetDispBase ( G_BASE_POS () );
		m_thunder0->Advance ();

		m_thunder1->SetDispBase ( G_BASE_POS () );
		m_thunder1->Advance ();

//		m_test->SetDispBase ( G_BASE_POS () );
//		m_thunder1->Advance ();

		m_r += 0.01;
		m_test->SetRadian ( m_r );


		TASK_VEC::Move ();
	}

	void EfClang::On ( VEC2 center )
	{
		m_impact->SetRevised ( center );
		m_impact->On ();

		m_circle->SetRevised ( center );
		m_circle->On ();

		m_thunder0->SetRevised ( center );
		m_thunder0->On ();

		m_thunder1->SetRevised ( center );
		m_thunder1->On ();

//		m_test->SetRevised ( center );
//		m_thunder1->On ();
	}

}
