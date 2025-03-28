﻿//=================================================================================================
//
//	Fighting デモState
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "FtgDemo_State.h"
#include "../../GameMain/SoundConst.h"
#include "FtgDemo_Actor.h"
#include "../../GameMain/G_Ftg.h"
#include "Fighting.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//=====================================================
	//デモ表示　グラフィック基準のオブジェクト生成
	P_GrpDemo FtgDemoState::MakeGrpValue ( s3d::String txName )
	{
		P_GrpDemo pGrp = std::make_shared < GrpDemo > ();
		pGrp->AddTexture_FromArchive ( txName );
		pGrp->SetPos ( VEC2 ( 128, 400 ) );
		//@info		GrpDemoのScalingCenterはテクスチャの中心になる
//		pGrp->SetScalingCenter ( VEC2 ( 512, 128 ) );
		pGrp->SetStartScaling ( VEC2 ( 1.3f, 1.3f ) );
		pGrp->SetSecondVel ( VEC2 ( -0.001f, -0.001f ) );
		pGrp->SetZ ( Z_SYS );	//@info SetZはGRPLST_INSERT()の後では行わない(リストが崩れる)
		pGrp->SetValid ( F );

		AddpTask ( pGrp );
		GRPLST_INSERT ( pGrp );
		return pGrp;
	}
	//=====================================================


	//------------------------------------------------
	//開幕挨拶
	FTG_DM_Greeting::FTG_DM_Greeting ()
	{
		m_timer = std::make_shared < Timer > ();
		m_timer->SetTargetTime ( 180 );
	}

	void FTG_DM_Greeting::Start ()
	{
		m_timer->Start ();
		GetpMutualChara ()->StartGreeting ();
	}

	void FTG_DM_Greeting::Do ()
	{
		m_timer->Move ();
		if ( m_timer->IsLast () )
		{
			GetwpFtgDemoActor ().lock ()->Change_Greeting_To_GetReady ();
		}

		//キャラ共通一連動作
		GetpMutualChara()->Conduct_InDemo ();
	}

	//------------------------------------------------
	//準備

	const UINT FTG_DM_GetReady::COUNT = 90;
	const UINT FTG_DM_GetReady::COUNT_D = 60 - COUNT % 60;

	FTG_DM_GetReady::FTG_DM_GetReady ()
	{
		m_grpGetReady = MakeGrpValue ( U"Demo_GetReady.png" );
		m_grpGetReady->SetEnd ( COUNT );


		m_timer = std::make_shared < Timer > ();
	}

	void FTG_DM_GetReady::Start ()
	{
		GetpMutualChara ()->StartGetReady ();

		//-------------------------------------------
//		P_Param pParam = Scene::GetpParam ();
		P_Param pParam =  m_prmFtgDemo->GetpSceneParam();
		GameSettingFile stg = pParam->GetGameSetting ();


		//BGM開始

		//パラメータから取得
		BGM_ID bgm_id = pParam->Get_BGM_ID ();

		//保存IDとゲーム管理IDは異なるので名前で検索
		BGM_NAME bgm_name = BGM_ID_TO_NAME [ bgm_id ];

		//すでに再生中でなければ再生
		if ( ! SND()->IsPlayBGM( bgm_name ) )
		{
			//全停止から再生
			SND_STOP_ALL_BGM ();
			SND_PLAY_LOOP_BGM ( bgm_name );
		}


		m_grpGetReady->Start ();
		m_timer->Start ();
	}

	void FTG_DM_GetReady::Final ()
	{
	}

	void FTG_DM_GetReady::Do ()
	{
		m_timer->Move ();

		if ( ! m_grpGetReady->GetValid () )
		{
			GetwpFtgDemoActor ().lock ()->Change_GetReady_To_Main ();
		}

		//キャラ共通一連動作
		GetpMutualChara()->Conduct_InDemo ();
	}

	//------------------------------------------------
	//メイン
	FTG_DM_Main::FTG_DM_Main ()
	{
		m_grpAttack = MakeGrpValue ( U"Demo_Fight.png" );
		m_grpAttack->SetEnd ( 90 );
	}


	void FTG_DM_Main::Start ()
	{
		//Fight! 表示
		m_grpAttack->Start ();

		//戦闘開始
		GetpMutualChara ()->StartFighting ();

		//時間計測開始
		GetwpFighting().lock()->StartTime ();
	}

	void FTG_DM_Main::Do ()
	{
		m_grpAttack->Move ();

		P_MutualChara pMutual = GetpMutualChara ();


		//一時停止
		if ( GetpFtgGrp()->IsStart_ScpStop () )
		{
			pMutual->ShiftScpStop ();
		}
		//最終時に通常状態に戻す
		if ( GetpFtgGrp()->IsLast_ScpStop () )
		{
			GetpFtgGrp()->ClearTmr_ScpStop ();
			pMutual->ShiftFightingMain ();
		}


		//[一時] 壁割
		bool bOnWallBreak = GetpFtgGrp()->GetWallBreak ();
		if ( bOnWallBreak )
		{
			GetwpFtgDemoActor().lock()->Shift_Main_To_WallBreak ();
		}

		//終了判定
		P_FTG pFtg = GetwpFighting().lock();

		// 格闘終了判定
		if ( pFtg->FinishCheck_ZeroLife () )
		{
			//トレーニングモードは終了しない
			if ( pFtg->GetbTraining () )
			{
				//リスタートもしないので戻るときは手動でリセット
				//pFtg->TrainingRestart ();	//リスタート
			}
			else
			{
				//ダウン状態に移行
				GetwpFtgDemoActor ().lock ()->Change_Main_To_Down ();
			}
		}

		// タイムアップ判定
		if ( pFtg->FinishCheck_TimeUp () )
		{
			GetwpFtgDemoActor ().lock ()->Change_Main_To_TimeUpWait ();
		}

		//キャラ共通一連動作
		pMutual->Conduct ();
	}

	void FTG_DM_Main::Final ()
	{
		//枠リセット
//		GetpMutualChara()->ResetRect ();

		//戦闘終了
		GetpMutualChara()->EndBattle ();
	}

	//------------------------------------------------
	//特殊演出 (一時停止)
	void FTG_DM_ScpStop::Start ()
	{
	}

	void FTG_DM_ScpStop::Do ()
	{
		//キャラ共通一連動作
		GetpMutualChara()->Conduct_InStop ();
	}

	//------------------------------------------------
	//特殊演出：壁割り
	FTG_DM_WallBreak::FTG_DM_WallBreak ()
	{
		m_wallBreakEf = std::make_shared < WallBreak > ();
		AddpTask ( m_wallBreakEf );
		m_timer = std::make_shared < Timer > ( 60 );
	}

	void FTG_DM_WallBreak::Start ()
	{
		//壁割エフェクト位置
		float wall_R = G_Ftg::inst()->GetWallRight ();
		m_wallBreakEf->SetPos ( wall_R - (float)GAME_WIDTH_HALF );
		m_wallBreakEf->On ();

		//タイマスタート
		m_timer->Start ();

		//最初の１回目で条件をオフにしておく
		m_prmFtgDemo->GetpFtgGrp()->SetWallBreak ( F );
	}

	void FTG_DM_WallBreak::Do ()
	{
		m_timer->Move ();

		//終了
		if ( m_timer->IsLast() )
		{
			m_wallBreakEf->Off ();

			//壁位置をリセット
			G_Ftg::inst()->ResetWall ();

			//通常状態へ移行
			PLAYER_ID WB_Player = m_prmFtgDemo->GetpFtgGrp()->GetWB_Player ();
			GetpMutualChara()->WallBreak_Action ( WB_Player );
			GetpMutualChara()->ShiftFightingMain ();
			GetwpFtgDemoActor().lock()->Shift_WallBreak_To_Main();
		}

		//キャラ共通一連動作
		GetpMutualChara ()->Conduct_InStop ();
	}

	//------------------------------------------------
	//敗北ダウン
	FTG_DM_Down::FTG_DM_Down ()
	{
		m_grpDown = MakeGrpValue ( U"Demo_Down.png" );
		m_grpDown->SetPos ( VEC2 ( ( WINDOW_WIDTH - 617 ) * 0.5f, 400.f ) );
		m_grpDown->SetEnd ( 120 );


		m_grp_Ketsu = std::make_shared < GrpDemo > ();
		m_grp_Ketsu->AddTexture_FromArchive ( U"decision_ketsu.png" );
		m_grp_Ketsu->SetPos ( VEC2 ( 200, 150 ) );
		m_grp_Ketsu->SetZ ( Z_SYS );	//@info SetZはGRPLST_INSERT()の後では行わない(リストが崩れる)
		m_grp_Ketsu->SetStartScaling ( VEC2 ( 8.f, 8.f ) );
		m_grp_Ketsu->SetTargetScaling ( VEC2 ( 1.5f, 1.5f ) );
		m_grp_Ketsu->SetSecondVel ( VEC2 ( -0.001f, -0.001f ) );
		m_grp_Ketsu->SetValid ( F );
		m_grp_Ketsu->SetEnd ( 120 );
		AddpTask ( m_grp_Ketsu );
		GRPLST_INSERT ( m_grp_Ketsu );

		m_grp_chaku = std::make_shared < GrpDemo > ();
		m_grp_chaku->AddTexture_FromArchive ( U"decision_chaku.png" );
		m_grp_chaku->SetPos ( VEC2 ( 800, 600 ) );
		m_grp_chaku->SetZ ( Z_SYS );	//@info SetZはGRPLST_INSERT()の後では行わない(リストが崩れる)
		m_grp_chaku->SetStartScaling ( VEC2 ( 8.f, 8.f ) );
		m_grp_chaku->SetTargetScaling ( VEC2 ( 1.5f, 1.5f ) );
		m_grp_chaku->SetSecondVel ( VEC2 ( -0.001f, -0.001f ) );
		m_grp_chaku->SetValid ( F );
		m_grp_chaku->SetEnd ( 120 );
		AddpTask ( m_grp_chaku );
		GRPLST_INSERT ( m_grp_chaku );

		m_grpLight0 = std::make_shared < GrpDemo > ();
		m_grpLight0->AddTexture_FromArchive ( U"decision_light0.png" );
		m_grpLight0->SetShader ( T );
		m_grpLight0->SetPos ( VEC2 ( 800, 480 ) );
		m_grpLight0->SetZ ( Z_SYS );	//@info SetZはGRPLST_INSERT()の後では行わない(リストが崩れる)
		m_grpLight0->SetStartScaling ( VEC2 ( 2.f, 2.f ) );
		m_grpLight0->SetVel ( VEC2 ( 0.f, 0.f ) );
		m_grpLight0->SetAcc ( VEC2 ( 0.1f, 0.f ) );
		m_grpLight0->SetTargetScaling ( VEC2 ( 10.f, 2.f ) );
		m_grpLight0->SetSecondVel ( VEC2 ( 0.f, 0.f ) );
		m_grpLight0->SetValid ( F );
		m_grpLight0->SetEnd ( 120 );
		AddpTask ( m_grpLight0 );
		GRPLST_INSERT ( m_grpLight0 );


		m_timer = std::make_shared < Timer > ( 120 );
	}

	void FTG_DM_Down::Start ()
	{
		//勝者側を待機状態にする	 / 敗者側をダウンにする
		GetpMutualChara ()->StartEndWait ();

		//戦闘時間を停止
		GetwpFighting().lock()->StopTimer ();

		//Demo
		m_grpDown->Start ();
		m_grp_Ketsu->Start ();
		m_grp_chaku->Start ();
		m_grpLight0->Start ();
	}

	void FTG_DM_Down::Do ()
	{
		//タイマ
		m_timer->Move ();

		//タイマ稼働時
		if ( m_timer->IsActive () )
		{
			//タイマ終了時
			if ( m_timer->IsLast () )
			{
				//表示消し
				m_grpDown->SetValid ( F );

				m_timer->Clear ();

				//ダウンから勝者表示へ
				GetwpFtgDemoActor ().lock ()->Change_Down_To_Winner ();
			}
		}
		else //非稼働時
		{
			//キャラステートが敗北ダウン持続に入ったらタイマスタート
			if ( GetpMutualChara ()->IsDown_Calm () )
			{
				m_timer->Start ();
			}
		}

		//キャラ共通一連動作
		GetpMutualChara ()->Conduct_InDemo ();
	}


	//------------------------------------------------
	//タイムアップ 待機
	FTG_DM_TimeUpWait::FTG_DM_TimeUpWait ()
	{
		m_grpTimeUp = MakeGrpValue ( U"Demo_TimeUp.png" );
		m_grpTimeUp->SetPos ( VEC2 ( ( WINDOW_WIDTH - 1024 ) * 0.5f, 400.f ) );
		m_grpTimeUp->SetValid ( F );
		m_grpTimeUp->SetEnd ( 120 );
	}

	void FTG_DM_TimeUpWait::Start ()
	{
		m_grpTimeUp->Start ();
		GetwpFighting().lock()->StartEndWait ();
	}

	void FTG_DM_TimeUpWait::Do ()
	{
		bool bWait = GetpMutualChara ()->IsWait ();
		bool bDispOff = ! m_grpTimeUp->GetValid ();

		//両者待機状態かつ表示終了時
		if ( bWait && bDispOff )
		{
			//タイムアップ
			GetwpFtgDemoActor ().lock ()->Change_Main_To_TimeUp ();
		}

		//キャラ共通一連動作
		GetpMutualChara ()->Conduct_InDemo ();
	}

	//------------------------------------------------
	//タイムアップ
	FTG_DM_TimeUp::FTG_DM_TimeUp ()
	{
		m_timer = std::make_shared < Timer > ( 120 );
		AddpTask ( m_timer );
	}

	void FTG_DM_TimeUp::Start ()
	{
		m_timer->Start ();
		GetwpFighting().lock()->StartTimeUp ();
	}

	void FTG_DM_TimeUp::Do ()
	{
		//一定時間で次へ
		if ( m_timer->IsLast () )
		{
			GetwpFtgDemoActor ().lock ()->Change_TimeUp_To_Winner ();
		}

		//キャラ共通一連動作
		GetpMutualChara ()->Conduct_InDemo ();
	}


	//------------------------------------------------
	//勝者表示
	FTG_DM_Winner::FTG_DM_Winner ()
	{
		m_dispTimer = std::make_shared < Timer > ( 240 );
		AddpTask ( m_dispTimer );

		m_grpWinner = std::make_shared < GrpDemo > ();
		m_grpWinner ->AddTexture_FromArchive ( U"Demo_Winner.png" );
		m_grpWinner->SetPos ( VEC2 ( 1.f * 1280 / 2 - 1024 / 2, 200.f ) );
		m_grpWinner->SetEnd ( 240 );
		m_grpWinner->SetValid ( F );
		AddpTask ( m_grpWinner );
		GRPLST_INSERT ( m_grpWinner );

		m_grp1p = std::make_shared < GrpDemo > ();
		m_grp1p ->AddTexture_FromArchive ( U"Demo_1P.png" );
		m_grp1p->SetPos ( VEC2 ( 1.f * 1280 / 2 - 256 / 2, 400.f ) );
		m_grp1p->SetEnd ( 240 );
		m_grp1p->SetValid ( F );
		AddpTask ( m_grp1p );
		GRPLST_INSERT ( m_grp1p );

		m_grp2p = std::make_shared < GrpDemo > ();
		m_grp2p ->AddTexture_FromArchive ( U"Demo_2P.png" );
//		m_grp2p->SetScalingCenter ( VEC2 ( 128, 128 ) );
		m_grp2p->SetPos ( VEC2 ( 1.f * 1280 / 2 - 256 / 2, 400.f ) );
		m_grp2p->SetEnd ( 240 );
		m_grp2p->SetValid ( F );
		AddpTask ( m_grp2p );
		GRPLST_INSERT ( m_grp2p );

		m_grpDraw = MakeGrpValue ( U"Demo_Draw.png" );
//		m_grpDraw->SetScalingCenter ( VEC2 ( 256, 256 ) );
		m_grpDraw->SetPos ( VEC2 ( 1.f * 1280 / 2 - 512 / 2, 300.f ) );
		m_grpDraw->SetEnd ( 240 );

		m_fade = std::make_shared < FadeRect > ();
		m_fade->SetTime ( 8 );
		AddpTask ( m_fade );
		GRPLST_INSERT ( m_fade );
	}

	void FTG_DM_Winner::Start ()
	{
		m_dispTimer->Start ();

		//キャラ
		GetpMutualChara ()->StartWinner ( );
//		GetwpFighting().lock()->WinnerDemo ();


		//勝者表示
		P_Param p = m_prmFtgDemo->GetpSceneParam ();
		switch ( p->GetWinner () )
		{
		case PLAYER_ID_1:
			m_grpWinner->Start ();
			m_grp1p->Start ();
			GetwpFighting().lock()->AddRound_1p ();
			break;

		case PLAYER_ID_2:
			m_grpWinner->Start ();
			m_grp2p->Start ();
			GetwpFighting().lock()->AddRound_2p ();
			break;

		case _PLAYER_NUM:
			m_grpDraw->Start ();
			break;

		default: break;
		}
	}

	void FTG_DM_Winner::Do ()
	{
		//フェード開始
		if ( m_dispTimer->IsLast () )
		{
			m_fade->Start ();
		}

		//一定時間で次へ
		if ( m_fade->IsActive () )
		{
			if ( m_fade->IsLast () )
			{
				//目標ラウンド取得なら
				bool b = GetwpFighting().lock()->IsEndMutch ();
				if ( b )
				{
					//各種終了
					m_fade->Off ();
					SND_STOP_ALL_BGM ();

					//リザルトへ移行
					GetwpFtgDemoActor().lock ()->End_Down_To_Result ();
				}
				else
				{
					m_fade->Off ();

					//初期化
					GetwpFighting().lock()->Init();

					//準備から開始
					GetwpFtgDemoActor ().lock ()->Change_Winner_To_GetReady ();
				}
			}
		}

		//キャラ共通一連動作
		GetpMutualChara ()->Conduct_InDemo ();
	}


}	//namespace GAME

