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
		m_bg->AddTexture_FromArchive ( U"CharaSele_BG.png" );
		m_bg->SetPos ( 0, 0 );
		m_bg->SetZ ( Z_BG );
		AddpTask ( m_bg );
		GRPLST_INSERT ( m_bg );

		//プレイヤ別の位置など
		m_chsl_pl_1p = std::make_shared < CharaSele_Player > ();
		m_chsl_pl_1p->PlayerInit ( PLAYER_ID_1 );
		AddpTask ( m_chsl_pl_1p );

		m_chsl_pl_2p = std::make_shared < CharaSele_Player > ();
		m_chsl_pl_2p->PlayerInit ( PLAYER_ID_2 );
		AddpTask ( m_chsl_pl_2p );


		//フェードアウト
		m_fade_toTitle = std::make_shared < FadeRect > ();
		AddpTask ( m_fade_toTitle );
		GRPLST_INSERT ( m_fade_toTitle );

		m_fade_toFighting = std::make_shared < FadeRect > ();
		AddpTask ( m_fade_toFighting );
		GRPLST_INSERT ( m_fade_toFighting );

		//ステージセレクト
		m_stageSelect = std::make_shared < GameGraphic > ();
		//m_stageSelect->AddTexture_FromArchive ( U"stage_select_0.png" );
		//m_stageSelect->AddTexture_FromArchive ( U"stage_select_1.png" );
		//m_stageSelect->AddTexture_FromArchive ( U"stage_select_2.png" );
		m_stageSelect->AddTexture_FromArchive ( U"BG_Preview_Evening.png" );
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

		//SOUND
		SOUND->Stop_BGM ( BGM_CHARA_SELE );
		SOUND->Play_Loop_BGM ( BGM_CHARA_SELE );

		Scene::Load ();
	}

	P_GameScene CharaSele::Transit ()
	{
		//BackSpaceで戻る
		if ( WND_UTL::AscKey ( VK_BACK ) )
		{
			SOUND->Play_SE ( SE_Sys_Cancel );

			//フェード開始
			m_fade_toTitle->SetBlackOut ( 68 );
		}

		return Scene::Transit (); 
	}


	void CharaSele::ParamInit ()
	{
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
		//タイトルに移行
		if ( m_fade_toTitle->IsActive() )
		{
			if ( m_fade_toTitle->IsLast () )
			{
				SOUND->Stop_BGM ( BGM_CHARA_SELE );
				Scene::Transit_Title ();
			}
		}
		//戦闘に移行
		if ( m_fade_toFighting->IsActive () )
		{
			if ( m_fade_toFighting->IsLast () )
			{
				SOUND->Stop_BGM ( BGM_CHARA_SELE );
				Scene::Transit_Fighting ();
			}
		}

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

#if 0
		switch ( m_stageSelect->Getpap_ob()->at ( 0 )->GetIndexTexture () )
		{
		case 0: ret = STAGE_ASAHINO_HARA; break;
		case 1: ret = STAGE_YUUHINO_HARA; break;
		case 2: ret = STAGE_YORUNO_HARA; break;
		}
#endif // 0

		return ret;
	}


}	//namespace GAME

