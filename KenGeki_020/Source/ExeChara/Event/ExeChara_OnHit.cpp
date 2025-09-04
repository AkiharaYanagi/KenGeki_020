//=================================================================================================
//
//	ExeChara_OnHit
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "ExeChara_OnHit.h"
#include "../Main/ExeChara.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//==========================================
	//◆ 自分・攻撃 -> 相手・くらい
	//ヒット発生(攻撃成立側)
	//==========================================
	ExeChara_OnHit::ExeChara_OnHit ( BtlParam & btlPrm )
		: m_btlPrm ( btlPrm )
	{
	}

	ExeChara_OnHit::~ExeChara_OnHit ()
	{
	}


	void ExeChara_OnHit::SetEnvironment ( WP_ExeChara pSelf, WP_ExeChara pOther )
	{
		m_pSelf = pSelf;
		m_pOther = pOther;

		m_btlPrm = pSelf.lock()->GetrBtlPrm ();
	}

	void ExeChara_OnHit:: SetpParam ( P_Param p )
	{
		m_pParam = p;
	}


	//======================================================
	//イベント：与ダメージ時
	void ExeChara_OnHit::OnHit ()
	{
		P_ExeChara pSelf = m_pSelf.lock ();		//自分
		P_ExeChara pOther = m_pOther.lock ();	//相手

		P_Script pScp = pSelf->GetpScript ();

		//-----------------------------------------------------
		//ゲージ増減 (超必殺以外)
		if ( ! pSelf->IsActCtg ( AC_OVERDRIVE ) )
		{
			//攻撃値を超必殺技ゲージに加算
			int p = pScp->m_prmBattle.Power;

			//アクセルゲージ補正 ( -1.000倍 ~ +2.000倍 )
			//( -500 ~ +1000 )
			double dp = p * 0.002f * m_btlPrm.GetAccel();

			m_btlPrm.AddMana ( (int)dp );

			//バランス固定回復
			m_btlPrm.AddBalance ( 100 );
		}


		//-----------------------------------------------------
		//避けを直前成立させるとスロウ
#if 0
		if ( m_pOther.lock()->IsNameAction ( _T ( "避け" ) ) )
		{
			if ( m_pOther.lock()->m_frame < 8 )
			{
				m_pFtgGrp->StartSlow ();

				//相手のアクション変更
				m_pOther.lock()->SetAction ( _T("避け直前成立") );

				//自身のスロウ開始
				m_actor.ShiftSlowSkip ();
				m_tmrSlow.SetValid ( T );

				//以降の処理(スクリプト変更など)を飛ばす
				return;
			}
		}
#endif // 0

		//ガード成立時、分岐しない
//		if ( pOther->CanGuard () ) { return; }

		//-----------------------------------------------------
		//条件分岐 (相手→自分でないとスクリプトが変わってしまう)

		if ( pSelf->IsThrowCheck () )
		{
			//投げのとき、相手の状態によっては移項しない　（投げ不能状態）
			pSelf->TransitAction_Condition_E ( BRC_THR_E, T );	//投げ・相手
			pSelf->TransitAction_Condition_I ( BRC_THR_I, F );	//投げ・自分
		}
		else
		{
			pSelf->TransitAction_Condition_E ( BRC_HIT_E, T );	//ヒット・相手
			pSelf->TransitAction_Condition_I ( BRC_HIT_I, F );	//ヒット・自分
		}
		//-------------------------------------------------

		//分岐後 ヒット時処理
#if 0
		//特定アクション
		if ( pSelf->IsNameAction ( U"特大攻撃" ) )
		{
			m_pFtgGrp->StartVibration ( 10 );
		}
#endif // 0

		//-------------------------------------------------
		//ノックバック
		OnKnockBack ();
		
		//-----------------------------------------------------
		//パラメータ
		m_btlPrm.OnHit ();
	}


	//自分ノックバック処理
	void ExeChara_OnHit::OnKnockBack ()
	{
		P_ExeChara pSelf = m_pSelf.lock ();		//自分
		P_ExeChara pOther = m_pOther.lock ();	//相手
		P_Script pScp = pSelf->GetpScript ();


		// スクリプトで指定した値は10倍の値なので1/10にする
		// 実効値 (float) = (float)1/10

		float recoil_i = 0.1f * pScp->m_prmBattle.Recoil_I;
//		float pre_rcl = recoil_i;

		//----------------------------------------------------------
		// 剣撃対抗 -> ExeChara_Func.cpp に移項
		
		//----------------------------------------------------------
		//画面端距離補正
		float d_side = 1.f;

		//@todo 相手のノックバック量も参照
		float self_x = pSelf->GetPos ().x;
		float other_x = pOther->GetPos ().x;
		float padding = 300;

		float left = 0 + padding;
		bool leftSide = self_x < left && other_x < left;

		float right = (float)GAME_WIDTH - padding;
		bool rightSide = right < self_x && right < other_x;

		if ( leftSide || rightSide )
		{
			d_side = 1.2f;
		}

		//----------------------------------------------------------
		//距離ヒット数補正
		UINT chain = m_btlPrm.GetChainHitNum ();

//		float d_revise = 1.f + (float)chain * (float)chain * 0.1f;
		float d_revise = 1.f + (float)chain * 0.1f;
//		if ( 10 <= chain ) { d_revise *= d_revise; }	//10hit以降補正

		//----------------------------------------------------------
		//超必殺のみ補正外
		if ( pSelf->IsOverdrive () )
		{
			d_revise = 1.f;
			d_side = 1.f;
		}
		recoil_i = d_revise * recoil_i *d_side;

#if 0
		if ( m_btlPrm.GetPlayerID () == PLAYER_ID_1 )
		{
			DBGOUT_WND_F ( DBGOUT_0, U"pre_rcl = {}"_fmt ( pre_rcl ) );
			DBGOUT_WND_F ( DBGOUT_1, U"rev = {}"_fmt ( d_revise ) );
			DBGOUT_WND_F ( DBGOUT_2, U"recoil_i = {}"_fmt ( recoil_i ) );
		}
#endif // 0

		//----------------------------------------------
		//最後に相手と逆向き修正
		float ox = pOther->GetPos ().x;
		float mx = pSelf ->GetPos ().x;

		//同位置のときは向きは持続
		if ( mx != ox )
		{
			bool bPosLeft = mx < ox;	//自身が左位置のとき
			float dir = bPosLeft ? -1.f : 1.f;	//自分の向きによらず左方向

			//絶対値に符号(向き)を乗算
			float abs = std::abs ( recoil_i );
			float recoil_dir = dir * abs;

#if 0
			if ( m_btlPrm.GetPlayerID () == PLAYER_ID_1 )
			{
				DBGOUT_WND_F ( DBGOUT_5, U"p1:recoil_i {} = {} * {}"_fmt ( recoil_dir, dir, abs ) );
			}
			if ( m_btlPrm.GetPlayerID () == PLAYER_ID_2 )
			{
				DBGOUT_WND_F ( DBGOUT_6, U"p2:recoil_i {} = {} * {}"_fmt ( recoil_dir, dir, abs ) );
			}
#endif // 0

			//保存
			recoil_i = recoil_dir;
		}
		else
		{
		//同位置のときは向きは持続
		}

		//----------------------------------------------
		//パラメータに反映
		m_btlPrm.SetAccRecoil ( recoil_i );
	}


#if 0
	//投げられ判定
	bool ExeChara_OnHit::CanBeThrown () const 
	{
		P_ExeChara pSelf = m_pSelf.lock ();		//自分
		P_ExeChara pOther = m_pOther.lock ();	//相手
		P_Action pAct = m_pSelf.lock()->GetpAction ();

#if 0
		//指定アクションのとき 「可能」
		if ( pAct->IsName ( _T("ダメージ小") ) ) { return T; }
		if ( pAct->IsName ( _T("ダメージ大") ) ) { return T; }
#endif // 0

		//指定アクションのとき　「不可」
		if ( pAct->IsName ( U"ガード大" ) ) { return F; }
		if ( pAct->IsName ( U"投げやられ" ) ) { return F; }

		//アクション態勢が"AP_JUMP"は「不可」
		if ( pSelf->Is_AP_Jump () ) { return F; }

		//アクション属性が"AC_DAMAGED"は「不可」
		if ( pSelf->IsDamaged () ) { return F; }

		//それ以外は「可能」
		return T;
	}

	//投げ判定
	bool ExeChara_OnHit::IsThrowAction () const
	{
		P_ExeChara pSelf = m_pSelf.lock ();		//自分

		//状態遷移に「投げ」を条件に持つものがあるとき true を返す
		UINT i = pSelf->Check_TransitAction_Condition ( BRC_THR_I );
		UINT e = pSelf->Check_TransitAction_Condition ( BRC_THR_E );

		return ( i != NO_COMPLETE ) || ( e != NO_COMPLETE );
	}
	
	//相殺しない判定
	bool ExeChara_OnHit::IsNotOffset () const
	{
		P_ExeChara pSelf = m_pSelf.lock ();		//自分

		//投げ
		if ( IsThrowAction () ) { return T; }

#if 0
		//超必殺
		P_Action pAct = m_pAction;
		if ( pAct->IsName ( _T("超必殺発動") ) ) { return T; }
		if ( pAct->IsName ( _T("超必B発動") ) ) { return T; }
#endif // 0

		return F;
	}
#endif // 0


	//エフェクトヒット発生(攻撃成立側)
	void ExeChara_OnHit::OnEfHit ()
	{
		P_ExeChara pSelf = m_pSelf.lock ();		//自分
		P_ExeChara pOther = m_pOther.lock ();	//相手

		//自分のエフェクトからブランチ（相手ヒット）を検索し、遷移先アクション名を取得する
		P_OprEf pOprtEf = pSelf->GetpOprEf ();
		const s3d::String& nameAction = pOprtEf->GetpExeEf_BrcHitE ();

		//-----------------------------------------------------
		m_btlPrm.SetHitEst ( true );		//攻撃成立フラグ
//		m_tmrHitstop->Start ();		//エフェクトはヒットストップしない
		m_btlPrm.GetTmr_HitPitch ()->Start ();

		//-----------------------------------------------------
		//相手の変更先アクション名を保存
		pSelf->SetNameChangeOther ( nameAction );
		
		//-------------------------------------------------
	}


}	//namespace GAME

