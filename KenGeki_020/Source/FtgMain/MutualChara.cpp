//=================================================================================================
//
//	MutualChara ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "MutualChara.h"
//#include "../GameMain/SoundConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	MutualChara::MutualChara ()
	{
		//判定 キャラに譲渡するためオブジェクトのみ先に確保
		m_decision = std::make_shared < Decision > ();

		//キャラ
		m_exeChara1 = std::make_shared < ExeChara > ( PLAYER_ID_1 );
		m_exeChara2 = std::make_shared < ExeChara > ( PLAYER_ID_2 );

		m_exeChara1->SetpOther ( m_exeChara2 );
		m_exeChara2->SetpOther ( m_exeChara1 );

#if 0
		m_exeChara1->SetpParticle ( m_decision->GetpEfPart () );
		m_exeChara2->SetpParticle ( m_decision->GetpEfPart () );
#endif // 0

		AddpTask ( m_exeChara1 );
		AddpTask ( m_exeChara2 );

		//判定
		m_collision = std::make_shared < Collision > ();
		m_collision->SetpChara ( m_exeChara1, m_exeChara2 );
		AddpTask ( m_collision );

		m_decision->SetpChara ( m_exeChara1, m_exeChara2 );
		AddpTask ( m_decision );

		//------------------------------------------------
		//タイム
		m_btlTime = std::make_shared < BattleTime > ();
		AddpTask ( m_btlTime );

		//------------------------------------------------
		//ラウンド
		m_round = std::make_shared < Round > ();
		AddpTask ( m_round );


		//------------------------------------------------
		//デバッグ用枠表示初期切替
#define DISP_RECT	0
#if DISP_RECT
		bDispRect = T;
		m_exeChara1->OnDispRect ();
		m_exeChara2->OnDispRect ();
#else
		m_exeChara1->OffDispRect ();
		m_exeChara2->OffDispRect ();
#endif // DISP_RECT
	}

	MutualChara::~MutualChara ()
	{
	}


	void MutualChara::ParamInit ( P_Param pParam )
	{
		m_pParam = pParam;
		m_exeChara1->ParamInit ( pParam );
		m_exeChara2->ParamInit ( pParam );
	}

	void MutualChara::Load ()
	{
		m_exeChara1->SetpFtgGrp ( m_pFtgGrp );
		m_exeChara2->SetpFtgGrp ( m_pFtgGrp );
		TASK_VEC::Load ();
	}

	void MutualChara::Init ()
	{
		m_pParam->SetN_Act1p ( 0 );
		m_pParam->SetN_Act2p ( 0 );
		TASK_VEC::Init ();
	}



	//■#########################################################
	//■
	//■	スクリプトの毎フレーム処理
	//■
	//■#########################################################
	void MutualChara::Conduct ()
	{
		//---------------------------------------------------
		//システム変更
		SwitchDispInput ();	//入力表示切替
		SwitchRect ();	//枠表示切替
		SwitchFrontEnd ();	//ゲージ類表示切替
#if 0
		ResetMatch ();	//試合初期化
		SwithcCPU ();	//CPU操作切替
		//---------------------------------------------------
#endif // 0

		//◆スクリプト前処理(入力、移動など)
		m_exeChara1->PreScriptMove ();
		m_exeChara2->PreScriptMove ();

		//◆相互判定(ぶつかり枠)
		_Collision ();

		//◆ぶつかり後、攻撃・ヒット判定枠を設定
		m_exeChara1->RectMove ();
		m_exeChara2->RectMove ();

		//◆相互判定(攻撃・ヒット枠)
		_Decision ();

		//◆スクリプト後処理(グラフィック位置など)
		m_exeChara1->PostScriptMove ();
		m_exeChara2->PostScriptMove ();

		//グラフィック共通
		Grp ();

#if 0
		//シーン共通パラメータ記録
		m_pParam->SetN_Life1p ( m_exeChara1->GetLife () );
		m_pParam->SetN_Life2p ( m_exeChara2->GetLife () );
		m_pParam->SetN_Act1p ( m_exeChara1->GetBtlParam ().GetNActTrs () );
		m_pParam->SetN_Act2p ( m_exeChara2->GetBtlParam ().GetNActTrs () );

#endif // 0

		//test
		float x1 = m_exeChara1->GetPos ().x;
		float x2 = m_exeChara2->GetPos ().x;
		DBGOUT_WND()->DebugOutf ( U"{}, {}"_fmt( x1, x2 ) );
	}

#if 0
	//■#########################################################
	
	//一時停止時コンダクト
	void MutualChara::Conduct_InStop ()
	{
		//---------------------------------------------------
		//システム変更
		SwitchRect ();	//枠表示切替
		SwitchDispInput ();	//入力表示切替
		SwitchFrontEnd ();	//ゲージ類表示切替
		SwithcCPU ();	//CPU操作切替
		ResetMatch ();	//試合初期化
		//---------------------------------------------------

		//◆スクリプト前処理(入力、移動など)
		m_exeChara1->Input ();
		m_exeChara2->Input ();

		//◆画像の更新
		m_exeChara1->UpdateGraphic ();
		m_exeChara2->UpdateGraphic ();
	}

	//■#########################################################


#endif // 0

	//◆================================
	//◆		相互判定(ぶつかり枠)
	//◆================================
	void MutualChara::_Collision ()
	{
		m_collision->Do ();
	}

	//◆================================
	//◆		相互判定 (攻撃・ヒット枠)
	//◆================================
	void MutualChara::_Decision ()
	{
		m_decision->Do ();
	}


	//◆================================
	//◆		共通グラフィック
	//◆================================
	void MutualChara::Grp ()
	{
#if 0
		//---------------------------------------------------
		//暗転
		UINT bo1 = m_exeChara1->GetBlackOut ();
		UINT bo2 = m_exeChara2->GetBlackOut ();

		//どちらかが発生したとき
		if ( 0 < bo1 || 0 < bo2 )
		{
			//大きい方で上書
			m_blackOut = ( bo2 < bo1 ) ? bo1 : bo2;
			m_exeChara1->SetBlackOut ( 0 );
			m_exeChara2->SetBlackOut ( 0 );
		}

		//---------------------------------------------------
		//スクリプトからの停止
		UINT scpStop1P = m_exeChara1->GetScpStop ();
		UINT scpStop2P = m_exeChara2->GetScpStop ();
		if ( 0 < scpStop1P )
		{
			m_scpStop = scpStop1P;
			m_exeChara1->SetScpStop ( 0 );

			m_exeChara1->SetStopTimer ( m_scpStop );
			m_exeChara2->SetStopTimer ( m_scpStop );
		}

		//---------------------------------------------------
		//白転
		bool whiteOut1 = m_exeChara1->GetWhiteOut ();
		bool whiteOut2 = m_exeChara2->GetWhiteOut ();

		if ( whiteOut1 || whiteOut2 )
		{
			m_whiteOut = T;
			m_exeChara1->SetWhiteOut ( F );
			m_exeChara2->SetWhiteOut ( F );
		}

#endif // 0

		//---------------------------------------------------
		//キャラ位置から画面表示の基準位置(カメラ)を決定
		VEC2 pos1p = m_exeChara1->GetPos ();
		VEC2 pos2p = m_exeChara2->GetPos ();

		G_FTG()->CulcPosMutualBase ( pos1p, pos2p );

	}

#if 0


	//------------------------------------------------------
	//	終了判定
	//------------------------------------------------------
	bool MutualChara::CheckZeroLife ()
	{
		//終了判定
		bool finish1p = m_exeChara1->IsZeroLife ();
		bool finish2p = m_exeChara2->IsZeroLife ();

		//どちらか、または両方ライフ０なら終了
		if ( finish1p || finish2p )
		{
			PLAYER_ID plr = _PLAYER_NUM;
			if ( finish1p && finish2p )
			{
				plr = _PLAYER_NUM;
			}
			else if ( ! finish1p && finish2p )
			{
				plr = PLAYER_ID_1;
			}
			else if ( finish1p && ! finish2p )
			{
				plr = PLAYER_ID_2;
			}
			//シーン共通パラメータ記録
			m_pParam->SetWinner ( plr );
			return T;
		}

		return F;
	}

#if 0
	bool MutualChara::CheckDown ()
	{
		//ダウン判定
		bool down1p = m_exeChara1->IsDown ();
		bool down2p = m_exeChara2->IsDown ();
		return (down1p || down2p);
	}

	bool MutualChara::CheckDownEnd ()
	{
		//ダウン判定
		bool downEnd1p = m_exeChara1->IsDownEnd ();
		bool downEnd2p = m_exeChara2->IsDownEnd ();
		return (downEnd1p || downEnd2p);
	}

	bool MutualChara::CheckWin ()
	{
		//勝利状態判定
		bool win1p = m_exeChara1->IsWin ();
		bool win2p = m_exeChara2->IsWin ();
		return (win1p || win2p);
	}

	bool MutualChara::CheckWinEnd ()
	{
		//勝利状態判定
		bool winEnd1p = m_exeChara1->IsWinEnd ();
		bool winEnd2p = m_exeChara2->IsWinEnd ();
		return (winEnd1p || winEnd2p);
	}

	bool MutualChara::CheckWinner ()
	{
		bool bRet = false;

		//ライフで勝利者を決定する
		int life1p = m_exeChara1->GetLife ();
		int life2p = m_exeChara2->GetLife ();

		//Double K.O.
		if ( life1p <= 0 && life2p <= 0 ) { m_winner = WINNER_DP; }
		//2P Win
		else if ( life1p <= 0 ) { m_winner = WINNER_2P; }
		//1P Win
		else if ( life2p <= 0 ) { m_winner = WINNER_1P; }
		//Draw
		else if ( life1p == life2p ) { m_winner = WINNER_DRAW; }

		switch ( m_winner )
		{
		case WINNER_1P: 
			m_exeChara1->SetCharaState ( CHST_WIN_END );
			m_exeChara2->SetCharaState ( CHST_DOWN_END );
			break;
		case WINNER_2P: 
			m_exeChara1->SetCharaState ( CHST_DOWN_END );
			m_exeChara2->SetCharaState ( CHST_WIN_END );
			break;
		case WINNER_DP: break;
		default: break;
		}

		return bRet;
	}

	void MutualChara::ForcedEnd ()
	{
		m_exeChara1->ForcedEnd ();
		m_exeChara2->ForcedEnd ();
	}
#endif // 0


	CHARA_NAME MutualChara::GetWinnerName () const
	{
		switch ( m_winner )
		{
		case WINNER_1P: return m_exeChara1->GetCharaName (); break;
		case WINNER_2P: return m_exeChara2->GetCharaName (); break;
		case WINNER_DP: break;
		default: break;
		}
		return CHARA_NAME ();
	}

#endif // 0

	//------------------------------------------------------
	//	内部関数
	//------------------------------------------------------


	//------------------------------------------------------
	//入力表示切替
	void MutualChara::SwitchDispInput ()
	{
		static bool bDispInput = T;		//状態
		static bool pre_bDispInput = F;	//前回押しているか
		static bool is_bDispInput = F;	//今回押しているか

		is_bDispInput = ( WND_UTL::AscKey ( '2' ) );

		//今回押した瞬間ならば、1回のみ切替
		if ( ! pre_bDispInput && is_bDispInput )	// false -> true
		{
			if ( ! bDispInput )
			{
				m_exeChara1->OnDispInput ();
				m_exeChara2->OnDispInput ();
				bDispInput = true;
			}
			else
			{
				m_exeChara1->OffDispInput ();
				m_exeChara2->OffDispInput ();
				bDispInput = false;
			}
		}

		pre_bDispInput = is_bDispInput;
	}

	//------------------------------------------------------
	//枠表示切替 
	//@info ExeCharaで呼ぶと1P2Pで２回呼ばれてしまう
	void MutualChara::SwitchRect ()
	{
		static bool bDispRect = T;		//状態
		static bool pre_bDispRect = F;	//前回押しているか
		static bool is_bDispRect = F;	//今回押しているか

		is_bDispRect = ( WND_UTL::AscKey ( '1' ) );

		//@info キーボード入力は押しっぱなしで一定時間後連打状態になる
		//TRACE_F ( _T ( "b = %d, pre = %d, is = %d\n" ), bDispRect ? 1 : 0, pre_bDispRect ? 1 : 0, is_bDispRect ? 1 : 0  );

		//今回押した瞬間ならば、1回のみ切替
		if ( ! pre_bDispRect && is_bDispRect )	// false -> true
		{
			if ( ! bDispRect )
			{
				m_exeChara1->OnDispRect ();
				m_exeChara2->OnDispRect ();
				bDispRect = T;
			}
			else
			{
				m_exeChara1->OffDispRect ();
				m_exeChara2->OffDispRect ();
				bDispRect = F;
			}
		}
		pre_bDispRect = is_bDispRect;
	}

	//------------------------------------------------------
	//ゲージ類表示切替
	void MutualChara::SwitchFrontEnd ()
	{
		static bool bFrontEnd = T;		//状態
		static bool pre_bFrontEnd = F;	//前回押しているか
		static bool is_bFrontEnd = F;	//今回押しているか

		is_bFrontEnd = ( WND_UTL::AscKey ( '3' ) );

		//今回押した瞬間ならば、1回のみ切替
		if ( ! pre_bFrontEnd && is_bFrontEnd )	// false -> true
		{
			if ( ! bFrontEnd )
			{
				m_exeChara1->OnFrontEnd ();
				m_exeChara2->OnFrontEnd ();
				bFrontEnd = true;
			}
			else
			{
				m_exeChara1->OffFrontEnd ();
				m_exeChara2->OffFrontEnd ();
				bFrontEnd = false;
			}
		}

		pre_bFrontEnd = is_bFrontEnd;
	}

#if 0

	//------------------------------------------------------
	//CPU操作切替
	void MutualChara::SwithcCPU ()
	{
		static bool cpu1 = F;
		if ( WND_UTL::AscKey ( '6' ) )
		{
			cpu1 ^= T;
			if ( cpu1 )
			{
				m_exeChara1->ControlCPU ();
			}
			else
			{
				m_exeChara1->ControlPlayer ();
			}
		}

		static bool cpu2 = F;
		if ( WND_UTL::AscKey ( '7' ) )
		{
			cpu2 ^= T;
			if ( cpu2 )
			{
				m_exeChara2->ControlCPU ();
			}
			else
			{
				m_exeChara2->ControlPlayer ();
			}
		}
	}

	void MutualChara::Set_1P_vs_2P ()
	{
		m_exeChara1->ControlPlayer ();
		m_exeChara2->ControlPlayer ();
	}

	void MutualChara::Set_1P_vs_CPU ()
	{
		m_exeChara1->ControlPlayer ();
		m_exeChara2->ControlCPU ();
	}

	void MutualChara::Set_CPU_vs_CPU ()
	{
		m_exeChara1->ControlCPU ();
		m_exeChara2->ControlCPU ();
	}


	//------------------------------------------------------

	//試合初期化
	void MutualChara::ResetMatch ()
	{
		if ( ::GetAsyncKeyState ( '0' ) & 0x0001 )
		{
			m_exeChara1->Init ();
			m_exeChara2->Init ();
		}
	}


#endif // 0

	//トレーニングモード初期化
	void MutualChara::TrainingInit ()
	{
		m_exeChara1->TrainingInit ();
		m_exeChara2->TrainingInit ();

//		m_pFtgGrp->InitSlow ();
	}


	//------------------------------------------------------
	//	ExeChara両者操作
	//------------------------------------------------------
	//開始デモ
	void MutualChara::StartGreeting ()
	{
		m_exeChara1->StartGreeting ();
		m_exeChara2->StartGreeting ();
	}

	//開始準備
	void MutualChara::StartGetReady ()
	{
		m_exeChara1->StartGetReady ();
		m_exeChara2->StartGetReady ();
	}

	//戦闘開始
	void MutualChara::StartFighting ()
	{
		m_exeChara1->StartFighting ();
		m_exeChara2->StartFighting ();
	}

	//----------------------------------------------------
	//	戦闘時間
	//----------------------------------------------------

	//タイム計測開始
	void MutualChara::StartTime ()
	{
		m_btlTime->Start ();
	}


	//時間計測初期化
	void MutualChara::TimeSet ()
	{
		m_btlTime->Set ();
	}

	//タイムアップ
	void MutualChara::StartTimeUp ()
	{
		DecideWinner_FromLife();

		m_exeChara1->StartTimeUp ();
		m_exeChara2->StartTimeUp ();
	}

	//タイムアップ終了待機
	void MutualChara::StartEndWait ()
	{
		m_exeChara1->StartEndWait ();
		m_exeChara2->StartEndWait ();
	}


	//終了ステップ開始
	void MutualChara::StartEnd ()
	{
	}



	//両者待機状態
	bool MutualChara::IsWait ()
	{
		bool b1 = m_exeChara1->IsWait ();
		bool b2 = m_exeChara2->IsWait ();
		return b1 && b2;
	}

	//----------------------------------------------------


	//------------------------------------------------------
	//	終了判定
	//------------------------------------------------------

	//ライフ０による終了
	bool MutualChara::FinishCheck_ZeroLife ()
	{
		//終了判定
		bool finish1p = m_exeChara1->IsZeroLife ();
		bool finish2p = m_exeChara2->IsZeroLife ();

		//どちらか、または両方ライフ０なら終了
		if ( finish1p || finish2p )
		{
			PLAYER_ID plr = _PLAYER_NUM;
			if ( finish1p && finish2p )
			{
				plr = _PLAYER_NUM;
			}
			else if ( ! finish1p && finish2p )
			{
				plr = PLAYER_ID_1;
			}
			else if ( finish1p && ! finish2p )
			{
				plr = PLAYER_ID_2;
			}
			//シーン共通パラメータ記録
			m_pParam->SetWinner ( plr );
			return T;
		}

		return F;
	}

	//タイムアップによる終了
	bool MutualChara::FinishCheck_TimeUp ()
	{
		return m_btlTime->IsTimeUp ();
	}



#if 0
	void MutualChara::RevertSlow ()
	{
		m_exeChara1->RevertSlow ();
		m_exeChara2->RevertSlow ();
	}
#endif // 0

	//残ライフで勝者決定
	void MutualChara::DecideWinner_FromLife ()
	{
		//タイムアップ時、残り体力で勝者を決める
		int life_1 = m_exeChara1->GetBtlPrm ().GetLife ();
		int life_2 = m_exeChara2->GetBtlPrm ().GetLife ();


		//1P勝利
		if ( life_1 > life_2 )
		{
			m_exeChara1->SetAction ( U"Demo_Win" );
			m_exeChara2->SetAction ( U"Demo_TimeUpLose" );

			//ラウンド加算
			m_round->AddRound_1p ();

			//シーンパラメータに保存
			m_pParam->SetWinner ( PLAYER_ID_1 );
		}
		//2P勝利
		else if ( life_1 < life_2 )
		{
			m_exeChara1->SetAction ( U"Demo_TimeUpLose" );
			m_exeChara2->SetAction ( U"Demo_Win" );

			//ラウンド加算
			m_round->AddRound_2p ();

			//シーンパラメータに保存
			m_pParam->SetWinner ( PLAYER_ID_2 );
		}
		//引き分け
		else
		{
			m_exeChara1->SetAction ( U"Demo_Draw" );
			m_exeChara2->SetAction ( U"Demo_Draw" );

			//どちらもラウンド取得なし

			//シーンパラメータに保存
			m_pParam->SetWinner ( _PLAYER_NUM );	//Dra
		}
	}



}	//namespace GAME

