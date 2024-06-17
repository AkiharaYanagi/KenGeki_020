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
	//	アクション遷移
	//================================================
#if 0
	//アクション移項（コマンドに関する処理）
	bool ExeChara::TranditAction_Command ()
	{
		//-----------------------------------------------------
		// コマンドによる分岐
		//コマンドが完成したIDを優先順に保存したリスト
		m_pCharaInput->MakeTransitIDList ( *m_pChara, m_pScript, m_btlPrm.GetDirRight () );
		const std::vector < UINT > & vCompID = m_pCharaInput->GetvCompID ();

		UINT transitID = NO_COMPLETE;
		for ( UINT id : vCompID )
		{
			//遷移先チェック
			P_Action pAct = m_pChara->GetpAction ( id );

			//特殊アクション 除外 指定　：　不可能なら次をチェック
			if ( ! TranditAction_Special ( pAct ) )
			{
				continue;
			}

			//------------------------------------------

			//可能なら遷移先に指定して終了
			transitID = id;
			break;
		}

		//コマンドが完成していたら
		if ( NO_COMPLETE != transitID )
		{
			//現在アクションとして最後の処理
			EndAction ();

			//遷移先チェック
			P_Action pact = m_pChara->GetpAction ( transitID );
			P_Script pscr = pact->GetpScript ( 0 );

			//バランス処理
			int bl_a = pact->GetBalance ();		//アクション消費バランス
			m_btlPrm.AddBalance ( bl_a );

			//アクション遷移
			m_actionID = transitID;

			//スクリプト処理
			ExeScript ();

			//アクション移項を計測
			m_btlPrm.AddNActTrs ( 1 );

			//次フレームのスクリプトを１つ進める
			//今回フレームは取得済みのm_pScriptを用いる
			++ m_frame;

			//終了
			return T;
		}

		return F;
	}
#endif // 0


	//アクションの移項(直接指定)
	void ExeChara::SetAction ( UINT action_id )
	{
		m_actionID = action_id;
		m_pAction = m_pChara->GetpAction ( m_actionID );
		m_frame = 0;
		m_pScript = m_pAction->GetpScript ( m_frame );

		//スクリプトからのパラメータ反映
		SetParamFromScript ();
	}

	void ExeChara::SetAction ( s3d::String action_name )
	{
		UINT idAction = m_pChara->GetActionID ( action_name );
		if ( NO_ACTION == idAction ) { assert ( T ); }
		SetAction ( idAction );
	}

#if 0

	//アクション移行(自身)
	void  ExeChara::TransitAction_Condition_I ( BRANCH_CONDITION CONDITION, bool forced )
	{
		//ヒット・相手
		UINT indexAction = Check_TransitAction_Condition ( CONDITION );
		if ( NO_COMPLETE != indexAction )
		{
			//遷移先チェック
			P_Action pAct = m_pChara->GetpAction ( indexAction );
			P_Script pScr = pAct->GetpScript ( 0 );

			//自身を変更
			SetAction ( indexAction );	//遷移
			m_btlPrm.SetForcedChange ( forced );	//強制
		}
	}

	//アクション移行 ( 自分攻撃、相手ヒット )
	void  ExeChara::TransitAction_Condition_E ( BRANCH_CONDITION CONDITION, bool forced )
	{
#if 0
		UINT indexAction = Check_TransitAction_Condition ( CONDITION );

		//該当無しは何もしない
		if ( NO_COMPLETE == indexAction ) { return; }

		//遷移先チェック
		P_Action pAct = m_pChara->GetpAction ( indexAction );

		//相手を変更
		m_pOther.lock ()->SetAction ( indexAction );	//遷移
		m_pOther.lock ()->m_btlPrm.SetForcedChange ( forced );	//強制
#endif // 0

		//----------------------------------------------
		//@info 相手側のアクションなので ”名前” で検索する
		//----------------------------------------------

		//アクション名を取得
		tstring nameAction = Check_TransitAction_Condition_str ( CONDITION );

		//該当無しは何もしない
		if ( _T("") == nameAction ) { return; }

		//=================================================================
		//遷移先チェック
		P_Action pAct = m_pOther.lock()->m_pChara->GetpAction ( nameAction );

		//やられ状態のとき空中チェック
		bool bDai = _T("ダメージ大") == nameAction ;
		bool bSyou = _T("ダメージ小") == nameAction ;

		if ( bDai || bSyou )
		{
			ACTION_POSTURE ap = m_pOther.lock()->GetPosture ();
			if ( ap == ACTION_POSTURE::AP_JUMP )
			{
				nameAction = _T("空中やられ");
			}
		}

		//@todo のけぞり時間を指定してある場合、相手に適用

		//スクリプト
		if ( m_pScript->m_prmBattle.Warp != 0 )
		{
		}


		//=================================================================
		//相手の変更先アクション名を保存
		m_nameChangeOther = nameAction;
#if 0
		//相手を変更
		m_pOther.lock ()->SetAction ( nameAction );	//遷移
		m_pOther.lock ()->m_btlPrm.SetForcedChange ( forced );	//強制
#endif // 0
	}

	void ExeChara::ChangeOhter ()
	{
		//相手を変更
		m_pOther.lock ()->SetAction ( m_nameChangeOther );	//遷移
		m_pOther.lock ()->m_btlPrm.SetForcedChange ( T );	//強制
	}


	//アクション移行(条件チェック)
	UINT ExeChara::Check_TransitAction_Condition ( BRANCH_CONDITION BRC_CND ) const
	{
		//キャラの持つルート,ブランチ,コマンドの参照
		const VP_Route& vpRoute = m_pChara->GetvpRoute ();
		const VP_Branch& vpBranch = m_pChara->GetvpBranch ();

		//スクリプトの持つルートリスト
		for ( UINT indexRut : m_pScript->GetcvRouteID () )
		{
			const V_UINT& vBrcID = vpRoute [ indexRut ]->GetcvIDBranch ();

			//対象のブランチリスト
			for ( UINT id : vBrcID )
			{
				//条件成立
				if ( BRC_CND != vpBranch [ id ]->GetCondition () ) { continue; }

				return vpBranch [ id ]->GetIndexSequence ();
			}
		}
		return NO_COMPLETE;
	}


	//アクション移行(条件チェック) 名前を返す
	tstring ExeChara::Check_TransitAction_Condition_str ( BRANCH_CONDITION BRC_CND ) const
	{
		//キャラの持つルート,ブランチ,コマンドの参照
		const VP_Route& vpRoute = m_pChara->GetvpRoute ();
		const VP_Branch& vpBranch = m_pChara->GetvpBranch ();

		//スクリプトの持つルートリスト
		for ( UINT indexRut : m_pScript->GetcvRouteID () )
		{
			const V_UINT& vBrcID = vpRoute [ indexRut ]->GetcvIDBranch ();

			//対象のブランチリスト
			for ( UINT id : vBrcID )
			{
				//条件不成立は続行
				if ( BRC_CND != vpBranch [ id ]->GetCondition () ) { continue; }

				//条件成立
				return vpBranch [ id ]->GetNameSequence ();
			}
		}
		return _T("");
	}


	//-------------------------------------------------------------------------------------------------

	//アクション移項時、前アクションの最後の処理
	void ExeChara::EndAction ()
	{
		//次アクションを指定
		//実効アクションm_pActionは次フレーム時のMove()でm_actionIDを使って取得される
		m_actionID = m_pAction->GetNextID ();

		//------------------------------------------------
		//◆移項限定処理
		//ダッシュから次アクションに移項するとき、慣性を残す
		if ( m_pChara->GetActionID ( _T ( "FrontDashStart" ) ) == m_actionID )
		{
			m_btlPrm.SetDashInertial ( VEC2 ( 10.f, 0 ) );
		}
		if ( m_pChara->GetActionID ( _T ( "FrontDash" ) ) == m_actionID )
		{
			m_btlPrm.SetDashInertial ( VEC2 ( 10.f, 0 ) );
		}
		if ( m_pChara->GetActionID ( _T ( "BackDash" ) ) == m_actionID )
		{
			m_btlPrm.SetDashInertial ( VEC2 ( -8.f, 0 ) );
		}
		//------------------------------------------------

		//各種状態の終了
		m_btlPrm.EndAction ();
		m_frame = 0;
	}
#endif // 0


}	//namespace GAME

