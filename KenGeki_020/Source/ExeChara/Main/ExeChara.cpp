﻿//=================================================================================================
//
// エグゼキャラ　ソースファイル
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
	//===========================================================
	//コンストラクタ
	ExeChara::ExeChara ( PLAYER_ID m_playerID )
	{
		//キャラデータ生成
		m_pChara = std::make_shared < Chara > ();	//キャラデータ実体
		m_btlPrm.SetPlayerID ( m_playerID );	//バトルパラメータ
		m_charaRect = std::make_shared < CharaRect > ();	//実効枠

		//表示
		m_dispChara = std::make_shared < DispChara > ();
		m_dispChara->LoadPlayer ( m_playerID );	//表示(1P/2P側による位置)
		AddpTask ( m_dispChara );

		//エフェクト監理
		m_oprtEf = std::make_shared < OperateEffect > ();
		AddpTask ( m_oprtEf );

		//エフェクト剣撃走破
		m_efSouha = std::make_shared < EfSouha > ();
		AddpTask ( m_efSouha );
		GRPLST_INSERT ( m_efSouha );
	}

	//デストラクタ
	ExeChara::~ExeChara ()
	{
	}


	//===========================================================
	//***********************************************************
	//	毎フレームMutualCharaから呼ばれる主なスクリプト処理関数の一連
	//***********************************************************
	//	↓ 処理順番
	//	void ExeChara::PreScriptMove ();	//	スクリプト前処理
	//	//void MutualChara::Collision ();	//	相互判定 (接触枠)
	//	void ExeChara::RectMove ();			//	ぶつかり後、判定枠を設定
	//	//void MutualChara::Decision ();	//	相互判定 (攻撃枠、ヒット枠)
	//	void ExeChara::PostScriptMove ();	//	スクリプト後処理
	//===========================================================
	//各処理で何を行い、何を飛ばすかはアクタがステートによって指定する


	//■	毎フレーム スクリプト前処理
	void ExeChara::PreScriptMove () { m_actor.PreScriptMove (); }

	//■	両者の接触判定後に攻撃・相殺・当り判定枠を設定
	void ExeChara::RectMove () { m_actor.RectMove (); }

	//■	毎フレーム スクリプト後処理
	void ExeChara::PostScriptMove () { m_actor.PostScriptMove (); }


	//===========================================================
	//***********************************************************
	//	Stateから呼ばれる状態別処理
	//***********************************************************
	//PreScriptMove
	//	void Input ();			//入力処理
	//	void TransitAction ();	//アクション移項
	//	void CalcPos ();		// 位置計算		//ぶつかり後、位置の修正
	//	voidGenerate_Effect ()
	//	void PreMove_Effect ();		//スクリプト処理 前 エフェクト動作

	//PostScriptMove
	//	void PostMove_Effect ();	//スクリプト処理 後 エフェクト動作
	//	void MoveTimer () { m_btlPrm.TimerMove (); }		//タイマ稼働
	//	void CheckLife ();		//ライフ判定
	//	void UpdateGraphic ();	//グラフィック更新
	//	void SE_Play ();
	//===========================================================


	//================================================
	//入力処理
	void ExeChara::Input ()
	{
		//入力の更新
		m_pCharaInput->Update ( GetDirRight () );
	}

	//================================================
	//アクションの移項
	//	void TransitAction ();
	//	-> "ExeChara_Transit.cpp"

	//================================================
	// 位置計算
	void ExeChara::CalcPos ()
	{
		m_btlPrm.CalcBalance ( m_pScript );	//バランス処理
		m_btlPrm.CalcPos ( m_pScript );		//位置計算
		m_btlPrm.Landing ();	//着地
	}

	//================================================
	//エフェクト スクリプト生成
	void ExeChara::Generate_Effect ()
	{
		m_oprtEf->Generate ( m_pScript, m_btlPrm );

		//通常時はGenerate()後に生成フラグを解除する
		m_oprtEf->SetbGnrt ( F );
	}

	//エフェクト スクリプト生成１回のみ
	void ExeChara::Generate_Effect_once ()
	{
		m_oprtEf->Generate ( m_pScript, m_btlPrm );
		//通常時はGenerate()後に生成フラグを解除するが、
		//一時停止中など１回のみは解除しない
	}

	//エフェクト スクリプト処理 前
	void ExeChara::PreMove_Effect ()
	{
		m_oprtEf->PreMove ( m_pScript, m_btlPrm );
	}

	//================================================
	//エフェクト スクリプト処理 後
	void ExeChara::PostMove_Effect ()
	{
		m_oprtEf->PostMove ( m_btlPrm );
	}

	//================================================
	//タイマ稼働
	void ExeChara::MoveTimer ()
	{
		m_btlPrm.TimerMove ();
	}

	//================================================
	//ライフ判定
	void ExeChara::CheckLife ()
	{
#if 0
		//自分がライフ０
		if ( 0 >= m_btlPrm.GetLife () )
		{
			//ダウン状態に強制変更
			SetAction ( _T("敗北ダウン浮き") );
			m_btlPrm.GetTmr_Down ()->Start ();
#if 0
			//test
			//ライフを戻して続行
			m_btlPrm.SetLife ( 10000 );
#endif // 0
		}
#endif // 0

		//-----------------------------------------
		//ライフによるバランスゲージ増分
		// L=100 -> B= 50,
		// L= 50 -> B= 75,
		// L=  0 -> B=100,
		int life = m_btlPrm.GetLife ();
		int b_max = BALANCE_START + ( LIFE_MAX - life ) / 2;
		m_btlPrm.SetBalanceMax ( b_max );
	}




	//====================================================================================
	//グラフィック更新
	void ExeChara::UpdateGraphic ()
	{
		m_dispChara->Update ( m_pAction, m_pScript, m_btlPrm, m_pCharaInput );
		m_dispChara->UpdateStateName ( m_actor.GetStateName() );
	}

	//サウンドエフェクトの再生
	void ExeChara::SE_Play ()
	{
		//一時停止中は１回のみ
		if ( m_btlPrm.GetFirstSE () ) { return; }
		
		//ヒットストップ中は除く
		if ( m_btlPrm.GetTmr_HitStop()->IsActive () )
		{
			return;
		}

		//スクリプトから名前で指定
		//SE
		const s3d::String se_name =  m_pScript->m_prmStaging.SE_Name;
		if ( se_name.compare ( U"" ) != 0 )
		{
			SND_PLAY_ONESHOT_SE ( se_name );		//名前から再生
		}

		//VC
		PlayVoice ( m_pScript->m_prmStaging.VC_Name );

		//再生フラグをOn (CharaStateでOff)
		m_btlPrm.SetFirstSE ( T );
	}

	//ボイスの再生指定
	void ExeChara::PlayVoice ( const s3d::String & vc_name )
	{
		//空欄は何もしない
		if ( vc_name.compare ( U"" ) == 0 ) { return; }

		//被ダメ時はランダムに飛ばす
		if ( IsDamaged () )
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


	//====================================================================================

	//入力表示切替
	void ExeChara::OnDispInput ()
	{
		m_dispChara->OnInput ();
	}
	void ExeChara::OffDispInput ()
	{
		m_dispChara->OffInput ();
	}

	//最前面表示切替
	void ExeChara::OnFrontEnd ()
	{
		m_dispChara->OnFrontEnd ();
	}
	void ExeChara::OffFrontEnd ()
	{
		m_dispChara->OffFrontEnd ();
	}

#if 0
	//================================================
	//	外部からの状態(State)変更
	//================================================
	void ExeChara::RevertSlow ()
	{
		m_tmrSlow.Init ();
		m_actor.ShiftFighting ();
	}

#endif // 0
	//================================================
	//	内部関数
	//================================================


	//==================================================
	//スクリプト通常処理
	//==================================================
	//アクションの移項
	//	void TransitAction ();
	//	-> "ExeChara_Transit.cpp"

	void ExeChara::ExeScript ()
	{
		//------------------------------------------------
		//このフレームでスクリプトを処理するため、移行先アクションとスクリプトを保存
		//今回のフレーム中はm_pActionとm_pScriptを用い、
		//これ以降はm_actionIDとm_frameを用いない
		m_pAction = m_pChara->GetpAction ( m_actionID );
		m_pScript = m_pAction->GetpScript ( m_frame );

		//------------------------------------------------
		//	特殊アクション指定
		SpecialAction ();

		//------------------------------------------------
		//スクリプトからのパラメータ反映
		SetParamFromScript ();
	}


	//スクリプトからパラメータに反映する
	void ExeChara::SetParamFromScript ()
	{
		//------------------------------------------------
		//アクションとスクリプトをバトルパラメータに渡す
		m_btlPrm.Update ( m_pAction, m_pScript );

		//------------------------------------------------
		//	全体演出
		//------------------------------------------------
		//暗転
		UINT blackOut = m_pScript->m_prmStaging.BlackOut;
		if ( blackOut > 0 )
		{
			//全体グラフィックに値を指定する
			m_pFtgGrp->StartBlackOut ( blackOut );
		}

		//------------------------------------------------
		//スクリプトからの停止
		//	タイマの状態を確認しないと同じスクリプトを調べ続けてしまう
		if ( ! m_pFtgGrp->IsActive_ScpStop () )
		{
			UINT scpStop = m_pScript->m_prmStaging.Stop;
			m_btlPrm.SetScpStop ( scpStop );
			if ( scpStop > 0 )
			{
				//全体グラフィックに値を指定する
				m_pFtgGrp->StartScpStop ( scpStop );

				//互いに時間停止ステートにシフト
				ShiftScpStop ();
				m_pOther.lock ()->ShiftScpStop ();
			}
		}

	}

	//====================================================================================

	//-------------------------------------------------------------------------------------------------
	//EfPart重なり
#if 0
	void ExeChara::OverEfPart ()
	{
#if 0
		//1p2p同時重なりは両方が取得

		//当り枠を取得
		PV_RECT pvHRect = GetpCharaRect ()->GetpvHRect ();

		//EF側の点集合を取得
		std::vector < PrmEfPart > & vPrm = m_efPart->Getrv_Prm ();

		//重なり判定
		UINT count = 0;
		UINT i = 0;
		for ( PrmEfPart prm : vPrm )
		{
			if ( 0 != prm.m_count ) { continue; }

			if ( prm.m_pOb->GetValid () )
			{
				for ( const RECT & rect : ( *pvHRect ) )
				{
					//重なっていたとき
					if ( OverlapPoint ( prm.m_pos, rect ) )
					{
						vPrm [ i ].m_gotten = T;
						++ count;
						break;	//RECTのループを抜け、EfPartの点を続行
					}
				}
			}

			++ i;
		}

		m_btlPrm.AddMana ( 100 * count );
#endif // 0
	}


#endif // 0


	//-------------------------------------------------------------------------------------------------
	//トレーニングモード初期化
	void ExeChara::TrainingInit ()
	{
		Init ();
		m_btlPrm.TrainingInit ();
	}


	//CPU操作切替
	void ExeChara::ControlCPU ()
	{
		m_pCharaInput = m_pCPUInput;
		//m_dispChara->SetControl_CPU ();
	}

	void ExeChara::ControlPlayer ()
	{
		m_pCharaInput = m_pPlayerInput;
		//m_dispChara->SetControl_PLAYER ();
	}




}	//namespace GAME

