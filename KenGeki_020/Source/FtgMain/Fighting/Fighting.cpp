//=================================================================================================
//
//	Fighting ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Fighting.h"
#include "../FtgConst.h"	
#include "../../GameMain/G_Ftg.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	const float Fighting::BGM_X = 640 - (303 / 2);
	const float Fighting::BGM_Y = 935;


	Fighting::Fighting ()
	{
		//------------------------------------------------
		//背景
		m_bg = std::make_shared < BG > ();
		AddpTask ( m_bg );

		//=====================================================
		//キャラ (GrpLstの登録順により前面に描画される)
		m_exeChara2 = std::make_shared < ExeChara > ( PLAYER_ID_2 );
		m_exeChara1 = std::make_shared < ExeChara > ( PLAYER_ID_1 );

		m_exeChara1->SetpOther ( m_exeChara2 );
		m_exeChara2->SetpOther ( m_exeChara1 );

		AddpTask ( m_exeChara1 );
		AddpTask ( m_exeChara2 );

		//キャラ相互処理
		m_mutualChara = std::make_shared < MutualChara > ();
		AddpTask ( m_mutualChara );

		m_mutualChara->SetpChara ( m_exeChara1, m_exeChara2 );

		//=====================================================
		//デモ
		m_demoActor = std::make_shared < FtgDemoActor > ();
		m_demoActor->SetpMutualChara ( m_mutualChara );
		AddpTask ( m_demoActor );

		//Debug用　開始デモをスキップ切替
#define DEMO_ON		1
#if DEMO_ON
		m_demoSkip = F;
#else
		m_demoSkip = T;
#endif // DEMO_ON

		//=====================================================
		//画面共通グラフィック処理
		m_pFtgGrp = std::make_shared < FtgGrp > ();
		AddpTask ( m_pFtgGrp );

		//=====================================================
		//ステート名
		m_strState = std::make_shared < GrpStr > ();
		m_strState->SetStr ( U"State" );
		m_strState->SetZ ( Z_SYS );
		m_strState->SetColorF ( s3d::ColorF { 0.0f, 0.0f, 0.5f, 1.f } );
		AddpTask ( m_strState );
		GRPLST_INSERT ( m_strState );

		//=====================================================
		//タイム
		m_btlTime = std::make_shared < BattleTime > ();
		AddpTask ( m_btlTime );

		//------------------------------------------------
		//ラウンド
		m_round = std::make_shared < Round > ();
		AddpTask ( m_round );

		//------------------------------------------------
		//BGM名
		m_bgmName = std::make_shared < GameGraphic > ();
		m_bgmName->AddTexture_FromArchive ( U"Battle\\BGM_NAME_main_Gaba.png" );
		m_bgmName->AddTexture_FromArchive ( U"Battle\\BGM_NAME_main_Ouka.png" );
		m_bgmName->AddTexture_FromArchive ( U"Battle\\BGM_NAME_main_Sae.png" );
		m_bgmName->AddTexture_FromArchive ( U"Battle\\BGM_NAME_main_Retsudou.png" );
		m_bgmName->SetPos ( VEC2 ( BGM_X, BGM_Y ) );
		m_bgmName->SetZ ( Z_EFF );
		AddpTask ( m_bgmName );
		GRPLST_INSERT ( m_bgmName );



		//@todo
		// 毎フレームにアサート前にキャラ状態をテキストファイルに書出

	}

	Fighting::~Fighting ()
	{
	}


	void Fighting::ParamInit ( P_Param pParam )
	{
		m_pParam = pParam;

		m_demoActor->ParamLoad ( pParam );
		m_mutualChara->ParamInit ( pParam );
		m_exeChara1->ParamInit ( pParam );
		m_exeChara2->ParamInit ( pParam );
		m_bg->ParamInit ( pParam );
	}

	void Fighting::Load ()
	{
		m_demoActor->SetwpFighting ( shared_from_this () );
		m_demoActor->SetpFtgGrp ( m_pFtgGrp );
//		m_mutualChara->SetpFtgGrp ( m_pFtgGrp );
		m_exeChara1->SetpFtgGrp ( m_pFtgGrp );
		m_exeChara2->SetpFtgGrp ( m_pFtgGrp );

		m_bgmName->SetIndexTexture ( m_pParam->Get_BGM_ID () );

		m_strState->SetSize ( G_Font::SIZE_40 );
		m_strState->SetPos ( VEC2 ( 640 - 110, 145 ) );

		//初期値は非表示
		m_strState->SetValid ( F );

		TASK_LST::Load ();
	}

	void Fighting::Init ()
	{
		//----------------------------------------
		//基準 初期化
		TASK_LST::Init ();

		//----------------------------------------
		//初期化後
		
		//デモスキップ
		if ( m_demoSkip )
		{
			m_demoActor->StartFighting ();
		}
		else
		{
			m_demoActor->StartGreeting ();
		}

		//----------------------------------------
		m_btlTime->Init ();
	}


	void Fighting::Move ()
	{
		//--------------------------
		//デモ分岐
		//@info 一時停止をConduct_InStop()ではなくキャラステートで分類する
		m_demoActor->Do ();

		//--------------------------
		//共通グラフィック処理
		Grp ();

		//--------------------------
		TASK_LST::Move ();
	}

	void Fighting::DemoRestart ()
	{
		G_Ftg::inst()->Init ();
		m_btlTime->Init ();
		m_pFtgGrp->Init ();
		m_bg->Init ();
		m_mutualChara->TrainingInit ();

		m_demoActor->StartGreeting ();


		//BGM
//		P_Param pParam = Scene::GetpParam ();
//		P_Param pParam =  m_prmFtgDemo->GetpSceneParam();
		BGM_ID bgm_id = m_pParam->Get_BGM_ID ();
		SND_STOP_ALL_BGM ();
		SND_PLAY_LOOP_BGM ( BGM_ID_TO_NAME [ bgm_id ] );


	}

	void Fighting::TrainingRestart ()
	{
		G_Ftg::inst()->Init ();
		m_btlTime->Init ();
		m_pFtgGrp->Init ();
		m_bg->Init ();
		m_mutualChara->TrainingInit ();

		m_demoActor->StartFighting ();
	}


	//----------------------------------------------------
	//	戦闘時間
	//----------------------------------------------------

	//タイム計測開始
	void Fighting::StartTime ()
	{
		//トレーニングモードは時間計測しない
		if ( m_bTraining ) { return; }

		m_btlTime->Start ();
	}


	//時間計測初期化
	void Fighting::TimeSet ()
	{
		m_btlTime->Set ();
	}

	//タイムアップ
	void Fighting::StartTimeUp ()
	{
		DecideWinner_FromLife();

		m_exeChara1->StartTimeUp ();
		m_exeChara2->StartTimeUp ();
	}

	//タイムアップ終了待機
	void Fighting::StartEndWait ()
	{
		m_exeChara1->StartEndWait ();
		m_exeChara2->StartEndWait ();
	}

	//タイマ停止
	void Fighting::StopTimer ()
	{
		m_btlTime->Stop ();
	}


	//タイムアップによる終了
	bool Fighting::FinishCheck_TimeUp ()
	{
		return m_btlTime->IsTimeUp ();
	}

	//ライフ０による終了
	bool Fighting::FinishCheck_ZeroLife ()
	{
		//終了判定
		bool finish1p = m_exeChara1->IsZeroLife ();
		bool finish2p = m_exeChara2->IsZeroLife ();

#if 0
		//トレーニングモードは終了しない
		if ( m_bTraining )
		{
			if ( finish1p ) { m_exeChara1->Init (); }
			if ( finish2p ) { m_exeChara2->Init (); }
			return F;
		}
#endif // 0


		//どちらか、または両方ライフ０なら終了
		if ( finish1p || finish2p )
		{
			PLAYER_ID plr = _PLAYER_NUM;
			if ( finish1p && finish2p )
			{
				plr = _PLAYER_NUM;
			}
			else if ( ! finish1p && finish2p )
			{
				plr = PLAYER_ID_1;
			}
			else if ( finish1p && ! finish2p )
			{
				plr = PLAYER_ID_2;
			}
			//シーン共通パラメータ記録
			m_pParam->SetWinner ( plr );
			return T;
		}

		return F;
	}



	//残ライフで勝者決定
	void Fighting::DecideWinner_FromLife ()
	{
		//トレーニングモードは時間計測しない
		if ( m_bTraining ) { return; }

		//タイムアップ時、残り体力で勝者を決める
		int life_1 = m_exeChara1->GetBtlPrm ().GetLife ();
		int life_2 = m_exeChara2->GetBtlPrm ().GetLife ();

		//1P勝利
		if ( life_1 > life_2 )
		{
			//ラウンド加算
//			m_round->AddRound_1p ();

			//シーンパラメータに保存
			m_pParam->SetWinner ( PLAYER_ID_1 );
		}
		//2P勝利
		else if ( life_1 < life_2 )
		{
			//ラウンド加算
//			m_round->AddRound_2p ();

			//シーンパラメータに保存
			m_pParam->SetWinner ( PLAYER_ID_2 );
		}
		//引き分け
		else
		{
			//どちらもラウンド取得なし

			//シーンパラメータに保存
			m_pParam->SetWinner ( _PLAYER_NUM );	//Dra
		}
	}

		//勝利デモ移行
	void Fighting::WinnerDemo ()
	{
		//トレーニングモードは時間計測しない
		if ( m_bTraining ) { return; }

		//タイムアップ時、残り体力で勝者を決める
		int life_1 = m_exeChara1->GetBtlPrm ().GetLife ();
		int life_2 = m_exeChara2->GetBtlPrm ().GetLife ();

		//1P勝利
		if ( life_1 > life_2 )
		{
			m_exeChara1->SetAction ( U"勝利" );
			m_exeChara2->SetAction ( U"時間切れ敗北" );
		}
		//2P勝利
		else if ( life_1 < life_2 )
		{
			m_exeChara1->SetAction ( U"時間切れ敗北" );
			m_exeChara2->SetAction ( U"勝利" );
		}
		//引き分け
		else
		{
			m_exeChara1->SetAction ( U"引分" );
			m_exeChara2->SetAction ( U"引分" );
		}
	}

	bool Fighting::IsDraw () const
	{
		int life_1 = m_exeChara1->GetBtlPrm ().GetLife ();
		int life_2 = m_exeChara2->GetBtlPrm ().GetLife ();

		//ダウン時もダウンしないときもライフが同じなら引分状態
		if ( life_1 == life_2 ) { return T; }

		return F;
	}


	//=============================================================
	//	内部関数
	//=============================================================

	//共通グラフィック処理
	void Fighting::Grp ()
	{
		//----------------------------------------------------
		//@info 共通のフラグポインタを MutalChara -> ExeChara まで渡す
	 
		//---------------------------------------------------
		//キャラ位置から画面表示の基準位置(カメラ)を決定
		VEC2 pos1p = m_exeChara1->GetPos ();
		VEC2 pos2p = m_exeChara2->GetPos ();

		//共通変数に保存
		G_FTG()->CulcPosMutualBase ( pos1p, pos2p );

#if 0
		//----------------------------------------------------
		//暗転
		bool bBlackOut = m_pFtgGrp->IsActive_BlackOut ();
//		UINT blackOut = m_mutualChara->GetBlackOut ();
		if ( bBlackOut )
		{
			//m_bg->SetBlackOut ( blackOut );
			//m_mutualChara->SetBlackOut ( 0 );
			m_bg->OnBlackOut ();
		}
		else
		{
			m_bg->OffBlackOut ();
		}


		//----------------------------------------------------
		//白転
		UINT whiteOut = m_mutualChara->CheckWhiteOut () ? 60 : 0;
		if ( 0 != whiteOut )
		{
			m_bg->SetWhiteOut ( whiteOut );
			m_mutualChara->SetWhiteOut ( F );
		}

		//----------------------------------------------------
		//スロー
		if ( m_pFtgGrp->IsSlowStart () )
		{
			m_bg->SetBlackOut ( 60 );
		}

		if ( m_pFtgGrp->IsSlowLast () )
		{
			//スロウ解除
			m_bg->OffBlackOut ();
			m_mutualChara->RevertSlow ();
		}
#endif // 0

		//----------------------------------------------------
		//表示切替
//		SwitchDisp ();

		//----------------------------------------------------
		//背景通常処理
		m_bg->Grp ();


		//----------------------------------------------------
		//共通グラフィックからステートの変更
		if ( m_pFtgGrp->GetWallBreak () )
		{
			m_demoActor->Shift_Main_To_WallBreak ();
		}

		//----------------------------------------------------
		//ステート名
		m_strState->SetStr ( m_demoActor->GetName () );

	}

	void Fighting::SwitchDisp ()
	{
//		static bool bDisp = F;		//状態
//		static bool pre_bDisp = F;	//前回押しているか
//		static bool is_bDisp = F;	//今回押しているか

		//		is_bDisp0 = ( WND_UTL::AscKey ( '4' ) );
		//Asyncの判定２回目以降
		bool is_bDisp = G_FTG()->GetSysDisp ();

		//今回押した瞬間ならば、1回のみ切替
		if ( ! m_pre_bDispSys && is_bDisp )	// false -> true
		{
			if ( m_bDispSys )
			{
				OnDisp ();
			}
			else
			{
				OffDisp ();
			}
		}

		m_pre_bDispSys = is_bDisp;
	}


	void Fighting::OnDisp ()
	{
		m_btlTime->On ();
		m_round->On ();
		m_bDispSys = T;
	}

	void Fighting::OffDisp ()
	{
		m_btlTime->Off ();
		m_round->Off ();
		m_bDispSys = F;
	}


	void Fighting::SwitchDispStrState ()
	{
//		static bool bDisp = F;		//状態
//		static bool pre_bDisp = F;	//前回押しているか
//		static bool is_bDisp = F;	//今回押しているか


//		is_bDisp = ( WND_UTL::AscKey ( '4' ) );
		//Asyncの判定２回目以降
		bool is_bDisp = G_FTG()->GetSysDisp ();


		//今回押した瞬間ならば、1回のみ切替
		if ( ! m_pre_bDispStrState && is_bDisp )	// false -> true
		{
			if ( m_bDispStrState )
			{
				m_strState->SetValid ( F );
				m_bDispStrState = F;
			}
			else
			{
				m_strState->SetValid ( T );
				m_bDispStrState = T;
			}
		}

		m_pre_bDispStrState = is_bDisp;
	}


}	//namespace GAME

