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


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
#pragma region CONST
	const float Result::CHARA_PY = 20.f;	//位置Y

	const float Result::CHARA_PX = -100.f;	//目標位置
	const float Result::CHARA_SX = -800.f;	//初期位置
	const float Result::CHARA_VX = 30.f;	//速度

	const float Result::NEXT_X = 1100.f;
	const float Result::NEXT_Y = 860.f;

	const float Result::NUM_X = 1140.f;
	const float Result::NUM_Y = 482.f;
	const float Result::NUM_P = 68.f;

	const float Result::MSG_X = 150.f;
	const float Result::MSG_Y = 750.f;
#pragma endregion


	Result::Result ()
	{
		m_mov = std::make_shared < GrpMov > ();
		m_mov->SetMovName ( U"Mov\\Result.mp4" );
		m_mov->Loop ( T );
		m_mov->Start ();
		m_mov->SetZ ( Z_BG );
		AddpTask ( m_mov );
		GRPLST_INSERT ( m_mov );

		m_chara = std::make_shared < GameGraphic > ();
		m_chara->AddTexture_FromArchive ( U"CharaSele\\Stand_Ouka.png" );
		m_chara->AddTexture_FromArchive ( U"CharaSele\\Stand_Sae.png" );
		m_chara->AddTexture_FromArchive ( U"CharaSele\\Stand_Retsudou.png" );
		m_chara->SetPos ( CHARA_SX, CHARA_PY );
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

		m_fade_in->StartBlackIn ( 16 );

		//フェードアウト
		m_fade_out = std::make_shared < FadeRect > ();
		m_fade_out->SetAfterClear ( F );
		AddpTask ( m_fade_out );
		GRPLST_INSERT ( m_fade_out );


		//次へ
		m_next_tri = std::make_shared < GrpBlink > ();
		m_next_tri->AddTexture_FromArchive ( U"NextTriangle.png" );
		m_next_tri->SetPos ( NEXT_X, NEXT_Y );
		m_next_tri->SetBlinkTime ( 15 );
		m_next_tri->Start ();
		AddpTask ( m_next_tri );
		GRPLST_INSERT ( m_next_tri );


		//メニュ
//		m_menu = std::make_shared < ResultMenu > ();
//		AddpTask ( m_menu );

		//勝利メッセージ
		m_win_msg = std::make_shared < GrpStr > ();
		m_win_msg->SetPos ( MSG_X, MSG_Y );
		m_win_msg->SetSize ( G_Font::SIZE_40 );
		AddpTask ( m_win_msg );
		GRPLST_INSERT ( m_win_msg );

		//@info size40で22文字で枠内
		m_msg.assign ( U"勝利メッセージのテスト。\nリザルト画面を待つ状態でどこまで表示できるか" );

		//数値
		m_n_offset = MakeStr ( NUM_X, NUM_Y + NUM_P * 0 );
		m_n_max_chn = MakeStr ( NUM_X, NUM_Y + NUM_P * 1 );
		m_n_max_dmg = MakeStr ( NUM_X, NUM_Y + NUM_P * 2 );

	}

	P_GrpStr Result::MakeStr ( float x, float y )
	{
		P_GrpStr pStr = std::make_shared < GrpStr > ();
		pStr->SetPos ( x, y );
		pStr->SetSize ( G_Font::SIZE_40 );
		AddpTask ( pStr );
		pStr->SetStr ( U"{}"_fmt ( y )  );
		GRPLST_INSERT ( pStr );
		return pStr;
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

	void Result::Init ()
	{
		m_chara_x = CHARA_SX;
		Scene::Init ();
	}

	void Result::Move ()
	{
		//フェード中もキャラ表示は移動
		m_chara_x += CHARA_VX;
		if ( m_chara_x > CHARA_PX ) { m_chara_x = CHARA_PX; }
		m_chara->SetPos ( m_chara_x, CHARA_PY );


		//フェードのラストでBGM開始
		if ( m_fade_in->IsLast () )
		{
			//BGM
			SOUND->Stop_BGM ( BGM_Result );
			SOUND->Play_BGM ( BGM_Result );
		}

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

		//メッセージ
		const size_t length = static_cast < size_t > ( s3d::Scene::Time () / 0.05 );
		m_win_msg->SetStr ( m_msg.substr ( 0, length ) );

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
				SOUND->Stop_BGM ( BGM_Result );

				//キャラセレに移行
				Scene::Transit_CharaSele ();
				m_plus_wait = 0;
			}
			++ m_plus_wait;
		}

		return Scene::Transit ();
	}


}	//namespace GAME

