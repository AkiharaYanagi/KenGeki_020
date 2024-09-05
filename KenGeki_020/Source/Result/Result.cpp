//=================================================================================================
//
//	タイトル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Result.h"
#include "../GameMain/SoundConst.h"

//遷移先
#include "../FtgMain/FtgMain.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	Result::Result ()
	{
		m_mov = std::make_shared < GrpMov > ();
		m_mov->SetMovName ( U"Result.mp4" );
		m_mov->Loop ( T );
		m_mov->Start ();
		m_mov->SetZ ( Z_BG );
		AddpTask ( m_mov );
		GRPLST_INSERT ( m_mov );

		m_chara = std::make_shared < GameGraphic > ();
		m_chara->AddTexture_FromArchive ( U"CharaSele\\Stand_Ouka.png" );
		m_chara->AddTexture_FromArchive ( U"CharaSele\\Stand_Sae.png" );
		m_chara->AddTexture_FromArchive ( U"CharaSele\\Stand_Retsudou.png" );
		m_chara->SetPos ( -100, 10 );
		AddpTask ( m_chara );
		GRPLST_INSERT ( m_chara );

		m_state = std::make_shared < GameGraphic > ();
		m_state->AddTexture_FromArchive ( U"Result\\Result_State.png" );
		m_state->SetPos ( 900, 400 );
		AddpTask ( m_state );
		GRPLST_INSERT ( m_state );

		m_Msg = std::make_shared < GameGraphic > ();
		m_Msg->AddTexture_FromArchive ( U"Result\\MsgWnd.png" );
		m_Msg->SetPos ( 0.5f * ( 1280 - 1068 ), 700 );
		AddpTask ( m_Msg );
		GRPLST_INSERT ( m_Msg );


		//フェードイン
		m_fade_in = std::make_shared < FadeRect > ();
		AddpTask ( m_fade_in );
		GRPLST_INSERT ( m_fade_in );

		m_fade_in->StartBlackIn ( 8 );

		//フェードアウト
		m_fade_out = std::make_shared < FadeRect > ();
		m_fade_out->SetAfterClear ( F );
		AddpTask ( m_fade_out );
		GRPLST_INSERT ( m_fade_out );
	}

	Result::~Result ()
	{
	}

	void Result::Load ()
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

	void Result::ParamInit ()
	{
		P_Param pParam = Scene::GetpParam ();
		PLAYER_ID win_player = pParam->GetWinner ();
		CHARA_NAME name = pParam->GetCharaName ( win_player );

		switch ( name )
		{
		case CHARA_OUKA:
			m_chara->SetIndexTexture ( 0 );
			break;
		case CHARA_SAE:
			m_chara->SetIndexTexture ( 1 );
			break;
		case CHARA_RETSUDOU:
			m_chara->SetIndexTexture ( 2 );
			break;
		}
	}

	void Result::Move ()
	{
		//フェード中は何もしない
		if ( m_fade_in->IsActive () ) { Scene::Move (); return; }
		if ( m_fade_out->IsActive () ) { Scene::Move (); return; }

		//キー1でシーンを進める
		if ( CFG_PUSH_KEY ( P1_BTN0 ) || CFG_PUSH_KEY ( P2_BTN0 ) )
		{
			SOUND->Play_SE ( SE_Sys_Enter );

			//フェード開始
			m_fade_out->StartBlackOut ( 16 );
		}

		Scene::Move ();
	}

	P_GameScene Result::Transit ()
	{
		//フェード待機後、遷移開始
		if ( m_fade_out->IsLast () )
		{
			++ m_plus_wait;
		}

		if ( m_plus_wait > 0 )
		{
			if ( m_plus_wait > 15 )
			{
				Scene::Transit_Title ();
				m_plus_wait = 0;
			}
			++ m_plus_wait;
		}

		return Scene::Transit ();
	}


}	//namespace GAME

