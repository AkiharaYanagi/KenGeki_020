//		DBGOUT_WND_F ( 6, _T ( "scriptRead_Time = %d, Document_Time = %d, DtoC_Time = %d, LoadImage_Time = %d" ), t0, t1, t2, t3 );
//=================================================================================================
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
	ExeChara::ExeChara ( PLAYER_ID m_playerID )
	{
		//キャラデータ生成
		m_pChara = std::make_shared < Chara > ();	//キャラデータ実体
//		m_charaRect = make_shared < CharaRect > ();	//実効枠
		m_btlPrm.SetPlayerID ( m_playerID );	//バトルパラメータ

		//表示
		m_dispChara = std::make_shared < DispChara > ();
//		m_dispChara->LoadPlayer ( m_playerID );	//表示(1P/2P側による位置)
		AddpTask ( m_dispChara );

#if 0
		//エフェクト監理
		m_oprtEf = make_shared < OperateEffect > ();
		AddpTask ( m_oprtEf );
#endif // 0
	}

	//デストラクタ
	ExeChara::~ExeChara ()
	{
	}

	//基本タスク関数
	void ExeChara::Move ()
	{
#if 0
		m_tmrSlow.Move ();	//タイマ手動
#endif // 0
		TASK_VEC::Move ();
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

#if 0

	//■	毎フレーム スクリプト前処理
	void ExeChara::PreScriptMove () { m_actor.PreScriptMove (); }

	//■	両者の接触判定後に攻撃・相殺・当り判定枠を設定
	void ExeChara::RectMove () { m_actor.RectMove (); }

	//■	毎フレーム スクリプト後処理
	void ExeChara::PostScriptMove () { m_actor.PostScriptMove (); }
#endif // 0


	void ExeChara::PreScriptMove () {}
	void ExeChara::RectMove () {}
	void ExeChara::PostScriptMove () {}

#if 0

	//各処理で何を行い、何を飛ばすかはアクタがステートによって指定する
	
	//===========================================================
	//***********************************************************
	//	Stateから呼ばれる状態別処理
	//***********************************************************
	//	void Input ();			//入力処理
	//	void TransitAction ();	//アクション移項
	//	void CalcPos ();		// 位置計算		//ぶつかり後、位置の修正
	//	void CheckLife ();		//ライフ判定
	//	void UpdateGraphic ();	//グラフィック更新
	//	void PreMove_Effect ();		//スクリプト処理 前 エフェクト動作
	//	void PostMove_Effect ();	//スクリプト処理 後 エフェクト動作
	//	void MoveTimer () { m_btlPrm.TimerMove (); }		//タイマ稼働
	//===========================================================

	//================================================
	//入力処理
	void ExeChara::Input ()
	{
		//入力の更新
		m_pCharaInput->Update ( GetDirRight () );
	}

	//================================================
	// アクション移項(条件:コマンド, アクション終了)
	void ExeChara::TransitAction ()
	{
		assert ( nullptr != m_pAction && nullptr != m_pScript );

		//-----------------------------------------------------
		// のけぞり時間はコマンドによる行動不可
		if ( m_btlPrm.GetTmr_Lurch ()->IsActive () ) { return; }

		//-----------------------------------------------------
		// コマンドによる分岐
		if ( TranditAction_Command () )
		{
			//分岐が成立していたら以降はチェックしない
			return;
		}

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


		if ( m_playerID == PLAYER_ID_1 )
		{
			DBGOUT_WND_F ( 8, _T ( "tmrSlow.m_count = %d" ), m_tmrSlow.GetCount () );
		}


		//スロウのとき
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

#if 0
		//-----------------------------------------------------
		//現在スクリプトが現在アクションにおける最終フレーム ならば
		if ( m_pAction->IsOverScript ( m_frame ) )
		{
			EndAction ();	//アクション終了処理
			ExeScript ();	//スクリプト通常処理

			//スクリプト遷移時に１つ進める
			++ m_frame;
			return;			//終了
		}

		//-----------------------------------------------------
		// スクリプト通常処理
		ExeScript ();

		//通常処理：スクリプトを１つ進める
		++ m_frame;
#endif // 0
	}

	//================================================
	// 位置計算
	void ExeChara::CalcPos ()
	{
		m_btlPrm.CalcBalance ( m_pScript );	//バランス処理
		m_btlPrm.CalcPos ( m_pScript );		//位置計算
		m_btlPrm.Landing ();	//着地
	}

	//================================================
	//エフェクト
	void ExeChara::PreMove_Effect ()
	{
		m_oprtEf->PreMove ( m_pScript, m_btlPrm );
	}

	void ExeChara::PostMove_Effect ()
	{
		m_oprtEf->PostMove ( m_btlPrm );

		//サウンドエフェクト
	}

	//================================================
	//ライフ判定
	void ExeChara::CheckLife ()
	{
		//自分がライフ０
		if ( 0 >= m_btlPrm.GetLife () )
		{
			//ダウン状態に強制変更
			SetAction ( _T("Demo_Down") );
			m_btlPrm.GetTmr_Down ()->Start ();
#if 0
			//test
			//ライフを戻して続行
			m_btlPrm.SetLife ( 10000 );
#endif // 0
		}

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

#endif // 0


	//グラフィック更新
	void ExeChara::UpdateGraphic ()
	{
#if 0
		m_dispChara->Update ( m_pAction, m_pScript, m_btlPrm, m_pCharaInput );
#endif // 0
		m_dispChara->Update ();
	}

#if 0
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

	//================================================
	//	外部からの状態(State)変更
	//================================================
	void ExeChara::RevertSlow ()
	{
		m_tmrSlow.Init ();
		m_actor.ShiftFighting ();
	}

	//================================================
	//	内部関数
	//================================================


	//==================================================
	//スクリプト通常処理
	//==================================================
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
#endif // 0

	//スクリプトからパラメータを反映する
	void ExeChara::SetParamFromScript ()
	{
		//------------------------------------------------
		//アクションとスクリプトをパラメータに渡す
		m_btlPrm.Update ( m_pAction, m_pScript );

		//------------------------------------------------
		//暗転
		m_btlPrm.SetBlackOut ( m_pScript->m_prmStaging.BlackOut );

		//------------------------------------------------
		//スクリプト停止
		if ( ! m_btlPrm.GetTmr_Stop ()->IsActive () )
		{
			//スクリプトからの停止
			m_btlPrm.SetScpStop ( m_pScript->m_prmStaging.Stop );
		}
	}

#if 0
	//====================================================================================

	//-------------------------------------------------------------------------------------------------
	//EfPart重なり
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
		m_dispChara->SetControl_CPU ();
	}

	void ExeChara::ControlPlayer ()
	{
		m_pCharaInput = m_pPlayerInput;
		m_dispChara->SetControl_PLAYER ();
	}

#if 0
	void ExeChara::SetwpFighting ( WP_FTG wp )
	{
		//mwp_fighting = wp;
	}
#endif // 0


#endif // 0


}	//namespace GAME

