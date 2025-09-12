//=================================================================================================
//
//	ExeChara_OnDamaged
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "ExeChara_OnDamaged.h"
#include "../Main/ExeChara.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	ExeChara_OnDamaged::ExeChara_OnDamaged ( BtlParam & btlPrm )
		: m_btlPrm ( btlPrm )
	{
	}

	ExeChara_OnDamaged::~ExeChara_OnDamaged ()
	{
	}

	void ExeChara_OnDamaged::SetEnvironment ( WP_ExeChara pSelf, WP_ExeChara pOther )
	{
		m_pSelf = pSelf;
		m_pOther = pOther;
	}

	void ExeChara_OnDamaged:: SetpParam ( P_Param p )
	{
		m_pParam = p;
	}


	//イベント：被ダメージ時
	void ExeChara_OnDamaged::OnDamaged ()
	{
		P_ExeChara pSelf  = m_pSelf .lock ();		//自分
		P_ExeChara pOther = m_pOther.lock ();		//相手

		//自スクリプト
		P_Script pScpOther = pOther->GetpScript ();

		//相手パラメータ
		BtlParam& btlPrmOhter = pOther->GetrBtlPrm ();

		//-------------------------------------------------
		//当て身成立
#if 0
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
		//ガード判定とガード成立時処理
		bool bGuard = CheckGuard ();

		if ( bGuard )
		{
			//ガード成立時、分岐しない
			//pOther->m_nameChangeMine = U"ノーリアクション";
			pOther->SetNameChangeMine ( U"ノーリアクション" );
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
			btlPrmOhter.IncChainHitNum ();
		}

		//-------------------------------------------------
		//ダメージ処理
		int damage = pScpOther->m_prmBattle.Power;
//		m_btlPrm.AddLife ( - damage );
		//int pre_dmg = damage;

		//-------------------------------------------------
		//ヒット数補正
		UINT chain = btlPrmOhter.GetChainHitNum ();
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
		float throwRvs = btlPrmOhter.GetReviseThrow ();
		if ( pOther->IsThrow () )
		{
			//補正を保存
			throwRvs = 0.5f;
			btlPrmOhter.SetReviseThrow ( throwRvs );
		}

		//-------------------------------------------------
		//特殊補正（今回の仮定ダメージが超えたとき）
		//49.9% -> 45%補正
		int32 chainDamage = btlPrmOhter.GetChainDamage ();
		float d_45 = 1.f;
		if ( damage + chainDamage > 4500 )
		{
			//相手のヒット数で補正増加
			UINT hitnum = m_pOther.lock()->GetBtlPrm().GetChainHitNum ();

			if ( hitnum < 100 )
			{
				d_45 = 0.01f * ( 100 - (float)hitnum );
			}
			else
			{
				d_45 = 0.01f;
			}
		}
		//-------------------------------------------------
		//超必殺補正
		float rev_od = btlPrmOhter.GetReviseOverDrive ();
		//-------------------------------------------------
#if 0
		//--------------------------------------------
		//ダメージをライフによって補正(根性値)
		int lf = m_btlPrm.GetLife ();
		if ( lf < LIFE_MAX * 0.5f )
		{
			damage = (int)( damage * ( 0.001f * ( 0.5f * LIFE_MAX + lf ) ) );
		}
#endif // 0

		//最終確定補正値
		btlPrmOhter.SetCnfmRvs ( d_revise * throwRvs * rev_od * g * d_45 );

		//-------------------------------------------------

		//最終確定値
		float confirmed_revise = btlPrmOhter.GetCnfmRvs ();
		int confirmed_damage = (int) ( confirmed_revise * damage );

		m_btlPrm.OnDamage ( - confirmed_damage );	//power は＋の値、ダメージ計算はマイナスにして加算

		//スタミナ反映（くらい時増加、ガード時減少）
		if ( bGuard )
		{
			m_btlPrm.AddBalance ( (int)( -10.f * confirmed_damage ) );
		}
		else
		{
			m_btlPrm.AddBalance ( (int)(confirmed_damage * 0.4f ) );
		}



		//◆ 相手・攻撃 → 自分・くらい
		//@info 連続ヒットダメージ数は常に加算し、相手のニュートラル状態で０に戻す
		//相手の連続ヒットダメージ数
		btlPrmOhter.AddChainDamage ( confirmed_damage );

		int32 chnDmg = btlPrmOhter.GetChainDamage ();
		if ( m_btlPrm.GetPlayerID () == PLAYER_ID_2 )	//相手
		{
			DBGOUT_WND_F ( DBGOUT_0, U"ダメージ = {}"_fmt( damage ) );
			DBGOUT_WND_F ( DBGOUT_1, U"連続ヒットダメージ = {}"_fmt( chnDmg ) );
			DBGOUT_WND_F ( DBGOUT_2, U"rev_od = {}"_fmt( rev_od ) );
		}

		//リザルト用に保存 (相手の値)
		if ( pSelf->Is1P () )
		{
			m_pParam->UpdateIfMAX_DMG ( PLAYER_ID_2, chnDmg );
		}
		else if ( pSelf->Is2P () )
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

		//マイナス処理
		if (warp < 0)
		{
			//(int)足しても０以下の場合、(uint)最低値０にする
			if (warp + HITSTOP_TIME <= 0)
			{
				stopTime = 0;
			}
			else
			{
				stopTime += warp;	//マイナスを加算
			}
		}
		else if( warp != 0 )
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



	//ガード成立かどうか
	bool ExeChara_OnDamaged::CheckGuard ()
	{
		//相手
		P_ExeChara pOther = m_pOther.lock ();
		P_Script pScpOther = pOther->GetpScript ();

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


	//ガードできる状態かどうか
	bool ExeChara_OnDamaged::CanGuard () const
	{
		P_ExeChara pSelf  = m_pSelf .lock ();		//自分
		P_ExeChara pOther = m_pOther.lock ();		//相手


		//----------------------------------------------
		// 動作中判定
		//----------------------------------------------

		//ガード硬直中は入力なしでも自動的にガード
		bool bGuard = pSelf->IsGuard ();
		if ( bGuard ) { return T; }

		//----------------------------------------------
		//空中は不可
		bool bAir = pSelf->IsAir ();
		if ( bAir ) { return F; }

		//ダメージ状態は不可
		bool bDamaged = pSelf->IsDamaged ();
		if ( bDamaged ) { return F; }

		//「相手」が投げ判定は不可
		bool bThrowCheck = pOther->IsThrowCheck ();
		if ( bThrowCheck ) { return F; }

#if 0
		//立ち状態は可能
		if ( IsStand () ) { return T; }
#endif // 0

		//特殊行動中は不可(特大攻撃、足払い、避けなど)
		bool bSkill = pSelf->IsSkill ();
		if ( bSkill ) { return F; }

		//自身の「投げ」隙は不可
		bool bThrow_self = pSelf->IsThrow ();
		if ( bThrow_self ) { return F; }

		// 攻撃中は不可
		bool bAttacking = pSelf->IsAttacking ();
		if ( bAttacking ) { return F; }


		//----------------------------------------------
		// レバー入れ判定
		//----------------------------------------------

		bool bStandGurad = F;	//立ちガード
		bool bCrouchGurad = F;	//しゃがみガード

		//※相手と逆向き
		P_CharaInput pChInp = pSelf->GetpCharaInput();
		bool bLvr4 = pChInp->IsLvr4 ();	// 後	方向が入力されているとき
		bool bLvr1 = pChInp->IsLvr1 ();	// 後下	方向が入力されているとき
		bool bLvr3 = pChInp->IsLvr3 ();	// 前下	方向が入力されているとき
		bool bLvr13 = bLvr1 || bLvr3;	// 1 or 3 入力

		bool bLvr6 = pChInp->IsLvr6 ();	// 前	方向が入力されているとき

		//相手と逆向き
		float mx = pSelf ->GetPos ().x;
		float ox = pOther->GetPos ().x;

		//ほぼ同位置のときは向きは両方
		if ( std::abs ( mx - ox ) < 5 )
		{
			bStandGurad = bLvr4 || bLvr6;
		}
		//距離が離れた通常時
		else
		{
			//左位置
			if ( mx < ox )
			{
				//右向
				if ( pSelf->GetDirRight () )
				{
					bStandGurad = bLvr4;
				}
				//左向
				else
				{
					bStandGurad = bLvr6;	//相手と逆
				}
			}
			//右位置
			else if ( ox < mx )
			{
				//右向
				if ( pSelf->GetDirRight () )
				{
					bStandGurad = bLvr6;	//相手と逆
				}
				//左向
				else
				{
					bStandGurad = bLvr4;
				}
			}
		}

		//下段は両方向
		bCrouchGurad = bLvr13;


		if ( m_btlPrm.GetPlayerID () == PLAYER_ID_1 )
		{
			DBGOUT_WND_F ( DBGOUT_5, U"p1 std {},crc {}"_fmt ( bStandGurad, bCrouchGurad ) );
		}
		if ( m_btlPrm.GetPlayerID () == PLAYER_ID_2 )
		{
			DBGOUT_WND_F ( DBGOUT_6, U"p1 std {},crc {}"_fmt ( bStandGurad, bCrouchGurad ) );
		}



		//--------------------------------------------------------
		//足払いのみ下段
		bool bUnder = pOther->IsNameAction ( U"足払い初撃" );
		if ( bUnder )
		{
			if ( bCrouchGurad )
			{
				return T;
			}
			else
			{
				//しゃがみガードでなければヒット
				return F;
			}
		}

		//空中攻撃は中段
		bool bUpper = pOther->IsAir ();

		if ( bUpper )
		{
			// 立ちガード かつ しゃがみガード ではない
			if ( bStandGurad && ! bCrouchGurad )
			{
				return T;
			}
			else
			{
				//立ちガードでなければヒット
				return F;
			}
		}


		//他一般の両ガード　上段
		if ( bStandGurad || bCrouchGurad )
		{
			return T;
		}
		//--------------------------------------------------------


		return F;
	}


	//ガード成立後の処理
	void ExeChara_OnDamaged::OnGuard ()
	{
		//相手
		P_ExeChara pOther = m_pOther.lock ();
		P_Script pScpOther = pOther->GetpScript ();

		//-------------------------------------------------
		//アクション変更
		s3d::String guard_Name = U"ガード小";

		int32 guard_id = 0;

		//相手の強度によって変化
		bool bM = pOther->IsAttack_M ();
		bool bH = pOther->IsAttack_H ();
		if ( bM || bH ) { guard_id = 1; }


		bool bSk = pOther->IsSkill ();
		bool bSp = pOther->IsSpecial ();
		bool bOd = pOther->IsOverdrive ();
		if ( bSk || bSp || bOd ) { guard_id = 2; }


		switch ( guard_id )
		{
		case 0: guard_Name = U"ガード小"; break;
		case 1: guard_Name = U"ガード中"; break;
		case 2: guard_Name = U"ガード大"; break;
		}

		//相手の「相手の変更先アクション」を指定 (1周して自分のアクション)
		pOther->SetNameChangeOther ( guard_Name );


		//-------------------------------------------------
		//ガード時相手からのノックバック処理
		float recoil_e = 0.1f * pScpOther->m_prmBattle.Recoil_E;	// 値は (float) = (int)1/10
		if ( recoil_e != 0 )
		{
			m_btlPrm.SetAccRecoil ( recoil_e );
		}


	}

#if 0
	//相手ダメージ処理の後
	void ExeChara_OnDamaged::OnDamaged_After ()
	{
		P_ExeChara pSelf  = m_pSelf .lock ();	//自分
		P_ExeChara pOther = m_pOther.lock ();		//相手

		//-----------------------------------------------------
		//特殊アクションカテゴリ指定
		//ver 0.13 投げを追加
		if ( pSelf->IsSpecial () || pSelf->IsOverdrive () || pSelf->IsThrow () )
		{
			//必殺・超必殺時に相手の白ダメージ確定
			pOther->DecisionWhiteDamage ();
		}

	}
#endif // 0



}	//namespace GAME

