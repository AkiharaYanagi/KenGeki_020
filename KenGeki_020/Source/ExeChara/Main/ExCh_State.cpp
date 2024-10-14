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
		pExe->PreMove_Effect ();		//エフェクト生成と動作
	}

	//共通：ライフ判定なしPostScriptMove
	void ExeChara_State::PostScriptMove_NoLifeCheck ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->PostMove_Effect ();		//エフェクト生成と動作
		pExe->MoveTimer ();		//タイマ稼働
		//■		pExe->CheckLife ();		//ライフ判定
		pExe->UpdateGraphic ();		//グラフィックの更新
		pExe->SE_Play ();			//SEの再生
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
		pExe->PreMove_Effect ();		//エフェクト生成と動作
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
		if ( pExe->IsHitStop () ) { return; }

		pExe->TransitAction ();		//アクション遷移
		pExe->CalcPos ();			//位置計算
		pExe->SetCollisionRect ();	//接触枠設定
//		pExe->OverEfPart ();		//EfPart重なり
		pExe->PreMove_Effect ();		//エフェクト生成と動作
	}

	// AlwaysMove () アクションとスクリプトによらない一定の処理
#if 0
	void ExeChara::AlwaysMove ()
	{
		//ダメージ分のライフ表示減少
		int dmg = m_btlPrm.GetDamage ();
		if ( 0 < dmg ) { m_btlPrm.SetDamage ( dmg - 1 ); }

		//---------------------------------------------------
		//デモカウント
		//ダウン状態のとき
		if ( CHST_DOWN == m_charaState )
		{
			if ( ! m_btlPrm.GetTmr_Down ()->IsActive () )
			{
				m_charaState = CHST_DOWN_END;
			}
		}

		//勝利待機状態のとき
		if ( CHST_WIN_WAIT == m_charaState )
		{
#if 0
			//地上ニュートラルなら
			if ( IsBasicAction ( BA_STAND ) )
			{
				//勝利状態に移行
				m_actionID = m_pChara->GetBsAction ( BA_WIN );
				TransitAction ( m_actionID );
				m_tmrEnd->Start ();
				m_charaState = CHST_WIN;
			}
#endif // 0
		}

		//勝利状態のとき
		if ( CHST_WIN == m_charaState )
		{
			//if ( ! m_tmrEnd->IsActive () )
			if ( ! m_btlPrm.GetTmr_End ()->IsActive () )
			{
				m_charaState = CHST_WIN_END;
			}
		}
		//---------------------------------------------------
		//SE
		if ( m_btlPrm.GetFirstEf () )
		{
			SOUND->Play ( SE_Hit );
			m_btlPrm.SetFirstEf ( F );
		}

		//---------------------------------------------------
		//入力
		Input ();
	}
#endif // 0

	void CHST_Main::RectMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->SetRect ();		//枠設定
	}

	void CHST_Main::PostScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();
		pExe->PostMove_Effect ();	//エフェクト動作
		pExe->MoveTimer ();			//タイマ稼働
		pExe->CheckLife ();			//ライフ判定
		pExe->UpdateGraphic ();		//グラフィックの更新
		pExe->SE_Play ();			//SEの再生
	}


	//------------------------------------------------
	//バトル　一時停止

	void CHST_ScpStop::PreScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();
		pExe->Input ();				//入力		
		//■ 	pExe->TransitAction ();		//アクション遷移
		//■		pExe->CalcPos ();			//位置計算
		//■		pExe->SetCollisionRect ();	//接触枠設定
		//■		pExe->PreMove_Effect ();	//エフェクト生成と動作
	}

	void CHST_ScpStop::PostScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();
		//■		pExe->PostMove_Effect ();	//エフェクト動作
		//■		pExe->MoveTimer ();			//タイマ稼働
		//■		pExe->CheckLife ();			//ライフ判定
		pExe->UpdateGraphic ();		//グラフィックの更新
		//■		pExe->SE_Play ();			//SEの再生
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
		//■		pExe->PreMove_Effect ();	//エフェクト生成と動作
	}

	void CHST_WallBreak::PostScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();
		pExe->PostMove_Effect ();	//エフェクト動作
		//■		pExe->MoveTimer ();			//タイマ稼働
		//■		pExe->CheckLife ();			//ライフ判定
		pExe->UpdateGraphic ();		//グラフィックの更新
		pExe->SE_Play ();			//SEの再生
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
		//■		pExe->PreMove_Effect ();		//エフェクト生成と動作
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

