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
#include "../GameMain/G_Ftg.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	MutualChara::MutualChara ()
	{
		//ぶつかり判定
		m_collision = std::make_shared < Collision > ();
		AddpTask ( m_collision );

		//攻撃・ヒット判定
		m_decision = std::make_shared < Decision > ();
		AddpTask ( m_decision );

		//------------------------------------------------
		//タイム
		m_btlTime = std::make_shared < BattleTime > ();
		AddpTask ( m_btlTime );

		//------------------------------------------------
		//ラウンド
		m_round = std::make_shared < Round > ();
		AddpTask ( m_round );
	}

	MutualChara::~MutualChara ()
	{
	}

	void MutualChara::SetpChara ( P_ExeChara p1, P_ExeChara p2 )
	{
		m_exeChara1 = p1;
		m_exeChara2 = p2;
		m_utl.SetpChara ( m_exeChara1, m_exeChara2 );
		m_collision->SetpChara ( m_exeChara1, m_exeChara2 );
		m_decision->SetpChara ( m_exeChara1, m_exeChara2 );
	}


	void MutualChara::ParamInit ( P_Param pParam )
	{
		m_pParam = pParam;
	}

	void MutualChara::Load ()
	{
		mp_vtx = std::make_unique < s3d::VideoTexture > ( U"raiden.mp4", s3d::Loop::No );
		GrpLst::Inst()->SetupVtx ( std::move ( mp_vtx ) );
		TASK_VEC::Load ();
	}

	void MutualChara::Init ()
	{
		m_pParam->SetN_Act1p ( 0 );
		m_pParam->SetN_Act2p ( 0 );
		m_btlTime->Init ();
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
		m_utl.SwitchDispInput ();
		m_utl.SwitchRect ();
		m_utl.SwitchFrontEnd ();
//		m_utl.SwitchCPU ();

		//表示切替
		SwitchDisp ();

		//---------------------------------------------------

		//◆スクリプト前処理(入力、移動など)
		m_exeChara1->PreScriptMove ();
		m_exeChara2->PreScriptMove ();

		//◆相互判定(ぶつかり枠)
		m_collision->Do ();

		//◆ぶつかり後、攻撃・ヒット判定枠を設定
		m_exeChara1->RectMove ();
		m_exeChara2->RectMove ();

		//◆相互判定(攻撃・ヒット枠)
		m_decision->Do ();

		//◆スクリプト後処理(グラフィック位置など)
		m_exeChara1->PostScriptMove ();
		m_exeChara2->PostScriptMove ();

		//グラフィック共通
		Grp ();

		//シーン共通パラメータ記録
		SaveParam();



		//test
		float x1 = m_exeChara1->GetPos ().x;
		float x2 = m_exeChara2->GetPos ().x;
		DBGOUT_WND()->DebugOutf ( 0, U"{}, {}"_fmt( x1, x2 ) );



	}



#if 0
	//■#########################################################
	
	//一時停止中コンダクト
	void MutualChara::Conduct_InStop ()
	{
		//---------------------------------------------------
		//システム変更
		SwitchRect ();	//枠表示切替
		SwitchDispInput ();	//入力表示切替
		SwitchFrontEnd ();	//ゲージ類表示切替
		SwithcCPU ();	//CPU操作切替
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

		//---------------------------------------------------
		//超必殺カットイン
		if ( m_pFtgGrp->GetOverDrive () )
		{
	//		mp_vtx->advance ();
	//		mp_vtx->draw ();
			GrpLst::Inst()->StartVtx ();
			m_pFtgGrp->SetOverDrive ( F );	//条件をオフ
		}
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

	//トレーニングモード初期化
	void MutualChara::TrainingInit ()
	{
		m_exeChara1->TrainingInit ();
		m_exeChara2->TrainingInit ();

		Init ();
//		m_utl.SwitchDispInput ();
//		m_pFtgGrp->InitSlow ();
	}


	//シーン共通パラメータ記録
	void MutualChara::SaveParam()
	{
		m_pParam->SetN_Life1p ( m_exeChara1->GetLife () );
		m_pParam->SetN_Life2p ( m_exeChara2->GetLife () );
		m_pParam->SetN_Act1p ( m_exeChara1->GetBtlParam ().GetNActTrs () );
		m_pParam->SetN_Act2p ( m_exeChara2->GetBtlParam ().GetNActTrs () );
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

	//壁割後のアクション指定
	void MutualChara::WallBreak_Action ( PLAYER_ID id )
	{
		if ( id == PLAYER_ID_1 )
		{
			m_exeChara1->SetAction ( U"壁割後ダッシュ" );
			m_exeChara2->SetAction ( U"壁割から吹き飛び" );
		}
		else
		{
			m_exeChara1->SetAction ( U"壁割から吹き飛び" );
			m_exeChara2->SetAction ( U"壁割後ダッシュ" );
		}
	}

	//戦闘通常状態に戻る
	void MutualChara::Shift_Fighting ()
	{
		m_exeChara1->Shift_Fighting ();
		m_exeChara2->Shift_Fighting ();
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


#if 0
	void MutualChara::RevertSlow ()
	{
		m_exeChara1->RevertSlow ();
		m_exeChara2->RevertSlow ();
	}
#endif // 0

	void MutualChara::SwitchDisp ()
	{
		static bool bDisp = T;		//状態
		static bool pre_bDisp = F;	//前回押しているか
		static bool is_bDisp = F;	//今回押しているか

		//		is_bDisp0 = ( WND_UTL::AscKey ( '4' ) );
		//Asyncの判定２回目以降
		is_bDisp = G_FTG()->GetSysDisp ();

		//今回押した瞬間ならば、1回のみ切替
		if ( ! pre_bDisp && is_bDisp )	// false -> true
		{
			if ( bDisp )
			{
				OffDisp ();
				bDisp = false;
			}
			else
			{
				OnDisp ();
				bDisp = true;
			}
		}

		pre_bDisp = is_bDisp;
	}

	void MutualChara::OnDisp ()
	{
		m_btlTime->On ();
		m_round->On ();
	}

	void MutualChara::OffDisp ()
	{
		m_btlTime->Off ();
		m_round->Off ();
	}


}	//namespace GAME

