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
#include "../GameMain/SeConst.h"


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

	const float Result::NUM_BG_X = 900;	//戦闘数値 背景
	const float Result::NUM_BG_Y = 380;	
	const float Result::NUM_X = 900 + 240.f;	//戦闘数値 
	const float Result::NUM_Y = NUM_BG_Y + 82.f;
	const float Result::NUM_P = 68.f;

	const float Result::MSG_WND_X = 0.5f * ( WINDOW_WIDTH - 1068 );
	const float Result::MSG_WND_Y = 680.f;

	const float Result::MSG_X = 150.f;
	const float Result::MSG_Y = MSG_WND_Y + 10.f;

	const float Result::INST_X = 0;
	const float Result::INST_Y = 960 - 27;
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
		m_state->SetPos ( NUM_BG_X, NUM_BG_Y );
		AddpTask ( m_state );
		GRPLST_INSERT ( m_state );


		//勝利メッセージウィンドウ
		m_MsgWnd = std::make_shared < GameGraphic > ();
		m_MsgWnd->AddTexture_FromArchive ( U"Result\\MsgWnd.png" );
		m_MsgWnd->SetPos ( MSG_WND_X, MSG_WND_Y  );
		AddpTask ( m_MsgWnd );
		GRPLST_INSERT ( m_MsgWnd );


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

		//操作説明
		m_inst = std::make_shared < GameGraphic > ();
		m_inst->AddTexture_FromArchive ( U"Result\\Inst_Result.png" );
		m_inst->SetPos ( INST_X, INST_Y );
		AddpTask ( m_inst );
		GRPLST_INSERT ( m_inst );


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


		m_ch_msg.emplace ( CHARA_OUKA,		U"鵯 桜花：\n・・・。");
		m_ch_msg.emplace ( CHARA_SAE,		U"巴 紗絵：\nそれでおしまい？　\nもっと本気だしてよ♪");
		m_ch_msg.emplace ( CHARA_RETSUDOU,	U"烈火 烈堂：\n本当に良い刀ってのは鞘に入ってるもんだぜ･･･");


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
		P_Param pParam = Scene::GetpParam ();
		PLAYER_ID pl = pParam->GetWinner ();

		//各種数値
		int32 nOffset = pParam->GetOffset ();
		m_n_offset->SetStr ( U"{}"_fmt ( nOffset ) );

		if ( pl == PLAYER_ID_1 )
		{
			int32 n_max_chn = pParam->Get_MAX_CHN_1P ();
			m_n_max_chn->SetStr ( U"{}"_fmt ( n_max_chn ) );
			int32 n_max_dmg = pParam->Get_MAX_DMG_1P ();
			m_n_max_dmg->SetStr ( U"{}"_fmt ( n_max_dmg ) );
		}
		else if ( pl == PLAYER_ID_2 )
		{
			int32 n_max_chn = pParam->Get_MAX_CHN_2P ();
			m_n_max_chn->SetStr ( U"{}"_fmt ( n_max_chn ) );
			int32 n_max_dmg = pParam->Get_MAX_DMG_2P ();
			m_n_max_dmg->SetStr ( U"{}"_fmt ( n_max_dmg ) );
		}

		//フェード
		m_fade_in->StartBlackIn ( 16 );

		//キャラ表示
		m_chara_x = CHARA_SX;

		//文字カウント
		m_time_count = 0;

		Scene::Init ();
	}

	void Result::Move ()
	{
		P_Param pParam = Scene::GetpParam ();
		PLAYER_ID win_player = pParam->GetWinner ();
		CHARA_NAME name = pParam->GetCharaName ( win_player );

		//フェード中もキャラ表示は移動
		m_chara_x += CHARA_VX;
		if ( m_chara_x > CHARA_PX ) { m_chara_x = CHARA_PX; }
		m_chara->SetPos ( m_chara_x, CHARA_PY );


		//フェードのラストでBGM開始
		if ( m_fade_in->IsLast () )
		{
			//BGM
			SND_STOP_ALL_BGM ();
			SND_PLAY_BGM ( BGM_Result );
		}

		//フェード中は何もしない
		if ( m_fade_in->IsActive () ) { Scene::Move (); return; }
		if ( m_fade_out->IsActive () ) { Scene::Move (); return; }

		//キー1でシーンを進める
		if ( CFG_PUSH_KEY ( P1_BTN0 ) || CFG_PUSH_KEY ( P2_BTN0 ) )
		{
			SND_PLAY_ONESHOT_SE ( SE_select_decide );

			//フェード開始
			m_fade_out->StartBlackOut ( 16 );
		}



		//test
		// 
		//キー6でリセット
		if ( CFG_PUSH_KEY ( P1_BTN6 ) || CFG_PUSH_KEY ( P2_BTN6 ) )
		{
			SND_STOP_ALL_BGM ();
			Init ();
		}


		//メッセージ
		const size_t length = static_cast < size_t > ( m_time_count ++ / 5 );
		//m_win_msg->SetStr ( m_msg.substr ( 0, length ) );
		m_win_msg->SetStr ( m_ch_msg [ name ].substr ( 0, length ) );

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
				//SOUND->Stop_BGM ( BGM_Result );
				SND_STOP_ALL_BGM ();

				//シーンパラメータの戦闘数値をここでリセット
				GetpParam()->ResetBattleParam ();


				//キャラセレに移行
				Scene::Transit_CharaSele ();
				m_plus_wait = 0;
			}
			++ m_plus_wait;
		}

		return Scene::Transit ();
	}


}	//namespace GAME

