//=================================================================================================
//
//	CharaSele_BGM
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele_BGM.h"
#include "_CharaSele.h"
#include "../GameMain/SeConst.h"
#include "../GameMain/SoundConst.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	CharaSele_BGM::CharaSele_BGM ()
	{
		//背景
		m_scroll_bgm = std::make_shared < GameGraphic > ();
		m_scroll_bgm->SetShader ( T );
		m_scroll_bgm->AddTexture_FromArchive ( U"CharaSele\\CharaSele_Scroll_BGM.png" );
		m_scroll_bgm->SetPos ( BGM_SCROLL_X, BGM_SCROLL_Y );
		m_scroll_bgm->SetZ ( Z_BG );
		AddpTask ( m_scroll_bgm );
		GRPLST_INSERT ( m_scroll_bgm );

		m_scrlbgm_x = BGM_SCROLL_X;

		//名前画像
		m_bgmSelect = std::make_shared < GameGraphic > ();
		m_bgmSelect->AddTexture_FromArchive ( U"CharaSele\\BGM_NAME_GABADARUGA.png" );
		m_bgmSelect->AddTexture_FromArchive ( U"CharaSele\\BGM_NAME_HIYODORI_OUKA.png" );
		m_bgmSelect->AddTexture_FromArchive ( U"CharaSele\\BGM_NAME_TOMOE_SAE.png" );
		m_bgmSelect->AddTexture_FromArchive ( U"CharaSele\\BGM_NAME_REKKA_RETSUDOU.png" );
		m_bgmSelect->SetPos ( VEC2 ( BGM_X, BGM_Y ) );
		m_bgmSelect->SetZ ( Z_EFF );
		AddpTask ( m_bgmSelect );
		GRPLST_INSERT ( m_bgmSelect );

		//選択矢印
		m_bgmSelectTri = std::make_shared < GrpBlink > ();
		m_bgmSelectTri->AddTexture_FromArchive ( U"CharaSele\\SelectTriangleBGM.png" );
		m_bgmSelectTri->SetPos ( VEC2 ( BGM_TRI_X, BGM_TRI_Y ) );
		m_bgmSelectTri->SetZ ( Z_EFF );
		m_bgmSelectTri->SetHalf ( T );
		AddpTask ( m_bgmSelectTri );
		GRPLST_INSERT ( m_bgmSelectTri );

		//文字表示
		const s3d::String filename = U"CharaSele\\Text_BGM_SELECT.png";
		VEC2 pos { TXT_BGM_X, TXT_BGM_Y };
		m_txt_BGMSelect = _CharaSele::MakeTxtGrp ( pos, filename );
		AddpTask ( m_txt_BGMSelect );
	}

	CharaSele_BGM::~CharaSele_BGM ()
	{
	}

	void CharaSele_BGM::Move ()
	{
		m_scrlbgm_x += 20;
		if ( 0 < m_scrlbgm_x ) { m_scrlbgm_x = BGM_SCROLL_X; }
		m_scroll_bgm->SetPos ( m_scrlbgm_x, BGM_SCROLL_Y );

		TASK_VEC::Move ();
	}

	//-------------------------------------------------
	void CharaSele_BGM::On ()
	{
		m_bgmSelectTri->Start ();
	}

	void CharaSele_BGM::Off ()
	{
		m_bgmSelectTri->Stop ();
	}

	void CharaSele_BGM::Prev ()
	{
		switch ( m_bgm_id )
		{
		case BGM_ID_GABA:	m_bgm_id = BGM_ID_OUKA;		 break;
		case BGM_ID_OUKA:	m_bgm_id = BGM_ID_SAE;		 break;
		case BGM_ID_SAE:	m_bgm_id = BGM_ID_RETSU;	 break;
		case BGM_ID_RETSU:	m_bgm_id = BGM_ID_GABA;		 break;
		}

		Set_BGM_ID ( m_bgm_id );
	}

	void CharaSele_BGM::Next ()
	{
		switch ( m_bgm_id )
		{
		case BGM_ID_GABA:	m_bgm_id = BGM_ID_RETSU;	 break;
		case BGM_ID_OUKA:	m_bgm_id = BGM_ID_GABA;		 break;
		case BGM_ID_SAE:	m_bgm_id = BGM_ID_OUKA;		 break;
		case BGM_ID_RETSU:	m_bgm_id = BGM_ID_SAE;		 break;
		}

		Set_BGM_ID ( m_bgm_id );
	}

	void CharaSele_BGM::Decide ()
	{
//		GetpParam()->Set_BGM_ID ( m_bgm_id );
		SND_PLAY_ONESHOT_SE ( SE_select_decide );
	}

	void CharaSele_BGM::Set_BGM_ID ( BGM_ID id )
	{
		SND_PLAY_ONESHOT_SE ( SE_select_move );
		m_bgm_id = id;
		m_bgmSelect->SetIndexTexture ( m_bgm_id );
		SND_STOP_ALL_BGM();
		SND_PLAY_LOOP_BGM ( BGM_ID_TO_NAME [ id ] );
	}


	//BGMセレクト
	const float CharaSele_BGM::BGM_SCROLL_X = -1280;
	const float CharaSele_BGM::BGM_SCROLL_Y = 570;
	const float CharaSele_BGM::BGM_X = 640 - 225;
	const float CharaSele_BGM::BGM_Y = 605;
	const float CharaSele_BGM::BGM_TRI_X = (1280 - 450) * 0.5f;
	const float CharaSele_BGM::BGM_TRI_Y = BGM_Y + 4;
	const float CharaSele_BGM::TXT_BGM_X  = 640 - 184 / 2;
	const float CharaSele_BGM::TXT_BGM_Y  = 572;


}	//namespace GAME

