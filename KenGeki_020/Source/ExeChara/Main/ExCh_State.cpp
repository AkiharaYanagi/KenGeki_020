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

	//------------------------------------------------
	//開始時挨拶
	void CHST_Greeting::Start ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照

		//アクション・スクリプト初期化
		pExe->SetAction ( U"Start_Demo" );
	}

	void CHST_Greeting::PreScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
//■		pExe->Input ();				//入力		
		pExe->TransitAction ();		//アクション遷移
		pExe->CalcPos ();			//位置計算
//■		pExe->SetCollisionRect ();	//接触枠設定
		pExe->PreMove_Effect ();		//エフェクト生成と動作
	}

	void CHST_Greeting::PostScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->PostMove_Effect ();		//エフェクト生成と動作
		pExe->MoveTimer ();		//タイマ稼働
//■		pExe->CheckLife ();		//ライフ判定
		pExe->UpdateGraphic ();		//グラフィックの更新
	}


	//------------------------------------------------
	//準備
	void CHST_GetReady::Start ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照

		//アクション・スクリプト初期化
		pExe->SetAction ( U"Start_N" );
	}

	void CHST_GetReady::PreScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->Input ();				//入力		
		pExe->TransitAction ();		//アクション遷移
		pExe->CalcPos ();			//位置計算
//■		pExe->SetCollisionRect ();	//接触枠設定
		pExe->PreMove_Effect ();		//エフェクト生成と動作
	}

	void CHST_GetReady::PostScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->PostMove_Effect ();		//エフェクト生成と動作
		pExe->MoveTimer ();		//タイマ稼働
//■		pExe->CheckLife ();		//ライフ判定
		pExe->UpdateGraphic ();		//グラフィックの更新
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
		P_ExeChara pExe = GetwpExeChara ().lock ();
		pExe->PostMove_Effect ();	//エフェクト動作
		//■		pExe->MoveTimer ();			//タイマ稼働
		pExe->CheckLife ();			//ライフ判定
		pExe->UpdateGraphic ();		//グラフィックの更新
	}

	//------------------------------------------------
	//タイムアップ
	void CHST_TimeUp::Start ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
	}

	void CHST_TimeUp::PreScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		//■		pExe->Input ();				//入力		
		pExe->TransitAction ();		//アクション遷移
		pExe->CalcPos ();			//位置計算
		//■		pExe->SetCollisionRect ();	//接触枠設定
		pExe->PreMove_Effect ();		//エフェクト生成と動作
	}

	void CHST_TimeUp::PostScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->PostMove_Effect ();		//エフェクト生成と動作
		pExe->MoveTimer ();		//タイマ稼働
		//■		pExe->CheckLife ();		//ライフ判定
		pExe->UpdateGraphic ();		//グラフィックの更新
	}

	//------------------------------------------------
	//終了待機
	void CHST_EndWait::Start ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
	}

	void CHST_EndWait::PreScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		//■		pExe->Input ();				//入力		
		pExe->TransitAction ();		//アクション遷移
		pExe->CalcPos ();			//位置計算
		pExe->SetCollisionRect ();	//接触枠設定
		pExe->PreMove_Effect ();		//エフェクト生成と動作
	}

	void CHST_EndWait::RectMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		//■		pExe->SetRect ();		//枠設定
	}

	void CHST_EndWait::PostScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->PostMove_Effect ();		//エフェクト生成と動作
		pExe->MoveTimer ();		//タイマ稼働
		//■		pExe->CheckLife ();		//ライフ判定
		pExe->UpdateGraphic ();		//グラフィックの更新
	}


}	//namespace GAME

