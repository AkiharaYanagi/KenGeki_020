//=================================================================================================
//
//	CharaSele ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele.h"
#include "../Title/Title.h"
#include "../FtgMain/Fighting/Fighting.h"
//#include "../Training/Training.h"
#include "../GameMain/SoundConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	CharaSele::CharaSele ()
	{
		//BG
		m_bg = std::make_shared < GameGraphic > ();
		m_bg->AddTexture ( U"CharaSele_BG.png" );
		m_bg->SetZ ( Z_BG );
		AddpTask ( m_bg );
		GRPLST_INSERT ( m_bg );

#if 0
		//キャラ枠位置
		mv_pos.push_back ( ChSlct { CHSLID_0, 362,  17, CHSLID_7, CHSLID_3, CHSLID_2, CHSLID_1 } );
		mv_pos.push_back ( ChSlct { CHSLID_1, 512,  17, CHSLID_8, CHSLID_4, CHSLID_0, CHSLID_2 } );
		mv_pos.push_back ( ChSlct { CHSLID_2, 662,  17, CHSLID_9, CHSLID_4, CHSLID_1, CHSLID_0 } );
		mv_pos.push_back ( ChSlct { CHSLID_3, 437, 167, CHSLID_0, CHSLID_5, CHSLID_4, CHSLID_4 } );
		mv_pos.push_back ( ChSlct { CHSLID_4, 587, 167, CHSLID_1, CHSLID_6, CHSLID_3, CHSLID_3 } );
		mv_pos.push_back ( ChSlct { CHSLID_5, 437, 577, CHSLID_3, CHSLID_7, CHSLID_6, CHSLID_6 } );
		mv_pos.push_back ( ChSlct { CHSLID_6, 587, 577, CHSLID_4, CHSLID_8, CHSLID_5, CHSLID_5 } );
		mv_pos.push_back ( ChSlct { CHSLID_7, 362, 727, CHSLID_5, CHSLID_0, CHSLID_9, CHSLID_8 } );
		mv_pos.push_back ( ChSlct { CHSLID_8, 512, 727, CHSLID_6, CHSLID_1, CHSLID_7, CHSLID_9 } );
		mv_pos.push_back ( ChSlct { CHSLID_9, 662, 727, CHSLID_6, CHSLID_2, CHSLID_8, CHSLID_7 } );

		//カーソル
		m_cursor1p = make_shared < GrpBlink > ();
		m_cursor1p->AddTexture ( _T ( "CharaSele_Cursor_1p.png" ) );
		m_cursor1p->SetPos ( SELECT_1P_POS_X, SELECT_1P_POS_Y );
		m_cursor1p->SetTimer ( 15 );
		AddpTask ( m_cursor1p );
		GRPLST_INSERT_MAIN ( m_cursor1p );

		m_cursor2p = make_shared < GrpBlink > ();
		m_cursor2p->AddTexture ( _T ( "CharaSele_Cursor_2p.png" ) );
		m_cursor2p->SetPos ( SELECT_2P_POS_X, SELECT_2P_POS_Y );
		AddpTask ( m_cursor2p );
		GRPLST_INSERT_MAIN ( m_cursor2p );

		//選択位置
		m_chslct_id_1p = CHSLID_0;
		m_chslct_id_2p = CHSLID_2;


		//キャラ立絵
		m_chara_1p = make_shared < GrpAcv > ();
		m_chara_1p->AddTexture ( _T("Stand_Ouka.png") );
		m_chara_1p->AddTexture ( _T("Stand_Sae.png") );
		m_chara_1p->SetPos ( CHARA_1P_POS_X, CHARA_1P_POS_Y );
		AddpTask ( m_chara_1p );
		GRPLST_INSERT_MAIN ( m_chara_1p );

		m_chara_2p = make_shared < GrpAcv > ();
		m_chara_2p->AddTexture ( _T("Stand_Ouka.png") );
		m_chara_2p->AddTexture ( _T("Stand_Sae.png") );
		m_chara_2p->SetPos ( CHARA_2P_POS_X, CHARA_2P_POS_Y );
		AddpTask ( m_chara_2p );
		GRPLST_INSERT_MAIN ( m_chara_2p );

#endif // 0

		//選択プレイヤ
		m_chsl_pl_1p = std::make_shared < CharaSele_Player > ();
		m_chsl_pl_1p->PlayerInit ( PLAYER_ID_1 );
		AddpTask ( m_chsl_pl_1p );

		m_chsl_pl_2p = std::make_shared < CharaSele_Player > ();
		m_chsl_pl_2p->PlayerInit ( PLAYER_ID_2 );
		AddpTask ( m_chsl_pl_2p );

		//フェードアウト
#if 0
		m_fade_out = std::make_shared < PrmRect > ();
		m_fade_out->SetSize ( VEC2 ( 1280, 960 ) );
		m_fade_out->SetPos ( VEC2 ( 0, 0 ) );
		m_fade_out->SetColor ( 0x00000000 );
		m_fade_out->SetZ ( Z_FADE - 0.1f );
		m_fade_out->SetValid ( F );
		AddpTask ( m_fade_out );
		GRPLST_INSERT ( m_fade_out );
		m_wait_out_title = 0;
		m_wait_out_fighting = 0;
#endif // 0

		//ステージセレクト
		m_stageSelect = std::make_shared < GameGraphic > ();
		m_stageSelect->AddTexture ( U"stage_select_0.png" );
		m_stageSelect->AddTexture ( U"stage_select_1.png" );
		m_stageSelect->AddTexture ( U"stage_select_2.png" );
		m_stageSelect->SetPos ( VEC2 ( 640 - 128, 400 ) );
		m_stageSelect->SetZ ( Z_BG - 0.1f );
		AddpTask ( m_stageSelect );
		GRPLST_INSERT ( m_stageSelect );
	}

	CharaSele::~CharaSele ()
	{
	}

	void CharaSele::Load ()
	{
		//==================================================
		//	Scene共通
		//==================================================
		//遷移先を自身に設定
		//	(コンストラクタでは shared_from_this() が使えないため、Load() で呼び出す)
		Scene::SetwpThis ( shared_from_this () );
		//==================================================
		
		Scene::Load ();
	}

	P_GameScene CharaSele::Transit ()
	{
		//ESCで戻る
//		if ( ::GetAsyncKeyState ( VK_ESCAPE ) & 0x0001 )
		if ( WND_UTL::AscKey ( VK_ESCAPE ) )
		{
			//フェード開始
#if 0
			m_fade_out->SetFade ( 8, _CLR ( 0x00000000UL ), _CLR ( 0xff000000UL ) );	//開始値、目標値を手動設定
			m_wait_out_title = 1;
#endif // 0
		}

		return Scene::Transit (); 
	}


	void CharaSele::ParamInit ()
	{
//		Scene::GetpParam ();
		SOUND->Play_Loop_BGM ( BGM_CHARA_SELE );
	}
	

	void CharaSele::Init ()
	{
		Scene::Init (); 
	}
	
	void CharaSele::Move ()
	{
		//----------------------------------------------------------
		//キャラ選択、ステージ選択をパラメータに記録
		P_Param pPrm = Scene::GetpParam ();
		pPrm->SetCharaName1p ( m_chsl_pl_1p->GetName() );
		pPrm->SetCharaName2p ( m_chsl_pl_2p->GetName() );
		pPrm->SetStageName ( GetStageName () );

		//----------------------------------------------------------
		//フェードアウト中
#if 0
		//タイトルに移行
		if ( m_wait_out_title != 0 )
		{
			++ m_wait_out_title;

			if ( m_wait_out_title > 15 )
			{
				SOUND->Stop_BGM ( BGM_CHARA_SELE );
				Scene::Transit_Title ();
				m_wait_out_title = 0;
			}
		}
		//戦闘に移行
		if ( m_wait_out_fighting != 0 )
		{
			++ m_wait_out_fighting;

			if ( m_wait_out_fighting > 15 )
			{
				SOUND->Stop_BGM ( BGM_CHARA_SELE );
				Scene::Transit_Fighting ();
				m_wait_out_fighting = 0;
			}
		}
#endif // 0

		//----------------------------------------------------------

#if 0
		//決定
		bool b0 = ( m_wait_out_fighting == 0 );
		bool b1 = m_chsl_pl_1p->IsDecided ();
		bool b2 = m_chsl_pl_2p->IsDecided ();

		//片方が決定したらステージセレクト
		if ( b1 )
		{
			if ( CFG_PUSH_KEY ( P1_LEFT ) )
			{
				m_stageSelect->PrevIndexTexture ();
				SOUND->Play_SE ( SE_Sys_Select );
			}
			if ( CFG_PUSH_KEY ( P1_RIGHT ) )
			{
				m_stageSelect->NextIndexTexture ();
				SOUND->Play_SE ( SE_Sys_Select );
			}

			if ( CFG_PUSH_KEY ( P1_BTN0 ) )
			{
				m_stageDecide = T;
			}
		}
		if ( b2 )
		{
			if ( CFG_PUSH_KEY ( P2_LEFT ) )
			{
				m_stageSelect->PrevIndexTexture ();
				SOUND->Play_SE ( SE_Sys_Select );
			}
			if ( CFG_PUSH_KEY ( P2_RIGHT ) )
			{
				m_stageSelect->NextIndexTexture ();
				SOUND->Play_SE ( SE_Sys_Select );
			}

			if ( CFG_PUSH_KEY ( P2_BTN0 ) )
			{
				m_stageDecide = T;
			}
		}

		//両者決定したらFtgMainに移行
		if ( b0 && b1 && b2 && m_stageDecide )
		{ 
			//フェード開始
			m_fade_out->SetFade ( 8, _CLR ( 0x00000000UL ), _CLR ( 0xff000000UL ) );	//開始値、目標値を手動設定
			m_wait_out_fighting = 1;
		}
#endif // 0

		Scene::Move (); 
	}


	STAGE_NAME CharaSele::GetStageName ()
	{
		STAGE_NAME ret = STAGE_YUUHINO_HARA;

		switch ( m_stageSelect->Getpap_ob()->at ( 0 )->GetIndexTexture () )
		{
		case 0: ret = STAGE_ASAHINO_HARA; break;
		case 1: ret = STAGE_YUUHINO_HARA; break;
		case 2: ret = STAGE_YORUNO_HARA; break;
		}
		return ret;
	}


}	//namespace GAME

