﻿//=================================================================================================
//
// エグゼキャラ　ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "ExeChara.h"
#include "../../GameMain/G_Ftg.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//================================================
	//	アクション遷移
	//================================================


	// アクション移項(条件:コマンド, 特殊, アクション終了)
	void ExeChara::TransitAction ()
	{
		assert ( nullptr != m_pAction && nullptr != m_pScript );

#if 0

		//-----------------------------------------------------
		// のけぞり時間はコマンドによる行動不可
		if ( m_btlPrm.GetTmr_Lurch ()->IsActive () ) { return; }
#endif // 0

		//-----------------------------------------------------
		// コマンドによる分岐
		if ( TranditAction_Command () )
		{
			//分岐が成立していたら以降はチェックしない
			return;
		}

		//-----------------------------------------------------
		// 特殊条件による分岐
		TranditAction_Special ();


		//-----------------------------------------------------
		//現在スクリプトが現在アクションにおける最終フレーム ならば
		if ( m_pAction->IsOverScript ( m_frame ) )
		{
			EndAction ();	//アクション終了処理
			//次アクション m_frame = 0に遷移
		}

		//-----------------------------------------------------
		// スクリプト通常処理
		ExeScript ();


		//通常処理：スクリプトを１つ進める
		++ m_frame;


		//スロウのとき
#if 0

		if ( m_playerID == PLAYER_ID_1 )
		{
			DBGOUT_WND_F ( 8, _T ( "tmrSlow.m_count = %d" ), m_tmrSlow.GetCount () );
		}

		if ( m_tmrSlow.GetValid () )
		{
			if ( m_tmrSlow.Next () )
			{
				++ m_frame;
				m_actor.ShiftFighting ();
			}
			else
			{
				//スロウスキップ
				m_actor.ShiftSlowSkip ();
			}
		}
		else
		{
			//通常処理：スクリプトを１つ進める
			++ m_frame;
		}

#endif // 0


	}

	//アクション移項（コマンドに関する処理）
	bool ExeChara::TranditAction_Command ()
	{
		//-----------------------------------------------------
		// コマンドによる分岐
		
		//コマンドが完成したIDを優先順に保存したリスト
		m_pCharaInput->MakeTransitIDList ( *m_pChara, m_pScript, m_btlPrm.GetDirRight () );
		const V_UINT & vCompID = m_pCharaInput->GetvCompID ();

		uint32 transitID = (uint32)NO_COMPLETE;
		for ( UINT id : vCompID )
		{
			//遷移先チェック
			P_Action pAct = m_pChara->GetpAction ( id );

			//特殊アクション 除外 指定　：　不可能なら次をチェック
			if ( ! TranditAction_Exclusion ( pAct ) )
			{
				continue;
			}

			//可能なら遷移先に指定して終了
			transitID = id;
			break;
		}
		

		//相殺キャンセルチェック
		if ( m_btlPrm.GetTmr_OfstCncl()->IsActive () )
		{
			//空中は現在不可
			if ( ! IsAir () )
			{

				//コマンドが完成したIDを優先順に保存したリスト

				m_pCharaInput->MakeTransitIDList ( *m_pChara, m_vOfstCncl, m_btlPrm.GetDirRight () );
				const V_UINT & vCompID_Offset = m_pCharaInput->GetvCompID ();

				for ( UINT id : vCompID_Offset )
				{
					//遷移先チェック
					P_Action pAct = m_pChara->GetpAction ( id );

					//特殊アクション 除外 指定　：　不可能なら次をチェック
					if ( ! TranditAction_Exclusion ( pAct ) )
					{
						continue;
					}

					//可能なら遷移先に指定して終了
					transitID = id;
					break;
				}

			}
		}


		//コマンドが完成かつ移行条件がOKなら
		if ( NO_COMPLETE != transitID )
		{
			//現在アクションとして最後の処理
			EndAction ();

			//遷移先チェック
			P_Action pact = m_pChara->GetpAction ( transitID );
			P_Script pscr = pact->GetpScript ( 0 );

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
		if ( NO_ACTION == idAction )
		{
			TRACE_F ( _T("▼▼▼ アクション名呼び出しエラー:%s\n"), action_name.toWstr().c_str() );



			//@todo 呼び出しエラーのassertを仮値で続行させる



			assert ( action_name );
		}
		SetAction ( idAction );
	}


	//アクション移行(自身)
	void  ExeChara::TransitAction_Condition_I ( BRANCH_CONDITION CONDITION, bool forced )
	{
		(void)forced;

		//ヒット・相手
		UINT indexAction = Check_TransitAction_Condition ( CONDITION );
		if ( NO_COMPLETE != indexAction )
		{
			//遷移先チェック
			P_Action pAct = m_pChara->GetpAction ( indexAction );
			P_Script pScr = pAct->GetpScript ( 0 );


			s3d::String nameAction = Check_TransitAction_Condition_str ( CONDITION );

			//=================================================================
			//自身の変更先アクション名を保存
			m_nameChangeMine = nameAction;

			//自身を変更
//			SetAction ( indexAction );	//遷移
//			m_btlPrm.SetForcedChange ( forced );	//強制
		}
	}

	//アクション移行 ( 自分攻撃、相手ヒット )
	void  ExeChara::TransitAction_Condition_E ( BRANCH_CONDITION CONDITION, bool forced )
	{
		(void)forced;

#if 0
		if ( forced ) { int i = 0; ++ i; }
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
//		tstring nameAction = Check_TransitAction_Condition_str ( CONDITION );
		s3d::String nameAction = Check_TransitAction_Condition_str ( CONDITION );

		//該当無しは"ダメージ大"にして処理
		UINT index = m_pOther.lock()->m_pChara->GetActionID ( nameAction );
		if ( NO_ACTION == index )
		{
			nameAction = U"ダメージ大";
		}

		//=================================================================
		//遷移先チェック
		P_Action pAct = m_pOther.lock()->m_pChara->GetpAction ( nameAction );

		//やられ状態のとき空中チェック
		//@info 特殊状態　（特定技やられなど）は除く
		bool bDai = U"ダメージ大" == nameAction ;
		bool bSyou = U"ダメージ小" == nameAction ;
		if ( bDai || bSyou )
#if 0


		//相手がダメージかつ空中なら
		//bool bDmg = IsDamaged ();
		//bool bJump = Is_AP_Jump ();
//		if ( bDmg && bAir )
		bool bAir = m_pOther.lock()->m_btlPrm.GetPos().y < (float)GROUND_Y;

		if ( bAir )
#endif // 0
		{
			ACTION_POSTURE ap = m_pOther.lock()->GetPosture ();
			if ( ap == ACTION_POSTURE::AP_JUMP )
			{
				nameAction = U"空中やられ";
			}
		}

		//@info のけぞり時間を指定してある場合、相手に適用

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
		//ノーリアクション
		if ( 0 == m_nameChangeOther.compare ( U"ノーリアクション" ) )
		{
			//変更せず続行
			return;
		}


		//移行先名前チェック
		if ( ! m_pOther.lock ()->ExistActionName ( m_nameChangeOther ) )
		{
			TRACE_F ( _T("ChangeOther(): Error : name = %s\n"), m_nameChangeOther.toWstr().c_str () );
			//対象なしのときアサート
			//assert ( m_nameChangeOther );
			return;
		}

		//相手を変更
		m_pOther.lock ()->m_btlPrm.SetForcedChange ( T );	//強制
		m_pOther.lock ()->SetAction ( m_nameChangeOther );	//遷移
		m_nameChangeOther = U"ノーリアクション";

		m_pOther.lock()->m_btlPrm.SetFirstSE_HS ( F );
	}

	void ExeChara::ChangeMine ()
	{
		if ( ! ExistActionName ( m_nameChangeMine ) )
		{
			TRACE_F ( _T("ChangeOther(): Error : name = %s\n"), m_nameChangeMine.toWstr().c_str () );
			//対象なしのときアサート
			//assert ( m_nameChangeMine );
			return;
		}

		//ノーリアクション
		if ( 0 == m_nameChangeMine.compare ( U"ノーリアクション" ) )
		{
			//変更せず続行
			return;
		}

		//自身を変更
		m_btlPrm.SetForcedChange ( T );	//強制
		SetAction ( m_nameChangeMine );	//遷移
		m_nameChangeMine = U"ノーリアクション";
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
		return (UINT)NO_COMPLETE;
	}


	//アクション移行(条件チェック) 名前を返す
	s3d::String ExeChara::Check_TransitAction_Condition_str ( BRANCH_CONDITION BRC_CND ) const
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
		return U"";
	}

	//-------------------------------------------------------------------------------------------------
	// 特殊条件による分岐
	void ExeChara::TranditAction_Special ()
	{
#if 0
		if ( m_btlPrm.GetPlayerID () == PLAYER_ID_2 )
		{
			float edge_L = G_FTG()->GetEdgeLeft () + (float)FIELD_EDGE + 50;
			float edge_R = -50 - (float)FIELD_EDGE + G_FTG()->GetEdgeRight ();
			float x = m_btlPrm.GetPos().x;
			DBGOUT_WND_F ( DBGOUT_0, U"edge_R = {}, 2p_x = {}, edge_R = {}"_fmt( edge_L, x, edge_R ) );
			float base_x = G_FTG()->GetPosMutualBase().x;
			DBGOUT_WND_F ( DBGOUT_1, U"base_x = {}"_fmt( base_x ) );
		}
#endif // 0

		//条件：壁到達のブランチをチェック
		s3d::String ActionName = Check_TransitAction_Condition_str ( BRC_WALL );
		if ( ActionName.compare ( U"" ) != 0 )
		{
#if 0
			//壁位置
			float wall_L = (float)FIELD_EDGE + G_FTG()->GetWallLeft ();
			float wall_R = G_FTG()->GetWallRight () - (float)FIELD_EDGE;

			//壁位置に達していたら
			bool b_R = wall_R <= m_btlPrm.GetPos().x;
			bool b_L = m_btlPrm.GetPos().x <= wall_L;
#endif // 0
			//画面端位置
			float edge_L = G_FTG()->GetEdgeLeft () + (float)FIELD_EDGE + 50;
			float edge_R = -50 - (float)FIELD_EDGE + G_FTG()->GetEdgeRight ();


			//壁位置に達していたら
			bool b_L = m_btlPrm.GetPos().x <= edge_L;
			bool b_R = edge_R <= m_btlPrm.GetPos().x;

			if ( b_L || b_R )
			{
				//特定アクションの分岐
				bool b0 = m_pAction->IsName ( U"壁まで吹き飛び" );
				bool b1 = m_pAction->IsName ( U"壁まで吹き飛び持続" );
				if ( b0 || b1 )
				{
					//相手も遷移
					//壁割後ホーミング移動
					m_pOther.lock()->SetAction ( U"ホーミング" );

					//ステートの変更
					m_pActor->ShiftWallBreak ();
					m_pOther.lock()->m_pActor->ShiftWallBreak ();

					//グラフィックからFTG全体に反映
					m_pFtgGrp->SetWallBreak ( T );
					m_pFtgGrp->SetWB_Player ( m_btlPrm.GetPlayerID() );
				}

				SetAction ( ActionName );	//遷移
			}
		}
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
		if ( ! ExistActionName ( U"前ダッシュ開始" ) )
		{
			assert ( 0 );
		}
		if ( ! ExistActionName ( U"ボタンダッシュ開始" ) )
		{
			assert ( 0 );
		}

		bool bDash = IsNameAction ( U"前ダッシュ開始" );
		bool bBtnDash = IsNameAction ( U"ボタンダッシュ開始" );
		if ( bDash || bBtnDash )
		{
			m_btlPrm.SetDashInertial ( VEC2 ( 10.f, 0 ) );
		}
#if 0

		if ( m_pChara->GetActionID ( U"FrontDash" ) == m_actionID )
		{
			m_btlPrm.SetDashInertial ( VEC2 ( 10.f, 0 ) );
		}
		if ( m_pChara->GetActionID ( U"BackDash" ) == m_actionID )
		{
			m_btlPrm.SetDashInertial ( VEC2 ( -8.f, 0 ) );
		}

#endif // 0
		//------------------------------------------------

		//各種状態の終了
		m_btlPrm.EndAction ();
		m_frame = 0;
	}

}	//namespace GAME

