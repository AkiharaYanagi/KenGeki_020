//=================================================================================================
//
//	Fighting ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Fighting.h"
#include "FtgConst.h"	


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	Fighting::Fighting ()
	{
		//------------------------------------------------
		//背景
		m_bg = std::make_shared < BG > ();
		AddpTask ( m_bg );

		//=====================================================
		//キャラ
		m_exeChara1 = std::make_shared < ExeChara > ( PLAYER_ID_1 );
		m_exeChara2 = std::make_shared < ExeChara > ( PLAYER_ID_2 );

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
#define DEMO_ON		0
#if DEMO_ON
		m_demoSkip = F;
#else
		m_demoSkip = T;
#endif // DEMO_ON

		//=====================================================
		//画面共通グラフィック処理
		m_pFtgGrp = std::make_shared < FtgGrp > ();

		//=====================================================
		//ステート名
		m_strState = std::make_shared < GrpStr > ();
		m_strState->SetStr ( U"State" );
		m_strState->SetZ ( Z_MENU );
		m_strState->SetColorF ( s3d::ColorF { 0.0f, 0.0f, 0.5f, 1.f } );
		GRPLST_INSERT ( m_strState );
		AddpTask ( m_strState );
	}

	Fighting::~Fighting ()
	{
	}


	void Fighting::ParamInit ( P_Param pParam )
	{
		m_mutualChara->ParamInit ( pParam );
		m_exeChara1->ParamInit ( pParam );
		m_exeChara2->ParamInit ( pParam );
	}

	void Fighting::Load ()
	{
		m_demoActor->SetwpFighting ( shared_from_this () );
		m_demoActor->SetpFtgGrp ( m_pFtgGrp );
		m_mutualChara->SetpFtgGrp ( m_pFtgGrp );
		m_exeChara1->SetpFtgGrp ( m_pFtgGrp );
		m_exeChara2->SetpFtgGrp ( m_pFtgGrp );


		m_strState->SetSize ( 30 );
		m_strState->SetPos ( VEC2 ( 640 - 120, 160 ) );


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
	}


	void Fighting::Move ()
	{
		//--------------------------
		//キャラ共通一連動作
		m_mutualChara->Conduct ();

		//--------------------------
		//デモ分岐
		m_demoActor->Do ();

		//--------------------------
		//両者処理

#if 0
		//暗転時は通常処理しない
//		if ( m_bg->IsBlackOut () )
		if ( m_pFtgGrp->GetBlackOut () )
		{
			//入力のみ
			m_mutualChara->Conduct_InStop ();
		}
		else
		{
			//暗転以外のとき、通常処理
			m_mutualChara->Conduct ();
		}
#endif // 0

		//--------------------------
		//共通グラフィック処理
		Grp ();

		//--------------------------
		TASK_LST::Move ();
	}

	void Fighting::DemoRestart ()
	{
		TrainingRestart ();
		m_demoActor->StartGreeting ();
	}

	void Fighting::TrainingRestart ()
	{
		G_Ftg::inst()->Init ();
		m_pFtgGrp->Init ();
		m_bg->Init ();
		m_demoActor->StartFighting ();
		m_mutualChara->TrainingInit ();
	}



	//=============================================================
	//	内部関数
	//=============================================================

	//共通グラフィック処理
	void Fighting::Grp ()
	{
#if 0
		//----------------------------------------------------
		//@todo 共通のフラグポインタを MutalChara -> ExeChara まで渡す
	 
		//----------------------------------------------------
		//暗転
		UINT blackOut = m_mutualChara->GetBlackOut ();
		if ( 0 != blackOut )
		{
			m_bg->SetBlackOut ( blackOut );
			m_mutualChara->SetBlackOut ( 0 );
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

		m_pFtgGrp->Move ();

		//----------------------------------------------------
		//背景通常処理
		m_bg->Grp ();


		//共通グラフィックからステートの変更
		if ( m_pFtgGrp->GetWallBreak () )
		{
			m_demoActor->Shift_Main_To_WallBreak ();
		}

		//ステート名
		m_strState->SetStr ( m_demoActor->GetName () );
	}



}	//namespace GAME

