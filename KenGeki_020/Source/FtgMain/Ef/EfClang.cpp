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

		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_thunder0_00.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_thunder0_01.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_thunder0_02.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_thunder0_03.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_thunder0_04.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_thunder0_05.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_thunder0_06.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_thunder0_07.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_thunder0_08.png" );
		m_thunder0->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder0\\Ef_thunder0_09.png" );

		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_thunder1_00.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_thunder1_01.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_thunder1_02.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_thunder1_03.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_thunder1_04.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_thunder1_05.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_thunder1_06.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_thunder1_07.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_thunder1_08.png" );
		m_thunder1->AddTexture_FromArchive ( U"Ef_Clang\\Ef_Thunder1\\Ef_thunder1_09.png" );

		TASK_VEC::Load ();
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


		TASK_VEC::Move ();
	}

	void EfClang::On ( VEC2 center )
	{
		m_impact->SetRevised ( center );
		m_impact->On ();

		m_circle->SetRevised ( center );
		//		m_circle->SetFadeOut ( 30 );
		m_circle->On ();

		m_thunder0->SetRevised ( center );
		m_thunder0->On ();

		m_thunder1->SetRevised ( center );
		m_thunder1->On ();
	}

}
