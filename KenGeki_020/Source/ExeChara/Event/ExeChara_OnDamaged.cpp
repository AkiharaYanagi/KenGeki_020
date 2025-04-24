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
		//特殊補正
		//49.9% -> 45%補正
		int32 chainDamage = btlPrmOhter.GetChainDamage ();
		float d_45 = 1.f;
		if ( chainDamage > 4500 )
		{
			d_45 = 0.1f;
		}
		//-------------------------------------------------
		//超必殺補正
		float rev_od = btlPrmOhter.GetReviseOverDrive ();
		//-------------------------------------------------

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
			m_btlPrm.AddBalance ( (int)( -1.f * confirmed_damage ) );
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


		//空中は不可
		bool bAir = pSelf->IsAir ();
		if ( bAir ) { return F; }

		//ダメージ状態は不可
		bool bDamaged = pSelf->IsDamaged ();
		if ( bDamaged ) { return F; }

		//相手が投げ判定は不可
		bool bThrow = pOther->IsThrow ();
		if ( bThrow ) { return F; }

#if 0
		//立ち状態は可能
		if ( IsStand () ) { return T; }
#endif // 0

		//----------------------------------------------------
		// レバー入れ判定
		P_CharaInput pChInp = pSelf->GetpCharaInput();
		bool bLvr4 = pChInp->IsLvr4 ();	//後方向が入力されているとき
		bool bLvr1 = pChInp->IsLvr1 ();	// 後下 方向が入力されているとき
		bool bLvr3 = pChInp->IsLvr3 ();	// 前下 方向が入力されているとき
		bool bLvr13 = bLvr1 || bLvr3;	// 1 or 3 入力

		//足払いのみ下段
		bool bUnder = pOther->IsNameAction ( U"足払い初撃" );
		if ( bUnder )
		{
			if ( bLvr13 )
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
			// 4入力 かつ 1ではない
			if ( bLvr4 && ! bLvr1 )
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
		if ( bLvr4 || bLvr3 )
		{
			return T;
		}


		return F;
	}


	//ガード成立後の処理
	void ExeChara_OnDamaged::OnGuard ()
	{
		//相手
		P_ExeChara pOther = m_pOther.lock ();
		P_Script pScpOther = pOther->GetpScript ();

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
		pOther->SetNameChangeOther ( gaurd_Name );


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

