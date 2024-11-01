//=================================================================================================
//
//	ExeChara ステート
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "ExCh_State.h"
#include "ExeChara.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------
	// ※凡例
	//■	：他ステートと比較して外してある項目
 	//------------------------------------------------
	//
	// 
	//=====================================================
	//共通：入力なしPreScriptMove
	void ExeChara_State::PreScriptMove_NoInput ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		//■		pExe->Input ();				//入力		
		pExe->TransitAction ();		//アクション遷移
		pExe->CalcPos ();			//位置計算
		pExe->SetCollisionRect ();	//接触枠設定
		pExe->Generate_Effect ();	//エフェクト生成
		pExe->PreMove_Effect ();	//エフェクト動作
	}

	//共通：ライフ判定なしPostScriptMove
	void ExeChara_State::PostScriptMove_NoLifeCheck ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->PostMove_Effect ();		//エフェクト生成と動作
		//■		pExe->CheckLife ();		//ライフ判定
		pExe->UpdateGraphic ();		//グラフィックの更新
		pExe->SE_Play ();			//SEの再生
		pExe->VC_Play ();			//VCの再生

		pExe->MoveTimer ();		//タイマ稼働
		pExe->SetFirstSE ( F );		//SE再生フラグ
		pExe->SetFirstVC ( F );		//VC再生フラグ
	}

	//=====================================================

	//------------------------------------------------
	//開始時挨拶
	void CHST_Greeting::Start ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照

		//アクション・スクリプト初期化
		pExe->SetAction ( U"開幕" );
	}

	void CHST_Greeting::PreScriptMove ()
	{
		PreScriptMove_NoInput ();
	}

	void CHST_Greeting::PostScriptMove ()
	{
		PostScriptMove_NoLifeCheck ();
	}


	//------------------------------------------------
	//準備
	void CHST_GetReady::Start ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照

		//アクション・スクリプト初期化
		pExe->SetAction ( U"開幕待機" );
	}

	void CHST_GetReady::PreScriptMove ()
	{
		//@info 入力は可能

		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->Input ();				//入力		
		pExe->TransitAction ();		//アクション遷移
		pExe->CalcPos ();			//位置計算
//■		pExe->SetCollisionRect ();	//接触枠設定
		pExe->Generate_Effect ();	//エフェクト生成
		pExe->PreMove_Effect ();	//エフェクト動作
	}

	void CHST_GetReady::PostScriptMove ()
	{
		PostScriptMove_NoLifeCheck ();
	}


	//------------------------------------------------
	//バトル　メイン状態
	void CHST_Main::Start ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->Init ();
		//アクション・スクリプト初期化
		pExe->SetAction ( U"立ち" );
	}

	void CHST_Main::PreScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();
		pExe->Input ();				//入力		

		//ヒットストップ時は以降を飛ばす
		if ( pExe->IsHitStop () )
		{
			return;
		}

		pExe->TransitAction ();		//アクション遷移
		pExe->CalcPos ();			//位置計算
		pExe->SetCollisionRect ();	//接触枠設定
//		pExe->OverEfPart ();		//EfPart重なり
		pExe->Generate_Effect ();	//エフェクト生成
		pExe->PreMove_Effect ();	//エフェクト動作
	}

	void CHST_Main::RectMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->SetRect ();		//枠設定
	}

	void CHST_Main::PostScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();
		pExe->PostMove_Effect ();	//エフェクト動作
		pExe->CheckLife ();			//ライフ判定
		pExe->UpdateGraphic ();		//グラフィックの更新
		pExe->SE_Play ();			//SEの再生
		pExe->VC_Play ();			//VCの再生

		pExe->MoveTimer ();			//タイマ稼働
		pExe->SetFirstSE ( F );		//SE再生フラグ
		pExe->SetFirstVC ( F );		//VC再生フラグ
	}


	//------------------------------------------------
	//バトル　一時停止

	void CHST_ScpStop::Start ()
	{
		WP_ExeChara wpExeCh = GetwpExeChara ();
		UINT stop = wpExeCh.lock()->GetBtlPrm ().GetScpStop ();
		m_timer.Start ( stop );
	}

	void CHST_ScpStop::PreScriptMove ()
	{
		//タイマ
		m_timer.Move ();
		if ( m_timer.IsLast () )
		{
			//終了時に通常バトルにシフト
			GetwpActor ().lock()->ShiftFighting ();
		}

		//一連処理
		P_ExeChara pExe = GetwpExeChara ().lock ();
		pExe->Input ();				//入力		
		//■ 	pExe->TransitAction ();		//アクション遷移
		//■		pExe->CalcPos ();			//位置計算
		//■		pExe->SetCollisionRect ();	//接触枠設定

		//エフェクト生成のみ１回だけ、動作は毎回
		pExe->Generate_Effect_once ();	//エフェクト生成
		pExe->PreMove_Effect ();	//エフェクト動作
	}

	void CHST_ScpStop::PostScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();
		pExe->PostMove_Effect ();	//エフェクト動作
		//■		pExe->CheckLife ();			//ライフ判定
		pExe->UpdateGraphic ();		//グラフィックの更新

		//SEは再生してフラグを続投（通常時にOFF）
		pExe->SE_Play ();			//SEの再生
		pExe->VC_Play ();			//VCの再生
		pExe->GetBtlPrm().SetFirstSE ( T );		//SE再生フラグ
		pExe->GetBtlPrm().SetFirstVC ( T );		//VC再生フラグ

		//■		pExe->MoveTimer ();			//タイマ稼働
	}

	//------------------------------------------------
	//バトル　壁割

	void CHST_WallBreak::PreScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();
		pExe->Input ();				//入力		
		//■ 	pExe->TransitAction ();		//アクション遷移
		//■		pExe->CalcPos ();			//位置計算
		pExe->SetCollisionRect ();	//接触枠設定

		pExe->Generate_Effect ();	//エフェクト生成
		pExe->PreMove_Effect ();	//エフェクト動作
	}

	void CHST_WallBreak::PostScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();
		pExe->PostMove_Effect ();	//エフェクト動作
		//■		pExe->CheckLife ();			//ライフ判定
		pExe->UpdateGraphic ();		//グラフィックの更新
		pExe->SE_Play ();			//SEの再生
		pExe->VC_Play ();			//VCの再生

		//■		pExe->MoveTimer ();			//タイマ稼働
		pExe->SetFirstSE ( F );		//SE再生フラグ
		pExe->SetFirstVC ( F );		//VC再生フラグ
	}

	//------------------------------------------------
	//バトル　スロウスキップ状態(スロウ時に飛ばすフレーム処理のとき)

	void CHST_Slow_Skip::PreScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();
		pExe->Input ();				//入力		

		//ヒットストップ時は以降を飛ばす
		if ( pExe->IsHitStop () ) { return; }

		pExe->TransitAction ();		//アクション遷移
		//■		pExe->CalcPos ();			//位置計算
		pExe->SetCollisionRect ();	//接触枠設定
		pExe->Generate_Effect ();	//エフェクト生成
		//■		pExe->PreMove_Effect ();	//エフェクト動作
	}

	void CHST_Slow_Skip::RectMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->SetRect ();		//枠設定
	}

	void CHST_Slow_Skip::PostScriptMove ()
	{
		PostScriptMove_NoLifeCheck ();
	}

	//------------------------------------------------
	//タイムアップ
	void CHST_TimeUp::Start ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->ClearInput ();
	}

	void CHST_TimeUp::PreScriptMove ()
	{
		PreScriptMove_NoInput ();
	}

	void CHST_TimeUp::PostScriptMove ()
	{
		PostScriptMove_NoLifeCheck ();
	}

	//------------------------------------------------
	//終了待機
	void CHST_EndWait::Start ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->ClearInput ();
	}

	void CHST_EndWait::PreScriptMove ()
	{
		PreScriptMove_NoInput ();
	}

	void CHST_EndWait::PostScriptMove ()
	{
		PostScriptMove_NoLifeCheck ();
	}

	//------------------------------------------------
	//敗北ダウン状態
	void CHST_Down::Start ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->ClearInput ();
		pExe->SetLose ();

		//アクション・スクリプト初期化
		pExe->SetAction ( U"敗北ダウン浮き" );
	}

	void CHST_Down::PreScriptMove ()
	{
		PreScriptMove_NoInput ();
	}

	void CHST_Down::Do ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		//アクション・スクリプト初期化
		pExe->IsNameAction ( U"敗北ダウン" );
	}

	void CHST_Down::PostScriptMove ()
	{
		PostScriptMove_NoLifeCheck ();
	}

	//------------------------------------------------
	//勝者表示
	void CHST_Win::Start ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		//アクション指定移行
		pExe->SetAction ( U"勝利" );
	}

	void CHST_Win::PreScriptMove ()
	{
		PreScriptMove_NoInput ();
	}

	void CHST_Win::PostScriptMove ()
	{
		PostScriptMove_NoLifeCheck ();
	}


}	//namespace GAME

