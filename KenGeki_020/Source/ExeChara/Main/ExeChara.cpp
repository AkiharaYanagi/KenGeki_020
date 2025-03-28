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

		//アクタ
		m_pActor = std::make_shared < ExeChara_Actor > ();
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
	void ExeChara::PreScriptMove () { m_pActor->PreScriptMove (); }

	//■	両者の接触判定後に攻撃・相殺・当り判定枠を設定
	void ExeChara::RectMove () { m_pActor->RectMove (); }

	//■	毎フレーム スクリプト後処理
	void ExeChara::PostScriptMove () { m_pActor->PostScriptMove (); }


	//===========================================================
	//***********************************************************
	//	Stateから呼ばれる状態別処理
	//***********************************************************
	//PreScriptMove
	//	void Input ();				//入力処理
	//	void TransitAction ();		//アクション移項
	//	void CalcPos ();			//位置計算	//ぶつかり後、位置の修正
	//	void Generate_Effect ();	//スクリプト処理 前 エフェクト生成
	//	void PreMove_Effect ();		//スクリプト処理 前 エフェクト動作

	//PostScriptMove
	//	void PostMove_Effect ();	//スクリプト処理 後 エフェクト動作
	//	void MoveTimer ();			//タイマ稼働
	//	void CheckLife ();			//ライフ判定
	//	void UpdateGraphic ();		//グラフィック更新
	//	void Sound_Play ();			//音の再生(SE, VC)
	//	void EndScript ();			//スクリプト終了、次へ移行
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
		//フレーム開始処理
		m_btlPrm.FrameInit ();

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
	//バトルパラメータ入力処理
//	void ExeChara::BtlPrm_Move_Input ()
	//-> "ExeChara_Func.cpp"

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
		m_dispChara->UpdateStateName ( m_pActor->GetStateName() );
	}

	//================================================
	//効果音(SE, VC)の再生
	//	void Sound_Play ();
	//	-> "ExeChara_Sound.cpp"


	//================================================
	//スクリプト終了、次へ移行
	//	void EndScript ();
	//	-> "ExeChara_Transit.cpp"


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

	//プレイヤインプット面表示切替
	void ExeChara::On_DispPlayerInput ()
	{
		m_dispChara->On_DispPlayerInput ();
	}
	void ExeChara::Off_DispPlayerInput ()
	{
		m_dispChara->Off_DispPlayerInput ();
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

		if ( Is1P () )
		{
	//		UINT frame = GetpScript()->GetFrame ();
			DBGOUT_WND_F ( DBGOUT_1, U"TransitAction: m_frame = {}"_fmt( m_frame ) );
		}


		//------------------------------------------------
		//	特殊アクション指定
		SpecialAction ();

		if ( Is1P () )
		{
	//		UINT frame = GetpScript()->GetFrame ();
			DBGOUT_WND_F ( DBGOUT_2, U"TransitAction: m_frame = {}"_fmt( m_frame ) );
		}

		//------------------------------------------------
		//スクリプトからのパラメータ反映
		SetParamFromScript ();



		if ( Is1P () )
		{
	//		UINT frame = GetpScript()->GetFrame ();
			DBGOUT_WND_F ( DBGOUT_3, U"TransitAction: m_frame = {}"_fmt( m_frame ) );
		}

	}


	//スクリプトからパラメータに反映する
	void ExeChara::SetParamFromScript ()
	{
		if ( m_btlPrm.GetPlayerID () == PLAYER_ID_1 )
		{
			DBGOUT_WND_F ( DBGOUT_8, U"y = {}"_fmt( m_btlPrm.GetPos().y ) );
		}

		//------------------------------------------------
		//アクションとスクリプトをバトルパラメータに渡す
		m_btlPrm.Update ( m_pAction, m_pScript );

		//------------------------------------------------
		//直接ダメージ処理
		int drctDmg = m_pScript->m_prmBattle.DirectDamage;
		if ( drctDmg != 0 )
		{

			if ( IsNameAction ( U"超必殺Bヒット" ) )
			{
				bool b = m_pOther.lock()->IsNameAction ( U"烈堂_超必Bやられ" );
				if ( ! b )
				{
					drctDmg /= 10;
				}
			}

#if 0
#endif // 0

			m_pOther.lock()->m_btlPrm.OnDamage ( - drctDmg );

			//自分の連続ヒットダメージ数
			m_btlPrm.AddChainDamage ( drctDmg );


			OnDamaged_After ();	//白ダメージ判定
		}

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

		//振動
		UINT vibration = m_pScript->m_prmStaging.Vibration;
		if ( vibration > 0 )
		{
			m_pFtgGrp->StartVibration ( vibration );
		}

		//------------------------------------------------
		//スクリプトからの停止
		//	タイマの状態を確認しないと同じスクリプトを調べ続けてしまう
		if ( m_pFtgGrp->IsActive_ScpStop () )
		{
			//自身の一時停止を解除
			//ShiftFightingMain ();

			//@info 解除はFTG_DM_Main::Do()で行う
		}
		else
		{
			//一時停止状態でないとき

			//スクリプトから値を取得
			UINT scpStop = m_pScript->m_prmStaging.Stop;
			m_btlPrm.SetScpStop ( scpStop );

			//0でないとき
			if ( scpStop > 0 )
			{
				//全体グラフィックに値を指定する
				m_pFtgGrp->StartScpStop ( scpStop );

				//相手にも時間を指定する
				m_pOther.lock ()->m_btlPrm.SetScpStop ( scpStop );

				//互いに時間停止ステートにシフト
				ShiftScpStop ();
				m_pOther.lock ()->ShiftScpStop ();
			}
		}

	}
#if 0

	void ExeChara::RestoreScpStop ()
	{
		m_actor.RestoreScpStop ();
	}

#endif // 0


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
		//操作切換
		//m_pCharaInput = m_pCPUInput;
		m_pCharaInput = m_pNewCPUInput;
		//表示切換
		m_dispChara->SetControl_CPU ();
	}

	void ExeChara::ControlPlayer ()
	{
		//操作切換
		m_pCharaInput = m_pPlayerInput;
		//表示切換
		m_dispChara->SetControl_PLAYER ();
	}


	bool ExeChara::IsThrow () const
	{
		//カテゴリ
		if ( m_pAction->GetCategory () == AC_THROW ) { return T; }
		
		//または攻撃状態かつブランチ条件にTHRを持つ
		bool bThrI = Have_TransitAction_Condition ( BRC_THR_I );
		bool bThrE = Have_TransitAction_Condition ( BRC_THR_E );
		return bThrI || bThrE;
	}

	//アクション移行(条件チェック) 存在したらT
	bool ExeChara::Have_TransitAction_Condition ( BRANCH_CONDITION brc_cnd ) const
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
				//存在したらT
				if ( brc_cnd == vpBranch [ id ]->GetCondition () ) { return T; }
			}
		}
		return F;
	}


	void ExeChara::EndBattle ()
	{
		ResetRect ();
		m_dispChara->EndBattle ();
	}


}	//namespace GAME

