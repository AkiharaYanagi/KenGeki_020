﻿//=================================================================================================
//
// エグゼキャラ Sound　ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "ExeChara.h"
#include "../../GameMain/SoundConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//音の再生
	void ExeChara::SoundPlay ()
	{
		SE_Play ();
		VC_Play ();
	}


	//-------------------------------------------------------------------
	//サウンドエフェクトの再生
	void ExeChara::SE_Play ()
	{
		//空欄は何もしない
		if ( m_pScript->m_prmStaging.SE_Name.compare ( U"" ) == 0 ) { return; }

//		DBGOUT_WND_F ( DBGOUT_0, U" FirstSE = {}"_fmt(  m_btlPrm.GetFirstSE () ? 1 : 0 ) );
//		DBGOUT_WND_F ( DBGOUT_1, U" FirstSE = {}"_fmt(  m_btlPrm.GetFirstSE () ? 1 : 0 ) );

		//一時停止中は１回のみ
		if ( m_btlPrm.GetFirstSE () )
		{
			return;
		}
		
		//ヒットストップ中(同一スクリプト)は１回のみ
		P_Timer pTmr_HitStop = m_btlPrm.GetTmr_HitStop();
		if ( pTmr_HitStop->IsActive () )
		{
			//初回は鳴らす
			if ( ! m_btlPrm.GetFirstSE_HS () )
			{
				//フラグをオン
				m_btlPrm.SetFirstSE_HS ( T );
			}
			else
			{	//途中は何もしない
				return;
			}
		}
		else
		{
			//終了時に解除
			m_btlPrm.SetFirstSE_HS ( F );
		}
		if ( m_btlPrm.GetPlayerID() == PLAYER_ID_1 )
		{
			UINT n = m_pScript->GetFrame ();
			bool b = m_btlPrm.GetFirstSE_HS ();
			DBGOUT_WND_F ( DBGOUT_7, U"{}: FirstSE_HS = {}"_fmt( n, b ) );
		}


		//スクリプトから名前で指定
		PlaySE ( m_pScript->m_prmStaging.SE_Name );

		//再生フラグをOn (CharaStateでOff)
		m_btlPrm.SetFirstSE ( T );
	}

	//SEの再生指定
	void ExeChara::PlaySE ( const s3d::String & se_name )
	{
		SND_PLAY_ONESHOT_SE ( se_name );		//名前から再生
	}


	//-------------------------------------------------------------------
	//ボイスの再生
	void ExeChara::VC_Play ()
	{
		//一時停止中は１回のみ
		if ( m_btlPrm.GetFirstVC () )
		{
			return;
		}
		
		//ヒットストップ中(同一スクリプト)は１回のみ
		P_Timer pTmr = m_btlPrm.GetTmr_HitStop();
		if ( pTmr->IsStart () )
		{
			//初回は鳴らす
		}
		else if ( pTmr->IsActive () )
		{
			//途中は何もしない
			return;
		}

		//VC再生
		PlayVoice ( m_pScript->m_prmStaging.VC_Name );

		//再生フラグをOn (CharaStateでOff)
		m_btlPrm.SetFirstVC ( T );
	}


	//ボイスの再生指定
	void ExeChara::PlayVoice ( const s3d::String & vc_name )
	{
		//空欄は何もしない
		if ( vc_name.compare ( U"" ) == 0 ) { return; }

		//被ダメ時とガード時、小攻撃はランダムに飛ばす
		bool bDamaged = IsDamaged ();
		bool bGuard = IsGuard ();
		bool bLAttack_L = IsAttack_L ();

		if ( bDamaged ||  bGuard || bLAttack_L )
		{
			//初撃は確定、連続ヒット中はランダム
			UINT hitnum = m_pOther.lock()->GetBtlPrm().GetChainHitNum ();

			if ( 1 < hitnum )
			{
				//ランダム 0-2 (30%)で再生
				//ランダム 3-9 (70%)で非再生
				int rnd = s3d::Random < int > ( 0, 9 );
				if ( 2 < rnd ) { return; }
			}
		}

		SND_PLAY_ONESHOT_VC ( vc_name );		//名前から再生
	}


}	//namespace GAME

