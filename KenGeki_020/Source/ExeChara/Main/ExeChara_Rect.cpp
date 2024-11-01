//=================================================================================================
//
// エグゼキャラ　ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "ExeChara.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//================================================
	//	判定枠関連 内部関数
	//================================================

	//接触枠設定
	void ExeChara::SetCollisionRect ()
	{
		m_charaRect->SetCRect ( m_pScript->GetpvCRect (), m_btlPrm.GetDirRight (), m_btlPrm.GetPos () );
	}

	//相殺・攻撃・当り・枠設定
	void ExeChara::SetRect ()
	{
		SetOffsetRect ();
		SetAttackRect ();
		SetHitRect ();
	}

	//相殺枠設定
	void ExeChara::SetOffsetRect ()
	{
		m_charaRect->SetORect ( m_pScript->GetpvORect (), m_btlPrm.GetDirRight (), m_btlPrm.GetPos () );
	}

	//攻撃枠設定
	void ExeChara::SetAttackRect ()
	{
		//======================================
		// ヒット時に後の攻撃枠を一時停止(多段防止)
		//======================================

		//ヒット状態を確認 (ヒット状態設定は OnHit(), OnClang() )
		bool bHit = m_btlPrm.GetHitEst () || m_btlPrm.GetClang ();
//		bool bHit = m_btlPrm.GetHitEst ();

		//デバッグ表示あり
#if 1
		if ( m_btlPrm.GetPlayerID() == PLAYER_ID_1 )
		{
			DBGOUT_WND_F ( DBGOUT_4, U"bHit = {}"_fmt( bHit ? 1 : 0) );
			P_Timer ptHitStop = m_btlPrm.GetTmr_HitStop ();
			DBGOUT_WND_F ( DBGOUT_5, U"hitStop = {}"_fmt( ptHitStop->GetTime () ) );
			UINT hitpitch = m_pAction->GetHitPitch ();
			P_Timer ptHitPitch = m_btlPrm.GetTmr_HitPitch ();
			DBGOUT_WND_F ( DBGOUT_6, U"hitPitch = {} / {}"_fmt( ptHitPitch->GetTime (), hitpitch ) );
			UINT hitmax = m_pAction->GetHitNum ();
			UINT hitnum = m_btlPrm.GetHitNum ();
			DBGOUT_WND_F ( DBGOUT_7, U"hitnum = {} / {}"_fmt( hitnum, hitmax ) );
		}
#endif // 0

#if DEBUG_DISP
#else
		//デバッグ表示なし
#endif // DEBUG_DISP

		//--------------------------------------------------
		//ヒットしていない時(通常時)、攻撃枠を設定して終了
		if ( ! bHit )
		{
			//攻撃枠の設定
			m_charaRect->SetARect ( m_pScript->GetpvARect (), m_btlPrm.GetDirRight (), m_btlPrm.GetPos () );
			return;
		}

		//--------------------------------------------------
		//攻撃成立時・打合時に同一アクション中のみ枠を消失させる

		//1ヒット技は攻撃枠を空にして終了
		if ( 1 >= m_pAction->GetHitNum () )
		{
			//攻撃枠を空にする
			m_charaRect->ResetARect ();
			return;
		}

		//--------------------------------------------------
		//アクション内ヒット数が上限に達したとき枠を空にする

		UINT hitmax = m_pAction->GetHitNum ();
		if ( hitmax <= m_btlPrm.GetHitNum () )
		{
			//攻撃枠を空にする
			m_charaRect->ResetARect ();
			return;
		}

		//--------------------------------------------------
		//多段可能なアクションは、ヒット間隔をチェックして攻撃枠を再設定する
		P_Timer ptHitPitch = m_btlPrm.GetTmr_HitPitch ();
		UINT pitch = m_pAction->GetHitPitch ();
		//タイマが指定間隔未満なら枠を設定しない
		if ( pitch > ptHitPitch->GetTime () )
		{
			//攻撃枠を空にする
			m_charaRect->ResetARect ();
			return;
		}

		else
		{
			//再スタート
//			m_btlPrm.HitPitchWaitStart ();
		}

		//それ以外は枠を設定する
		//攻撃枠の設定
		m_charaRect->SetARect ( m_pScript->GetpvARect (), m_btlPrm.GetDirRight (), m_btlPrm.GetPos () );
		//--------------------------------------------------
	}

	//当り枠設定
	void ExeChara::SetHitRect ()
	{
		m_charaRect->SetHRect ( m_pScript->GetpvHRect (), m_btlPrm.GetDirRight (), m_btlPrm.GetPos () );
	}

	//枠をすべてリセット
	void ExeChara::ResetRect ()
	{
		m_charaRect->ResetAllRect ();
	}

	//枠表示切替
	void ExeChara::OnDispRect ()
	{
		m_dispChara->OnRect ();
//		m_oprtEf->OnDispRect ();
	}
	void ExeChara::OffDispRect ()
	{
		m_dispChara->OffRect ();
//		m_oprtEf->OffDispRect ();
	}


}	//namespace GAME

