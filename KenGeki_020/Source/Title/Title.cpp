﻿//=================================================================================================
//
//	タイトル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Title.h"
#include "../GameMain/SoundConst.h"
#include "../GameMain/VoiceConst.h"
#include "../GameMain/SeConst.h"
#include "../GameMain/DebugDisp.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

#pragma region CONST

#if 0
		//2024/11/03 デジゲー博 Ver 0.10
		//2024/11/03 修正パッチ Ver 0.12;
		//2024/12/15 変な格ゲー会 ver0.15
		//2024/12/30 冬コミ ver0.20
		//2024/12/31 冬コミ修正 ver0.21
		//2024/02/10 Steam ver0.22
		//2024/02/20 修正 ver0.23
#endif // 0
	const char32_t Title::Ver[] = U"ver 0.23";

	const float Title::BG_X = 0;
	const float Title::BG_Y = 0;
	const float Title::BG_VX = -64.f;
	const float Title::BG_P = (-7680 + 1920);

	const float Title::LOGO_X = ( WINDOW_WIDTH - 648 ) * 0.5f;
	const float Title::LOGO_Y = 0;

	const float Title::CURSOR_X = 400;
	const float Title::CURSOR_Y = 720;
	const float Title::CURSOR_P = 50;

	const float Title::MENU_X = CURSOR_X + 100;
	const float Title::MENU_Y = CURSOR_Y - 7;
	const float Title::MENU_Y0 = MENU_Y  + 0;
	const float Title::MENU_Y1 = MENU_Y0 + CURSOR_P;
	const float Title::MENU_Y2 = MENU_Y1 + CURSOR_P;
	const float Title::MENU_Y3 = MENU_Y2 + CURSOR_P;

	const float Title::INST_X = 0;
	const float Title::INST_Y = 960 - 27;

	const uint32 Title::FADE_IN_T = 16;
	const uint32 Title::FADE_OUT_T = 16;

	const uint32 Title::TITLE_CALL_WAIT = 2;

	const int32 Title::WAIT_DEMO = 300;
//	const int32 Title::WAIT_DEMO = 180;
	const int32 Title::BAR_DEMO_Y = 752;

#pragma endregion


	Title::Title ()
	{
		//---------------------------------------------------
		//グラフィック初期化
		//---------------------------------------------------
		m_bg = std::make_shared < GameGraphic > ();
		m_bg->AddTexture_FromArchive ( U"Title\\title_bg.png" );
		m_bg->SetPos ( BG_X, BG_Y );
		m_bg->SetZ ( Z_BG );
		AddpTask ( m_bg );
		GRPLST_INSERT ( m_bg );

		m_logo = std::make_shared < GameGraphic > ();
		m_logo->AddTexture_FromArchive ( U"Title\\title_logo.png" );
		m_logo->SetPos ( LOGO_X, LOGO_Y );
		m_logo->SetZ ( Z_BG );
		AddpTask ( m_logo );
		GRPLST_INSERT ( m_logo );

		m_menu_1PvsCPU = std::make_shared < GameGraphic > ();
		m_menu_1PvsCPU->AddTexture_FromArchive ( U"Title\\Title_Menu_1PvsCPU.png" );
		m_menu_1PvsCPU->SetPos ( MENU_X, MENU_Y0 );
		m_menu_1PvsCPU->SetZ ( Z_CH );
		AddpTask ( m_menu_1PvsCPU );
		GRPLST_INSERT ( m_menu_1PvsCPU );

		m_menu_1Pvs2P = std::make_shared < GameGraphic > ();
		m_menu_1Pvs2P->AddTexture_FromArchive ( U"Title\\Title_Menu_1Pvs2P.png" );
		m_menu_1Pvs2P->SetPos ( MENU_X, MENU_Y1 );
		m_menu_1Pvs2P->SetZ ( Z_CH );
		AddpTask ( m_menu_1Pvs2P );
		GRPLST_INSERT ( m_menu_1Pvs2P );

		m_menu_CPUvsCPU = std::make_shared < GameGraphic > ();
		m_menu_CPUvsCPU->AddTexture_FromArchive ( U"Title\\Title_Menu_CPUvsCPU.png" );
		m_menu_CPUvsCPU->SetPos ( MENU_X, MENU_Y2 );
		m_menu_CPUvsCPU->SetZ ( Z_CH );
		AddpTask ( m_menu_CPUvsCPU );
		GRPLST_INSERT ( m_menu_CPUvsCPU );

		m_menu_Training = std::make_shared < GameGraphic > ();
		m_menu_Training->AddTexture_FromArchive ( U"Title\\Title_Menu_Training.png" );
		m_menu_Training->SetPos ( MENU_X, MENU_Y3 );
		m_menu_Training->SetZ ( Z_CH );
		AddpTask ( m_menu_Training );
		GRPLST_INSERT ( m_menu_Training );

		m_cursor = std::make_shared < GameGraphic > ();
		m_cursor->AddTexture_FromArchive ( U"Title\\title_cursor.png" );
		m_cursor->SetPos ( CURSOR_X, CURSOR_Y );
		m_cursor->SetScalingCenter ( 0, 12.5f );
		m_cursor->SetZ ( Z_CH );
		AddpTask ( m_cursor );
		GRPLST_INSERT ( m_cursor );

		m_inst = std::make_shared < GameGraphic > ();
		m_inst->AddTexture_FromArchive ( U"Title\\Inst_Title.png" );
		m_inst->SetPos ( INST_X, INST_Y );
		m_inst->SetZ ( Z_CH );
		AddpTask ( m_inst );
		GRPLST_INSERT ( m_inst );

		//カーソル位置
		m_cursor->SetPos ( CURSOR_X, CURSOR_Y + CURSOR_P * (int32)m_to );


		//フェードイン
		m_fade_in = std::make_shared < FadeRect > ();
		AddpTask ( m_fade_in );
		GRPLST_INSERT ( m_fade_in );

		m_fade_in->StartWhiteIn ( FADE_IN_T );

		//フェードアウト
		m_fade_out = std::make_shared < FadeRect > ();
		m_fade_out->SetAfterClear ( F );
		AddpTask ( m_fade_out );
		GRPLST_INSERT ( m_fade_out );


		//タイマ
		m_tmr_title_bgm = std::make_shared < Timer > ( FADE_IN_T );
		m_tmr_title_bgm->Start ();
		m_tmr_title_call = std::make_shared < Timer > ( TITLE_CALL_WAIT );
		m_tmr_title_call->Start ();


		//Ver.
		m_strVer = std::make_shared < GrpStr > ();
		m_strVer->SetPos ( 1185, 905 );
		m_strVer->SetZ ( Z_MENU );
		m_strVer->SetStr ( Ver );

		AddpTask ( m_strVer );
		GRPLST_INSERT ( m_strVer );


		//デモ
		m_strDemo = std::make_shared < GrpStr > ();
		m_strDemo->SetSize ( G_Font::SIZE_40 );
		m_strDemo->SetPos ( 500, 700 );
		m_strDemo->SetZ ( Z_MENU );
		m_strDemo->SetStr ( U"- Demo Mode -" );
		AddpTask ( m_strDemo );
		GRPLST_INSERT ( m_strDemo );

		m_barDemo = std::make_shared < PrmRect > ();
		m_barDemo->SetSize ( 300, 2 );
		m_barDemo->SetColor ( _CLR ( 0xffff8080 ) );
		m_barDemo->SetPos ( 640 - 150, BAR_DEMO_Y );
		AddpTask ( m_barDemo );
		GRPLST_INSERT ( m_barDemo );

		m_strDemoSwitch = std::make_shared < GrpStr > ();
		m_strDemoSwitch->SetSize ( G_Font::SIZE_20 );
		m_strDemoSwitch->SetPos ( 522, 758 );
		m_strDemoSwitch->SetZ ( Z_MENU );
		m_strDemoSwitch->SetStr(U"( デモモード：F9で切換 )");
		AddpTask ( m_strDemoSwitch );
		GRPLST_INSERT ( m_strDemoSwitch );

		m_tmrDemo.SetTargetTime ( WAIT_DEMO );
		m_tmrDemo.Start ();

		m_fade_demo = std::make_shared < FadeRect > ();
		m_fade_demo->SetAfterClear ( F );
		AddpTask ( m_fade_demo );
		GRPLST_INSERT ( m_fade_demo );

		//初期値はOff
		OffDemo ();



		//体験版表示
#if TRIAL
		m_trial = std::make_shared < GameGraphic > ();

		m_trial->SetPos ( 1280 - 200, 820 );
		m_trial->AddTexture_FromArchive ( U"Title\\trial.png" );
		AddpTask ( m_trial );
		GRPLST_INSERT ( m_trial );
#else // TRIAL

#endif // TRIAL


	}

	Title::~Title ()
	{
	}

	void Title::Load ()
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


	void Title::ParamInit ()
	{
		P_Param pPrm = GetpParam();
		GameSettingFile stg = pPrm->GetGameSetting ();

		//デモ切換
		m_bDemo = stg.GetDemo();
		ValidDemo ( m_bDemo );
	}

	void Title::Move ()
	{
		//デモモード
		if ( m_bDemo )
		{
			//タイトルでカウントして自動で開始
			m_tmrDemo.Move ();

			uint32 t = m_tmrDemo.GetTime ();
			int32 w = (int32) ( (WAIT_DEMO - t) * 300.0 / WAIT_DEMO );
			m_barDemo->SetSize ( w, 2 );
			m_barDemo->SetPos ( 640 + 150 - w, BAR_DEMO_Y );

			//カウント終了後、シーン移行
			if ( m_tmrDemo.IsLast () )
			{
				//値の取得
				P_Param pPrm = GetpParam();

				//ランダムで各種値を決める
				pPrm->SetCharaName1p ( GetCharaName_Rnd () );	//キャラランダム
				pPrm->SetCharaName2p ( GetCharaName_Rnd () );	//キャラランダム
				pPrm->Set_BGM_ID ( GetBGM_ID_Rnd () );		//BGMランダム
				pPrm->SetStage_Name ( GetStageName_Rnd () );	//ステージランダム

				//CPU操作
				pPrm->SetMutchMode ( MUTCH_MODE::MODE_CPU_CPU );

				SND_PLAY_ONESHOT_SE ( SE_select_decide );
				m_fade_demo->StartBlackOut ( FADE_OUT_T );
				m_barDemo->SetValid ( F );
			}
		}
		
		//F9でデモ切替 (ボタン：リセットでも切換)
		if ( WND_UTL::AscKey ( VK_F9 ) || CFG_PUSH_KEY_12 ( PLY_BTN7 ) )
		{
			//値の取得
			P_Param pPrm = GetpParam();

			//反転
			m_bDemo = ! m_bDemo;
			ValidDemo ( m_bDemo );

			//開始時
			if ( m_bDemo )
			{
				//デモモードタイマのスタート
				m_tmrDemo.Start ();
			}
			else
			{
				//プレイヤ操作
				pPrm->SetMutchMode ( MUTCH_MODE::MODE_PLAYER_PLAYER );
			}

			//保存
			pPrm->SetDemo ( m_bDemo );
			pPrm->GetGameSetting ().Save ();

//			bool b = GetpParam()->GetGameSetting().GetDemo ();
		}

		//---------------------------------------------------------
		//常時演出
		
		//タイマ
		m_tmr_title_bgm->Move ();
		if ( m_tmr_title_bgm->IsLast () )
		{
			SND()->Test ();

			//BGM
			SND_STOP_ALL_BGM ();
			SND_PLAY_LOOP_BGM ( BGM_Title );
		}

		m_tmr_title_call->Move ();
		if ( m_tmr_title_call->IsLast () )
		{
			int rnd = s3d::Random ( 0, 2 );
			switch ( rnd )
			{
			case 0: SND_PLAY_ONESHOT_VC ( VC_00_SAE_TITLE_CALL ); break;
			case 1: SND_PLAY_ONESHOT_VC ( VC_01_RETSUDOU_TITLE_CALL ); break;
			case 2: SND_PLAY_ONESHOT_VC ( VC_02_OUKA_TITLE_CALL ); break;
			}
		}

		//背景スクロール
		m_bg_x += BG_VX;
		if ( m_bg_x < BG_P ) { m_bg_x = BG_X; }
		m_bg->SetPos ( m_bg_x, BG_Y );

		//カーソル回転
		m_cursor_scaling_y += m_cursor_scaling_vy;
		if ( m_cursor_scaling_y >=  1.f ) { m_cursor_scaling_vy = - 0.1f; }
		if ( m_cursor_scaling_y <= -1.f ) { m_cursor_scaling_vy =   0.1f; }
		m_cursor->SetScaling ( 1.f, m_cursor_scaling_y );

		//フェード中は入力を受付しない
		if ( m_fade_in->IsActive () ) { Scene::Move (); return; }
		if ( m_fade_out->IsActive () ) { Scene::Move (); return; }


		//デモモードは切換のみしか入力を受け付けない
		if ( ! m_bDemo )
		{
			//入力
			Input ();
		}

		Scene::Move ();
	}

	P_GameScene Title::Transit ()
	{
		//-----------------------------------
		//デモ フェード待機開始
		if ( m_fade_demo->IsLast () )
		{
			//ゲーム共通パラメータ
			P_Param pParam = Scene::GetpParam ();

			SND_STOP_ALL_BGM ();
			Scene::Transit_Fighting ( MUTCH_MODE::MODE_CPU_CPU );
		}

		//-----------------------------------
		//フェード待機開始
		if ( m_fade_out->IsLast () )
		{
			++ m_plus_wait;
		}

		//フェード待機後、遷移
		if ( m_plus_wait > 0 )
		{
			if ( m_plus_wait > FADE_OUT_T - 1 )
			{
				//ゲーム共通パラメータ
				P_Param pParam = Scene::GetpParam ();

				switch ( m_to )
				{
				case TITLE_TO_BATTLE_1PvsCPU:
					SND_STOP_ALL_BGM ();
					pParam->SetMutchMode ( MUTCH_MODE::MODE_PLAYER_CPU );
					pParam->SetGameMode ( GAME_MODE::MODE_MAIN );
					Scene::Transit_CharaSele ();
					break;
				case TITLE_TO_BATTLE_1Pvs2P:
					SND_STOP_ALL_BGM ();
					pParam->SetMutchMode ( MUTCH_MODE::MODE_PLAYER_PLAYER );
					pParam->SetGameMode ( GAME_MODE::MODE_MAIN );
					Scene::Transit_CharaSele ();
					break;
				case TITLE_TO_BATTLE_CPUvsCPU:
					SND_STOP_ALL_BGM ();
					pParam->SetMutchMode ( MUTCH_MODE::MODE_CPU_CPU );
					pParam->SetGameMode ( GAME_MODE::MODE_MAIN );
					Scene::Transit_CharaSele ();
					break;
#if 0
				case TITLE_TO_BATTLE:
					SND_STOP_ALL_BGM ();
					pParam->SetMutchMode ( MUTCH_MODE::MODE_PLAYER_CPU );
					pParam->SetGameMode ( GAME_MODE::MODE_MAIN );
					Scene::Transit_CharaSele ();
					break;
#endif // 0
				case TITLE_TO_TRAINING:
					SND_STOP_ALL_BGM ();
					pParam->SetMutchMode ( MUTCH_MODE::MODE_PLAYER_PLAYER );
					pParam->SetGameMode ( GAME_MODE::MODE_TRAINING );
					Scene::Transit_CharaSele ();
//					Scene::Transit_Training ();
					break;
				}

				m_plus_wait = 0;
			}

			++ m_plus_wait;
		}


		return Scene::Transit ();
	}


	void Title::Input ()
	{
		//----------------------------
		//	キー上下でシーンを選択
		//----------------------------

		//キー上
		if ( CFG_PUSH_KEY ( P1_UP ) || CFG_PUSH_KEY ( P2_UP ) )
		{
			switch ( m_to )
			{
			case TITLE_TO_BATTLE_1PvsCPU:
				m_to = TITLE_TO_TRAINING;
				break;
			case TITLE_TO_BATTLE_1Pvs2P:
				m_to = TITLE_TO_BATTLE_1PvsCPU;
				break;
			case TITLE_TO_BATTLE_CPUvsCPU:
				m_to = TITLE_TO_BATTLE_1Pvs2P;
				break;
			case TITLE_TO_TRAINING:
				m_to = TITLE_TO_BATTLE_CPUvsCPU;
				break;
			}

			SND_PLAY_ONESHOT_SE ( SE_select_move );
		}

		//キー下
		if ( CFG_PUSH_KEY ( P1_DOWN ) || CFG_PUSH_KEY ( P2_DOWN ) )
		{
			switch ( m_to )
			{
			case TITLE_TO_BATTLE_1PvsCPU:
				m_to = TITLE_TO_BATTLE_1Pvs2P;
				break;
			case TITLE_TO_BATTLE_1Pvs2P:
				m_to = TITLE_TO_BATTLE_CPUvsCPU;
				break;
			case TITLE_TO_BATTLE_CPUvsCPU:
				m_to = TITLE_TO_TRAINING;
				break;
			case TITLE_TO_TRAINING:
				m_to = TITLE_TO_BATTLE_1PvsCPU;
				break;
			}

			SND_PLAY_ONESHOT_SE ( SE_select_move );
		}

		//カーソル位置更新
		m_cursor->SetPos ( CURSOR_X, CURSOR_Y + CURSOR_P * (int32)m_to );


		//キー1でシーンを進める
		if ( CFG_PUSH_KEY ( P1_BTN0 ) || CFG_PUSH_KEY ( P2_BTN0 ) )
		{
			SND_PLAY_ONESHOT_SE ( SE_select_decide );

			//フェード開始
			m_fade_out->StartBlackOut ( FADE_OUT_T );
		}
#if 0
		if ( CFG_PUSH_KEY ( P1_BTN3 ) )
		{
			//BGM
			SND_STOP_ALL_BGM ();
			SND_PLAY_LOOP_BGM ( BGM_Title );
		}
#endif // 0

	}


	//----------------------------------------------------
	//デモ
	void Title::ValidDemo ( bool b )
	{
		if ( b ) { OnDemo (); }
		else { OffDemo (); }
	}

	void Title::OnDemo ()
	{
		m_strDemo->SetValid ( T );
		m_barDemo->SetValid ( T );
		m_strDemoSwitch->SetValid ( T );

		//通常選択肢はOff
		m_menu_1PvsCPU->SetValid ( F );
		m_menu_1Pvs2P->SetValid ( F );
		m_menu_CPUvsCPU->SetValid ( F );
		m_menu_Training->SetValid ( F );
		m_cursor->SetValid ( F );
	}

	void Title::OffDemo ()
	{
		m_strDemo->SetValid ( F );
		m_barDemo->SetValid ( F );
		m_strDemoSwitch->SetValid ( F );

		//通常選択肢はOn
		m_menu_1PvsCPU->SetValid ( T );
		m_menu_1Pvs2P->SetValid ( T );
		m_menu_CPUvsCPU->SetValid ( T );
		m_menu_Training->SetValid ( T );
		m_cursor->SetValid ( T );
	}


	//各種ランダム選択

	CHARA_NAME Title::GetCharaName_Rnd ()
	{
		CHARA_NAME ret = CHARA_NAME::CHARA_SAE;

		int rnd = s3d::Random ( 2 );
		switch ( rnd )
		{
		case 0: ret = CHARA_NAME::CHARA_SAE;		break;
		case 1: ret = CHARA_NAME::CHARA_RETSUDOU;	break;
		case 2: ret = CHARA_NAME::CHARA_OUKA;		break;
		};

		return ret;
	}

	STAGE_NAME Title::GetStageName_Rnd ()
	{
		STAGE_NAME ret = STAGE_YUUHINO_HARA;

		int rnd = s3d::Random ( 3 );
		switch ( rnd )
		{
		case 0: ret = STAGE_ASAHINO_HARA; break;
		case 1: ret = STAGE_YUUHINO_HARA; break;
		case 2: ret = STAGE_YORUNO_HARA; break;
		case 3: ret = STAGE_SCHOOL_NOON; break;
		}

		return ret;
	}

	BGM_ID Title::GetBGM_ID_Rnd ()
	{
		BGM_ID ret = BGM_ID_GABA;

		int rnd = s3d::Random ( 3 );
		switch ( rnd )
		{
		case 0: ret = BGM_ID_GABA;	break;
		case 1: ret = BGM_ID_OUKA;	break;
		case 2: ret = BGM_ID_SAE;	break;
		case 3: ret = BGM_ID_RETSU;	break;
		};

		return ret;
	}


}	//namespace GAME

