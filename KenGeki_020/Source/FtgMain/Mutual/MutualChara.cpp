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
#include "../../GameMain/G_Ftg.h"


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
		m_decision->SetpParam ( pParam );
	}

	void MutualChara::Load ()
	{
		TASK_VEC::Load ();
	}

	void MutualChara::Init ()
	{
		TASK_VEC::Init ();
	}



	//■#########################################################
	//■
	//■	スクリプトの毎フレーム処理
	//■
	//■#########################################################

	//通常
	void MutualChara::Conduct ()
	{
		SystemChange ();		//システム変更

		//---------------------------------------------------

		//◆スクリプト前処理(入力、遷移など)
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

		//---------------------------------------------------
		SaveParam();		//シーン共通パラメータ記録
	}


	//■#########################################################

	//コンダクト (デモ)
	void MutualChara::Conduct_InDemo ()
	{
		SystemChange ();		//システム変更

		//---------------------------------------------------
		//◆スクリプト前処理(入力、遷移など)
		m_exeChara1->PreScriptMove ();
		m_exeChara2->PreScriptMove ();

		//◆画像の更新
		m_exeChara1->UpdateGraphic ();
		m_exeChara2->UpdateGraphic ();

		//◆判定なし

		//◆スクリプト後処理(グラフィック位置など)
		m_exeChara1->PostScriptMove ();
		m_exeChara2->PostScriptMove ();

		//---------------------------------------------------
		SaveParam();		//シーン共通パラメータ記録
	}


	//■#########################################################

	//一時停止中コンダクト (アクション遷移なし)
	void MutualChara::Conduct_InStop ()
	{
		SystemChange ();		//システム変更

		//---------------------------------------------------
		//◆スクリプト前処理(入力)
		m_exeChara1->Input ();
		m_exeChara2->Input ();

		//◆画像の更新
		m_exeChara1->UpdateGraphic ();
		m_exeChara2->UpdateGraphic ();

		//◆判定なし

		//◆スクリプト後処理(グラフィック位置など)
		m_exeChara1->PostScriptMove ();
		m_exeChara2->PostScriptMove ();

		//---------------------------------------------------
		SaveParam();		//シーン共通パラメータ記録
	}

	//■#########################################################

	//------------------------------------------------------
	//	内部関数
	//------------------------------------------------------

	//トレーニングモード初期化
	void MutualChara::TrainingInit ()
	{
		m_exeChara1->TrainingInit ();
		m_exeChara2->TrainingInit ();

//		Init ();
//		m_utl.SwitchDispInput ();
//		m_pFtgGrp->InitSlow ();
	}


	//システム変更
	void MutualChara::SystemChange ()
	{
		m_utl.SwitchDispInput ();
		m_utl.SwitchRect ();
		m_utl.SwitchFrontEnd ();
		m_utl.SwitchCPU ();
	}


	//シーン共通パラメータ記録
	void MutualChara::SaveParam()
	{
		m_pParam->SetN_Life1p ( m_exeChara1->GetLife () );
		m_pParam->SetN_Life2p ( m_exeChara2->GetLife () );
		m_pParam->SetN_Act1p ( m_exeChara1->GetBtlPrm ().GetNActTrs () );
		m_pParam->SetN_Act2p ( m_exeChara2->GetBtlPrm ().GetNActTrs () );
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

	//一時停止
	void MutualChara::ShiftScpStop ()
	{
		m_exeChara1->ShiftScpStop ();
		m_exeChara2->ShiftScpStop ();
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
	void MutualChara::ShiftFighting ()
	{
		m_exeChara1->ShiftFighting ();
		m_exeChara2->ShiftFighting ();
	}

#if 0
	void MutualChara::RevertSlow ()
	{
		m_exeChara1->RevertSlow ();
		m_exeChara2->RevertSlow ();
	}
#endif // 0



	//両者待機状態
	bool MutualChara::IsWait ()
	{
		bool b1 = m_exeChara1->IsWait ();
		bool b2 = m_exeChara2->IsWait ();
		return b1 && b2;
	}


	//終了待機
	void MutualChara::StartEndWait ()
	{
		PLAYER_ID winner = m_pParam->GetWinner ();

		//勝者側を待機状態にする
		//敗者側をダウンにする

		if ( PLAYER_ID_1 == winner )
		{
			m_exeChara1->StartEndWait ();
			m_exeChara2->StartDown ();
		}
		else if ( PLAYER_ID_2 == winner )
		{
			m_exeChara1->StartDown ();
			m_exeChara2->StartEndWait ();
		}
	}

	bool MutualChara::IsDown_Calm ()
	{
		PLAYER_ID winner = m_pParam->GetWinner ();

		//敗者側のダウンが落ち着いたらTを返す

		if ( PLAYER_ID_1 == winner )
		{
			return m_exeChara2->IsDown_Calm ();
		}
		else if ( PLAYER_ID_2 == winner )
		{
			return m_exeChara1->IsDown_Calm ();
		}
		return F;
	}

	//勝者表示
	void MutualChara::StartWinner ()
	{
		PLAYER_ID winner = m_pParam->GetWinner ();

		//勝者表示に変更
		if ( PLAYER_ID_1 == winner )
		{
			m_exeChara1->StartWinner ();
		}
		else if ( PLAYER_ID_2 == winner )
		{
			m_exeChara2->StartWinner ();
		}

	}

	//----------------------------------------------------

}	//namespace GAME

