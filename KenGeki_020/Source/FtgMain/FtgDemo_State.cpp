//=================================================================================================
//
//	Fighting デモState
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "FtgDemo_State.h"
#include "../GameMain/SoundConst.h"
#include "FtgDemo_Actor.h"
#include "../GameMain/G_Ftg.h"


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
		pGrp->SetScalingCenter ( VEC2 ( 512, 128 ) );
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
		m_timer->SetTargetTime ( 120 );
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
			GetwpFtgDemoActor ().lock ()->Change_GetReady_To_Attack ();
		}
	}

	//------------------------------------------------
	//開始
	FTG_DM_Attack::FTG_DM_Attack ()
	{
		m_grpAttack = MakeGrpValue ( U"Demo_Fight.png" );
		m_grpAttack->SetEnd ( 90 );
	}

	void FTG_DM_Attack::Start ()
	{
		m_grpAttack->Start ();
		GetpMutualChara()->StartTime ();
	}

	void FTG_DM_Attack::Do ()
	{
		m_grpAttack->Move ();
	}

	//------------------------------------------------
	//メイン
	void FTG_DM_Main::Start ()
	{
		//戦闘開始
		GetpMutualChara ()->StartFighting ();

		//時間計測開始
		GetpMutualChara()->StartTime ();

	}

	void FTG_DM_Main::Do ()
	{
		//[一時] 壁割
		bool bOnWallBreak = m_prmFtgDemo->GetpFtgGrp ()->GetWallBreak ();
		if ( bOnWallBreak )
		{
			GetwpFtgDemoActor().lock()->Shift_Main_To_WallBreak ();
		}
		
		// 格闘終了判定
		if ( GetpMutualChara()->FinishCheck_ZeroLife () )
		{
			//GetpMutualChara ()->Stop ( true );
			//GetpMutualChara ()->SetEndWait ();
			GetwpFtgDemoActor ().lock ()->Change_Main_To_Down ();
		}

		// タイムアップ判定
		if ( GetpMutualChara()->FinishCheck_TimeUp () )
		{
			GetwpFtgDemoActor ().lock ()->Change_Main_To_TimeUpWait ();
		}
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
			GetpMutualChara()->Shift_Fighting ();
			GetwpFtgDemoActor().lock()->Shift_WallBreak_To_Main();
		}
	}

	//------------------------------------------------
	//ダウン
	FTG_DM_Down::FTG_DM_Down ()
	{
		m_grpDown = MakeGrpValue ( U"Demo_Down.png" );
		m_grpDown->SetEnd ( 120 );
	}

	void FTG_DM_Down::Start ()
	{
		m_grpDown->Start ();
	}

	void FTG_DM_Down::Do ()
	{
		if ( ! m_grpDown->GetValid () )
		{
			//新規開始
			GetpMutualChara ()->StartFighting ();
			GetwpFtgDemoActor ().lock ()->Change_Down_To_Greeting ();
#if 0
			//タイトルに戻る
			GetwpFtgDemoActor ().lock ()->End_Down_To_Result ();
#endif // 0
		}
	}


	//------------------------------------------------
	//タイムアップ 待機
	FTG_DM_TimeUpWait::FTG_DM_TimeUpWait ()
	{
		m_grpTimeUp = MakeGrpValue ( U"Demo_TimeUp.png" );
		m_grpTimeUp->SetEnd ( 120 );
	}

	void FTG_DM_TimeUpWait::Start ()
	{
		m_grpTimeUp->Start ();
		GetpMutualChara ()->StartEndWait ();
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
		GetpMutualChara ()->StartTimeUp ();
	}

	void FTG_DM_TimeUp::Do ()
	{
		//一定時間で次へ
		if ( m_timer->IsLast () )
		{
			GetwpFtgDemoActor ().lock ()->Change_TimeUp_To_Winner ();
		}
	}


	//------------------------------------------------
	//勝者表示
	FTG_DM_Winner::FTG_DM_Winner ()
	{
		m_dispTimer = std::make_shared < Timer > ( 240 );
		AddpTask ( m_dispTimer );

		m_grpWinner = std::make_shared < GrpDemo > ();
		m_grpWinner ->AddTexture ( U"Demo_Winner.png" );
		m_grpWinner->SetScalingCenter ( VEC2 ( 512, 128 ) );
		m_grpWinner->SetPos ( VEC2 ( 1.f * 1280 / 2 - 1024 / 2, 200.f ) );
		m_grpWinner->SetEnd ( 240 );
		m_grpWinner->SetValid ( F );
		AddpTask ( m_grpWinner );
		GRPLST_INSERT ( m_grpWinner );

		m_grp1p = std::make_shared < GrpDemo > ();
		m_grp1p ->AddTexture ( U"Demo_1P.png" );
		m_grp1p->SetScalingCenter ( VEC2 ( 128, 128 ) );
		m_grp1p->SetPos ( VEC2 ( 1.f * 1280 / 2 - 256 / 2, 400.f ) );
		m_grp1p->SetEnd ( 240 );
		m_grp1p->SetValid ( F );
		AddpTask ( m_grp1p );
		GRPLST_INSERT ( m_grp1p );

		m_grp2p = std::make_shared < GrpDemo > ();
		m_grp2p ->AddTexture ( U"Demo_2P.png" );
		m_grp2p->SetScalingCenter ( VEC2 ( 128, 128 ) );
		m_grp2p->SetPos ( VEC2 ( 1.f * 1280 / 2 - 256 / 2, 400.f ) );
		m_grp2p->SetEnd ( 240 );
		m_grp2p->SetValid ( F );
		AddpTask ( m_grp2p );
		GRPLST_INSERT ( m_grp2p );

		m_grpDraw = MakeGrpValue ( U"Demo_Draw.png" );
		m_grpDraw->SetScalingCenter ( VEC2 ( 256, 256 ) );
		m_grpDraw->SetPos ( VEC2 ( 1.f * 1280 / 2 - 512 / 2, 300.f ) );
		m_grpDraw->SetEnd ( 240 );

		m_fade = std::make_shared < FadeRect > ();
		m_fade->SetTime ( 16 );
		AddpTask ( m_fade );
		GRPLST_INSERT ( m_fade );
	}

	void FTG_DM_Winner::Start ()
	{
		m_dispTimer->Start ();

		//勝者表示
		P_Param p = m_prmFtgDemo->GetpSceneParam ();
		switch ( p->GetWinner () )
		{
		case PLAYER_ID_1:
			m_grpWinner->Start ();
			m_grp1p->Start (); break;

		case PLAYER_ID_2:
			m_grpWinner->Start ();
			m_grp2p->Start (); break;

		case _PLAYER_NUM:
			m_grpDraw->Start (); break;

		default: break;
		}
	}

	void FTG_DM_Winner::Do ()
	{
		//一定時間で次へ
		if ( m_dispTimer->IsLast () )
		{
			m_fade->Start ();
		}

		//フェード開始
		if ( m_fade->IsActive () )
		{
			if ( m_fade->IsLast () )
			{
				bool b = GetpMutualChara ()->IsEndMutch ();
				if ( b )
				{
					GetwpFtgDemoActor().lock ()->End_Down_To_Result ();
				}
				else
				{
					GetwpFtgDemoActor ().lock ()->Change_Down_To_Greeting ();
				}
			}
		}
	}


}	//namespace GAME

