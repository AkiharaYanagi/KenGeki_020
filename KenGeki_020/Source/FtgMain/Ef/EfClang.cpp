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
		m_circle = std::make_shared < GrpEf > ();

		AddpTask ( m_circle );
		SDRLST_INSERT ( m_circle );
	}

	EfClang::~EfClang ()
	{
	}



	void EfClang::Load ()
	{
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

		TASK_VEC::Load ();
	}



	void EfClang::Move ()
	{
		m_circle->SetDispBase ( G_BASE_POS () );

		if ( m_index >= m_circle->Getpap_tx()->size() )
		{
			m_index = 0;
			m_circle->Off ();
		}
		m_circle->SetIndexTexture ( m_index );
		++ m_index;


		TASK_VEC::Move ();
	}

	void EfClang::On ( VEC2 center )
	{
		m_circle->SetRevised ( center );
//		m_circle->SetFadeOut ( 30 );
		m_index = 0;
		m_circle->On ();
	}

}
