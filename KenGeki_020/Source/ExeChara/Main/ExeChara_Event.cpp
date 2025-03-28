﻿//=================================================================================================
//
// エグゼキャラ　ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "ExeChara.h"
//#include "../GameMain/SoundConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//================================================
	//	外部からの状況起因関数
	//================================================

	//---------------------------------------------
	//	イベント
	//---------------------------------------------

	//ダッシュ相殺
	void ExeChara::OnDashOffset ()
	{
		m_btlPrm.AddBalance ( -1000 );
		TransitAction_Condition_I ( BRC_DASH, F );	//ダッシュ相殺・自分
	}

	//----------------------------------------------
	//相殺発生//自分：Attack, 相手：Offset
	void ExeChara::OnOffset_AO ()
	{
		m_btlPrm.OnOffset_AO ();

		//共通
		OnOffset_Common ();
	}

	//相殺発生	//自分：Offset, 相手：Attack
	void ExeChara::OnOffset_OA ()
	{
		m_btlPrm.OnOffset_OA ();

		//共通
		OnOffset_Common ();
	}

	//相殺発生	//自分：Attack, 相手：Attack
	void ExeChara::OnOffset_AA ()
	{
		//相手のパラメータで増減
		P_Script scp = m_pOther.lock ()->GetpScript ();
		int balance_e = scp->m_prmBattle.Balance_E;
		m_btlPrm.AddBalance ( balance_e );

#if 0
		//バランスアウト
		if ( m_btlPrm.GetBalance () <= 0 )
		{
			//			SetAction ( _T ( "Dotty" ) );
			SetAction ( _T ( "立ち" ) );
		}
#endif // 0

		//パラメータ
		m_btlPrm.OnOffset_AA ();

		//共通
		OnOffset_Common ();
	}

	//相殺発生	//自分：Offset, 相手：Attack
	void ExeChara::OnOffset_Common ()
	{

		//全体振動
		m_pFtgGrp->StartVibration ( 10 );



		//@todo 相殺２撃目にアサート（名前指定？）


		//キャラの持つルート,ブランチの参照
		const VP_Route vpRoute = m_pChara->GetvpRoute ();
		const VP_Branch vpBranch = m_pChara->GetvpBranch ();

		//スクリプトの持つルートリスト
		for ( UINT indexRoute : m_pScript->GetcvRouteID () )
		{
			//ルートの取得
			P_Route pRut = vpRoute [ indexRoute ];
			const V_UINT vBranchID = vpRoute [ indexRoute ]->GetcvIDBranch ();

			//対象のブランチリスト
			for ( UINT indexBranch : vBranchID )
			{
				//ブランチの取得
				P_Branch pBrc = vpBranch [ indexBranch ];

				//"条件：相殺時" 以外は飛ばす
				if ( BRC_FLG_0 != pBrc->GetCondition () ) { continue; }

				//対象アクションに移行
				UINT id = vpBranch [ indexBranch ]->GetIndexSequence ();
				SetAction ( id );
			}
		}

		//相殺キャンセル開始
		m_btlPrm.GetTmr_OfstCncl()->Start ( OFST_CNCL );
	}


	//----------------------------------------------


	//==========================================
	//◆ 自分・攻撃 -> 相手・くらい
	//ヒット発生(攻撃成立側)
	//==========================================
	void ExeChara::OnHit ()
	{
		//相手
		P_ExeChara pOther = m_pOther.lock ();

		//-----------------------------------------------------
		//ゲージ増減 (超必殺以外)
		if ( ! IsActCtg ( AC_OVERDRIVE ) )
		{
			//攻撃値を超必殺技ゲージに加算
			int p = m_pScript->m_prmBattle.Power;

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

		if ( IsThrow () )
		{
			//投げのとき、相手の状態によっては移項しない　（投げ不能状態）
			TransitAction_Condition_E ( BRC_THR_E, T );	//投げ・相手
			TransitAction_Condition_I ( BRC_THR_I, F );	//投げ・自分
		}
		else
		{
			TransitAction_Condition_E ( BRC_HIT_E, T );	//ヒット・相手
			TransitAction_Condition_I ( BRC_HIT_I, F );	//ヒット・自分
		}
		//-------------------------------------------------


		//分岐後 ヒット時処理


		//特定アクション
		if ( IsNameAction ( U"特大攻撃" ) )
		{
			m_pFtgGrp->StartVibration ( 10 );
		}


		//ノックバック
		OnKnockBack ();
		
		//-----------------------------------------------------
		//パラメータ
		m_btlPrm.OnHit ();
	}


	//自分ノックバック処理
	void ExeChara::OnKnockBack ()
	{
		// スクリプトで指定した値は (int)1/10;
		// 実効値 (float) = (float)1/10

		float recoil_i = 0.1f * m_pScript->m_prmBattle.Recoil_I;
//		float pre_rcl = recoil_i;

#if 0

		//----------------------------------------------------------
		//★★★ 剣撃対抗 (打撃時にいずれかの入力で距離離し)
		P_ExeChara pOther =  m_pOther.lock();

		bool bTaikou = pOther->m_btlPrm.GetTmr_Taikou()->IsActive ();
		if ( bTaikou )
		{
			if ( pOther->m_pCharaInput->PushSomething () )
			{
				//@info スタミナゲージ消費
				//バランス消費で移項可能かチェック

				//現在値と比較
				int balance = pOther->m_btlPrm.GetBalance ();
				const int COST = 500;
				if ( balance < COST )
				{
					//足りないとき遷移しない
				}
				else
				{
					//必要量があれば消費して遷移する
					pOther->m_btlPrm.AddBalance ( -1 * COST );

					//成立時
					recoil_i *= 10;
					recoil_i += -10;

					//成立フラグ
					pOther->m_btlPrm.SetTaikou ( T );
					//フレーム最初にFalse、以降同一フレーム処理で判定に用いる
					//主にエフェクト発生
				}
			}
		}


#endif // 0


		//距離ヒット数補正
		UINT chain = m_btlPrm.GetChainHitNum ();

//		float d_revise = 1.f + (float)chain * (float)chain * 0.1f;
		float d_revise = 1.f + (float)chain * 0.1f;
//		if ( 10 <= chain ) { d_revise *= d_revise; }	//10hit以降補正

		//超必殺のみ補正外
		if ( IsOverdrive () )
		{
			d_revise = 1.f;
		}
		recoil_i = d_revise * recoil_i;

#if 0

		if ( m_btlPrm.GetPlayerID () == PLAYER_ID_1 )
		{
			DBGOUT_WND_F ( DBGOUT_0, U"pre_rcl = {}"_fmt ( pre_rcl ) );
			DBGOUT_WND_F ( DBGOUT_1, U"rev = {}"_fmt ( d_revise ) );
			DBGOUT_WND_F ( DBGOUT_2, U"recoil_i = {}"_fmt ( recoil_i ) );
		}

#endif // 0

		//パラメータに反映
		m_btlPrm.SetAccRecoil ( recoil_i );

	}


	//投げられ判定
	bool ExeChara::CanBeThrown () const 
	{
		P_Action pAct = m_pAction;
#if 0
		//指定アクションのとき 「可能」
		if ( pAct->IsName ( _T("ダメージ小") ) ) { return T; }
		if ( pAct->IsName ( _T("ダメージ大") ) ) { return T; }
#endif // 0

		//指定アクションのとき　「不可」
		if ( pAct->IsName ( U"ガード大" ) ) { return F; }
		if ( pAct->IsName ( U"投げやられ" ) ) { return F; }

		//アクション態勢が"AP_JUMP"は「不可」
		if ( Is_AP_Jump () ) { return F; }

		//アクション属性が"AC_DAMAGED"は「不可」
		if ( IsDamaged () ) { return F; }

		//それ以外は「可能」
		return T;
	}

	//投げ判定
	bool ExeChara::IsThrowAction () const
	{
		//状態遷移に「投げ」を条件に持つものがあるとき true を返す
		UINT i = Check_TransitAction_Condition ( BRC_THR_I );
		UINT e = Check_TransitAction_Condition ( BRC_THR_E );

		return ( i != NO_COMPLETE ) || ( e != NO_COMPLETE );
	}
	

	//相殺しない判定
	bool ExeChara::IsNotOffset () const
	{
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


	//エフェクトヒット発生(攻撃成立側)
	void ExeChara::OnEfHit ()
	{
		m_btlPrm.SetHitEst ( true );		//攻撃成立フラグ
//		m_tmrHitstop->Start ();		//エフェクトはヒットストップしない
		m_btlPrm.GetTmr_HitPitch ()->Start ();
	}

	//==========================================
	//◆ 相手・攻撃 → 自分・くらい
	//くらい状態・ダメージ処理
	//==========================================
	void ExeChara::OnDamaged ()
	{
		//相手
		P_ExeChara pOther = m_pOther.lock ();

		//自スクリプト
		P_Script pScpOther = pOther->m_pScript;

#if 0
		//-------------------------------------------------
		//当て身成立
		if ( IsNameAction ( U"竜巻必殺" ) )
		{
			UINT frame = m_pScript->GetFrame ();
			if ( 5 < frame )
			{
				//SetAction ( U"当て身成立" );	//遷移
				//相手の「相手の変更先アクション」を指定
				m_pOther.lock ()->m_nameChangeOther = U"当て身成立";

				//自分
				m_btlPrm.GetTmr_HitStop ()->Start ( 30 );	//ヒットストップの設定
				//相手
				m_pOther.lock()->m_btlPrm.GetTmr_HitStop ()->Start ( 60 );	//ヒットストップの設定
			}
			return;
		}
#endif // 0

		//-------------------------------------------------
		//ガード判定
#if 0
		bool bGuard = F;
		bool bThrow = pOther->IsThrow ();

		//自身がガード可能時、かつ相手の技が投げではないとき　ガード判定開始
		if ( CanGuard () && ! bThrow )
		{
			//-------------------------------------------------
			//ガード
			bGuard = OnGuard ();
		}
#endif // 0
		bool bGuard = CheckGuard ();

		if ( bGuard )
		{
			//ガード成立時、分岐しない
			pOther->m_nameChangeMine = U"ノーリアクション";
		}

		//-------------------------------------------------
		//★★★ 剣撃対抗 (打撃時にいずれかの入力で距離離し)

		if ( ! pOther->IsOverdrive () )	//攻撃した相手が超必殺でないとき
		{
			//受付タイマをON
			m_btlPrm.GetTmr_Taikou()->Start ( TAIKOU_TIME );
		}

		//-------------------------------------------------
		//相手(攻撃側)のヒット数加算 ガード時を除く
		if ( ! bGuard )
		{
			pOther->m_btlPrm.IncChainHitNum ();
		}

		//-------------------------------------------------
		//ダメージ処理
		int damage = pScpOther->m_prmBattle.Power;
//		m_btlPrm.AddLife ( - damage );
		//int pre_dmg = damage;

		//-------------------------------------------------
		//ヒット数補正
		UINT chain = pOther->m_btlPrm.GetChainHitNum ();
		if ( chain == 1 ) { chain = 0; }		//1hit目は補正なし
		if ( chain > 100 ) { chain = 100; }		//上限100

		float d_revise = ( 100.f - (float)chain ) * 0.01f;	//%に換算
		if ( 10 <= chain ) { d_revise *= d_revise; }	//10hit以降追加補正
		if ( d_revise < 0 ) { d_revise = 0.01f; }	//０未満にはしない

		//-------------------------------------------------
		//ガード成立時のダメージ補正
		float g = bGuard ? 0.1f : 1.f;

		//-------------------------------------------------
		//特殊補正
		//相手(攻撃側)が投げ 保存した値を使う
		float throwRvs = pOther->m_btlPrm.GetReviseThrow ();
		if ( pOther->IsThrow () )
		{
			//補正を保存
			throwRvs = 0.5f;
			pOther->m_btlPrm.SetReviseThrow ( throwRvs );
		}

		//-------------------------------------------------
		//特殊補正
		//49.9% -> 45%補正
		int32 chainDamage = pOther->m_btlPrm.GetChainDamage ();
		float d_45 = 1.f;
		if ( chainDamage > 4500 )
		{
			d_45 = 0.1f;
		}
		//-------------------------------------------------
		//超必殺補正
		float rev_od = pOther->m_btlPrm.GetReviseOverDrive ();
		//-------------------------------------------------

		//最終確定補正値
		pOther->m_btlPrm.SetCnfmRvs ( d_revise * throwRvs * rev_od * g * d_45 );

		//-------------------------------------------------

		//最終確定値
		float confirmed_revise = pOther->m_btlPrm.GetCnfmRvs ();
		int confirmed_damage = (int) ( confirmed_revise * damage );

		m_btlPrm.OnDamage ( - confirmed_damage );	//power は＋の値、ダメージ計算はマイナスにして加算

		//スタミナ反映
		m_btlPrm.AddBalance ( (int)(confirmed_damage * 0.1f ) );



		//◆ 相手・攻撃 → 自分・くらい
		//@info 連続ヒットダメージ数は常に加算し、相手のニュートラル状態で０に戻す
		//相手の連続ヒットダメージ数
		pOther->m_btlPrm.AddChainDamage ( confirmed_damage );

		int32 chnDmg = pOther->m_btlPrm.GetChainDamage ();
		if ( m_btlPrm.GetPlayerID () == PLAYER_ID_2 )	//相手
		{
			DBGOUT_WND_F ( DBGOUT_0, U"ダメージ = {}"_fmt( damage ) );
			DBGOUT_WND_F ( DBGOUT_1, U"連続ヒットダメージ = {}"_fmt( chnDmg ) );
			DBGOUT_WND_F ( DBGOUT_2, U"rev_od = {}"_fmt( rev_od ) );
		}

		//リザルト用に保存 (相手の値)
		if ( Is1P () )
		{
			m_pParam->UpdateIfMAX_DMG ( PLAYER_ID_2, chnDmg );
		}
		else if ( Is2P () )
		{
			m_pParam->UpdateIfMAX_DMG ( PLAYER_ID_1, chnDmg );
		}

		//-------------------------------------------------
		//バランス処理
		int b_e = pScpOther->m_prmBattle.Balance_E;
		int bl = m_btlPrm.GetBalance ();
		m_btlPrm.SetBalance ( bl - b_e );

		//-------------------------------------------------
		//ヒットストップ

		//相手スクリプトによる追加止め時間
		P_Action pAct = pOther->GetpAction();
		P_Script pScp = pOther->GetpScript();
		UINT stopTime = HITSTOP_TIME;

		int warp = pScp->m_prmBattle.Warp;
		if( warp != 0 )
		{
			stopTime += warp;
		}


		//ガード時
		if ( bGuard )
		{
			//個別
			bool bRai0 = pOther->IsNameAction ( U"雷電蹴_1" );
			bool bKuuRai0 = pOther->IsNameAction ( U"空中雷電蹴_1" );
			bool bKuuRai1 = pOther->IsNameAction ( U"空中雷電蹴_持続" );
			if ( bRai0 || bKuuRai0 || bKuuRai1 )
			{
				m_btlPrm.GetTmr_HitStop ()->Start ( stopTime );	//ヒットストップの設定
			}
		}
		//ガード時以外(ヒット時)
		else
		{
			m_btlPrm.GetTmr_HitStop ()->Start ( stopTime );	//ヒットストップの設定
		}


		//-------------------------------------------------
		//その他　効果
		// スクリプトが進まないヒットストップ中も見るのでフラグでチェックする
//		m_btlPrm.SetFirstEf ( true );			//初回のみエフェクト発生
//		m_btlPrm.SetFirstSE ( true );			//初回のみSE発生
		//->それぞれ発生箇所でフラグ管理
	}



	//ガードできる状態かどうか
	bool ExeChara::CanGuard () const
	{
		//相手
		P_ExeChara pOther = m_pOther.lock ();

		//空中は不可
		bool bAir = IsAir ();
		if ( bAir ) { return F; }

		//ダメージ状態は不可
		bool bDamaged = IsDamaged ();
		if ( bDamaged ) { return F; }

		//相手が投げ判定は不可
		bool bThrow = pOther->IsThrow ();
		if ( bThrow ) { return F; }

#if 0
		//立ち状態は可能
		if ( IsStand () ) { return T; }
#endif // 0

		//後方向が入力されているとき
		if ( m_pCharaInput->IsLvr4 () ) { return T; }

		//後下方向が入力されているとき
		if ( m_pCharaInput->IsLvr3 () ) { return T; }


		return F;
	}


	//ガード成立かどうか
	bool ExeChara::CheckGuard ()
	{
		//相手
		P_ExeChara pOther = m_pOther.lock ();
		P_Script pScpOther = pOther->m_pScript;

		//条件判定
		if ( CanGuard () )
		{
			//ガード実行
			OnGuard ();
			return T;
		}

		//ガード不成立
		return F;
	}


	//ガード成立後の処理
	void ExeChara::OnGuard ()
	{
		//相手
		P_ExeChara pOther = m_pOther.lock ();
		P_Script pScpOther = pOther->m_pScript;

#if 0

		//-------------------------------------------------
		//ガード判定
		//後方向が入力されているとき
		//後下方向
		if ( m_pCharaInput->IsLvr4 () )
		{
			//----------------------------
			//OnHit()
			//OnDamaaged()
			// の順番なので後で変更した方が優先
			//----------------------------

			//アクション変更
//			SetAction ( U"ガード小" );
			s3d::String gaurd_Name = U"ガード小";

#if 0
			int32 gaurd_id = s3d::Random ( 2 );
#endif // 0
			static int32 gaurd_id = 0;
//			if ( ++ gaurd_id >= 3 ) { gaurd_id = 0; }

			switch ( gaurd_id )
			{
			case 0: gaurd_Name = U"ガード小"; break;
			case 1: gaurd_Name = U"ガード中"; break;
			case 2: gaurd_Name = U"ガード大"; break;
			}

			//相手の「相手の変更先アクション」を指定
			m_pOther.lock ()->m_nameChangeOther = gaurd_Name;


			//-------------------------------------------------
			//ガード時相手からのノックバック処理
			float recoil_e = 0.1f * pScpOther->m_prmBattle.Recoil_E;	// 値は (float) = (int)1/10
			if ( recoil_e != 0 )
			{
				m_btlPrm.SetAccRecoil ( recoil_e );
			}


			return T;
		}
#endif // 0

		//-------------------------------------------------
		//アクション変更
		s3d::String gaurd_Name = U"ガード小";

		int32 gaurd_id = 0;

		//相手の強度によって変化


		switch ( gaurd_id )
		{
		case 0: gaurd_Name = U"ガード小"; break;
		case 1: gaurd_Name = U"ガード中"; break;
		case 2: gaurd_Name = U"ガード大"; break;
		}

		//相手の「相手の変更先アクション」を指定 (1周して自分のアクション)
		m_pOther.lock ()->m_nameChangeOther = gaurd_Name;


		//-------------------------------------------------
		//ガード時相手からのノックバック処理
		float recoil_e = 0.1f * pScpOther->m_prmBattle.Recoil_E;	// 値は (float) = (int)1/10
		if ( recoil_e != 0 )
		{
			m_btlPrm.SetAccRecoil ( recoil_e );
		}


	}


	//相手ダメージ処理の後
	void ExeChara::OnDamaged_After ()
	{
		//-----------------------------------------------------
		//特殊アクションカテゴリ指定
		if ( IsSpecial () || IsOverdrive () || IsThrow () )
		{
			//必殺・超必殺時に相手の白ダメージ確定
			//ver 0.13 投げを追加
			m_pOther.lock()->m_btlPrm.DecisionWhiteDamage ();
		}

	}



}	//namespace GAME

